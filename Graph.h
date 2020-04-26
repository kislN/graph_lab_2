//
// Created by Anastasiia Kislitsyna on 3/8/20.
//
#include <iostream>
#include <vector>
#include <fstream>
#include <string>
#include <iomanip>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <ctime>
#include <cstdlib>
#include <map>
#include <set>
#include <random>
#include <stdint.h>

#ifndef GRAPH_LAB_2_GRAPH_H
#define GRAPH_LAB_2_GRAPH_H

typedef unsigned int UI;    // 4 bytes [0; 4 294 967 295]
using namespace std;


UI tolerance = 100000000;

mt19937 gen(time(0));   // Mersenne twister
uniform_int_distribution<> uid(0, tolerance-1);


struct ADJ_VERTEX {
    UI vertex;
    int weight;
};

struct EDGE{
    UI vertex_a;
    UI vertex_b;
    int weight;
};


class Graph {
private:
    UI graph_size;
    UI edges_num;
    float edges_density;
    vector<EDGE> edges_list;
    vector<vector<ADJ_VERTEX>> adj_list;
    bool directed = false;
    boost::numeric::ublas::matrix<UI> adj_matrix;   // we use type UI because of conflict of matrix with different types

public:
    Graph(UI N, string dir = "undir"){
        graph_size = N;
        edges_num = 0;
        edges_density = 0;
        if (dir == "dir"){
            directed = true;
        }
        for (UI i=0; i<graph_size; i++){
            adj_list.push_back(vector<ADJ_VERTEX>{});
        }
        adj_matrix.resize(N, N);
        adj_matrix *= 0;
    }

    void generate_rand(float probability){
        UI prob = probability * tolerance;
        for(UI i=0; i<graph_size; i++){
            for(UI j=i+1; j<graph_size; j++){
//                if (prob > (rand() % tolerance)) {
                if (prob > (uid(gen))){
                    int weight = 1;
                    edges_list.push_back(EDGE{i, j, weight});
                    adj_list[i].push_back(ADJ_VERTEX{j, weight});
                    adj_list[j].push_back(ADJ_VERTEX{i, weight});

                    edges_num++;
                }
            }
        }
        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 2.);
    }

    void generate_connected(UI M, std::pair<int, int> weight_range){
        multimap<UI, EDGE> random_graph;

        for(UI i=0; i<graph_size; i++){
            UI j = 0;
            if (!directed){
                j = i + 1;
            }
            for(j; j<graph_size; j++){
                if (i != j) {
                    random_graph.insert(pair<UI, EDGE>(rand() % tolerance /*uid(gen)*/, EDGE{i, j}));
                }
            }
        }

//        for (auto itr = random_graph.begin(); itr != random_graph.end(); ++itr) {
//            cout << itr->first << "\t" << itr->second.vertex_a << "-" << itr->second.vertex_b << '\n';
//        }

        UI k = M - (graph_size - 1);

        vector<UI> id_trees;
        vector<vector<UI>> trees;

        for (UI i = 0; i < graph_size; ++i){
            id_trees.push_back(i);
            trees.push_back(vector<UI>{i});
        }

        for (auto itr = random_graph.begin(); itr != random_graph.end(); ++itr) {

//            uniform_int_distribution<> uid_w(weight_range.first, weight_range.second);
//            int weight = uid_w(gen);
            int weight = rand() % (weight_range.second - weight_range.first + 1) + weight_range.first;

            if (id_trees[itr->second.vertex_a] != id_trees[itr->second.vertex_b]){

                UI id_a = id_trees[itr->second.vertex_a];
                UI id_b = id_trees[itr->second.vertex_b];

                // merge two trees
                trees[id_a].insert(trees[id_a].end(), trees[id_b].begin(), trees[id_b].end());

                // change id of vertices
                for (UI i = 0; i < trees[id_b].size(); ++i){
                    id_trees[trees[id_b][i]] = id_a;
                }

                edges_list.push_back(EDGE{itr->second.vertex_a, itr->second.vertex_b, weight});
                adj_list[itr->second.vertex_a].push_back(ADJ_VERTEX{itr->second.vertex_b, weight});
                adj_matrix(itr->second.vertex_a, itr->second.vertex_b) = 1;
                if (!directed) {
                    adj_list[itr->second.vertex_b].push_back(ADJ_VERTEX{itr->second.vertex_a, weight});
                    adj_matrix(itr->second.vertex_b, itr->second.vertex_a) = 1;

                }

                edges_num++;
            }
            else{
                if (k > 0) {

                    edges_list.push_back(EDGE{itr->second.vertex_a, itr->second.vertex_b, weight});
                    adj_list[itr->second.vertex_a].push_back(ADJ_VERTEX{itr->second.vertex_b, weight});
                    adj_matrix(itr->second.vertex_a, itr->second.vertex_b) = 1;
                    if(!directed) {
                        adj_list[itr->second.vertex_b].push_back(ADJ_VERTEX{itr->second.vertex_a, weight});
                        adj_matrix(itr->second.vertex_b, itr->second.vertex_a) = 1;

                    }

                    edges_num++;
                    k--;
                }
            }
            if (M == edges_num) break;
        }

        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 1.);
        if(!directed) {
            edges_density *= 2.;
        }



    }


