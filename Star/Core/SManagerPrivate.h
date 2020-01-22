// Copyright (C) 2019-2020 star.engine at outlook dot com
//
// This file is part of StarEngine
//
// StarEngine is free software: you can redistribute it and/or modify
// it under the terms of the GNU Affero General Public License as published
// by the Free Software Foundation, either version 3 of the License, or
// (at your option) any later version.
//
// StarEngine is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU Affero General Public License for more details.
//
// You should have received a copy of the GNU Affero General Public License
// along with StarEngine.  If not, see <https://www.gnu.org/licenses/>.

#pragma once
#include <Star/SLockFree.h>
#include <Star/Core/SResource.h>
#include <Star/Core/SProducer.h>

namespace Star::Core {

class Producer;

class Manager {
    static std::unique_ptr<Manager> sInstance;

    struct LoadResource {
        Resource* mResource = nullptr;
    };
    struct UnloadResource {
        Resource* mResource = nullptr;
    };
    struct ResourceCreated {
        Resource* mResource = nullptr;
        void* mPointer = nullptr;
    };

    using Command = std::variant<
        LoadResource, UnloadResource, ResourceCreated
    >;
public:
    static Manager& instance() noexcept;

    Manager(size_t resourceCount, size_t taskCount)
        : mThreadID(std::this_thread::get_id())
        , mProducers(std::variant_size_v<ResourceType>)
        , mCommands(taskCount * 4)
    {
        mResources.reserve(resourceCount * 2);
        mQueueCurr.reserve(taskCount);
        mQueueNext.reserve(taskCount);
        mQueueCreated.reserve(taskCount);
    }

    void stop() noexcept {
        Expects(std::this_thread::get_id() == mThreadID);
        mStopped = true;
    }

    void registerProducer(const ResourceType& tag, Producer* producer) {
        Expects(std::this_thread::get_id() == mThreadID);
        Expects(producer);
        Expects(tag.index() < mProducers.size());
        Expects(!mProducers[tag.index()]);
        mProducers[tag.index()] = producer;
    }

    const Resource* get(const MetaID& metaID, const ResourceType& tag) const noexcept {
        const std::lock_guard<std::mutex> lock(mResourceMutex);
        auto iter = mResources.find(metaID);
        if (iter == mResources.end()) {
            bool succeeded;
            std::tie(iter, succeeded) = mResources.emplace(metaID, tag);
            Ensures(succeeded);
        } else {
            Expects(iter->mTag == tag);
        }

        return &*iter;
    }

    // functions
    void sync_created(const Resource& resource, void* pointer) noexcept {
        Expects(std::this_thread::get_id() == mThreadID);
        Expects(!mSyncCreated);
        mSyncCreated = ResourceCreated{ const_cast<Resource*>(&resource), pointer };
    }

    void async_created(const Resource& resource, void* pointer) const noexcept {
        Expects(!mStopped);
        mCommands.push(ResourceCreated{ const_cast<Resource*>(&resource), pointer });
    }
private:
    inline Producer* getProducer(const ResourceType& tag) const noexcept {
        Expects(tag.index() < mProducers.size());
        auto ptr = mProducers[tag.index()];
        Expects(ptr);
        return ptr;
    }

    // resource handler
    bool try_send(Resource& resource, bool async) noexcept {
        Expects(std::this_thread::get_id() == mThreadID);
        auto pProducer = getProducer(resource.mTag);
        bool succeeded;
        if (async) { // if async
            succeeded = pProducer->load(resource, async);
            if (succeeded) { // succeeded
                ++mJobCount;
            } else { // producer too busy, delayed to next frame
                mQueueNext.emplace(&resource);
            }
        } else {
            auto prevCount = mJobCount;
            ++mJobCount;
            succeeded = pProducer->load(resource, async);
            Ensures(succeeded);
        }
        return succeeded;
    }

    void enqueue(Resource& resource, bool async) {
        Expects(std::this_thread::get_id() == mThreadID);
        if (async) {
            mQueueCurr.emplace(&resource);
        }
    }

    void dequeue(Resource& resource, bool async) noexcept {
        Expects(std::this_thread::get_id() == mThreadID);
        if (async) {
            mQueueCurr.erase(&resource);
        }
    }

    void finishLoadingSucceeded(Resource& resource) {
        --mJobCount;
        auto pProducer = getProducer(resource.mTag);
        Expects(pProducer);
        pProducer->created(resource);
    }

    void finishLoadingFailed(Resource& resource) noexcept {
        --mJobCount;
        auto pProducer = getProducer(resource.mTag);
        Expects(pProducer);
        pProducer->destroy(resource);
    }

    void destroy(Resource& resource) const noexcept {
        auto pProducer = getProducer(resource.mTag);
        Expects(pProducer);
        pProducer->destroy(resource);
    }

    void loadNow(Resource& resource) noexcept {
        Expects(std::this_thread::get_id() == mThreadID);
        Expects(Resource::nr_regions::value == 1);
        auto prevCount = mJobCount;

        resource.load(false);
        Ensures(resource.current_state()[0] == 1); // Ensures queued

        Expects(!mSyncCreated);
        resource.start(false);
        Ensures(resource.current_state()[0] == 2); // Ensures loading
        Ensures(mSyncCreated);

        mSyncCreated->mResource->created(mSyncCreated->mPointer);
        Ensures(resource.current_state()[0] == 4); // Ensures loaded
        Ensures(prevCount == mJobCount);
        mSyncCreated.reset();
        Ensures(!mSyncCreated);
    }

    void postLoad(Resource& resource) noexcept {
        Expects(!mStopped);
        mCommands.push(LoadResource{ &resource });
    }

    void postUnload(Resource& resource) const noexcept {
        if (mStopped) {
            Expects(std::this_thread::get_id() == mThreadID);
            resource.unload(false);
        } else {
            mCommands.push(UnloadResource{ &resource });
        }
    }

    // async workflow
    void processEvents() {
        Expects(std::this_thread::get_id() == mThreadID);
        mCommands.consume_all([this](const Command& v) {
            handleCommand(v);
        });
    }

    inline void handleCommand(const Command& v) {
        Expects(std::this_thread::get_id() == mThreadID);
        visit(overload(
            [this](const LoadResource& c) {
                c.mResource->load(true);
            },
            [this](const UnloadResource& c) {
                c.mResource->unload(true);
            },
            [this](const ResourceCreated& c) {
                mQueueCreated.emplace_back(c);
            }
        ), v);
    }

    void loadResources() {
        Expects(std::this_thread::get_id() == mThreadID);
        for (auto& pResource : mQueueCurr) {
            pResource->start(true);
        }
        mQueueCurr.clear();
        std::swap(mQueueCurr, mQueueNext);
    }

    void updateResources() {
        Expects(std::this_thread::get_id() == mThreadID);
        for (const auto& c : mQueueCreated) {
            mSyncCreated->mResource->created(mSyncCreated->mPointer);
        }
        mQueueCreated.clear();
    }

    friend class Workflow;
    friend class ControlBlock;
    friend class Resource;

    bool mStopped = false;
    std::thread::id mThreadID = {};
    int64_t mJobCount = 0;
    mutable MessageQueue<Command> mCommands;
    std::vector<Producer*> mProducers;

    mutable std::mutex mResourceMutex;
    mutable MetaIDHashMap<Resource> mResources;

    boost::container::flat_set<Resource*> mQueueCurr;
    boost::container::flat_set<Resource*> mQueueNext;
    std::vector<ResourceCreated> mQueueCreated;
    std::optional<ResourceCreated> mSyncCreated;
};

}
