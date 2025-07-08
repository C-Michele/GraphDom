#ifndef GRAPH_H
#define GRAPH_H

/* TODO: once you have chosen the appropriate names, remove the following macros */
#define VERTEX_PTR_NAME vertex_ptr
#define CONSTANT_VERTEX_PTR_NAME const_vertex_ptr
#define EDGE_ITERATOR_NAME edge_iterator
#define CONSTANT_EDGE_ITERATOR_NAME const_edge_iterator

#include <cstdint>
#include <cstddef>

namespace MAIN_LIBRARY_NAMESPACE {
    template <typename VertexType>
    class graph {
        public:
            enum edge_type : std::uint8_t {
                undirected,
                directed
            };

            class VERTEX_PTR_NAME;
            class CONSTANT_VERTEX_PTR_NAME;
            class EDGE_ITERATOR_NAME;
            class CONSTANT_EDGE_ITERATOR_NAME;

            virtual ~graph() = default;

            [[nodiscard]] virtual std::size_t order() const = 0;
            [[nodiscard]] virtual std::size_t size() const = 0;

            //  template <typename... Args >
            //  [[nodiscard]] VERTEX_PTR_NAME emplace_vertex( Args&&... args );
            [[nodiscard]] virtual VERTEX_PTR_NAME insert_vertex(const VertexType&) = 0;
            [[nodiscard]] virtual VERTEX_PTR_NAME insert_vertex(VertexType&&) = 0;
            virtual void erase_vertex(CONSTANT_VERTEX_PTR_NAME&) = 0;
            virtual void insert_edge(const CONSTANT_VERTEX_PTR_NAME&, const CONSTANT_VERTEX_PTR_NAME&, edge_type) = 0;
            [[nodiscard]] virtual EDGE_ITERATOR_NAME erase_edge(CONSTANT_EDGE_ITERATOR_NAME&) = 0;
    };
}

#include "vertex_ptr.h"
#include "const_vertex_ptr.h"
#include "edge_iterator.h"
#include "const_edge_iterator.h"

#endif //GRAPH_H