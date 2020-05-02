#ifndef GRAPH_LAB_2_STRESS_TESTS_H
#define GRAPH_LAB_2_STRESS_TESTS_H

void test_dijkstra(ofstream &file, UI vertex_num, UI edges_num, UI iterations){

    UI count_dir = 0;
    UI count_undir = 0;

    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<listS, vecS, directedS,
                no_property, property<edge_weight_t, int> > graph_t;

        typedef graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

        Graph G(vertex_num, "dir");
        G.generate_connected(edges_num, std::pair<int, int>(1, 100));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weights;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weights.push_back(edges_list[i].weight);
        }

        graph_t g(edge_array.begin(), edge_array.end(), weights.begin(), vertex_num);

        for (size_t i = 0; i < vertex_num; ++i) {
            std::vector<int> s_p;
            dijkstra(G, i, s_p);

            std::vector<vertex_descriptor> p(num_vertices(g));
            std::vector<int> d(num_vertices(g));
            vertex_descriptor s = vertex(i, g);

            dijkstra_shortest_paths(g, s,
                                    predecessor_map(
                                            boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                                            distance_map(
                                            boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

            for (size_t j = 0; j < d.size(); ++j) {
                if (d[j] > INF) {
                    ///for the same value of missing path
                    d[j] = d[j] / 2;
                }
            }
            count_dir += (s_p != d);
        }
    }

    file <<"Dijkstra on dir graphs,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_dir << endl;


    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<listS, vecS, undirectedS,
                no_property, property<edge_weight_t, int> > graph_t;

        typedef graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

        Graph G(vertex_num, "undir");
        G.generate_connected(edges_num, std::pair<int, int>(1, 100));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weights;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weights.push_back(edges_list[i].weight);
        }

        graph_t g(edge_array.begin(), edge_array.end(), weights.begin(), vertex_num);

        for (size_t i = 0; i < vertex_num; ++i) {
            std::vector<int> s_p;
            dijkstra(G, i, s_p);

            std::vector<vertex_descriptor> p(num_vertices(g));
            std::vector<int> d(num_vertices(g));
            vertex_descriptor s = vertex(i, g);

            dijkstra_shortest_paths(g, s,
                                    predecessor_map(
                                            boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                                            distance_map(
                                            boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

            for (size_t j = 0; j < d.size(); ++j) {
                if (d[j] > INF) {
                    d[j] = d[j] / 2;
                }
            }
            count_undir = (s_p != d);
        }
    }

    file <<"Dijkstra on undir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_undir << endl;
}

void test_bellman_ford(ofstream &file, UI vertex_num, UI edges_num, UI iterations){

    UI count_dir = 0;
    UI count_undir = 0;

    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<vecS, vecS, directedS, no_property,
                property<edge_weight_t, int, property<edge_weight2_t, int> > > Graph_t;

        Graph G(vertex_num, "dir");
        G.generate_connected(edges_num, std::pair<int, int>(-10, 50));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weight;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weight.push_back(edges_list[i].weight);
        }

        Graph_t g(edge_array.begin(), edge_array.end(), weight.begin(), vertex_num);

        property_map<Graph_t, edge_weight_t>::type w = get(edge_weight, g);

        std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
        distance[0] = 0;
        if (bellman_ford_shortest_paths(g, int(vertex_num),
                                                       weight_map(w)
                                                               .distance_map(&distance[0]))) {
            for (UI i = 0; i < vertex_num; ++i) {

                std::vector<int> s_p;
                bool bell_ford_1 = bellman_ford(G, i, s_p);

                std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
                distance[i] = 0;

                bool bell_ford_2 = bellman_ford_shortest_paths(g, int(vertex_num),
                                                               weight_map(w)
                                                                       .distance_map(&distance[0]));

                for (size_t j = 0; j < distance.size(); ++j) {
                    if (distance[j] > 30000) {
                        ///for the same value of missing path
                        distance[j] = INF;
                    }
                }

                if (bell_ford_1 != bell_ford_2) {
                    count_dir += 1;
                    continue;
                } else {
                    if (bell_ford_1) {
                        count_dir += (s_p != distance);
                        if (s_p != distance) {
                            cout << endl;
                        }
                    }
                }
            }
        }
        else{
            bool flag = 1;
            for (int i = 0; i < vertex_num; ++i) {
                std::vector<int> s_p;
                if (!bellman_ford(G, i, s_p)){
                    flag = 0;
                    break;
                }
            }
            count_dir += flag;
        }
    }

    file <<"Bellman-Ford on dir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_dir << endl;


    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                property<edge_weight_t, int, property<edge_weight2_t, int> > > Graph_t;

        Graph G(vertex_num, "undir");
        G.generate_connected(edges_num, std::pair<int, int>(1, 100));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weight;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weight.push_back(edges_list[i].weight);
        }

        Graph_t g(edge_array.begin(), edge_array.end(), weight.begin(), vertex_num);

        property_map<Graph_t, edge_weight_t>::type w = get(edge_weight, g);

        for (UI i = 0; i < vertex_num; ++i) {

            std::vector<int> s_p;
            bool bell_ford_1 = bellman_ford(G, i, s_p);

            std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
            distance[i] = 0;

            bool bell_ford_2 = bellman_ford_shortest_paths(g, int(vertex_num),
                                                           weight_map(w)
                                                                   .distance_map(&distance[0]));

            for (size_t j = 0; j < distance.size(); ++j) {
                if (distance[j] > 30000) {
                    distance[j] = INF;
                }
            }

            if (bell_ford_1 != bell_ford_2) {
                count_undir += 1;
                continue;
            }
            else {
                if (bell_ford_1) {
                    count_undir += (s_p != distance);
                    if (s_p != distance) {
                        cout << endl;
                    }
                }
            }
        }
    }

    file <<"Bellman-Ford on undir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_undir << endl;
}

