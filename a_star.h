//
// Created by Anastasiia Kislitsyna on 4/19/20.
//

#ifndef GRAPH_LAB_2_A_STAR_H
#define GRAPH_LAB_2_A_STAR_H



bool a_star_algo(vector<vector<ADJ_VERTEX>>& adj, boost::numeric::ublas::matrix<UI>& h, const UI N, UI start_vert, UI goal_vert) {
    std::vector<UI> U(N, 0);
    std::vector<UI> Q{start_vert};
    std::vector<pair<bool, UI>> Qu(N, make_pair(0, 0));
    std::vector<UI> g(N);
    std::vector<UI> f(N, INF);
    std::vector<UI> parent(N, INF);

    Qu[start_vert] = make_pair(1, Q.size()-1);

    g[start_vert] = 0;
    f[start_vert] = g[start_vert] + h(start_vert, goal_vert);


    while (Q.size()){
        UI current = Q[0];
        for (size_t i = 1; i < Q.size(); ++i){
            if (f[Q[i]] < f[current]){
                current = Q[i];
            }
        }

        if (current == goal_vert) {
            std::vector<UI> path;
            path.push_back(current);
            cout << g[current] << endl;
            while(current != start_vert){
                path.push_back(parent[current]);
                current = parent[current];
            }

            std::copy(path.begin(), path.end(), std::ostream_iterator<UI>(std::cout," "));

            return 1;
        }

        Q.erase (Q.begin() + Qu[current].second);
        Qu[current].first = 0;
        for (size_t i = 0; i < Q.size(); ++i){
            UI ind = Qu[current].second;
            if (Qu[Q[i]].second > ind) {
                Qu[Q[i]].second--;
            }
        }
        U[current] = 1;

//        for (size_t i = 0; i < adj[current].size(); ++i){
//            UI v = adj[current][i].vertex;
//            int tent = g[current] + adj[current][i].weight;
//            if ((U[v]) and (tent >= g[v])){
//                continue;
//            }
//            else{
//                parent[v] = current;
//                g[v] = tent;
//                f[v] = g[v] + h(v, goal_vert);
//
//                if (!Qu[v]) {
//                    Q.push_back(v);
//                    Qu[v] = 1;
//                }
//
//            }
//        }

        for (size_t i = 0; i < adj[current].size(); ++i){

            UI v = adj[current][i].vertex;
            if (U[v]) continue;

            int tent = g[current] + adj[current][i].weight;

//            if ((Qu[v].first) and (tent < g[v])){
//                cout << "here1" << endl;
//                Q.erase (Q.begin() + Qu[v].second);
//                Qu[v].first = 0;
//                continue;
//            }
//
//            if ((U[v]) and (tent < g[v])){
////                cout << "here2" << endl;
////                U[v] = 0;
//                continue;
//            }

            if ((!Qu[v].first) or (tent < g[v])) {

                parent[v] = current;
                g[v] = tent;
                f[v] = g[v] + h(v, goal_vert);

                Q.push_back(v);
                Qu[v] = make_pair(1, Q.size() - 1);
            }


        }

    }

    return 0;

}


void a_star(Graph& G, UI start, UI goal, boost::numeric::ublas::matrix<UI>& h){
    UI N = G.get_graph_size();
    vector<vector<ADJ_VERTEX>> adj = G.get_adj_list();
    a_star_algo(adj, h, N, start, goal);
}

#endif //GRAPH_LAB_2_A_STAR_H
