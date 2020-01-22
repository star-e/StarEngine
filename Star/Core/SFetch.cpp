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

#include "SFetch.h"
#include "SResource.h"
#include "SManagerPrivate.h"

namespace Star::Core {

void FetchBase::Deleter::operator()(const Resource* ptr) const noexcept {
    if (ptr)
        ptr->release();
}

FetchBase::FetchBase() noexcept = default;

FetchBase::FetchBase(const MetaID& id, const ResourceType& tag, bool async) noexcept
    : mResource(Manager::instance().get(id, tag))
{
    if (async) {
        mResource->async_acquire();
    } else {
        mResource->sync_acquire();
    }
}

FetchBase::FetchBase(FetchBase&& rhs) noexcept = default;
FetchBase& FetchBase::operator=(FetchBase&& rhs) noexcept = default;

FetchBase::FetchBase(const FetchBase& rhs) noexcept
    : mResource(rhs.mResource.get()) 
{
    if (mResource)
        mResource->async_acquire();
}

FetchBase& FetchBase::operator=(const FetchBase& rhs) noexcept {
    mResource.reset(rhs.mResource.get());
    if (mResource)
        mResource->async_acquire();
    return *this;
}

FetchBase::~FetchBase() noexcept = default;

const MetaID& FetchBase::metaID() const noexcept {
    Expects(mResource);
    return mResource->metaID();
}

void FetchBase::resetResource() noexcept {
    mResource.reset();
}

void FetchBase::resetResource(const MetaID& id, const ResourceType& tag, bool async) noexcept {
    mResource.reset(Manager::instance().get(id, tag));
    if (async) {
        mResource->async_acquire();
    } else {
        mResource->sync_acquire();
    }
}

const void* FetchBase::get() const noexcept {
    Expects(mResource);
    return mResource->mPointer;
}

bool FetchBase::loading() const noexcept {
    Expects(mResource);
    return !mResource->mPointer;
}

}
