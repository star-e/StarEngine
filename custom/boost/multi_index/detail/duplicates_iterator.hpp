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

/* Copyright 2003-2018 Joaquin M Lopez Munoz.
 * Distributed under the Boost Software License, Version 1.0.
 * (See accompanying file LICENSE_1_0.txt or copy at
 * http://www.boost.org/LICENSE_1_0.txt)
 *
 * See http://www.boost.org/libs/multi_index for library home page.
 */

#ifndef BOOST_MULTI_INDEX_DETAIL_DUPLICATES_ITERATOR_HPP
#define BOOST_MULTI_INDEX_DETAIL_DUPLICATES_ITERATOR_HPP

#if defined(_MSC_VER)
#pragma once
#endif

#include <boost/config.hpp> /* keep it first to prevent nasty warns in MSVC */
#include <iterator>

namespace boost{

namespace multi_index{

namespace detail{

/* duplicates_operator is given a range of ordered elements and
 * passes only over those which are duplicated.
 */

template<typename Node,typename Predicate>
class duplicates_iterator
{
public:
  typedef typename Node::value_type        value_type;
  typedef typename Node::difference_type   difference_type;
  typedef const typename Node::value_type* pointer;
  typedef const typename Node::value_type& reference;
  typedef std::forward_iterator_tag        iterator_category;

  duplicates_iterator(Node* node_,Node* end_,Predicate pred_):
    node(node_),begin_chunk(0),end(end_),pred(pred_)
  {
    advance();
  }

  duplicates_iterator(Node* end_,Predicate pred_):
    node(end_),begin_chunk(end_),end(end_),pred(pred_)
  {
  }

  reference operator*()const
  {
    return node->value();
  }

  pointer operator->()const
  {
    return &node->value();
  }

  duplicates_iterator& operator++()
  {
    Node::increment(node);
    sync();
    return *this;
  }

  duplicates_iterator operator++(int)
  {
    duplicates_iterator tmp(*this);
    ++(*this);
    return tmp;
  }

  Node* get_node()const{return node;}

private:
  void sync()
  {
    if(node!=end&&pred(begin_chunk->value(),node->value()))advance();
  }

  void advance()
  {
    for(Node* node2=node;node!=end;node=node2){
      Node::increment(node2);
      if(node2!=end&&!pred(node->value(),node2->value()))break;
    }
    begin_chunk=node;
  }

  Node*     node;
  Node*     begin_chunk;
  Node*     end;
  Predicate pred;
};

template<typename Node,typename Predicate>
bool operator==(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return x.get_node()==y.get_node();
}

template<typename Node,typename Predicate>
bool operator!=(
  const duplicates_iterator<Node,Predicate>& x,
  const duplicates_iterator<Node,Predicate>& y)
{
  return !(x==y);
}

} /* namespace multi_index::detail */

} /* namespace multi_index */

} /* namespace boost */

#endif