void test_johnson(ofstream &file, UI vertex_num, UI edges_num, UI iterations) {

    UI count_dir = 0;
    UI count_undir = 0;

    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<vecS, vecS, directedS, no_property,
                property<edge_weight_t, int, property<edge_weight2_t, int> > > Graph_t;

        Graph G(vertex_num, "dir");
        G.generate_connected(edges_num, std::pair<int, int>(-10, 50));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weight;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weight.push_back(edges_list[i].weight);
        }

        Graph_t g(edge_array.begin(), edge_array.end(), weight.begin(), vertex_num);

        property_map<Graph_t, edge_weight_t>::type w = get(edge_weight, g);

        std::vector<std::vector<int>> s_p;
        bool johns = johnson(G, s_p);

        if (johns) {
            for (UI i = 0; i < vertex_num; ++i) {
                std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
                distance[i] = 0;

                bool bell_ford = bellman_ford_shortest_paths(g, int(vertex_num),
                                                             weight_map(w)
                                                                     .distance_map(&distance[0]));
                for (size_t j = 0; j < distance.size(); ++j) {
                    ///for the same value of missing path
                    if (distance[j] > 30000) {
                        distance[j] = INF;
                    }
                    if (s_p[i][j] > 30000) {
                        s_p[i][j] = INF;
                    }
                }

                if (johns != bell_ford) {
                    count_dir += 1;
                    continue;
                }
                else{
                        count_dir += (s_p[i] != distance);
                }
            }
        }
        else{
            std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
            distance[0] = 0;
            if (bellman_ford_shortest_paths(g, int(vertex_num),
                                                         weight_map(w)
                                                                     .distance_map(&distance[0]))){
                count_dir += 1;
            }
        }
    }

    file <<"Johnson on dir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_dir << endl;


    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                property<edge_weight_t, int, property<edge_weight2_t, int> > > Graph_t;


        Graph G(vertex_num, "undir");
        G.generate_connected(edges_num, std::pair<int, int>(0, 50));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weight;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weight.push_back(edges_list[i].weight);
        }

        Graph_t g(edge_array.begin(), edge_array.end(), weight.begin(), vertex_num);

        property_map<Graph_t, edge_weight_t>::type w = get(edge_weight, g);

        std::vector<std::vector<int>> s_p;
        bool johns = johnson(G, s_p);

        for (UI i = 0; i < vertex_num; ++i) {

            std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
            distance[i] = 0;

            bool bell_ford = bellman_ford_shortest_paths(g, int(vertex_num),
                                                         weight_map(w)
                                                                 .distance_map(&distance[0]));
            for (size_t j = 0; j < distance.size(); ++j) {
                if (distance[j] > 30000) {
                    distance[j] = INF;
                }
            }

            if (johns != bell_ford) {
                count_undir += 1;
                continue;
            }
            else {
                if (bell_ford) {
                    count_undir += (s_p[i] != distance);
                    if (s_p[i] != distance) {
                        cout << endl;
                    }
                }
            }
        }
    }

    file <<"Johnson on undir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_undir << endl;
}


