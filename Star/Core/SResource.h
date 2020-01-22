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
#include <Star/Core/SCoreTypes.h>

namespace Star::Core {

class Manager;
class Producer;

class alignas(16) ControlBlock : public boost::msm::front::state_machine_def<ControlBlock> {
public:
    ControlBlock(const MetaID& metaID, ResourceType tag)
        : mMetaID(metaID)
        , mTag(tag)
    {}

    // Events
    struct EventLoad {
        bool mAsync = false;
    };
    struct EventUnload {
        bool mAsync = false;
    };
    struct EventTryStart {
        bool mAsync = false;
    };
    struct EventCreated {
        void* mPointer = nullptr;
    };

    // config
    typedef int no_message_queue;
    //typedef int no_exception_thrown;

    // states
    struct Unloaded : boost::msm::front::state<> {};
    struct Queued : boost::msm::front::state<> {};
    struct Loading : boost::msm::front::state<> {};
    struct Cancelling : boost::msm::front::state<> {};
    struct Loaded : boost::msm::front::state<> {};

    // guard
    bool try_send(const EventTryStart& e) noexcept;

    // actions
    void unloaded_queued(const EventLoad& e);   
    void loading_loaded(const EventCreated& e);
    void cancelling_unloaded(const EventCreated& e) noexcept;
    void loaded_unloaded(const EventUnload& e) noexcept;
    void queued_unloaded(const EventUnload& e) noexcept;

    typedef Unloaded initial_state;
    typedef ControlBlock t;
    struct transition_table : boost::mpl::vector<
        a_row<  Unloaded    , EventLoad     , Queued    , &t::unloaded_queued                   >,
        a_row<  Queued      , EventUnload   , Unloaded  , &t::queued_unloaded                   >,

        g_row<  Queued      , EventTryStart , Loading                           , &t::try_send  >,

         _row<  Loading     , EventUnload   , Cancelling                                        >,
         _row<  Cancelling  , EventLoad     , Loading                                           >,

        a_row<  Cancelling  , EventCreated  , Unloaded  , &t::cancelling_unloaded               >,
        a_row<  Loading     , EventCreated  , Loaded    , &t::loading_loaded                    >,
        a_row<  Loaded      , EventUnload   , Unloaded  , &t::loaded_unloaded                   >>
    {};

    // exceptions
    template<class FSM, class Event>
    void no_transition(Event const& e, FSM& f, int state) {
        std::string error =  "no transition, state: " + std::to_string(state) +
            ", event: " + typeid(e).name();
        throw std::runtime_error(error);
    }

    const ResourceType mTag;
    mutable std::atomic_int32_t mRefCount = 0;
    mutable std::atomic<void*> mPointer = nullptr;
    const MetaID mMetaID;
};

class Resource : public boost::msm::back::state_machine<ControlBlock> {
public:
    Resource() = default;
    Resource(const MetaID& metaID, ResourceType tag)
        : boost::msm::back::state_machine<ControlBlock>(metaID, tag)
    {}

    const MetaID& metaID() const noexcept {
        return mMetaID;
    }

    bool unused() const noexcept {
        return mRefCount == 0;
    }

    inline void sync_acquire() const noexcept {
        if (atomicAddRef(mRefCount)) {
            const_cast<Resource*>(this)->loadNow();
        } else {
            Expects(mPointer);
        }
    }

    inline void async_acquire() const noexcept {
        if (atomicAddRef(mRefCount)) {
            this->startLoading();
        }
    }

    inline void release() const noexcept {
        if (atomicDecRef(mRefCount)) {
            atomicReleaseFence();
            this->startUnloading();
        }
    }
private:
    friend class Manager;

    void load(bool async) {
        process_event(EventLoad{ async });
    }
    void unload(bool async) noexcept {
        process_event(EventUnload{ async });
    }
    void start(bool async) {
        process_event(EventTryStart{ async });
    }
    void created(void* pointer) {
        process_event(EventCreated{ pointer });
    }
private:
    void loadNow() noexcept;
    void startLoading() const noexcept;
    void startUnloading() const noexcept;
};

CHECK_SIZE(ControlBlock, 32)
//PRINT_SIZE(ControlBlock)

}
