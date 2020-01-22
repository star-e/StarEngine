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

class Resource;

class STAR_CORE_API FetchBase {
public:
    struct Deleter {
        void operator()(const Resource* ptr) const noexcept;
    };

    FetchBase() noexcept;
    FetchBase(const MetaID& id, const ResourceType& tag, bool async) noexcept;
    FetchBase(FetchBase&& rhs) noexcept;
    FetchBase& operator=(FetchBase&& rhs) noexcept;
    FetchBase(const FetchBase& rhs) noexcept;
    FetchBase& operator=(const FetchBase& rhs) noexcept;
    ~FetchBase() noexcept;

    bool valid() const noexcept {
        return mResource != nullptr;
    }

    bool loading() const noexcept;
    const MetaID& metaID() const noexcept;
protected:
    void resetResource() noexcept;
    void resetResource(const MetaID& id, const ResourceType& tag, bool async) noexcept;
    const void* get() const noexcept;
#pragma warning(push)
#pragma warning(disable: 4251)
    std::unique_ptr<const Resource, Deleter> mResource;
#pragma warning(pop)
};

template<class T>
class Fetch : public FetchBase {
public:
    Fetch() noexcept = default;
    Fetch(const MetaID& id, bool async = true) noexcept
        : FetchBase(id, getTag((const T*)nullptr), async)
    {}

    Fetch(Fetch&& rhs) = default;
    Fetch& operator=(Fetch&& rhs) = default;

    Fetch(const Fetch& rhs) noexcept = default;
    Fetch& operator=(const Fetch& rhs) noexcept = default;

    explicit operator bool() const noexcept {
        return mCached;
    }

    void reset() noexcept {
        mCached = nullptr;
        resetResource();
    }

    void reset(const MetaID& id, bool async = true) noexcept {
        resetResource(id, getTag((const T*)nullptr), async);
        mCached = static_cast<const T*>(get());
    }

    const T* try_get() noexcept {
        if (!mCached) {
            mCached = static_cast<const T*>(get());
        }
        return mCached;
    }

    const T* cache() const noexcept {
        return mCached;
    }
    const T& operator*() const noexcept {
        return *mCached;
    }
    const T* operator->() const noexcept {
        return mCached;
    }
private:
    const T* mCached = nullptr;
};

}
