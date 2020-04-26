//
// Created by Anastasiia Kislitsyna on 3/23/20.
//

#ifndef GRAPH_LAB_2_DIJKSTRA_H
#define GRAPH_LAB_2_DIJKSTRA_H

const int INF = numeric_limits<int>::max() / 2;

bool dijkstra_algo(vector<vector<ADJ_VERTEX>>& adj, const UI N, UI start_vert, vector<int>& s_paths){
//    UI N = G.get_graph_size();
//    vector<vector<ADJ_VERTEX>> adj = G.get_adj_list();

    vector<int> d(N, INF),  parent(N);
    d[start_vert] = 0;

    vector<char> mark(N);

    for (UI i = 0; i < N; ++i) {
        int v = -1;
        for (UI j = 0; j < N; ++j)
            if (!mark[j] && (v == -1 || d[j] < d[v]))
                v = j;

        if (d[v] == INF)
            break;

        mark[v] = true;

        for (size_t j = 0; j < adj[v].size(); ++j) {
            UI to = adj[v][j].vertex;
            int len = adj[v][j].weight;
            if (len < 0){
                cout << "Edge " << v << " - " << adj[v][j].vertex << " has negative weight" << endl;
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
