#ifndef GRAPH_LAB_2_JOHNSON_H
#define GRAPH_LAB_2_JOHNSON_H

bool johnson(Graph& G, vector<vector<int>>& s_paths){

    vector<vector<ADJ_VERTEX>> adj = G.get_adj_list();
    vector<EDGE> edges = G.get_edges_list();
    UI N = G.get_graph_size();
    UI M = G.get_edges_num();
    UI dir = G.get_direct();
    vector<vector<int>> d(N, vector<int>(N, INF));
    vector<int> s_path;

    for (size_t i = 0; i < N; ++i){
        d[i][i] = 0;
    }

    adj.push_back(vector<ADJ_VERTEX>());
    for (UI i = 0; i < N; ++i){
        adj[N].push_back(ADJ_VERTEX{i, 0});
        edges.push_back(EDGE{N, i, 0});
    }

    if (bellman_ford_algo(edges, N+1, M+N, N, s_path, dir)){
        for (size_t i = 0; i < N; ++i){
            for (size_t j = 0; j < adj[i].size(); ++j){
                adj[i][j].weight += s_path[i] - s_path[adj[i][j].vertex];
            }
        }
        for (UI i = 0; i < N; ++i){
            vector<int> s_p;
            dijkstra_algo(adj, N, i, s_p);
            for (UI j = 0; j < N; ++j){
                d[i][j] = s_p[j] + s_path[j] - s_path[i];
            }
        }
        s_paths = d;
        return 1;
    }
    else return 0;

}

#endif //GRAPH_LAB_2_JOHNSON_H
