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
#include <Star/Core0/SConfig.h>
#include <boost/container/static_vector.hpp>
#include <boost/functional/hash.hpp>
#include <Star/Graphics/SSemantics.h>
#include <Star/Graphics/SRenderFormatTextureUtils.h>
#include <Star/SAliasCast.h>
#include <boost/iterator/iterator_facade.hpp>

namespace Star {

namespace Graphics {

struct alignas(8) VertexElement {
    int getSize() const noexcept {
        auto [bpe, blockWidth, blockHeight] = getEncoding(mFormat);
        Expects(blockWidth == 1);
        Expects(blockHeight == 1);
        return bpe;
    }
    VertexSemanticEnum  mSemantic;
    uint8_t             mIndex : 4;
    uint8_t             mSlot : 4;
    uint16_t            mAlignedByteOffset;
    Render::Format         mFormat;
};

static_assert(sizeof(VertexElement) == 8);

inline bool operator==(const VertexElement& lhs, const VertexElement& rhs) noexcept {
    return memcmp(&lhs, &rhs, sizeof(VertexElement)) == 0;
}

inline bool operator<(const VertexElement& lhs, const VertexElement& rhs) noexcept {
    return std::tie(lhs.mSlot, lhs.mSemantic, lhs.mIndex, lhs.mAlignedByteOffset, lhs.mFormat)
        < std::tie(rhs.mSlot, rhs.mSemantic, rhs.mIndex, rhs.mAlignedByteOffset, rhs.mFormat);
}

struct VertexLayout {
    typedef boost::container::static_vector<VertexElement, 15> vector_type;

    VertexLayout() = default;
    VertexLayout(std::initializer_list<VertexElement> l)
        : mElements(l) {
    }

    static VertexLayout layout_flat() {
        return VertexLayout{ {
            { POSITION , 0 , 0,  0 , Render::Format::R32G32B32_SFLOAT },
            { NORMAL   , 0 , 0, 12 , Render::Format::R32G32B32_SFLOAT },
            { TEXCOORD , 0 , 0, 24 , Render::Format::R32G32_SFLOAT },
            { UNKNOWN  , 0 , 0, 32 , Render::Format::UNKNOWN }
        } };
    }

    VertexElement* data() noexcept {
        return mElements.data();
    }

    const VertexElement* data() const noexcept {
        return mElements.data();
    }

    // deprecated
    int getVertexSize() const noexcept {
        for (const auto& elem : mElements) {
            if (elem.mSemantic == 0) {
                return elem.mAlignedByteOffset;
            }
        }
        return 0;
    }

    struct ElementRange {
        typedef vector_type vector_type;

        uint32_t vertexSize() const noexcept {
            return mEnd->mAlignedByteOffset;
        }

        VertexElement* mBegin = nullptr;
        VertexElement* mEnd = nullptr;
    };

    struct ConstElementRange {
        ConstElementRange() = default;
        ConstElementRange(const VertexElement* beg, const VertexElement* end)
            : mBegin(beg), mEnd(end)
        {}
        ConstElementRange(const ElementRange& range)
            : mBegin(range.mBegin), mEnd(range.mEnd)
        {}

        uint32_t vertexSize() const noexcept {
            return mEnd->mAlignedByteOffset;
        }

        typedef const vector_type vector_type;
        const VertexElement* mBegin = nullptr;
        const VertexElement* mEnd = nullptr;
    };

