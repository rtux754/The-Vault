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

int main() {

    ifstream fileGambar("test.jpg", ios::binary | ios::ate);

    if(!fileGambar.is_open()) {
        cout << "File tidak dapat dibuka!" << endl;
        return 1;
    }
    dataVault file11;

    // Mengisi Metadata
        file11.id_item = "VLT-001";
        file11.alias = "Rencana_Rahasia";
        file11.ekstensi = ".jpg";
        file11.tanggal_dibuat = "2026-04-30";
        file11.deskripsi = "Ini adalah eksperimen biner pertama yang sukses di Mabox.";

    streamsize size = fileGambar.tellg();
    if (size > 0) {
        fileGambar.seekg(0, ios::beg);
        file11.payLoad.resize(static_cast<size_t>(size));
        fileGambar.read(file11.payLoad.data(), size);
    }

    if (size <= 0) {
        cout << "File kosong atau tidak bisa dibaca!" << endl;
        return 1;
    }

    cout << "data berhasil dimuat kedalam struct" << file11.payLoad.size() << " byte." << endl;

    ofstream tujuan("hasil.jpg", ios::binary);

    tujuan.write(file11.payLoad.data(), file11.payLoad.size());

    cout << "Data dari struct telah berhasil ditulis ke dalam file baru" << endl;
    cout << "=== INFORMASI FILE ===\n" << endl;
    cout << "ID = " << file11.id_item << endl;
    cout << "Alias = " << file11.alias << endl;
    cout << "Ekstensi = " << file11.ekstensi << endl;
    cout << "Tanggal = " << file11.tanggal_dibuat << endl;
    cout << "Deskripsi = " << file11.deskripsi << endl;

    fileGambar.close();

    return 0;
}
