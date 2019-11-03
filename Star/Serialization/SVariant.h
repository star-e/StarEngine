// Copyright (C) 2019 star.engine at outlook dot com
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
#include <Star/SSerializationUtils.h>
#include <variant>

namespace boost {
namespace serialization {

// std::monostate
STAR_CLASS_IMPLEMENTATION(std::monostate, object_serializable);
STAR_CLASS_TRACKING(std::monostate, track_never);
template<class Archive>
void serialize(Archive& ar, std::monostate& v, const uint32_t version) {
    // do nothing
}

// std::variant
// helper
template<size_t N>
struct VariantLoadImpl {
    template<class Archive, class Variant>
    static void load(Archive& ar, Variant& var, size_t index) {
        if (index == N - 1) {
            typedef std::variant_alternative_t<N - 1, Variant> value_type;
            value_type v;
            ar >> v;
            var = std::move(v);
            return;
        }
        VariantLoadImpl<N - 1>::load(ar, var, index);
    }
};

template<>
struct VariantLoadImpl<0> {
    template<class Archive, class Variant>
    static void load(Archive& ar, Variant& var, size_t index) {}
};

// impl
template <class... Types_>
struct implementation_level_impl<const std::variant<Types_...>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level_impl::type::value);
};

template<class... Types_>
struct tracking_level<std::variant<Types_...>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
    /* tracking for a class  */
    BOOST_STATIC_ASSERT((mpl::greater<        
        implementation_level<std::variant<Types_...>>,
        mpl::int_<primitive_type>>::value));
};

template<class Archive, class... Types_>
void save(Archive& ar, const std::variant<Types_...>& v, const uint32_t version) {
    uint32_t id = static_cast<uint32_t>(v.index());
    ar << id;

    visit(Star::overload(
        [&](const auto & c) {
            ar << c;
        }
    ), v);
}

template<class Archive, class... Types_>
void load(Archive& ar, std::variant<Types_...>& v, const uint32_t version) {
    uint32_t id;
    ar >> id;
    VariantLoadImpl<std::variant_size_v<std::variant<Types_...>>>::load(ar, v, size_t(id));
}

template<class Archive, class... Types_>
inline void serialize(Archive& ar, std::variant<Types_...>& t, const uint32_t file_version) {
    split_free(ar, t, file_version);
}

}

}
