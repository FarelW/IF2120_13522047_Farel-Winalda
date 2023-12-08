#include "src/graph.hpp"

const int MAX_NAME_LENGTH = 256;

int main() {
    Graph market;
    market.index = 0;

    if (!readNationDataFromJson("test/data.json", market)) {
        cerr << "Failed to read nation data from JSON." << endl;
        return 1;
    }

    printGraph(&market);

    string sourceName, destinationName;

    cout << endl << "Enter country: ";
    getline(cin, sourceName);

    cout << "Enter destination country: ";
    getline(cin, destinationName);

    char sourceNameChar[MAX_NAME_LENGTH];
    char destinationNameChar[MAX_NAME_LENGTH];

    strncpy(sourceNameChar, sourceName.c_str(), MAX_NAME_LENGTH);
    strncpy(destinationNameChar, destinationName.c_str(), MAX_NAME_LENGTH);

    dijkstra(&market, sourceNameChar, destinationNameChar);

    return 0;
}

