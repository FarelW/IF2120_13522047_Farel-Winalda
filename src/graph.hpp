#ifndef GRAPH_HPP
#define GRAPH_HPP

#include <json/json.h>
#include <bits/stdc++.h>

using namespace std;

#define MAX 8
#define MARK 9999

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

void addNation(Graph* graph, string& country, string& name);

bool readNationDataFromJson(const string& filename, Graph& nationGraph);

int findNationIndex(Graph* graph, const string& name);

void dijkstra(Graph* graph, const string& start, const string& end);

void printGraph(Graph* graph);

#endif
