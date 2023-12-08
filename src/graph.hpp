#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <iostream>
#include <unordered_map>
#include <set>
#include <fstream>
#include <json/json.h>
#include <climits>
#include <iomanip>
#include <algorithm>

using namespace std;

#define MAX 8
#define MARK INT_MAX

struct Nation {
    string country;
    string name;
};

struct Graph {
    struct Nation nations[MAX];
    int distances[MAX][MAX];
    int allies[MAX][MAX];
    int index;
};

int findNationIndex(Graph* graph, const string& name);

bool readNationDataFromJson(const string& filename, Graph& nationGraph);

void dijkstra(Graph* graph, const string& start, const string& end);

void printGraph(Graph* graph);

#endif
