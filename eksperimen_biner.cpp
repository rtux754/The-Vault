#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

struct dataVault {
    // metadata
    string id_item;
    string alias;
    string ekstensi;
    string tanggal_dibuat;

    // konten teks
    string deskripsi;

    // konten biner
    vector<char> payLoad; // tempat menampung data gambar/dokumen
};

void load(dataVault *&head);

void load(dataVault *&head) {
    ofstream FileGambar("hasil.jpg" ios::binary);

    if (!FileGambar.is_open()) {
        cout << "[ERROR] gagal membuka file untuk membaca data!" << endl;
		return;
    }

    ifstream FileGambar("hasil.jpg" ios::binary, ios::ate);

    if (!FileGambar.is_open()) {
        cout << "[ERROR] gagal membuka file untuk membaca data!" << endl;
		return;
    }

    streampos pos = FileGambar.

}

int main() {
    dataVault *head = nullptr;
    load(head);

    return 0;
}
