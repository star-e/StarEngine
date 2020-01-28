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
#include <Star/Graphics/SConfig.h>
#include <Star/SBitwise.h>
#include <Star/SLockFree.h>
#include <Star/SCircularBuffer.h>
#include <Star/SFlatMap.h>

namespace Star {

namespace Graphics {

class DescriptorPool;

class STAR_GRAPHICS_API DescriptorBlock {
public:
    DescriptorBlock() noexcept = default;
    DescriptorBlock(const DescriptorPool& pool, uint32_t begin, uint32_t end) noexcept
        : mBlock(begin, end), mPool(&pool)
    {

    }
    DescriptorBlock(DescriptorBlock&& rhs) noexcept
        : mBlock(std::move(rhs.mBlock))
        , mPool(rhs.mPool)
    {
        rhs.mPool = nullptr;
    }

    DescriptorBlock& operator=(DescriptorBlock&& rhs) noexcept {
        reset();
        mPool = rhs.mPool;
        mBlock = std::move(rhs.mBlock);
        rhs.mPool = nullptr;
        return *this;
    }

    ~DescriptorBlock() noexcept {
        reset();
    }

    inline uint32_t begin() const noexcept {
        return mBlock.first;
    }
    inline uint32_t end() const noexcept {
        return mBlock.second;
    }
    std::pair<uint32_t, uint32_t> get() const noexcept {
        return mBlock;
    }
private:
    void reset() noexcept;
#pragma warning(push)
#pragma warning(disable: 4251)
    std::pair<uint32_t, uint32_t> mBlock;
#pragma warning(pop)
    const DescriptorPool* mPool = nullptr;
};

CHECK_SIZE(DescriptorBlock, 16);

class STAR_GRAPHICS_API DescriptorPool {
    friend class DescriptorBlock;
public:
    typedef std::pmr::polymorphic_allocator<std::byte> allocator_type;
    allocator_type get_allocator() const noexcept {
        return mAllocator.resource();
    }
    DescriptorPool(uint32_t blockSize, uint32_t capacity, const allocator_type& alloc);
    DescriptorPool(const DescriptorPool&) = delete;
    DescriptorPool& operator=(const DescriptorPool&) = delete;
    ~DescriptorPool();

    DescriptorBlock allocateRange() const;

    inline uint32_t getBlockSize() const noexcept {
        return mBlockSize;
    }
    inline uint32_t getBlockCount() const noexcept {
        return mBlockCount;
    }
private:
    void reset(uint32_t offset, uint32_t count);
    void destroyBuffer(const std::pair<uint32_t, uint32_t>& block) const noexcept;

    struct Range {
        uint32_t mBegin;
        uint32_t mEnd;
    };

    const uint32_t mBlockSize = 0;
    uint32_t mBlockStart = 0;
    uint32_t mBlockCount = 0;
#pragma warning(push)
#pragma warning(disable: 4251)
    std::pmr::polymorphic_allocator<Range> mAllocator;
    mutable std::mutex mMutex;
    mutable std::atomic_int32_t mAllocatedCount = 0;
    mutable std::pmr::deque<Range> mFreeBlocks;

    //mutable pmr_lockfree_queue<Range,
    //    boost::lockfree::fixed_sized<true>
    //> mFreeBlocks;
#pragma warning(pop)
};

inline void DescriptorBlock::reset() noexcept {
    if (mPool) {
        mPool->destroyBuffer(mBlock);
        mPool = nullptr;
    }
}

class STAR_GRAPHICS_API PersistentDescriptorBlock {
public:
    struct BinSize {
        uint32_t mValue;
    };

    struct VectorSize {
        uint32_t mValue;
    };

    PersistentDescriptorBlock(DescriptorBlock range, BinSize sz);
    PersistentDescriptorBlock(PersistentDescriptorBlock&& rhs) noexcept;
    PersistentDescriptorBlock& operator=(PersistentDescriptorBlock&&) noexcept;
    ~PersistentDescriptorBlock();

    std::pair<uint32_t, uint32_t> try_allocate(VectorSize sz);

    void bulk_deallocate(uint64_t mask) noexcept;

    bool not_in_use(BinSize sz) const noexcept;

    std::pair<uint32_t, uint32_t> find(uint32_t curr) const noexcept {
        if (curr >= mRange.begin() && curr < mRange.end())
            return mRange.get();
        return std::pair<uint32_t, uint32_t>(0, 0);
    }

    uint32_t begin() const noexcept {
        return mRange.begin();
    }
    uint32_t end() const noexcept {
        return mRange.end();
    }
private:
    void allocate_at(uint32_t index) noexcept {
        Expects(index < 64);
        mMask &= ~(uint64_t(1) << index);
    }

    DescriptorBlock mRange;
    uint64_t mMask = 0;
};

CHECK_SIZE(PersistentDescriptorBlock, 24);

class PersistentDescriptorPool;

class STAR_GRAPHICS_API PersistentDescriptorTable {
    friend class PersistentDescriptorPool;
public:
    typedef std::pmr::polymorphic_allocator<std::byte> allocator_type;
    allocator_type get_allocator() const noexcept {
        return mBlocks.get_allocator().resource();
    }
    PersistentDescriptorTable(uint32_t swapchainCount, uint32_t maxBlockCount,
        PersistentDescriptorBlock::VectorSize blockVectorSize,
        PersistentDescriptorBlock::BinSize blockBinSize, const allocator_type& alloc);

    PersistentDescriptorTable(PersistentDescriptorTable&& rhs, const allocator_type& alloc);
    PersistentDescriptorTable(PersistentDescriptorTable&& rhs);
    PersistentDescriptorTable& operator=(PersistentDescriptorTable&& rhs);
    ~PersistentDescriptorTable();

