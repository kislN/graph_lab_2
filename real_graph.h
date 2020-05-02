#ifndef GRAPH_LAB_2_REAL_GRAPH_H
#define GRAPH_LAB_2_REAL_GRAPH_H

std::vector<string> & split(const string &s, char delim, std::vector<string> &elems) {
    stringstream ss(s);
    string item;
    while(getline(ss, item, delim)) {
        elems.push_back(item);
    }
    return elems;
}

std::vector<string> split(const string &s, char delim) {
    std::vector<string> elems;
    return split(s, delim, elems);
}

void experiment_with_real(ofstream& file, Graph& G){

    UI vertex_num = G.get_graph_size();
    UI edges_num = G.get_edges_num();

    UI  time_dijkstra = 0,
            time_bell_ford = 0,
            time_john = 0,
            time_floyd_w = 0,
            time_seidel = 0,
            time_a_star = 0;

    UI start_vertex = 0;

    UI start_time = clock();
    std::vector<int> s_p1;
    dijkstra(G, start_vertex, s_p1);
    time_dijkstra += (clock() - start_time);

    start_time = clock();
    std::vector<int> s_p2;
    bellman_ford(G, start_vertex, s_p2);
    cout << "bellman-ford" << endl;
    time_bell_ford += (clock() - start_time);

    start_time = clock();
    std::vector<std::vector<int>> s_p3;
    johnson(G, s_p3);
    cout << "johnson" << endl;
    time_john += (clock() - start_time);

    start_time = clock();
    std::vector<std::vector<int>> s_p4;
    floyd_warshall(G, s_p4);
    cout << "floyd" << endl;
    time_floyd_w += (clock() - start_time);

//    start_time = clock();
//    Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> s_p5;
//    seidel(G, s_p5);
//    cout << "seidel" << endl;
//    time_seidel += (clock() - start_time);
//
//    UI goal_vertex = vertex_num - 1;
//
//    start_time = clock();
//    a_star(G, start_vertex, goal_vertex, s_p5);
//    cout << "a_star" << endl;
//    time_a_star += (clock() - start_time);

    file << vertex_num << "," << edges_num << "," << time_dijkstra / 1000000.0 << ","
         << time_bell_ford / 1000000.0 << "," << time_john / 1000000.0 << ","
         << time_floyd_w / 1000000.0 <<endl;

}

bool create_real_graph(string filename, Graph& G) {
    ifstream file(filename);
    if (!file.is_open())
        return 0;

    string line;
    while (getline(file, line)){
        std::vector<string> spl = split(line, ',');
        std::vector<int> new_edge{stoi(spl[0]), stoi(spl[1]), stoi(spl[2])};
        G.add_edge(new_edge[0]-1, new_edge[1]-1, new_edge[2]);
    }

    file.close();
    return 1;
}

bool experiment_with_real(){

    Graph OL_graph(100);
    create_real_graph("../data/Oldenburg.csv", OL_graph);

//    OL_graph.print_adj_matrix();

    ofstream out_OL("../data/OL_graph_experiments.csv");
    if (out_OL.is_open()) cout << "File is open " << endl;

    out_OL << "NumVert,NumEdges,Dijkstra,Bellman-Ford,Jonhson,Floyd-Warshall" << endl;
    experiment_with_real(out_OL, OL_graph);

    out_OL.close();


    Graph CA_graph(2000);
    create_real_graph("../data/California.csv", CA_graph);

    ofstream out_CA("../data/CA_graph_experiments.csv");
    if (out_CA.is_open()) cout << "File is open " << endl;

    out_CA << "NumVert,NumEdges,Dijkstra,Bellman-Ford,Jonhson,Floyd-Warshall" << endl;
    experiment_with_real(out_CA, CA_graph);

    out_CA.close();

}
#endif //GRAPH_LAB_2_REAL_GRAPH_H
