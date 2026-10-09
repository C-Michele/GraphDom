/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_FRIEND_H
#define GRAPHDOM_VERTEX_HANDLE_FRIEND_H

#include <cstddef>

#include "../graph.h"
#include "vertex_handle.h"
#include "vertex_const_handle.h"
#include "multiset_graph_vertex_handle.h"

template <typename VertexType>
template <typename HashFunctorClass>
class graphdom::graph<VertexType>::vertex_handle_friend {
    public:
        vertex_handle_friend();
        vertex_handle_friend(const vertex_handle_friend& other);
        vertex_handle_friend(vertex_handle_friend&& other);
        vertex_handle_friend(const HashFunctorClass& other);
        vertex_handle_friend(HashFunctorClass&& other);

        std::size_t operator()(const graphdom::graph<VertexType>::vertex_handle& to_hash) const;
        std::size_t operator()(const graphdom::graph<VertexType>::vertex_const_handle& to_hash) const;
        std::size_t operator()(const typename graphdom::multiset_graph<VertexType>::vertex_handle& to_hash) const;
        constexpr const HashFunctorClass& hash_function() const;

        vertex_handle_friend& operator=(const vertex_handle_friend& other);
        vertex_handle_friend& operator=(vertex_handle_friend&& other);
        vertex_handle_friend& operator=(HashFunctorClass& other);
        vertex_handle_friend& operator=(HashFunctorClass&& other);
        constexpr HashFunctorClass& hash_function();
    private:
        HashFunctorClass hash_functor;
};

#include "impl/vertex_handle_friend.h"

#endif //GRAPHDOM_VERTEX_HANDLE_FRIEND_H