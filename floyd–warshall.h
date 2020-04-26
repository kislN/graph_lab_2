//
// Created by Anastasiia Kislitsyna on 3/24/20.
//

#ifndef GRAPH_LAB_2_FLOYD_WARSHALL_H
#define GRAPH_LAB_2_FLOYD_WARSHALL_H


void floyd_warshall(Graph& G, vector<vector<int>>& s_paths) {
    UI N = G.get_graph_size();
    vector<vector<ADJ_VERTEX>> adj = G.get_adj_list();
    vector<vector<int>> d(N, vector<int>(N, INF));

    for (UI i = 0; i < N; ++i){
        d[i][i] = 0;
    }

    for (UI i = 0; i < N; ++i){
        for (UI j = 0; j < adj[i].size() ;++j){
            d[i][adj[i][j].vertex] = adj[i][j].weight;
        }
    }

    for (int k = 0; k < N; ++k) {
        for (int i = 0; i < N; ++i) {
            for (int j = 0; j < N; ++j) {
                if (d[i][k] < INF && d[k][j] < INF) {
                    d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
                }
            }
        }
    }

    for (int i = 0; i < N; ++i)
        for (int j = 0; j < N; ++j)
            for (int t = 0; t < N; ++t)
                if (d[i][t] < INF && d[t][t] < 0 && d[t][j] < INF)
                    d[i][j] = -INF;


    s_paths = d;
}

#endif //GRAPH_LAB_2_FLOYD_WARSHALL_H
