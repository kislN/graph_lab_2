#ifndef GRAPH_LAB_2_SEIDEL_H
#define GRAPH_LAB_2_SEIDEL_H


Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> seidel_algo(Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> A, const UI N){

    Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic>  Z = A * A,
                                                        D(N, N),
                                                        T(N, N),
                                                        X(N, N),
                                                        B(N, N);
    std::vector<UI> degree(N);

    bool flag = 1;
    for (size_t i = 0; i < N; ++i){
        B(i, i) = 0;
        for (size_t j = i + 1; j < N; ++j){
            if ((A(i, j) == 1) or (Z(i, j) > 0)) {
                B(i, j) = 1;
                B(j, i) = 1;
            }
            else{
                flag = 0;
                B(i, j) = 0;
                B(j, i) = 0;
            }
        }
    }


    if (flag) {
        D = 2 * B - A;
        return D;
    }

    T = seidel_algo(B, N);
    X = T * A;


    for (size_t i = 0; i < N; ++i){
        degree[i] = A.row(i).sum();
    }

    for (size_t i = 0; i < N; ++i){
        for (size_t j = i; j < N; ++j){
            if (X(i, j) >= T(i, j) * degree[j]) {
                D(i, j) = 2 * T(i, j);
                D(j, i) = 2 * T(i, j);
            }
            else{
                D(i, j) = 2 * T(i, j) - 1;
                D(j, i) = 2 * T(i, j) - 1;
            }
        }
    }

    return D;
}


void seidel(Graph& G, Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic>& D){

    Eigen::Matrix<UI, Eigen::Dynamic, Eigen::Dynamic> adj = G.get_adj_matrix();
    UI N = G.get_graph_size();
    D = seidel_algo(adj, N);

}

#endif //GRAPH_LAB_2_SEIDEL_H
