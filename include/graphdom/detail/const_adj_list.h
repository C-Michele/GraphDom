#ifndef GRAPHDOM_CONST_ADJ_LIST_H
#define GRAPHDOM_CONST_ADJ_LIST_H

#include "../graph.h"
#include "vertex_container.h"
#include "base_adj_list.h"
#include "adj_list.h"
#include "../multiset_graph.h"
#include "multiset_graph_adj_list.h"

namespace graphdom {
    template <typename VertexType>
    class graph<VertexType>::const_adj_list : public graph<VertexType>::base_adj_list< const graph<VertexType>::vertex_container* > {
        public:
            const_adj_list() = delete;
            const_adj_list(const const_adj_list& other);
            const_adj_list(const graph<VertexType>::adj_list& other);
            const_adj_list(const typename multiset_graph<VertexType>::adj_list& other);

            ~const_adj_list() = default;

            [[nodiscard]] graph<VertexType>::adj_list_const_iterator begin() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator end() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator cbegin() const;
            [[nodiscard]] graph<VertexType>::adj_list_const_iterator cend() const;

            friend class graph<VertexType>::vertex_handle;
            friend class graph<VertexType>::vertex_const_handle;
            friend class multiset_graph<VertexType>::vertex_handle;
        private:
            const_adj_list(
                const graphdom::graph<VertexType>* adj_list_owner_graph_pointer,
                graphdom::graph<VertexType>::graph_edges_type adj_list_owner_graph_edges_type,
                const graphdom::graph<VertexType>::vertex_container* adj_list_common_begin_point_vertex_container_pointer,
                typename graphdom::graph<VertexType>::edges_type_selection_type adj_list_edges_type_selection = none
            );
    };
}

#include "impl/const_adj_list.h"

#endif //GRAPHDOM_CONST_ADJ_LIST_H