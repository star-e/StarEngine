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

// Copyright (C) 2015-2018 Zhou Zhenglong <zlzhou.sh@outlook.com>
// Distributed under the Boost Software License, Version 1.0.
//    (See accompanying file LICENSE_1_0.txt or copy at
//          http://www.boost.org/LICENSE_1_0.txt)

#pragma once
#include <Star/SMathFwd.h>
#include <boost/serialization/serialization.hpp>
#include <boost/serialization/level.hpp>
#include <boost/serialization/tracking.hpp>
#include <boost/serialization/split_free.hpp>
#include <boost/serialization/array.hpp>

namespace boost {

namespace serialization {

template <typename Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
struct implementation_level_impl<
    const Eigen::Matrix<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>>
{
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<object_serializable> type;
    BOOST_STATIC_CONSTANT(int, value = implementation_level_impl::type::value);
};

template<typename Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
struct tracking_level<Eigen::Matrix<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>> {
    typedef mpl::integral_c_tag tag;
    typedef mpl::int_<track_never> type;
    BOOST_STATIC_CONSTANT(int, value = tracking_level::type::value);
    /* tracking for a class  */
    BOOST_STATIC_ASSERT((mpl::greater<        
        implementation_level<Eigen::Matrix<Scalar, _Rows, _Cols, _Options, _MaxRows, _MaxCols>>,
        mpl::int_<primitive_type>>::value));
};

// dynamic
template<class Archive, typename Scalar, int _Options, int _MaxRows, int _MaxCols>
void save(Archive & ar, const Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    int rows = v.rows();
    int cols = v.cols();

    ar << rows;
    ar << cols;
    ar << boost::serialization::make_array(v.data(), rows * cols);
}

template<class Archive, typename Scalar, int _Options, int _MaxRows, int _MaxCols>
void load(Archive & ar, Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    int rows, cols;
    ar >> rows >> cols;
    v.resize(rows, cols);
    ar >> boost::serialization::make_array(v.data(), rows * cols);
}

template<class Archive, typename Scalar, int _Options, int _MaxRows, int _MaxCols>
void serialize(Archive & ar,  Eigen::Matrix<Scalar, Eigen::Dynamic, Eigen::Dynamic,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    split_free(ar, v, version);
}

// fixed _Cols
template<class Archive, typename Scalar, int _Cols, int _Options, int _MaxRows, int _MaxCols>
void save(Archive & ar, const Eigen::Matrix<Scalar, Eigen::Dynamic, _Cols,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    int rows = v.rows();
    ar << rows;
    ar << boost::serialization::make_array(v.data(), rows * _Cols);
}


template<class Archive, typename Scalar, int _Cols, int _Options, int _MaxRows, int _MaxCols>
void load(Archive & ar, Eigen::Matrix<Scalar, Eigen::Dynamic, _Cols,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    int rows;
    ar >> rows;
    v.resize(rows, _Cols);
    ar >> boost::serialization::make_array(v.data(), rows * _Cols);
}

template<class Archive, typename Scalar, int _Cols, int _Options, int _MaxRows, int _MaxCols>
void serialize(Archive & ar, Eigen::Matrix<Scalar, Eigen::Dynamic, _Cols,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    split_free(ar, v, version);
}

// fixed _Rows
template<class Archive, typename Scalar, int _Rows, int _Options, int _MaxRows, int _MaxCols>
void save(Archive & ar, const Eigen::Matrix<Scalar, _Rows, Eigen::Dynamic,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    int cols = v.cols();
    ar << cols;
    ar << boost::serialization::make_array(v.data(), _Rows * cols);
}

template<class Archive, typename Scalar, int _Rows, int _Options, int _MaxRows, int _MaxCols>
void load(Archive & ar, Eigen::Matrix<Scalar, _Rows, Eigen::Dynamic,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    int cols;
    ar >> cols;
    v.resize(_Rows, cols);
    ar >> boost::serialization::make_array(v.data(), _Rows * cols);
}

template<class Archive, typename Scalar, int _Rows, int _Options, int _MaxRows, int _MaxCols>
void serialize(Archive & ar, Eigen::Matrix<Scalar, _Rows, Eigen::Dynamic,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    split_free(ar, v, version);
}

// fixed size Matrix
template<class Archive, typename Scalar, int _Rows, int _Cols, int _Options, int _MaxRows, int _MaxCols>
void serialize(Archive & ar, Eigen::Matrix<Scalar, _Rows, _Cols,
    _Options, _MaxRows, _MaxCols>& v, const unsigned int version)
{
    ar & boost::serialization::make_array(v.data(), _Rows * _Cols);
}

}

}
