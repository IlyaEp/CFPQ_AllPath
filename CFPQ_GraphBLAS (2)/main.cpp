#include <iostream>
#include <chrono>
#include <fstream>
#include <fstream>
extern "C" {
#include "GraphBLAS.h"
}
#include <stdio.h>
#include "Grammar.h"
#include "Graph.h"
#include "apmatrix.h"
#include "pathindex.h"
using namespace std;

extern "C" {
Grammar *grammar_new(char *name) {
    return new Grammar(name);
}

void elements_del(char *elements)
{
    free(elements);
}

void grammar_del(Grammar* grammar)
{
    delete grammar;
}

void graphblas_init()
{
    GrB_init(GrB_NONBLOCKING);
    InitGBSemiring();
}

void graphblas_finalize()
{
    GrB_finalize();
}

void intersect(Grammar* grammar, char *argv[])
{
    Graph graph = Graph(argv[0]);
    auto begin = std::chrono::steady_clock::now();
    auto times = grammar->intersection_with_graph(graph);
    auto end = std::chrono::steady_clock::now();
    auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
    grammar->print_results(argv[1], elapsed_ms.count());
}

char* get_elements(Grammar* grammar, char *S)
{
    return grammar->get_elements(S);
}

void getpaths(Grammar* grammar, int i, int j, char *S, int current_len)
{
    std::vector<std::pair<std::string, unsigned int>> res = grammar->get_paths(i, j, S, current_len);
    string name_graphs = "go.txt";
    std::ofstream file;
    file.open("result_matr/paths/result_paht_" + name_graphs, ios_base::app);
    file << res.size() << "\n";
    file.close();
    //for(auto path : res)
    //{
        //cout << path.second << endl << path.first << endl << endl;
    //}
    
}

}

int main(int argc, char *argv[]) {
    //getpaths(argc, argv, 0, 0, 0, 10);
    return 0;
}

