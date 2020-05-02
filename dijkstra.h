#ifndef GRAPH_LAB_2_DIJKSTRA_H
#define GRAPH_LAB_2_DIJKSTRA_H

bool dijkstra_algo(vector<vector<ADJ_VERTEX>>& adj, const UI& N, UI& start_vert, vector<int>& s_paths){

    vector<int> d(N, INF),  parent(N);
    d[start_vert] = 0;
    vector<char> mark(N);

    for (size_t i = 0; i < N; ++i) {
        int v = -1;
        for (size_t j = 0; j < N; ++j)
            if (!mark[j] && (v == -1 || d[j] < d[v]))
                v = j;

        if (d[v] == INF)
            break;

        mark[v] = true;
        for (size_t j = 0; j < adj[v].size(); ++j) {
            UI to = adj[v][j].vertex;
            int len = adj[v][j].weight;
            if (len < 0){
                return 0;
            }
            if (d[v] + len < d[to]) {
                d[to] = d[v] + len;
                parent[to] = v;
            }
        }
    }
    s_paths = d;
    return 1;
}

bool dijkstra(Graph& G, UI start_vert, vector<int>& s_paths){

    UI N = G.get_graph_size();
    vector<vector<ADJ_VERTEX>> adj = G.get_adj_list();

    if (dijkstra_algo(adj, N, start_vert, s_paths))
        return 1;

    else return 0;
}

#endif //GRAPH_LAB_2_DIJKSTRA_H
