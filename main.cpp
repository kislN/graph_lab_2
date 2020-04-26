#include <iostream>
#include <utility> // std::pair
#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/array.hpp>
#include "boost/numeric/ublas/matrix.hpp"
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include<boost/range/numeric.hpp>
#include <numeric>
#include "boost/numeric/ublas/vector.hpp"

#include <boost/property_map/property_map.hpp>

#include "Graph.h"
#include "dijkstra.h"
#include "a_star.h"
#include "connected_comp.h"
#include "bellman-ford.h"
#include "floyd–warshall.h"
#include "johnson.h"
#include "seidel.h"

#include "improved_algo.h"


using namespace boost;
using namespace boost::numeric::ublas;





int main() {


    boost::numeric::ublas::matrix<double> a(2,2);
    a(0,0)=1.;
    a(0,1)=2.;
    a(1,0)=3.;
    a(1,1)=4.;

    boost::numeric::ublas::zero_matrix<double> m (3, 3);
    print_matrix("a", a);
    a(0, 0) = 1;
    print_matrix("m", a);


//
//
//    std::cout << std::endl << boost::accumulate(boost::numeric::ublas::matrix_row<matrix<UI> > (a, 1), 0);
//
//    std::cout << "(" << a.size1() << ", " << a.size2() << ")" << endl;
//    print_matrix("a:", a);
//
//    // матрица b - единичная
//    boost::numeric::ublas::matrix<UI> b(2,2);
//    b(0,0)=1.;
//    b(0,1)=0.;
//    b(1,0)=0.;
//    b(1,1)=1.;
//    print_matrix("b:", b);
//
//    // перемножение двух матриц
//    boost::numeric::ublas::matrix<double> c = prod(b, a);
//    print_matrix("c=a*b:", c);


    srand(20);

    UI N = 5;
    Graph Gr(N, "undir");
    Gr.generate_connected(5, std::pair<int, int>(1,5));
//    Gr.add_edge(1, 0, -1);
    UI start_time = clock();
    Gr.print_adj_list();
    Gr.print_adj_matrix();


//
    cout << "Number of connected comps = " << connected_comp_num(Gr) << endl;
//
    std::vector<int> s_p, s_p2;
//
    for (int i=0; i<N; ++i) {
        cout << "Dijkstra - " << dijkstra(Gr, i, s_p) << " | ";
//
        copy(s_p.begin(), s_p.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    cout << endl;

    for (int i=0; i<N; ++i) {
        cout << "Bell-Ford - " << bellman_ford(Gr, i, s_p2) << " | ";

//
        copy(s_p2.begin(), s_p2.end(), ostream_iterator<int>(cout, " "));
        cout << endl;
    }

    cout << "\nfloyd-w" << endl;

    std::vector<std::vector<int>> s_p3;

    floyd_warshall(Gr, s_p3);

    for(size_t i = 0; i < s_p3.size(); ++i){
        copy(s_p3[i].begin(), s_p3[i].end(), ostream_iterator<int>(cout," "));
        cout << endl;
    }


    std::vector<std::vector<int>> s_p4;

    cout << endl << "johns " << endl;
    johnson(Gr, s_p4);

    for(size_t i = 0; i < s_p4.size(); ++i){
        copy(s_p4[i].begin(), s_p4[i].end(), ostream_iterator<int>(cout," "));
        cout << endl;
    }


    cout << endl << "seidel" << endl;

    boost::numeric::ublas::matrix<UI> D;

    seidel(Gr, D);

    print_matrix("D ", D);


    a_star(Gr, 2, 4, D);


//
//    Graph Gr2(4, "dir");
//    Gr2.add_edge(0, 1, -5);
//    Gr2.add_edge(0, 2, 2);
//    Gr2.add_edge(0, 3, 3);
//    Gr2.add_edge(1, 2, 4);
//    Gr2.add_edge(2, 3, 1);
//
//    cout <<" TEST" << endl;
//
//    Gr.print_adj_list();
//
//    cout << "Number of connected comps = " << connected_comp_num(Gr) << endl;
//
////    vector<int> s_p, s_p2;
//
//    cout << "Dijkstra runs - " << dijkstra(Gr2, 0, s_p) << endl;
//
//    copy(s_p.begin(), s_p.end(), ostream_iterator<int>(cout," "));
//    cout << endl;
//
//    cout << "Bellman-Ford runs - " << endl;
//    bellman_ford(Gr2, 0, s_p2);
//
//    copy(s_p2.begin(), s_p2.end(), ostream_iterator<int>(cout," "));
//
//    cout << "\nfloyd-w" << endl;
//
////    vector<vector<int>> s_p3;
//
//    floyd_warshall(Gr2, s_p3);
//
//    for(size_t i = 0; i < s_p3.size(); ++i){
//        copy(s_p3[i].begin(), s_p3[i].end(), ostream_iterator<int>(cout," "));
//        cout << endl;
//    }
//
//
////    vector<vector<int>> s_p4;
//
//    johnson(Gr2, s_p4);
//
//    for(size_t i = 0; i < s_p4.size(); ++i){
//        copy(s_p4[i].begin(), s_p4[i].end(), ostream_iterator<int>(cout," "));
//        cout << endl;
//    }
//
//


}