    std::pair<uint32_t, uint32_t> allocate(const DescriptorPool* pPool);
    void deallocate(uint32_t pos) noexcept;

    void advanceFrame();
private:
    void do_deallocate() noexcept;

    struct FreeMask {
        inline void turn_on(uint32_t index) noexcept {
            Expects(index < 64);
            uint64_t mask = (uint64_t(1) << index);
            Ensures((mMask & mask) == 0);
            mMask |= mask;
        }
        uint64_t mMask;
    };

    PersistentDescriptorBlock::VectorSize mBlockVectorSize;
    PersistentDescriptorBlock::BinSize mBlockBinSize;
    uint32_t mMaxBlockCount = 0;
    uint32_t mCurrentDeallocationList = 0;
#pragma warning(push)
#pragma warning(disable: 4251)
    std::pmr::vector<PersistentDescriptorBlock> mBlocks;
    std::pmr::vector<PmrFlatMap<uint32_t, FreeMask>> mDeallocationList;
#pragma warning(pop)
};

CHECK_SIZE(PersistentDescriptorTable, 80);

class STAR_GRAPHICS_API PersistentDescriptorPool {
public:
    typedef std::pmr::polymorphic_allocator<std::byte> allocator_type;
    allocator_type get_allocator() const noexcept {
        return mTables.get_allocator().resource();
    }

    PersistentDescriptorPool(uint32_t capacity, const DescriptorPool* pPool,
        uint32_t swapchainCount = 3,
        uint32_t blockSize = 64, uint32_t maxVectorSize = 8,
        const allocator_type& alloc = std::pmr::get_default_resource());

    PersistentDescriptorPool(const PersistentDescriptorPool& rhs) = delete;
    PersistentDescriptorPool& operator=(const PersistentDescriptorPool& rhs) = delete;
    ~PersistentDescriptorPool();

    std::pair<uint32_t, uint32_t> allocate(uint32_t count);
    void deallocate(uint32_t pos, uint32_t count) noexcept;
    void advanceFrame();
private:
    uint32_t mCapacity = 0;
    uint32_t mSwapChainCount = 0;
    uint32_t mBlockSize = 0;
    uint32_t mMaxVectorSize = 0;

    const DescriptorPool* mPool = nullptr;
    int64_t mAllocated = 0;
#pragma warning(push)
#pragma warning(disable: 4251)
    std::pmr::vector<PersistentDescriptorTable> mTables;
#pragma warning(pop)
};

CHECK_SIZE(PersistentDescriptorPool, 64);

struct CircularDescriptorBlock {
    CircularDescriptorBlock(DescriptorBlock&& range)
        : mBlock(std::move(range))
        , mCurrent(mBlock.begin())
    {}

    void reset(uint32_t swapchain) noexcept {
        mCurrent = mBlock.begin();
        mCurrentSwapChain = swapchain;
    }

    std::pair<uint32_t, uint32_t> try_allocate(uint32_t count) noexcept {
        Expects(mCurrent <= mBlock.end());
        std::pair<uint32_t, uint32_t> res{};

        if (count <= mBlock.end() - mCurrent) {
            res.first = mCurrent;
            mCurrent += count;
            res.second = mCurrent;
        }

        return res;
    }

    DescriptorBlock mBlock;
    uint32_t mCurrent = 0;
    uint32_t mCurrentSwapChain = 0;
};

class STAR_GRAPHICS_API CircularDescriptorPool {
public:
    typedef std::pmr::polymorphic_allocator<std::byte> allocator_type;
    allocator_type get_allocator() const noexcept {
        return mBuffer.get_allocator().resource();
    }

    CircularDescriptorPool(uint32_t capacity, uint32_t reserve,
        const DescriptorPool* pPool, uint32_t swapChainCount,
        uint32_t blockSize, const allocator_type& alloc);

    CircularDescriptorPool(const CircularDescriptorPool&) = delete;
    CircularDescriptorPool& operator=(const CircularDescriptorPool&) = delete;
    ~CircularDescriptorPool();

    std::pair<uint32_t, uint32_t> allocate(uint32_t count);
    void advanceFrame();
private:
    uint32_t mCapacity = 0;
    uint32_t mSwapChainCount = 0;
    uint32_t mBlockSize = 0;
    uint32_t mCurrentSwapChain = 0;
    const DescriptorPool* mPool = nullptr;
#pragma warning(push)
#pragma warning(disable: 4251)
    pmr_circular_buffer<CircularDescriptorBlock> mBuffer;
    pmr_circular_buffer<CircularDescriptorBlock> mReserved;
#pragma warning(pop)
};

class STAR_GRAPHICS_API MonotonicDescriptorPool {
public:
    typedef std::pmr::polymorphic_allocator<std::byte> allocator_type;
    allocator_type get_allocator() const noexcept {
        return mBlocks.get_allocator().resource();
    }

    MonotonicDescriptorPool(const DescriptorPool* pPool, const allocator_type& alloc);
    MonotonicDescriptorPool(const MonotonicDescriptorPool&) = delete;
    MonotonicDescriptorPool& operator=(const MonotonicDescriptorPool&) = delete;
    ~MonotonicDescriptorPool();

    void clear() noexcept;
    std::pair<uint32_t, uint32_t> allocate(uint32_t count);
private:
    const DescriptorPool* mPool = nullptr;
    uint32_t mCurrent = 0;
#pragma warning(push)
#pragma warning(disable: 4251)
    std::pmr::vector<DescriptorBlock> mBlocks;
#pragma warning(pop)
};

}

}