    template<class Value>
    class BufferIterator : public boost::iterator_facade<
        BufferIterator<Value>,
        Value,
        boost::forward_traversal_tag,
        Value
    > {
        struct enabler {};
    public:
        typedef typename Value::vector_type vector_type;

        BufferIterator() noexcept = default;
        explicit BufferIterator(vector_type& vec)
            : mVector(&vec)
        {
            if (vec.empty())
                return;

            mBegin = 0;
            mEnd = findEnd(mBegin);
            if (mEnd == mBegin) {
                throw std::invalid_argument("invalid vertex layout");
            }
        }

        template <class OtherValue>
        BufferIterator(
            BufferIterator<OtherValue> const& other
            , typename boost::enable_if<boost::is_convertible<OtherValue, Value>
            , enabler>::type = enabler()
        )
            : mVector(other.mVector)
            , mBegin(other.mBegin)
            , mEnd(other.mEnd)
        {}

    private:
        int findEnd(const int begin) const noexcept {
            Expects(mVector);
            Expects(begin != -1);
            auto& vec = *mVector;
            
            for (int end = begin + 1; end != gsl::narrow_cast<int>(mVector->size()); ++end) {
                Expects(vec[end].mSlot == vec[begin].mSlot);
                if (vec[end].mFormat == Render::Format::UNKNOWN) {
                    return end;
                }
            }
            return begin;
        }
       
        friend class boost::iterator_core_access;

        void increment() {
            auto begin = mEnd + 1;
            Expects(begin <= gsl::narrow_cast<int>(mVector->size()));

            if (begin != gsl::narrow_cast<int>(mVector->size())) {
                auto end = findEnd(begin);
                if (end == begin) {
                    throw std::invalid_argument("invalid vertex layout");
                }
                mBegin = begin;
                mEnd = end;
            } else {
                mBegin = -1;
                mEnd = -1;
            }
        }

        template <class OtherValue>
        bool equal(BufferIterator<OtherValue> const& other) const {
            //Expects(mVector == other.mVector);
            return mBegin == other.mBegin && mEnd == other.mEnd;
        }

        Value dereference() const {
            return Value{ &(*mVector)[mBegin], &(*mVector)[mEnd] };
        }
    private:
        vector_type* mVector = nullptr;
        int mBegin = -1;
        int mEnd = -1;
    };

    typedef BufferIterator<ElementRange> iterator;
    typedef BufferIterator<ConstElementRange> const_iterator;

    iterator begin() {
        return iterator(mElements);
    }
    iterator end() {
        return iterator();
    }

    const_iterator begin() const {
        return const_iterator(mElements);
    }
    const_iterator end() const {
        return const_iterator();
    }

    size_t size2() const noexcept {
        return mElements.size();
    }

    size_t count() const noexcept {
        Expects(mElements.size() != 1);
        return mElements.empty() ? 0 : mElements.size() - 1;
    }

    void clear() noexcept {
        mElements.clear();
    }

    void resize(size_t count) {
        mElements.resize(count);
    }

    bool operator==(const VertexLayout& rhs) const noexcept {
        return mElements == rhs.mElements;
    }

    bool operator<(const VertexLayout& rhs) const noexcept {
        return mElements < rhs.mElements;
    }

    VertexElement& operator[](size_t i) noexcept {
        return mElements[i];
    }

    const VertexElement& operator[](size_t i) const noexcept {
        return mElements[i];
    }

    vector_type mElements;
};

static_assert(sizeof(VertexLayout) == 16 * sizeof(VertexElement));
static_assert(sizeof(VertexLayout) == 128);

}

}

namespace std {

template<class T> struct hash;

template<>
struct hash<Star::Graphics::VertexElement> {
    size_t operator()(const Star::Graphics::VertexElement& desc) const noexcept {
        auto pData = Star::alias_cast<const int64_t*>(&desc);
        static_assert(sizeof(Star::Graphics::VertexElement) / 4 == 2, "size not correct");
        return std::hash<int64_t>()(*pData);
    }
};

template<>
struct hash<Star::Graphics::VertexLayout> {
    size_t operator()(const Star::Graphics::VertexLayout& desc) const noexcept {
        size_t seed = 0;
        for (int i = 0; i != desc.size2(); ++i) {
            boost::hash_combine(seed, desc[i]);
        }
        return seed;
    }
};

}

namespace boost {

template<class T> struct hash;

template<>
struct hash<Star::Graphics::VertexElement> {
    size_t operator()(const Star::Graphics::VertexElement& desc) const noexcept {
        return std::hash<Star::Graphics::VertexElement>()(desc);
    }
};

template<>
struct hash<Star::Graphics::VertexLayout> {
    size_t operator()(const Star::Graphics::VertexLayout& desc) const noexcept {
        return std::hash<Star::Graphics::VertexLayout>()(desc);
    }
};

}
