#include "src/graph.hpp"

int main() {
    // Create a market graph
    MarketGraph marketGraph;
    marketGraph.numMarkets = 0;

    // Read market data from JSON file
    if (!readMarketDataFromJson("src/data.json", marketGraph)) {
        cerr << "Failed to read market data from JSON." << endl;
        return 1;
    }

    // Print the market graph
    printGraph(&marketGraph);

    // Read source and destination market names from the user
    string sourceName, destinationName;

    cout << "Enter source market name: ";
    getline(cin, sourceName);

    cout << "Enter destination market name: ";
    getline(cin, destinationName);

    // Example usage of Dijkstra's algorithm
    dijkstra(&marketGraph, sourceName.c_str(), destinationName.c_str());

    return 0;
}