void test_floyd_warshall(ofstream &file, UI vertex_num, UI edges_num, UI iterations) {

    UI count_dir = 0;
    UI count_undir = 0;

    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<vecS, vecS, directedS, no_property,
                property<edge_weight_t, int, property<edge_weight2_t, int> > > Graph_t;

        Graph G(vertex_num, "dir");
        G.generate_connected(edges_num, std::pair<int, int>(-10, 50));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weight;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weight.push_back(edges_list[i].weight);
        }

        Graph_t g(edge_array.begin(), edge_array.end(), weight.begin(), vertex_num);

        property_map<Graph_t, edge_weight_t>::type w = get(edge_weight, g);

        std::vector<std::vector<int>> s_p;
        bool floyd_w = floyd_warshall(G, s_p);

        if (floyd_w) {
            for (UI i = 0; i < vertex_num; ++i) {
                std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
                distance[i] = 0;

                bool bell_ford = bellman_ford_shortest_paths(g, int(vertex_num),
                                                             weight_map(w)
                                                                     .distance_map(&distance[0]));
                for (size_t j = 0; j < distance.size(); ++j) {
                    if (distance[j] > 30000) {
                        ///for the same value of missing path
                        distance[j] = INF;
                    }
                }

                if (floyd_w != bell_ford) {
                    count_dir += 1;
                    continue;
                }
                else{
                    count_dir += (s_p[i] != distance);
                }
            }
        }
        else{
            std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
            distance[0] = 0;
            if (bellman_ford_shortest_paths(g, int(vertex_num),
                                            weight_map(w)
                                                    .distance_map(&distance[0]))){
                count_dir += 1;
            }
        }
    }

    file <<"Floyd-Warshall on dir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_dir << endl;


    for (UI iter = 0; iter < iterations; ++iter) {

        typedef adjacency_list<vecS, vecS, undirectedS, no_property,
                property<edge_weight_t, int, property<edge_weight2_t, int> > > Graph_t;


        Graph G(vertex_num, "undir");
        G.generate_connected(edges_num, std::pair<int, int>(0, 50));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weight;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weight.push_back(edges_list[i].weight);
        }

        Graph_t g(edge_array.begin(), edge_array.end(), weight.begin(), vertex_num);

        property_map<Graph_t, edge_weight_t>::type w = get(edge_weight, g);

        std::vector<std::vector<int>> s_p;
        bool floyd_w = floyd_warshall(G, s_p);

        for (UI i = 0; i < vertex_num; ++i) {

            std::vector<int> distance(vertex_num, (std::numeric_limits<short>::max)());
            distance[i] = 0;

            bool bell_ford = bellman_ford_shortest_paths(g, int(vertex_num),
                                                         weight_map(w)
                                                                 .distance_map(&distance[0]));
            for (size_t j = 0; j < distance.size(); ++j) {
                if (distance[j] > 30000) {
                    distance[j] = INF;
                }
            }

            if (floyd_w != bell_ford) {
                count_undir += 1;
                continue;
            }
            else {
                if (bell_ford) {
                    count_undir += (s_p[i] != distance);
                    if (s_p[i] != distance) {
                        cout << endl;
                    }
                }
            }
        }
    }

    file <<"Floyd_Warshall on undir graphs ,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_undir << endl;

}

