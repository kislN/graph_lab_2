#include <iostream>
#include <utility>
#include <fstream>
#include <cmath>
#include <iomanip>
#include <string>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <random>
#include <stdint.h>

#include <boost/graph/graph_traits.hpp>
#include <boost/graph/adjacency_list.hpp>
#include <boost/graph/topological_sort.hpp>
#include <boost/graph/dijkstra_shortest_paths.hpp>
#include <boost/graph/bellman_ford_shortest_paths.hpp>
#include <boost/graph/named_function_params.hpp>
#include <boost/property_map/property_map.hpp>
#include "boost/numeric/ublas/vector.hpp"
#include <boost/array.hpp>
#include <boost/numeric/ublas/matrix_proxy.hpp>
#include <boost/range/numeric.hpp>
#include <boost/config.hpp>

#include <Eigen/Dense>

typedef unsigned int UI;

using namespace std;
using namespace boost;
using namespace Eigen;

const int INF = numeric_limits<int>::max() / 2;


#include "Graph.h"
#include "dijkstra.h"
#include "a_star.h"
#include "connected_comp.h"
#include "bellman-ford.h"
#include "floyd–warshall.h"
#include "johnson.h"
#include "seidel.h"
#include "stress_tests.h"
#include "experiments.h"
#include "real_graph.h"

int main() {

    stress_test();
    all_experiments();
    experiment_with_real();

    return 0;

}