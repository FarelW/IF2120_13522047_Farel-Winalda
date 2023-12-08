#include <iostream>
#include <fstream>
#include <jsoncpp/json/json.h>
#include <vector>
#include <limits.h>

#define MAX_MARKETS 100

using namespace std;

struct Market {
    char name[50];
};

struct MarketGraph {
    struct Market markets[MAX_MARKETS];
    int numMarkets;
    int distances[MAX_MARKETS][MAX_MARKETS];
};

int findMarketIndex(const MarketGraph* graph, const char* name);

void addMarket(MarketGraph* graph, const char* name);

void addDistance(MarketGraph* graph, const char* name1, const char* name2, int distance);

int findMinDistance(const int* dist, const int* visited, int numMarkets);

void dijkstra(const MarketGraph* graph, const char* start, const char* end);

void printGraph(const MarketGraph* graph);

bool readMarketDataFromJson(const std::string& filename, MarketGraph& marketGraph);