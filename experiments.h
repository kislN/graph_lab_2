#ifndef GRAPH_LAB_2_EXPERIMENTS_H
#define GRAPH_LAB_2_EXPERIMENTS_H


bool experiment_dijk_bellman_astar_undir(string file_name, UI iterations, UI step, UI average = 3){

    ofstream file(file_name);
    if (!file.is_open()) {
        return 0;
    }
    cout << "File is open " << endl;

    file << "NumVert,NumEdges,Dijkstra,Bellman-Ford,A_star" << endl;

    std::vector<pair<UI, UI>> coef{pair<UI,UI>{1,2}, pair<UI,UI>{1,4},
                                   pair<UI,UI>{1,16}, pair<UI,UI>{2,1}};

    for (auto edge_param : coef) {

        UI vertex_num = 10;

        for (UI iter = 0; iter < iterations; ++iter) {

            UI edges_num = pow(vertex_num / 2, edge_param.first) * edge_param.second;

            UI  time_dijkstra = 0,
                    time_bell_ford = 0,
                    time_a_star = 0;

            for (UI av = 0; av < average; ++av) {

                Graph G(vertex_num, "undir");
                G.generate_connected(edges_num, std::pair<int, int>(0, 100));

                UI start_vertex = 0;

                UI start_time = clock();
                std::vector<int> s_p1;
                dijkstra(G, start_vertex, s_p1);
                time_dijkstra += (clock() - start_time);

                start_time = clock();
                std::vector<int> s_p2;
                bellman_ford(G, start_vertex, s_p2);
                time_bell_ford += (clock() - start_time);

                Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> s_p3;
                seidel(G, s_p3);
                UI goal_vertex = vertex_num - 1;

                start_time = clock();
                a_star(G, start_vertex, goal_vertex, s_p3);
                time_a_star += (clock() - start_time);

            }

            file << vertex_num << "," << edges_num << "," << time_dijkstra / average / 1000000.0 << ","
                 << time_bell_ford / average / 1000000.0 << "," << time_a_star / average / 1000000.0 << endl;

            vertex_num += step;
        }
    }
    file.close();
    return 1;
}

bool experiment_dijk_bellman_dir(string file_name, UI iterations, UI step, UI average = 3){

    ofstream file(file_name);
    if (!file.is_open()) {
        return 0;
    }
    cout << "File is open " << endl;

    file << "NumVert,NumEdges,Dijkstra,Bellman-Ford" << endl;

    std::vector<pair<UI, UI>> coef{pair<UI,UI>{1,2}, pair<UI,UI>{1,4},
                                   pair<UI,UI>{1,16}, pair<UI,UI>{2,1}};

    for (auto edge_param : coef) {

        UI vertex_num = 10;

        for (UI iter = 0; iter < iterations; ++iter) {

            UI edges_num = pow(vertex_num / 2, edge_param.first) * edge_param.second;

            UI  time_dijkstra = 0,
                    time_bell_ford = 0;

            for (UI av = 0; av < average; ++av) {

                Graph G(vertex_num, "dir");
                G.generate_connected(edges_num, std::pair<int, int>(0, 100));

                UI start_vertex = 0;

                UI start_time = clock();
                std::vector<int> s_p1;
                dijkstra(G, start_vertex, s_p1);
                time_dijkstra += (clock() - start_time);

                start_time = clock();
                std::vector<int> s_p2;
                bellman_ford(G, start_vertex, s_p2);
                time_bell_ford += (clock() - start_time);

            }

            file << vertex_num << "," << edges_num << "," << time_dijkstra / average / 1000000.0 << ","
                 << time_bell_ford / average / 1000000.0 << endl;

            vertex_num += step;
        }
    }
    file.close();
    return 1;
}

