/*
 * Copyright 2026 Michele Comparini
 *
 * SPDX-License-Identifier: Apache-2.0
 */

#ifndef GRAPHDOM_VERTEX_HANDLE_FRIEND_IMPL_H
#define GRAPHDOM_VERTEX_HANDLE_FRIEND_IMPL_H

#include "../vertex_handle_friend.h"

template <typename VertexType>
template <typename HashFunctorClass>
graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::vertex_handle_friend() : hash_functor( HashFunctorClass() ) {}

template <typename VertexType>
template <typename HashFunctorClass>
graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::vertex_handle_friend(const vertex_handle_friend& other) : hash_functor( other.hash_functor ) {}

template <typename VertexType>
template <typename HashFunctorClass>
graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::vertex_handle_friend(vertex_handle_friend&& other) : hash_functor( std::move( other.hash_functor ) ) {}

template <typename VertexType>
template <typename HashFunctorClass>
graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::vertex_handle_friend(const HashFunctorClass& other) : hash_functor( other ) {}

template <typename VertexType>
template <typename HashFunctorClass>
graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::vertex_handle_friend(HashFunctorClass&& other) : hash_functor( std::move( other ) ) {}

template <typename VertexType>
template <typename HashFunctorClass>
std::size_t graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator()(
    const typename graphdom::graph<VertexType>::vertex_handle& to_hash) const {
    return hash_functor( static_cast< const void* >( to_hash.vertex_container_pointer ) );
}

template <typename VertexType>
template <typename HashFunctorClass>
std::size_t graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator()(
    const typename graphdom::graph<VertexType>::vertex_const_handle& to_hash) const {
    return hash_functor( static_cast< const void* >( to_hash.vertex_container_pointer ) );
}

template <typename VertexType>
template <typename HashFunctorClass>
std::size_t graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator()(
    const typename graphdom::multiset_graph<VertexType>::vertex_handle& to_hash) const {
    return hash_functor( static_cast< const void* >( to_hash.vertex_container_pointer ) );
}

template <typename VertexType>
template <typename HashFunctorClass>
typename graphdom::graph<VertexType>::template vertex_handle_friend<HashFunctorClass>& graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator=(
    const vertex_handle_friend& other) {
    if ( this != &other ) {
        hash_functor = other.hash_functor;
    }
    return *this;
}

template <typename VertexType>
template <typename HashFunctorClass>
typename graphdom::graph<VertexType>::template vertex_handle_friend<HashFunctorClass>& graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator=(
    vertex_handle_friend&& other) {
    if ( this != &other ) {
        hash_functor = std::move( other.hash_functor );
    }
    return *this;
}

template <typename VertexType>
template <typename HashFunctorClass>
typename graphdom::graph<VertexType>::template vertex_handle_friend<HashFunctorClass>& graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator=(
    HashFunctorClass& other) {
    if ( &hash_functor != &other.hash_functor ) {
        hash_functor = other.hash_functor;
    }
    return *this;
}

template <typename VertexType>
template <typename HashFunctorClass>
typename graphdom::graph<VertexType>::template vertex_handle_friend<HashFunctorClass>& graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::operator=(
    HashFunctorClass&& other) {
    if ( &hash_functor != &other.hash_functor ) {
        hash_functor = std::move( other.hash_functor );
    }
    return *this;
}

template <typename VertexType>
template <typename HashFunctorClass>
constexpr const HashFunctorClass& graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::hash_function() const {
    return hash_functor;
}

template <typename VertexType>
template <typename HashFunctorClass>
constexpr HashFunctorClass& graphdom::graph<VertexType>::vertex_handle_friend<HashFunctorClass>::hash_function() {
    return hash_functor;
}

#endif //GRAPHDOM_VERTEX_HANDLE_FRIEND_IMPL_H
