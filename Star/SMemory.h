// Copyright (C) 2019 star.engine@outlook.com
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
#include <memory>

namespace Star {

template<class T>
class polymorphic_delete {
public:
    polymorphic_delete(std::pmr::memory_resource* res = nullptr) noexcept
        : mMemoryResource(res) {}

    template<class T2, std::enable_if_t<std::is_convertible_v<T2*, T*>, int> = 0>
    polymorphic_delete(const polymorphic_delete<T2>& rhs) noexcept
        : mMemoryResource(rhs.mMemoryResource)
    {
        // construct from another polymorphic_delete
    }

    polymorphic_delete(polymorphic_delete&& rhs) noexcept
        : mMemoryResource(std::move(rhs.mMemoryResource))
    {
        rhs.mMemoryResource = nullptr;
    }

    polymorphic_delete& operator=(polymorphic_delete&& rhs) noexcept {
        mMemoryResource = rhs.mMemoryResource;
        rhs.mMemoryResource = nullptr;
        return *this;
    }

    void operator()(T* ptr) const noexcept {
        static_assert(0 < sizeof(T), "can't delete an incomplete type");
        if (ptr) {
            ptr->~T();
            std::pmr::polymorphic_allocator<T> alloc(mMemoryResource);
            std::allocator_traits<std::pmr::polymorphic_allocator<T>>::deallocate(alloc, ptr, 1);
        }
    }

    std::pmr::memory_resource* resource() const noexcept {
        return mMemoryResource;
    }
private:
    std::pmr::memory_resource* mMemoryResource;
};

template<class T>
class polymorphic_delete<T[]> {
public:
    polymorphic_delete(size_t count = 0, std::pmr::memory_resource* res = nullptr) noexcept
        : mMemoryResource(res), mCount(count) {}

    template<class T2, std::enable_if_t<std::is_convertible_v<T2(*)[], T(*)[]>, int> = 0>
    polymorphic_delete(const polymorphic_delete<T2[]>& rhs) noexcept
        : mMemoryResource(rhs.mMemoryResource)
        , mCount(rhs.mCount)
    {
        // construct from another polymorphic_delete
    }

    polymorphic_delete(polymorphic_delete&& rhs) noexcept
        : mMemoryResource(std::move(rhs.mMemoryResource))
        , mCount(std::move(rhs.mCount))
    {
        rhs.mMemoryResource = nullptr;
        rhs.mCount = 0;
    }

    polymorphic_delete& operator=(polymorphic_delete&& rhs) noexcept {
        mMemoryResource = rhs.mMemoryResource;
        mCount = rhs.mCount;
        rhs.mMemoryResource = nullptr;
        rhs.mCount = 0;
        return *this;
    }

    template<class U, std::enable_if_t<std::is_convertible_v<U(*)[], T(*)[]>, int> = 0>
    void operator()(U* ptr) const noexcept {
        static_assert(0 < sizeof(U), "can't delete an incomplete type");
        if (ptr) {
            Expects(mMemoryResource);
            Expects(mCount > 0);
            for (size_t i = 0; i != mCount; ++i) {
                ptr[i].~U();
            }
            std::pmr::polymorphic_allocator<U> alloc(mMemoryResource);
            std::allocator_traits<std::pmr::polymorphic_allocator<U>>::deallocate(alloc, ptr, mCount);
        }
    }

    std::pmr::memory_resource* resource() const noexcept {
        return mMemoryResource;
    }

    size_t size() const noexcept {
        return mCount;
    }
private:
    std::pmr::memory_resource* mMemoryResource;
    size_t mCount;
};

template<class T>
using pmr_unique_ptr = std::unique_ptr<T, Star::polymorphic_delete<T>>;

template<class T, class... Args>
inline pmr_unique_ptr<T> pmr_make_unique(std::pmr::memory_resource* mr, Args&&... args) {
    std::pmr::polymorphic_allocator<T> alloc(mr);
    using traits = std::allocator_traits<std::pmr::polymorphic_allocator<T>>;
    auto hold_deleter = [&alloc](auto p) {
        traits::deallocate(alloc, p, 1);
    };
    using hold_t = std::unique_ptr<T, decltype(hold_deleter)>;
    auto hold = hold_t(traits::allocate(alloc, 1), hold_deleter);
    traits::construct(alloc, hold.get(), std::forward<Args>(args)...);
    auto deleter = polymorphic_delete<T>(mr);
    return pmr_unique_ptr<T>{ hold.release(), std::move(deleter) };
}

inline std::unique_ptr<char[], polymorphic_delete<char[]>>
pmr_allocate_buffer(std::pmr::memory_resource* mr, size_t count) {
    using traits = std::allocator_traits<std::pmr::polymorphic_allocator<char>>;
    std::pmr::polymorphic_allocator<char> alloc(mr);
    auto deleter = polymorphic_delete<char[]>(count, mr);
    return std::unique_ptr<char[], polymorphic_delete<char[]>>{
        traits::allocate(alloc, count), std::move(deleter)
    };
}

}

namespace std {

namespace pmr {

template<class T>
void swap(polymorphic_allocator<T>& lhs, polymorphic_allocator<T>& rhs) noexcept {
    if (lhs != rhs) {
        // swap unequal polymorphic_allocator is undefined behaviour
        std::terminate();
    }
}

}

}
