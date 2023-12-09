#include "graph.hpp"

int findNationIndex(Graph* graph, const string& country) { // Pencarian indeks dari nation
    for (int i = 0; i < graph->index; ++i) {
        if (graph->nations[i].country == country) {
            return i;
        }
    }
    return -1;
}

void addNation(Graph* graph, string& country, string& name) { // Primitif menambahkan negara ke struktur data Graph
    if (graph->index < MAX) {
        graph->nations[graph->index].country = country;
        graph->nations[graph->index].name = name;
        ++graph->index;
    } else {
        cout << "Max limit of nations reached." << endl;
    }
}

bool readNationDataFromJson(const string& filename, Graph& nationGraph) { // Membaca file json
    Json::CharReaderBuilder reader;
    Json::Value root;

    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "Error opening JSON file: " << filename << endl;
        return false;
    }

    Json::parseFromStream(reader, file, &root, nullptr);
    if (!root.isMember("Nations") || !root.isMember("distances") || !root.isMember("Ally")) {
        cerr << "Invalid JSON format. Missing 'Nations', 'distances', or 'Ally' field." << endl;
        return false;
    }

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

    Json::Value distancesJson = root["distances"];
    for (int i = 0; i < nationGraph.index; ++i) {
        for (int j = 0; j < nationGraph.index; ++j) {
            nationGraph.distances[i][j] = distancesJson[i][j].asInt();
        }
    }

    Json::Value alliesJson = root["Ally"];
    for (int i = 0; i < nationGraph.index; ++i) {
        for (int j = 0; j < nationGraph.index; ++j) {
            nationGraph.allies[i][j] = alliesJson[i][j].asInt();
        }
    }

    return true;
}

int findMinDistance(int* dist, bool* visited) { // Mencari jarak terpendek
    int minIndex = -1;
    int minDist = MARK;

    for (int i = 0; i < MAX; ++i) {
        if (!visited[i] && dist[i] < minDist) {
            minDist = dist[i];
            minIndex = i;
        }
    }
    return minIndex;
}

void dijkstra(Graph* graph, const string& start, const string& end) {
    int startIdx = findNationIndex(graph, start); // Mencari index nation awal
    int endIdx = findNationIndex(graph, end); // Mencari index nation tujuan

    if (startIdx == -1 || endIdx == -1) { // Bangsa tidak ditemukan
        cout << "Invalid nation names for Dijkstra's algorithm." << endl;
        return;
    }

    int dist[MAX]; // Array untuk menyimpan jarak terpendek dari bangsa awal
    bool visited[MAX]; // Array penanda kunjungan ke setiap bangsa
    int previous[MAX]; // Array untuk menyimpan predecessor atau bangsa sebelumnya dalam jalur terpendek

    for (int i = 0; i < MAX; ++i) { // Inisialisasi array jarak, visited, dan previous
        dist[i] = MARK;
        visited[i] = false;
        previous[i] = -1;
    }
    dist[startIdx] = 0;

    for (int count = 0; count < MAX; ++count) { // Loop untuk menemukan jalur terpendek
        int u = findMinDistance(dist, visited); // Mencari bangsa dengan jarak terpendek yang belum dikunjungi
        visited[u] = true; // Menandai bangsa yang sudah dikunjungi

        for (int v = 0; v < MAX; ++v) { // Loop untuk mencari jarak lainnya terpendek ke bangsa lain
            if (!visited[v] && v < MAX && u < MAX && graph->distances[u][v] != 0 && dist[u] != MARK) { 
                // Memeriksa sekutu atau bukan dan membandingkan dengan jarak sebelumnya
                if (graph->allies[u][v] == 1 && dist[u] + graph->distances[u][v] < dist[v]) {
                    dist[v] = dist[u] + graph->distances[u][v];
                    previous[v] = u;
                }
            }
        }
    }

    cout << endl << "Shortest path from " << graph->nations[startIdx].name << " to " << graph->nations[endIdx].name << " : " << endl << endl;
    if (dist[endIdx] == MARK) { // Kondisi tidak ada jalan menuju bangsa yang dituju
        cout << "No path found." << endl << endl;
        return;
    }

    int current = endIdx; // Rekonstruksi jalur terpendek dari predecessor
    int path[MAX];
    int pathLength = 0;
    while (current != -1) {
        path[pathLength++] = current;
        current = previous[current];
    }

    int totalDistance = 0;
    for (int i = pathLength - 1; i >= 0; --i) { // Menampilkan jalur terpendek dan menghitung total jarak
        cout << graph->nations[path[i]].country;
        if (i > 0) {
            cout << " --> ";
            totalDistance += graph->distances[path[i-1]][path[i]];
        }
    }

    for (int i = 1; i < pathLength; ++i) { // Menampilkan jalur kembali ke bangsa awal
        cout << " --> " << graph->nations[path[i]].country;
        totalDistance += graph->distances[path[i-1]][path[i]];
    }

    cout << endl << endl  << setw(15) << left << "Total Distance" << " : " <<totalDistance << endl;
    cout  << setw(15) << left << "Total Reward" << " : " <<graph->distances[startIdx][endIdx] << endl << endl;    
}


void printGraph(Graph* graph) { // Menampilkan bangsa-bangsa yang ada
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
