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

#include "SDescriptorPools.h"

namespace Star {

namespace Graphics {

// DescriptorPool
DescriptorPool::DescriptorPool(
    uint32_t blockSize, uint32_t capacity, const allocator_type& alloc)
    : mBlockSize(blockSize)
    , mBlockCount(gsl::narrow_cast<uint32_t>(boost::alignment::align_up(capacity, blockSize)) / blockSize)
    , mAllocator(alloc.resource())
    , mFreeBlocks(mAllocator)
{
    reset(0, mBlockCount * mBlockSize);
}

DescriptorPool::~DescriptorPool() = default;

DescriptorRange DescriptorPool::allocateRange() const {
    std::lock_guard<std::mutex> guard(mMutex);

    if (mFreeBlocks.empty()) {
        throw std::runtime_error("not enough descriptor block");
    }

    auto range = mFreeBlocks.front();
    mFreeBlocks.pop_front();

    ++mAllocatedCount;
    return DescriptorRange(*this, range.mBegin, range.mEnd);
}

void DescriptorPool::destroyBuffer(const std::pair<uint32_t, uint32_t>& block) const noexcept {
    std::lock_guard<std::mutex> guard(mMutex);
    mFreeBlocks.emplace_back(Range{ block.first, block.second });
    --mAllocatedCount;
}

void DescriptorPool::reset(uint32_t offset, uint32_t descCount) {
    std::lock_guard<std::mutex> guard(mMutex);

    Expects(mBlockSize);
    Expects(boost::alignment::align_up(descCount, mBlockSize) == descCount);

    descCount = gsl::narrow_cast<uint32_t>(
        boost::alignment::align_up(descCount, mBlockSize));

    mBlockStart = offset;
    mBlockCount = descCount / mBlockSize;

    if (mAllocatedCount == 0) {
        while (!mFreeBlocks.empty()) {
            mFreeBlocks.pop_front();
        }
    } else {
        throw std::runtime_error("descriptors still in use");
    }

    uint32_t count = 0;
    for (int i = 0; i != mBlockCount; ++i) {
        auto begin = mBlockStart + count;
        mFreeBlocks.emplace_back(Range{ begin, begin + mBlockSize });
        count += mBlockSize;
    }
    Ensures(count == descCount);
    std::ignore = count;
}

// Persistent
PersistentDescriptorBlock::PersistentDescriptorBlock(DescriptorRange range, BinSize sz)
    : mRange(std::move(range))
    , mMask(set_least_n_bits(sz.mValue))
{

}

PersistentDescriptorBlock::PersistentDescriptorBlock(PersistentDescriptorBlock && rhs) noexcept = default;
PersistentDescriptorBlock& PersistentDescriptorBlock::operator=(PersistentDescriptorBlock&&) noexcept = default;
PersistentDescriptorBlock::~PersistentDescriptorBlock() = default;

std::pair<uint32_t, uint32_t> PersistentDescriptorBlock::try_allocate(VectorSize sz) {
    std::pair<uint32_t, uint32_t> range;
    auto res = find_lsb(mMask);
    if (res.second) {
        allocate_at(res.first);
        range.first = mRange.begin() + sz.mValue * res.first;
        range.second = range.first + sz.mValue;
    }
    return range;
}

void PersistentDescriptorBlock::bulk_deallocate(uint64_t mask) noexcept {
    // pre-condition
#ifndef NDEBUG
    Expects(mask); // must have released something
    auto sz = count_bits(mask);
    Expects(sz);
    auto before = count_bits(mMask);
#endif
    // deallocate
    mMask |= mask;

    // post-condition
#ifndef NDEBUG
    auto after = count_bits(mMask);
    Ensures(before + sz == after); // must correctly released
    std::ignore = before, sz, after;

    //auto res = find_lsb(mMask);
    //Ensures(res.second); // just released, so must have ones
    //Ensures((int)res.first < binSize.mValue); // largest index must less than max count
    //std::ignore = res;
#endif
}

bool PersistentDescriptorBlock::not_in_use(BinSize sz) const noexcept {
    uint64_t mask = set_least_n_bits(sz.mValue);
    if (mask == mMask)
        return true;

    return false;
}

PersistentDescriptorTable::PersistentDescriptorTable(uint32_t swapchainCount, uint32_t maxBlockCount,
    PersistentDescriptorBlock::VectorSize blockVectorSize,
    PersistentDescriptorBlock::BinSize blockBinSize, const allocator_type& alloc)
    : mBlockVectorSize(blockVectorSize)
    , mBlockBinSize(blockBinSize)
    , mMaxBlockCount(maxBlockCount)
    , mCurrentDeallocationList(0)
    , mBlocks(alloc)
    , mDeallocationList(swapchainCount, alloc)
{
    mBlocks.reserve(mMaxBlockCount);

    for (int i = 0; i != mDeallocationList.size(); ++i) {
        mDeallocationList[i].reserve(mMaxBlockCount);
    }
}

PersistentDescriptorTable::PersistentDescriptorTable(PersistentDescriptorTable&& rhs,
    const allocator_type& alloc)
    : mBlockVectorSize(std::move(rhs.mBlockVectorSize))
    , mBlockBinSize(std::move(rhs.mBlockBinSize))
    , mMaxBlockCount(std::move(rhs.mMaxBlockCount))
    , mCurrentDeallocationList(std::move(rhs.mCurrentDeallocationList))
    , mBlocks(std::move(rhs.mBlocks), alloc)
    , mDeallocationList(std::move(rhs.mDeallocationList), alloc)
{
    Expects(false);
}

PersistentDescriptorTable::PersistentDescriptorTable(PersistentDescriptorTable&& rhs) = default;
PersistentDescriptorTable& PersistentDescriptorTable::operator=(PersistentDescriptorTable&& rhs) = default;
PersistentDescriptorTable::~PersistentDescriptorTable() = default;

std::pair<uint32_t, uint32_t> PersistentDescriptorTable::allocate(const DescriptorPool* pPool) {
    std::pair<uint32_t, uint32_t> range;

    for (auto& block : mBlocks) {
        range = block.try_allocate(mBlockVectorSize);
        if (range.first != range.second)
            return range;
    }

    mBlocks.emplace_back(pPool->allocateRange(), mBlockBinSize);
    range = mBlocks.back().try_allocate(mBlockVectorSize);
    Ensures(range.first != range.second);
    return range;
}

void PersistentDescriptorTable::deallocate(uint32_t pos) noexcept {
    for (const auto& block : mBlocks) {
        auto range = block.find(pos);
        if (range.first != range.second) {

            Expects((pos - range.first) % mBlockVectorSize.mValue == 0);
            uint32_t index = (pos - range.first) / mBlockVectorSize.mValue;
            mDeallocationList[mCurrentDeallocationList][range.first].turn_on(index);
            return;
        }
    }
    Ensures(false);
}

void PersistentDescriptorTable::advanceFrame() {
    ++mCurrentDeallocationList;
    mCurrentDeallocationList %= static_cast<uint32_t>(mDeallocationList.size());
    do_deallocate();
}

void PersistentDescriptorTable::do_deallocate() noexcept {
    auto& freeList = mDeallocationList[mCurrentDeallocationList];

    // sweep all blocks
    for (auto& block : mBlocks) {
        auto iter = freeList.find(block.begin());
        if (iter != freeList.end()) {
            Expects(iter->second.mMask);
            Expects(find_msb(iter->second.mMask).first < mBlockBinSize.mValue);
            block.bulk_deallocate(iter->second.mMask);
            freeList.erase(iter);
        }
    }

    Ensures(freeList.empty());
    freeList.clear();

    // return desriptors
    for (int i = 0; i != mBlocks.size();) {
        if (mBlocks[i].not_in_use(mBlockBinSize))
            mBlocks.erase(mBlocks.begin() + i);
        else
            ++i;
    }
}

PersistentDescriptorPool::PersistentDescriptorPool(uint32_t capacity,
    const DescriptorPool* pPool,
    uint32_t swapchainCount, uint32_t blockSize, uint32_t maxVectorSize,
    const allocator_type& alloc)
    : mPool(pPool)
    , mCapacity(gsl::narrow_cast<uint32_t>(boost::alignment::align_up(capacity, blockSize)))
    , mSwapChainCount(swapchainCount)
    , mBlockSize(blockSize)
    , mMaxVectorSize(maxVectorSize)
    , mTables(alloc)
{
    mTables.reserve(maxVectorSize);

    auto maxBlockCount = mCapacity / blockSize;
    for (auto i = 0u; i != maxVectorSize; ++i) {
        PersistentDescriptorBlock::VectorSize vecSize{ i + 1 };
        PersistentDescriptorBlock::BinSize binSize{ 64 / vecSize.mValue };
        mTables.emplace_back(swapchainCount, maxBlockCount, vecSize, binSize);
    }
}

PersistentDescriptorPool::~PersistentDescriptorPool() {
    Ensures(mAllocated == 0);
}

std::pair<uint32_t, uint32_t> PersistentDescriptorPool::allocate(uint32_t count) {
    if (count > mMaxVectorSize || count == 0)
        throw std::runtime_error("exceeds max descriptor vector size range");

    uint32_t slot = count - 1;
    Expects(slot < mTables.size());

    auto range = mTables[slot].allocate(mPool);
    ++mAllocated;
    return range;
}

void PersistentDescriptorPool::deallocate(uint32_t pos, uint32_t count) noexcept {
    if (count > mMaxVectorSize || count == 0)
        return;

    uint32_t slot = count - 1;
    Expects(slot < mTables.size());
    mTables[slot].deallocate(pos);
    --mAllocated;
}

void PersistentDescriptorPool::advanceFrame() {
    for (auto& table : mTables) {
        table.do_deallocate();
    }
}

CircularDescriptorPool::CircularDescriptorPool(uint32_t capacity, uint32_t reserve,
    const DescriptorPool* pPool, uint32_t swapChainCount,
    uint32_t blockSize, const allocator_type& alloc)
    : mPool(pPool)
    , mCapacity(gsl::narrow_cast<uint32_t>(boost::alignment::align_up(capacity, blockSize)))
    , mSwapChainCount(swapChainCount)
    , mBlockSize(blockSize)
    , mBuffer(mCapacity / mBlockSize, alloc)
    , mReserved(mCapacity / mBlockSize, alloc)
{
    reserve = gsl::narrow_cast<uint32_t>(boost::alignment::align_up(reserve, blockSize));
    auto count = reserve / mBlockSize;
    for (int i = 0; i != count; ++i) {
        mReserved.push_back(CircularDescriptorBlock(mPool->allocateRange()));
    }
}

CircularDescriptorPool::~CircularDescriptorPool() = default;

std::pair<uint32_t, uint32_t> CircularDescriptorPool::allocate(uint32_t count) {
    Expects(count <= 64 && count > 0);

    std::pair<uint32_t, uint32_t> range;
    if (!mBuffer.empty() && mBuffer.back().mCurrentSwapChain == mCurrentSwapChain) {
        range = mBuffer.back().try_allocate(count);
        if (range.first != range.second) {
            return range;
        }
    }

    // allocation failed, add more blocks
    if (mReserved.empty()) {
        mReserved.push_back(CircularDescriptorBlock(mPool->allocateRange()));
    }

    mReserved.front().reset(mCurrentSwapChain);
    mBuffer.push_back(std::move(mReserved.front()));
    mReserved.pop_front();

    range = mBuffer.back().try_allocate(count);
    Ensures(range.first != range.second);

    return range;
}

void CircularDescriptorPool::advanceFrame() {
    ++mCurrentSwapChain;
    mCurrentSwapChain %= mSwapChainCount;

    while (!mBuffer.empty()) {
        if (mBuffer.front().mCurrentSwapChain == mCurrentSwapChain) {
            mReserved.push_back(std::move(mBuffer.front()));
            mBuffer.pop_front();
        } else {
            break;
        }
    }

    // validate post-condition
    for (const auto& block : mBuffer) {
        if (block.mCurrentSwapChain == mCurrentSwapChain)
            throw std::runtime_error("circular buffer internal error");
    }
}

MonotonicDescriptorPool::MonotonicDescriptorPool(
    const DescriptorPool* pPool, const allocator_type& alloc)
    : mPool(pPool)
    , mBlocks(alloc)
{
    mBlocks.reserve(mPool->getBlockCount());
}

MonotonicDescriptorPool::~MonotonicDescriptorPool() = default;

void MonotonicDescriptorPool::clear() noexcept {
    mBlocks.clear();
    mCurrent = 0;
}

std::pair<uint32_t, uint32_t> MonotonicDescriptorPool::allocate(uint32_t count) {
    if (mBlocks.empty() || count > mBlocks.back().end() - mCurrent) {
        mBlocks.emplace_back(mPool->allocateRange());
        mCurrent = 0;
    }

    Expects(mCurrent < mBlocks.back().end());
    Expects(count > mBlocks.back().end() - mCurrent);

    std::pair<uint32_t, uint32_t> range;
    range.first = mCurrent;
    mCurrent += count;
    range.second = mCurrent;
     
    return range;
}

}

}
