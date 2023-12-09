#include "src/graph.hpp"

const int MAXLENGTH = 256;

int main() {
    Graph market; // Inisialisasi Graf
    market.index = 0; // Inisialisasi data masukan

    if (!readNationDataFromJson("test/data.json", market)) { // Proses pembacaan data JSON
        cerr << "Failed to read nation data from JSON." << endl;
        return 1;
    }

    printGraph(&market); // Menampilkan daftar bangsa

    string sourceName, destinationName;

    cout << endl << setw(25) << left << "Enter country" << " : "; // Input bangsa awal
    getline(cin, sourceName);

    cout<< setw(25) << left << "Enter destination country" << " : "; // Input bangsa tujuan
    getline(cin, destinationName);

    char sourceNameChar[MAXLENGTH];
    char destinationNameChar[MAXLENGTH];

    strncpy(sourceNameChar, sourceName.c_str(), MAXLENGTH); // Metode mengubah char menjadi string
    strncpy(destinationNameChar, destinationName.c_str(), MAXLENGTH); // Metode mengubah char menjadi string

    dijkstra(&market, sourceNameChar, destinationNameChar); // Memanggil fungsi dijkstra dari file graph.cpp

    return 0;
}

