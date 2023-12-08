#include "graph.hpp"


int findMarketIndex(const MarketGraph* graph, const char* name) {
    for (int i = 0; i < graph->numMarkets; ++i) {
        if (strcmp(graph->markets[i].name, name) == 0) {
            return i;
        }
    }
    return -1;
}

void addMarket(MarketGraph* graph, const char* name) {
    if (graph->numMarkets < MAX_MARKETS) {
        strcpy(graph->markets[graph->numMarkets].name, name);
        ++graph->numMarkets;
    } else {
        printf("Max limit of markets reached.\n");
    }
}

void addDistance(MarketGraph* graph, const char* name1, const char* name2, int distance) {
    int index1 = findMarketIndex(graph, name1);
    int index2 = findMarketIndex(graph, name2);

    if (index1 != -1 && index2 != -1) {
        graph->distances[index1][index2] = distance;
        graph->distances[index2][index1] = distance;
    } else {
        printf("Invalid market names for distance calculation.\n");
    }
}

int findMinDistance(const int* dist, const int* visited, int numMarkets) {
    int minIndex = -1;
    int minDist = INT_MAX;

    for (int i = 0; i < numMarkets; ++i) {
        if (!visited[i] && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }

    return minIndex;
}

void dijkstra(const MarketGraph* graph, const char* start, const char* end) {
    int startIdx = findMarketIndex(graph, start);
    int endIdx = findMarketIndex(graph, end);

    if (startIdx == -1 || endIdx == -1) {
        cout << "Invalid market names for Dijkstra's algorithm." << endl;
        return;
    }

    int dist[MAX_MARKETS];
    int visited[MAX_MARKETS];
    int previous[MAX_MARKETS];

    for (int i = 0; i < graph->numMarkets; ++i) {
        dist[i] = INT_MAX;
        visited[i] = 0;
        previous[i] = -1;
    }

    dist[startIdx] = 0;

    for (int count = 0; count < graph->numMarkets; ++count) {
        int u = findMinDistance(dist, visited, graph->numMarkets);
        visited[u] = 1;

        for (int v = 0; v < graph->numMarkets; ++v) {
            if (!visited[v] && graph->distances[u][v] && dist[u] != INT_MAX
                && dist[u] + graph->distances[u][v] < dist[v]) {
                dist[v] = dist[u] + graph->distances[u][v];
                previous[v] = u;
            }
        }
    }

    cout << "Shortest path from " << start << " to " << end << ": ";
    if (dist[endIdx] == INT_MAX) {
        cout << "No path found." << endl;
        return;
    }

    int current = endIdx;
    vector<int> path;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    for (int i = path.size() - 1; i >= 0; --i) {
        cout << graph->markets[path[i]].name;
        if (i > 0) {
            cout << " <- ";
        }
    }
    cout << endl;
}

void printGraph(const MarketGraph* graph) {
    cout << "Market Graph:" << endl;

    cout << "Markets: ";
    for (int i = 0; i < graph->numMarkets; ++i) {
        cout << graph->markets[i].name << " ";
    }
    cout << endl;

    cout << "Distances:" << endl;
    for (int i = 0; i < graph->numMarkets; ++i) {
        for (int j = 0; j < graph->numMarkets; ++j) {
            cout << graph->distances[i][j] << " ";
        }
        cout << endl;
    }
}

bool readMarketDataFromJson(const string& filename, MarketGraph& marketGraph) {
    Json::CharReaderBuilder reader;
    Json::Value root;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening JSON file: " << filename << endl;
        return false;
    }

    Json::parseFromStream(reader, file, &root, nullptr);

    if (!root.isMember("markets") || !root.isMember("distances")) {
        cerr << "Invalid JSON format. Missing 'markets' or 'distances' field." << endl;
        return false;
    }

    Json::Value marketsJson = root["markets"];
    for (const auto& market : marketsJson) {
        if (!market.isMember("name")) {
            cerr << "Invalid JSON format. Missing 'name' field for a market." << endl;
            return false;
        }
        const string name = market["name"].asString();
        addMarket(&marketGraph, name.c_str());
    }

    Json::Value distancesJson = root["distances"];
    for (int i = 0; i < marketGraph.numMarkets; ++i) {
        for (int j = 0; j < marketGraph.numMarkets; ++j) {
            if (!distancesJson[i][j].isNull()) {
                addDistance(&marketGraph, marketGraph.markets[i].name, marketGraph.markets[j].name, distancesJson[i][j].asInt());
            }
        }
    }

    return true;
}