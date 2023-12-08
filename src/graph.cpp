#include "graph.hpp"

int findNationIndex(Graph* graph, const string& country) {
    for (int i = 0; i < graph->index; ++i) {
        if (graph->nations[i].country == country) {
            return i;
        }
    }
    return -1; // Nation not found
}

void addNation(Graph* graph, string& country, string& name) {
    if (graph->index < MAX) {
        graph->nations[graph->index].country = country;
        graph->nations[graph->index].name = name;
        ++graph->index;
    } else {
        cout << "Max limit of nations reached." << endl;
    }
}

bool readNationDataFromJson(const string& filename, Graph& nationGraph) {
    Json::CharReaderBuilder reader;
    Json::Value root;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening JSON file: " << filename << endl;
        return false;
    }

    Json::parseFromStream(reader, file, &root, nullptr);

    // Check if the required fields are present
    if (!root.isMember("Nations") || !root.isMember("distances") || !root.isMember("Ally")) {
        cerr << "Invalid JSON format. Missing 'Nations', 'distances', or 'Ally' field." << endl;
        return false;
    }

    // Read nations
    Json::Value nationsJson = root["Nations"];
    for (auto& nation : nationsJson) {
        if (!nation.isMember("country") || !nation.isMember("name")) {
            cerr << "Invalid JSON format. Missing 'country' or 'name' field for a nation." << endl;
            return false;
        }
        string country = nation["country"].asString();
        string name = nation["name"].asString();
        addNation(&nationGraph, country, name);
    }

    // Read distances
    Json::Value distancesJson = root["distances"];
    for (int i = 0; i < nationGraph.index; ++i) {
        for (int j = 0; j < nationGraph.index; ++j) {
            nationGraph.distances[i][j] = distancesJson[i][j].asInt();
        }
    }

    // Read allies
    Json::Value alliesJson = root["Ally"];
    for (int i = 0; i < nationGraph.index; ++i) {
        for (int j = 0; j < nationGraph.index; ++j) {
            nationGraph.allies[i][j] = alliesJson[i][j].asInt();
        }
    }

    return true;
}

int findMinDistance(int* dist, set<int>& visited) {
    int minIndex = -1;
    int minDist = MARK;

    for (int i = 0; i < MAX; ++i) {
        if (visited.find(i) == visited.end() && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(Graph* graph, const string& start, const string& end) {
    int startIdx = findNationIndex(graph, start);
    int endIdx = findNationIndex(graph, end);

    if (startIdx == -1 || endIdx == -1) {
        cout << "Invalid nation names for Dijkstra's algorithm." << endl;
        return;
    }

    int dist[MAX];
    set<int> visited;
    int previous[MAX];

    for (int i = 0; i < MAX; ++i) {
        dist[i] = MARK;
        previous[i] = -1;
    }

    dist[startIdx] = 0;

    for (int count = 0; count < MAX; ++count) {
        int u = findMinDistance(dist, visited);
        visited.insert(u);

        for (int v = 0; v < MAX; ++v) {
            if (visited.find(v) == visited.end() && graph->distances[u][v] != 0
                && dist[u] != MARK) {
                
                // Check if v is an enemy, and u is an ally of v
                if (graph->allies[u][v] == 1 && dist[u] + graph->distances[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph->distances[u][v];
                    previous[v] = u;
                }
            }
        }
    }

    cout << endl << "Shortest path from " << graph->nations[startIdx].name << " to " << graph->nations[endIdx].name << ": " << endl << endl;
    if (dist[endIdx] == MARK) {
        cout << "No path found." << endl << endl;
        return;
    }

    int current = endIdx;
    vector<int> path;
    while (current != -1) {
        path.push_back(current);
        current = previous[current];
    }

    int totalDistance = 0;
    for (int i = path.size() - 1; i >= 0; --i) {
        cout << graph->nations[path[i]].country;
        if (i > 0) {
            cout << " --> ";
            totalDistance += graph->distances[path[i-1]][path[i]];
        }
    }
    cout << endl << endl << "Total Distance: " << totalDistance << endl;
    cout << "Total Reward: " << graph->distances[startIdx][endIdx] << endl << endl;    
}


void printGraph(Graph* graph) {
    cout << endl << "Nations List:" << endl;
    for (int i = 0; i < graph->index; ++i) {
        cout << "Country: " << setw(12) << left << graph->nations[i].country
             << "Name: " << graph->nations[i].name << endl;
    }

    // cout << endl << "Distances:" << endl;
    // for (int i = 0; i < graph->index; ++i) {
    //     for (int j = 0; j < graph->index; ++j) {
    //         cout << graph->distances[i][j] << " ";
    //     }
    //     cout << endl;
    // }

    // cout << endl << "Allies:" << endl;
    // for (int i = 0; i < graph->index; ++i) {
    //     for (int j = 0; j < graph->index; ++j) {
    //         cout << graph->allies[i][j] << " ";
    //     }
    //     cout << endl;
    // }
}
