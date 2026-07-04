#ifndef GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_H
#define GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_H

#include <type_traits>

#include "../graph.h"
#include "vertex_container.h"
#include "edge_endpoint.h"

namespace graphdom {
    template <typename VertexType>
    template <typename VertexContainerPointerType>
    class graph<VertexType>::custom_edge_endpoint_less final {
        public:
            static_assert(
                std::is_same< VertexContainerPointerType , graphdom::graph<VertexType>::vertex_container* >::value ||
                std::is_same< VertexContainerPointerType , const graphdom::graph<VertexType>::vertex_container* >::value
                ,
                "The typename 'VertexContainerPointerType' of 'graphdom::graph<VertexType>::custom_edge_endpoint_less<VertexContainerPointerType>' class must be a pointer to graphdom::graph<VertexType>::vertex_container"
            );

            bool constexpr operator()(
                const edge_endpoint<VertexContainerPointerType>* left,
                const edge_endpoint<VertexContainerPointerType>* right) const;

            using is_transparent = void;

            bool constexpr operator()(
                const edge_endpoint<VertexContainerPointerType>* left,
                const vertex_container* right) const;

            bool constexpr operator()(
                const vertex_container* left,
                const edge_endpoint<VertexContainerPointerType>* right) const;

        private:
            static constexpr std::less<const vertex_container*> less_functor = std::less<const vertex_container*>();
    };
}

#include "impl/custom_edge_endpoint_less.h"

#endif //GRAPHDOM_CUSTOM_EDGE_ENDPOINT_LESS_H