#ifndef GRAPH_LAB_2_A_STAR_H
#define GRAPH_LAB_2_A_STAR_H

UI a_star_algo(vector<vector<ADJ_VERTEX>>& adj,
               Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic>& h,
                const UI& N,
                UI start_vert,
                UI goal_vert)
{
    std::vector<UI> closed(N, 0),
                    opened{start_vert},
                    g(N),
                    f(N, INF),
                    parent(N, INF);
    std::vector<pair<bool, UI>> opened_indexes(N, make_pair(0, 0));

    opened_indexes[start_vert] = make_pair(1, opened.size() - 1);
    g[start_vert] = 0;
    f[start_vert] = g[start_vert] + h(start_vert, goal_vert);

    while (opened.size()){
        UI current = opened[0];
        for (size_t i = 1; i < opened.size(); ++i){
            if (f[opened[i]] < f[current]){
                current = opened[i];
            }
        }

        if (current == goal_vert) {
            std::vector<UI> path;
            path.push_back(current);
            return g[current];
//            while(current != start_vert){
//                path.push_back(parent[current]);
//                current = parent[current];
//            }

        }

        opened.erase (opened.begin() + opened_indexes[current].second);
        opened_indexes[current].first = 0;
        UI ind = opened_indexes[current].second;
        for (size_t i = 0; i < opened.size(); ++i){
            if (opened_indexes[opened[i]].second > ind) {
                opened_indexes[opened[i]].second--;
            }
        }
        closed[current] = 1;

        for (size_t i = 0; i < adj[current].size(); ++i){

            UI v = adj[current][i].vertex;
            if (closed[v]) continue;

            int tent = g[current] + adj[current][i].weight;

            if ((!opened_indexes[v].first) ) {

                parent[v] = current;
                g[v] = tent;
                f[v] = g[v] + h(v, goal_vert);

                opened.push_back(v);
                opened_indexes[v] = make_pair(1, opened.size() - 1);
            }
            else{
                if ( (tent < g[v])){
                    parent[v] = current;
                    g[v] = tent;
                    f[v] = g[v] + h(v, goal_vert);
                }
            }
        }

    }
    return 0;
}


UI a_star(Graph& G, UI start, UI goal, Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic>& h){

    UI N = G.get_graph_size();
    vector<vector<ADJ_VERTEX>> adj = G.get_adj_list();

    UI ans = a_star_algo(adj, h, N, start, goal);
    return ans;

}

#endif //GRAPH_LAB_2_A_STAR_H