bool experiment_undir_unweight(string file_name, UI iterations, UI step, UI average = 3){

    ofstream file(file_name);
    if (!file.is_open()) {
        return 0;
    }
    cout << "File is open " << endl;

    file << "NumVert,NumEdges,Johnson,Floyd-Warshall,Seidel" << endl;

    std::vector<pair<UI, UI>> coef{pair<UI,UI>{1,2}, pair<UI,UI>{1,4},
                              pair<UI,UI>{1,16}, pair<UI,UI>{2,1}};

    for (auto edge_param : coef) {

        UI vertex_num = 10;

        for (UI iter = 0; iter < iterations; ++iter) {

            UI edges_num = pow(vertex_num / 2, edge_param.first) * edge_param.second;

            UI  time_john = 0,
                time_floyd_w = 0,
                time_seidel = 0;

            for (UI av = 0; av < average; ++av) {

                Graph G(vertex_num, "undir");
                G.generate_connected(edges_num, std::pair<int, int>(1, 1));

                UI start_time = clock();
                std::vector<std::vector<int>> s_p1;
                johnson(G, s_p1);
                time_john += (clock() - start_time);

                start_time = clock();
                std::vector<std::vector<int>> s_p2;
                bool floyd_w = floyd_warshall(G, s_p2);
                time_floyd_w += (clock() - start_time);

                start_time = clock();
                Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> s_p3;
                seidel(G, s_p3);
                time_seidel += (clock() - start_time);
            }

            file << vertex_num << "," << edges_num << "," << time_john / average / 1000000.0 << ","
                 << time_floyd_w / average / 1000000.0 << "," << time_seidel / average / 1000000.0 << endl;

            vertex_num += step;
        }
    }
    file.close();
    return 1;
}

bool experiment_undir_weight(string file_name, UI iterations, UI step, UI average = 3){

    ofstream file(file_name);
    if (!file.is_open())
        return 0;
    cout << "File is open " << endl;

    file << "NumVert,NumEdges,Johnson,Floyd-Warshall" << endl;

    std::vector<pair<UI, UI>> coef{pair<UI,UI>{1,2}, pair<UI,UI>{1,4},
                              pair<UI,UI>{1,8}, pair<UI,UI>{2,1}};

    for (auto edge_param : coef) {

        UI vertex_num = 10;

        for (UI iter = 0; iter < iterations; ++iter) {

            UI edges_num = pow(vertex_num / 2, edge_param.first) * edge_param.second;

            UI  time_john = 0,
                time_floyd_w = 0;

            for (UI av = 0; av < average; ++av) {

                Graph G(vertex_num, "undir");
                G.generate_connected(edges_num, std::pair<int, int>(0, 100));

                UI start_time = clock();
                std::vector<std::vector<int>> s_p1;
                johnson(G, s_p1);
                time_john += (clock() - start_time);

                start_time = clock();
                std::vector<std::vector<int>> s_p2;
                bool floyd_w = floyd_warshall(G, s_p2);
                time_floyd_w += (clock() - start_time);

            }

            file << vertex_num << "," << edges_num << "," << time_john / average / 1000000.0 << ","
                 << time_floyd_w / average / 1000000.0 << endl;

            vertex_num += step;
        }
    }
    file.close();
    return 1;
}


bool experiment_dir_negative_weight(string file_name, UI iterations, UI step, UI average = 3){

    ofstream file(file_name);
    if (!file.is_open())
        return 0;
    cout << "File is open " << endl;

    file << "NumVert,NumEdges,Johnson,Floyd-Warshall" << endl;

    std::vector<pair<UI, UI>> coef{pair<UI,UI>{1,2}, pair<UI,UI>{1,4},
                              pair<UI,UI>{1,16}, pair<UI,UI>{2,1}};

    for (auto edge_param : coef) {

        UI vertex_num = 10;

        for (UI iter = 0; iter < iterations; ++iter) {

            UI edges_num = pow(vertex_num / 2, edge_param.first) * edge_param.second;

            while(1) {
                UI time_john = 0,
                    time_floyd_w = 0;

                for (UI av = 0; av < average; ++av) {

                    Graph G(vertex_num, "dir");
                    G.generate_connected(edges_num, std::pair<int, int>(-20, 100));

                    UI start_time = clock();
                    std::vector<std::vector<int>> s_p1;
                    bool john = johnson(G, s_p1);
                    time_john += (clock() - start_time);

                    if (!john) continue;

                    start_time = clock();
                    std::vector<std::vector<int>> s_p2;
                    bool floyd_w = floyd_warshall(G, s_p2);
                    time_floyd_w += (clock() - start_time);
                }

                file << vertex_num << "," << edges_num << "," << time_john / average / 1000000.0 << ","
                     << time_floyd_w / average / 1000000.0 << endl;

                break;
            }

            vertex_num += step;
        }
    }
    file.close();
    return 1;
}

void all_experiments() {

    experiment_dijk_bellman_astar_undir("../data/d_b_a_undir.csv", 10, 50, 3);
    experiment_dijk_bellman_dir("../data/d_b_dir.csv", 10, 50, 3);
    experiment_undir_unweight("../data/undir_unweight.csv", 10, 50, 3);
    experiment_undir_weight("../data/undir_weight.csv", 10, 50, 3);
    experiment_dir_negative_weight("../data/dir_negative_weight.csv", 10, 50, 3);

}

#endif //GRAPH_LAB_2_EXPERIMENTS_H
