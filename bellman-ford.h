#ifndef GRAPH_LAB_2_BELLMAN_FORD_H
#define GRAPH_LAB_2_BELLMAN_FORD_H

bool bellman_ford_algo(vector<EDGE>& edges_list,
                        const UI& N,
                        const UI& M,
                        UI& start_vert,
                        vector<int>& d,
                        const bool& directed) {

    d = vector<int>(N, INF);
    d[start_vert] = 0;
    vector<int> parent(N, -1);

    int x;
    for (size_t i = 0; i < N; ++i) {
        x = -1;
        for (size_t j = 0; j < M; ++j) {
            if (d[edges_list[j].vertex_a] < INF) {
                if (d[edges_list[j].vertex_b] > d[edges_list[j].vertex_a] + edges_list[j].weight) {
                    d[edges_list[j].vertex_b] = max(-INF, d[edges_list[j].vertex_a] + edges_list[j].weight);
                    parent[edges_list[j].vertex_b] = edges_list[j].vertex_a;
                    x = edges_list[j].vertex_b;
                }
            }
            if (!directed) {
                if (d[edges_list[j].vertex_b] < INF) {
                    if (d[edges_list[j].vertex_a] > d[edges_list[j].vertex_b] + edges_list[j].weight) {
                        d[edges_list[j].vertex_a] = max(-INF, d[edges_list[j].vertex_b] + edges_list[j].weight);
                        parent[edges_list[j].vertex_a] = edges_list[j].vertex_b;
                        x = edges_list[j].vertex_a;
                    }
                }
            }
        }
        if (x == -1) break;
    }

    if (x == -1) {
        return 1;
    }
    else {
//        int y = x;
//        for (int i=0; i<N; ++i)
//            y = parent[y];
//
//        vector<int> path;
//        for (int cur = y; ; cur = parent[cur]) {
//            path.push_back (cur);
//            if (cur == y && path.size() > 1)  break;
//        }
//        reverse (path.begin(), path.end());

//        cout << "Negative cycle: ";
//        for (size_t i = 0; i < path.size(); ++i)
//            cout << path[i] << ' ';
        return 0;
    }
}


bool bellman_ford(Graph& G, UI start_vert, vector<int>& s_paths){

    UI N = G.get_graph_size();
    UI M = G.get_edges_num();
    bool directed = G.get_direct();
    vector<EDGE> edges_list = G.get_edges_list();

    if (bellman_ford_algo(edges_list, N, M, start_vert, s_paths, directed)) {
        return 1;
    }
    else {
        return 0;
    }
}

#endif //GRAPH_LAB_2_BELLMAN_FORD_H
