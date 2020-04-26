//
// Created by Anastasiia Kislitsyna on 3/23/20.
//

#ifndef GRAPH_LAB_2_CONNECTED_COMP_H
#define GRAPH_LAB_2_CONNECTED_COMP_H

void dfs_connected ( UI &current,
                     vector<vector<ADJ_VERTEX>> &adj,
                     vector<bool> &used,
                     vector<UI> &comp )
{
    used[current] = 1;
    comp.push_back(current);
    for (UI i = 0; i < adj[current].size(); ++i) {
        UI child = adj[current][i].vertex;
        if (!used[child])
            dfs_connected (child, adj, used, comp);
    }
}

UI connected_comp_num(Graph &G) {    // Return amount of connected components.
    size_t N = G.get_graph_size();
    bool directed = G.get_direct();
    UI comp_amount = 0;
    vector<bool> used(N);
    vector<UI> comp;
    for (UI vertex = 0; vertex < N; ++vertex)
        if (! used[vertex]) {
            ++comp_amount;
            comp.clear();
            dfs_connected (vertex, G.get_adj_list(), used, comp);
        }
    return comp_amount;
}

#endif //GRAPH_LAB_2_CONNECTED_COMP_H
