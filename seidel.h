//
// Created by Anastasiia Kislitsyna on 4/18/20.
//

#ifndef GRAPH_LAB_2_SEIDEL_H
#define GRAPH_LAB_2_SEIDEL_H

template <typename T>
void print_matrix(const std::string& sText, boost::numeric::ublas::matrix<T> a)
{
    std::cout <<"Matrix " << sText << std::endl;
    for (size_t i = 0; i < a.size1(); ++i){
        for (size_t j = 0; j < a.size2(); ++j){
            std::cout << a(i, j) << " ";
        }
        std::cout << std::endl;
    }
}


boost::numeric::ublas::matrix<UI> seidel_algo(boost::numeric::ublas::matrix<bool> A, const UI N){

    boost::numeric::ublas::matrix<UI> Z = prod(A, A);
    boost::numeric::ublas::matrix<bool> B(N, N);
    boost::numeric::ublas::matrix<UI> D(N, N);
    boost::numeric::ublas::matrix<UI> T(N, N);
    boost::numeric::ublas::matrix<UI> X(N, N);
    std::vector<int> degree(N);

    bool fl = 1;
    for (size_t i = 0; i < N; ++i){
        B(i, i) = 0;
        for (size_t j = i + 1; j < N; ++j){
            if ((A(i, j) == 1) or (Z(i, j) > 0)) {
                B(i, j) = 1;
                B(j, i) = 1;
            }
            else{
                fl = 0;
                B(i, j) = 0;
                B(j, i) = 0;
            }
        }
    }

    if (fl) {
        D = 2 * B - A;
        return D;
    }


    T = seidel_algo(B, N);
    X = prod(T, A);

    for (size_t i = 0; i < N; ++i){
        degree[i] = boost::accumulate(boost::numeric::ublas::matrix_row<boost::numeric::ublas::matrix<bool> > (A, i), 0);
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


void seidel(Graph& G, boost::numeric::ublas::matrix<UI>& D){
    boost::numeric::ublas::matrix<bool> adj = G.get_adj_matrix();
    UI N = G.get_graph_size();
    D = seidel_algo(adj, N);
}

#endif //GRAPH_LAB_2_SEIDEL_H
