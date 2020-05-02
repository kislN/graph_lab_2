
#ifndef GRAPH_LAB_2_FLOYD_WARSHALL_H
#define GRAPH_LAB_2_FLOYD_WARSHALL_H


bool floyd_warshall(Graph& G, vector<vector<int>>& d) {

    UI N = G.get_graph_size();
    d = G.get_weight_matrix();

    for (size_t k = 0; k < N; ++k) {
        for (size_t i = 0; i < N; ++i) {
            for (size_t j = 0; j < N; ++j) {
                if (d[i][k] < INF && d[k][j] < INF) {
                    if (d[i][k] + d[k][j] < d[i][j]){
                        d[i][j] = d[i][k] + d[k][j];
                    }
                }
            }
        }
    }

    /// for negative cycles
    for (size_t i = 0; i < N; ++i) {
        for (size_t j = 0; j < N; ++j) {
            for (size_t t = 0; t < N; ++t) {
                if (d[i][t] < INF && d[t][t] < 0 && d[t][j] < INF) {
                    d[i][j] = -INF;
                    return 0;
                }
            }
        }
    }

    return 1;
}

#endif //GRAPH_LAB_2_FLOYD_WARSHALL_H