//    void gen_connect_unwei_dir(UI M){
//        srand(7);
//        multimap<UI, EDGE> random_graph;
//
//        for(UI i=0; i<graph_size; i++){
//            for(UI j=0; j<graph_size; j++){
//                if (i != j) {
//                    random_graph.insert(pair<UI, EDGE>(rand() % tolerance /*uid(gen)*/, EDGE{i, j}));
//                }
//            }
//        }
////        for (auto itr = random_graph.begin(); itr != random_graph.end(); ++itr) {
////            cout << itr->first << "\t" << itr->second.vertex_a << "-" << itr->second.vertex_b << '\n';
////        }
//
//        UI k = M - (graph_size - 1);
//
//        vector<UI> id_trees;
//        vector<vector<UI>> trees;
//
//        for (UI i = 0; i < graph_size; ++i){
//            id_trees.push_back(i);
//            trees.push_back(vector<UI>{i});
//        }
//
//
//        for (auto itr = random_graph.begin(); itr != random_graph.end(); ++itr) {
//            if (id_trees[itr->second.vertex_a] != id_trees[itr->second.vertex_b]){
//
//                UI id_a = id_trees[itr->second.vertex_a];
//                UI id_b = id_trees[itr->second.vertex_b];
//
//                // merge two trees
//                trees[id_a].insert(trees[id_a].end(), trees[id_b].begin(), trees[id_b].end());
//
//                // change id of vertices
//                for (UI i = 0; i < trees[id_b].size(); ++i){
//                    id_trees[trees[id_b][i]] = id_a;
//                }
//
//                int weight = 1;
//
//                edges_list.push_back(EDGE{itr->second.vertex_a, itr->second.vertex_b, weight});
//                adj_list[itr->second.vertex_a].push_back(ADJ_VERTEX{itr->second.vertex_b, weight});
////                adj_list[itr->second.vertex_b].push_back(ADJ_VERTEX{itr->second.vertex_a, weight});
//
//                edges_num++;
//            }
//            else{
//                if (k > 0) {
//
//                    int weight = 1;
//
//                    edges_list.push_back(EDGE{itr->second.vertex_a, itr->second.vertex_b, weight});
//                    adj_list[itr->second.vertex_a].push_back(ADJ_VERTEX{itr->second.vertex_b, weight});
////                    adj_list[itr->second.vertex_b].push_back(ADJ_VERTEX{itr->second.vertex_a, weight});
//
//                    edges_num++;
//                    k--;
//                }
//            }
//            if (M == edges_num) break;
//        }
//
//        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 1.);
//        directed = true;
//    }


    bool add_edge(UI a, UI b, int weight=1){
        if((a == b) || (a >= graph_size) || (b >= graph_size)) return 0;
        for (UI i = 0; i < adj_list[a].size(); i++) {
            if (b == adj_list[a][i].vertex) return 0;
        }

        edges_list.push_back(EDGE{a, b, weight});
        adj_list[a].push_back(ADJ_VERTEX{b, weight});
        adj_matrix(a, b) = 1;
        if(!directed) {
            adj_list[b].push_back(ADJ_VERTEX{a, weight});
            adj_matrix(b, a) = 1;
        }
        edges_num++;

        edges_density = edges_num / ((graph_size * (graph_size - 1)) * 1.);

        if(!directed) {
            edges_density *= 2;
        }

        return 1;
    }

//    bool add_dir_edge(UI a, UI b, int weight=1){
//        if((a == b) || (a >= graph_size) || (b >= graph_size)) return 0;
//        for (UI i = 0; i<adj_list[a].size(); i++) {
//            if (b == adj_list[a][i].vertex) return 0;
//        }
//
//        edges_list.push_back(EDGE{a, b, weight});
//        adj_list[a].push_back(ADJ_VERTEX{b, weight});
//        edges_num++;
//        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 2.);
//
//        directed= true;
//        return 1;
//
//    }


//    void delete_edge(UI a, UI b){
//
//        for (UI i=0; i<adj_list[a].size(); i++){
//            if (b == adj_list[a][i]) {
//                adj_list[a].erase(adj_list[a].begin()+i);
//                break;
//            }
//        }
//        for (UI i=0; i<adj_list[b].size(); i++){
//            if (a == adj_list[b][i]) {
//                adj_list[b].erase(adj_list[b].begin() + i);
//                break;
//            }
//        }
//        edges_num--;
//        edges_density = edges_num / ((graph_size * (graph_size - 1)) / 2.);
//    }

    bool get_direct(){
        return directed;
    }

    UI get_edges_num(){
        return edges_num;
    }

    UI get_graph_size(){
        return graph_size;
    }

    float get_edges_dens(){
        return edges_density;
    }

    vector<vector<ADJ_VERTEX>> & get_adj_list(){
        return adj_list;
    }

    boost::numeric::ublas::matrix<UI> & get_adj_matrix(){
        return adj_matrix;
    }

    vector<EDGE> & get_edges_list(){
        return edges_list;
    }

    bool is_empty(){
        for (UI i=0; i<graph_size; i++){
            if (!adj_list[i].empty())
                return 0;
        }
        return 1;
    }

    void print_adj_list(){
        if (this->is_empty())
            cout << "List is empty" << endl;
        else {
            for (UI i = 0; i < graph_size; i++) {
                cout << "vert " << i << ": ";
                for (UI j = 0; j < adj_list[i].size(); j++) {
                    cout << adj_list[i][j].vertex << "(" << adj_list[i][j].weight << ") ";
                }
                cout << endl;
            }
        }
    }

    void print_adj_matrix(){
//        if (this->is_empty())
//            cout << "List is empty" << endl;
//        else {
            for (UI i = 0; i < graph_size; i++) {
                cout << "vert " << i << ": ";
                for (UI j = 0; j < graph_size; j++) {
                    cout << adj_matrix(i, j) << " ";
                }
                cout << endl;
//            }
        }
    }


    void print_edges_list(){
        if (this->is_empty())
            cout << "List is empty" << endl;
        else {
            for (UI i=0; i<edges_num; i++){
                cout << edges_list[i].vertex_a << " - " << edges_list[i].vertex_b << ": " << edges_list[i].weight << endl;
            }
        }
    }

};



#endif //GRAPH_LAB_2_GRAPH_H