void test_seidel(ofstream &file, UI vertex_num, UI edges_num, UI iterations){

    UI count_undir = 0;

    for (UI iter = 0; iter < iterations; ++iter) {
        typedef adjacency_list<listS, vecS, undirectedS,
                no_property, property<edge_weight_t, int> > graph_t;

        typedef graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

        Graph G(vertex_num, "undir");
        G.generate_connected(edges_num, std::pair<int, int>(1, 1));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weights;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weights.push_back(edges_list[i].weight);
        }

        graph_t g(edge_array.begin(), edge_array.end(), weights.begin(), vertex_num);

        Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> s_p;

        seidel(G, s_p);

        for (size_t i = 0; i < vertex_num; ++i) {

            std::vector<vertex_descriptor> p(num_vertices(g));
            std::vector<int> d(num_vertices(g));
            vertex_descriptor s = vertex(i, g);

            dijkstra_shortest_paths(g, s,
                                    predecessor_map(
                                            boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                                            distance_map(
                                            boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));


            for (size_t j = 0; j < d.size(); ++j) {
                count_undir += (s_p(i, j) != d[j]);
            }
        }
    }

    file <<"Seidel on undir unweig graphs,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_undir << endl;
}

void test_a_star(ofstream &file, UI vertex_num, UI edges_num, UI iterations){

    UI count_undir = 0;

    for (UI iter = 0; iter < iterations; ++iter) {
        typedef adjacency_list<listS, vecS, undirectedS,
                no_property, property<edge_weight_t, int> > graph_t;

        typedef graph_traits<graph_t>::vertex_descriptor vertex_descriptor;

        Graph G(vertex_num, "undir");
        G.generate_connected(edges_num, std::pair<int, int>(1, 10));

        std::vector<EDGE> &edges_list = G.get_edges_list();
        std::vector<std::pair<UI, UI>> edge_array;
        std::vector<int> weights;

        for (size_t i = 0; i < edges_list.size(); ++i) {
            edge_array.push_back(std::make_pair(edges_list[i].vertex_a, edges_list[i].vertex_b));
            weights.push_back(edges_list[i].weight);
        }

        graph_t g(edge_array.begin(), edge_array.end(), weights.begin(), vertex_num);

        Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> s_p;

        seidel(G, s_p);

        for (size_t i = 0; i < vertex_num; ++i) {

            std::vector<vertex_descriptor> p(num_vertices(g));
            std::vector<int> d(num_vertices(g));
            vertex_descriptor s = vertex(i, g);

            dijkstra_shortest_paths(g, s,
                                    predecessor_map(
                                            boost::make_iterator_property_map(p.begin(), get(boost::vertex_index, g))).
                                            distance_map(
                                            boost::make_iterator_property_map(d.begin(), get(boost::vertex_index, g))));

            for (size_t j = 0; j < vertex_num; ++j) {
                UI ans = a_star(G, i, j, s_p);
                    count_undir += (ans != d[j]);
            }
        }
    }
    file <<"A star on undir graphs,"<< vertex_num << "," << edges_num << "," << iterations << "," << count_undir << endl;
}


void stress_test() {

    ofstream out_stress("../data/stress_tests.csv");
    out_stress << "Algorithm,NumVert,NumEdges,Iterations,Errors" << endl;

    test_seidel(out_stress, 50, 200, 1000);
    test_a_star(out_stress, 50, 200, 1000);
    test_dijkstra(out_stress, 50, 200, 1000);
    test_bellman_ford(out_stress, 50, 200, 1000);
    test_johnson(out_stress, 50, 200, 1000);
    test_floyd_warshall(out_stress, 50, 200, 1000);

    test_seidel(out_stress, 50, 1000, 1000);
    test_a_star(out_stress, 50, 1000, 1000);
    test_dijkstra(out_stress, 50, 1000, 1000);
    test_bellman_ford(out_stress, 50, 1000, 1000);
    test_johnson(out_stress, 50, 1000, 1000);
    test_floyd_warshall(out_stress, 50, 1000, 1000);

    out_stress.close();
}


#endif //GRAPH_LAB_2_STRESS_TESTS_H
