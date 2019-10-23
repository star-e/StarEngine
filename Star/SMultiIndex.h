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

namespace Star {

namespace Index {

struct Identity {};
struct Index {};
struct Name {};
struct MetaID {};
struct VariantID {};

}

template<class T>
using NameMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >
    >
>;

template<class T>
using PmrNameMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::pmr::string, &T::mName>,
            std::less<>
        >
    >,
    std::pmr::polymorphic_allocator<T>
>;

template<class T>
using OrderedNameMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >
>;

template<class T>
using PmrOrderedNameMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::pmr::string, &T::mName>,
            std::less<>
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >,
    std::pmr::polymorphic_allocator<T>
>;

template<class T>
using IdentityMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Identity>,
            boost::multi_index::identity<T>
        >
    >
>;

template<class T>
using IdentityNameMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Identity>,
            boost::multi_index::identity<T>
        >
    >
>;

template<class T>
using OrderedIdentityMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Identity>,
            boost::multi_index::identity<T>
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >
>;

template<class T>
using OrderedIdentityNameMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Identity>,
            boost::multi_index::identity<T>
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >
>;

template<class T>
using NameMetaIDHashMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<Index::MetaID>,
            boost::multi_index::const_mem_fun<T, const boost::uuids::uuid&, &T::metaID>
        >,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >
    >
>;

template<class T>
using MetaIDHashMap = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<Index::MetaID>,
            boost::multi_index::const_mem_fun<T, const boost::uuids::uuid&, &T::metaID>
        >
    >
>;

template<class T>
using NameSortedVector = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>,
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >
    >
>;

template<class T>
using NameHashedVector = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>,
        boost::multi_index::hashed_unique<
            boost::multi_index::tag<Index::Name>,
            boost::multi_index::member<T, std::string, &T::mName>,
            std::less<>
        >
    >
>;

struct VariantIndexKey {
    typedef size_t result_type;

    template<class... Args>
    size_t operator()(const std::variant<Args...>& var) const {
        return var.index();
    }
};

template<class... Args>
using OrderedVariantIDMap = boost::multi_index::multi_index_container<std::variant<Args...>,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::VariantID>,
            VariantIndexKey
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >
>;

struct VariantIndexKey2 {
    typedef size_t result_type;

    template<class T>
    size_t operator()(const T& v) const {
        return v.mVariant.index();
    }
};

template<class T>
using OrderedVariantIDMap2 = boost::multi_index::multi_index_container<T,
    boost::multi_index::indexed_by<
        boost::multi_index::ordered_unique<
            boost::multi_index::tag<Index::VariantID>,
            VariantIndexKey2
        >,
        boost::multi_index::random_access<boost::multi_index::tag<Index::Index>>
    >
>;

}
