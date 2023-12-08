#include "src/graph.hpp"

int main() {
    MarketGraph marketGraph;
    marketGraph.numMarkets = 0;

    if (!readMarketDataFromJson("src/data.json", marketGraph)) {
        cerr << "Failed to read market data from JSON." << endl;
        return 1;
    }

    printGraph(&marketGraph);

    string sourceName, destinationName;

    cout << "Enter source market name: ";
    getline(cin, sourceName);

    cout << "Enter destination market name: ";
    getline(cin, destinationName);

    dijkstra(&marketGraph, sourceName.c_str(), destinationName.c_str());

    return 0;
}