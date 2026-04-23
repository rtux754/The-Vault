#include <iostream>
#include <cstring>
#include <fstream>
using namespace std;

struct Kontak {
	char nama[30];
	char nomerHP[15];
	Kontak *next;
};

void tambahkontak(Kontak *&head, const char *namaBaru, const char *nomorBaru);
void tampilkanKontak(Kontak *head);
void simpanKeFile(Kontak *head);
void hapusKontak(Kontak *&head, const char *namaDiHapus);

void tampilkanKontak(Kontak *head) {
	Kontak *jalan = head;
	while (jalan != nullptr) {
		cout << "Nama  : " << jalan->nama << endl;
        cout << "No HP : " << jalan->nomerHP << endl;
        cout << "----------------------" << endl;
        jalan = jalan->next;
	}
}

void tambahkontak(Kontak *&head, const char *namaBaru, const char *nomorBaru) {
	// ciptakan memori baru untuk kontak baru
	Kontak *baru = new Kontak;
	
	// isi datanya
	strcpy(baru->nama, namaBaru);
	strcpy(baru->nomerHP, nomorBaru);
	baru->next = nullptr; // karena ditaruh di paling belakang jadi kosong
	
	// masukkan ke dalam brankas
	if (head == nullptr) { 
		// jika brankas masih kosong, baru jadi kontak pertama
		head = baru;
	} else {
		// jika sudah isinya, jalan sampai ujung brankas
		Kontak *jalan = head;
		while (jalan->next != nullptr) {
			jalan = jalan->next;
		}
		// sambungkan kontak baru di belakang kontak terakhir
		jalan->next = baru;
	}
}

void hapusKontak(Kontak *&head, const char *namaDiHapus) {
	// jika brankas masih kosong
	if (head == nullptr) {
		cout << "[ERROR] Brankas kosong, tidak ada kontak yang bisa dihapus." << endl;
		return;
	}
	// jika target berada di urutan pertama
	if (strcmp(head->nama, namaDiHapus) == 0) {
		Kontak *temp = head;
		head = head->next;
		delete temp;
		cout << "[SISTEM] Kontak bernama '" << namaDiHapus << "' berhasil dihapus!" << endl;
		return;
	} 
	// jika target di tengah atau di akhir
	Kontak *sebelumnya = head;
	Kontak *sekarang = head->next;
	while (sekarang != nullptr) {
		if (strcmp(sekarang->nama, namaDiHapus) == 0) {
			// target ditemukan, sambungkan tali melewati target
			sebelumnya->next = sekarang->next;
			delete sekarang; // eksekusi target
			cout << "[SISTEM] Kontak bernama '" << namaDiHapus << "' berhasil dihapus!" << endl;
			return;
		}
		sebelumnya = sekarang;
		sekarang = sekarang->next;
	}
	// jika sudah mencari sampai ujung tapi tidak ketemu
	cout << "[ERROR] Kontak bernama '" << namaDiHapus << "' tidak ditemukan di brankas." << endl;
}

void simpanKeFile(Kontak *head) {
	// membuat atau membuka file .txt
	ofstream fileBuku("DataVault.txt");
	
	if (!fileBuku.is_open()) {
		cout << "[ERROR] gagal membuka file untuk menyimpan data!" << endl;
		return;
	}

	Kontak *jalan = head;
	// tulis data satu per satu
	while (jalan != nullptr) {
		// format penulisan memisahkan koma atau baris baru
		fileBuku << jalan->nama << endl;
		fileBuku << jalan->nomerHP << endl;

		jalan = jalan -> next;
	}

	fileBuku.close();
	cout << "[SISTEM] Data berhasil diamankan ke dalam SSD (DataVault.txt)." << endl;
}

int main() {
	Kontak *head = nullptr; // dimulai dengan kosong
	char inputNama[30];
	char inputHP[15];
	char tambahLagi;
	int nomorUrut = 1;
	
	cout << "=== WELCOME TO THE VAULT ===" << endl;
	
	// coba 2 kontak dulu
	do{
		cout << "\nMasukkan nama kontak ke-" << nomorUrut << ": ";
		cin.getline(inputNama, 30); // membaca spasi juga
		
		cout << "\nMasukkan nomor hp: ";
		cin >> inputHP; // membaca teks tanpa spasi
		
		cin.ignore(); // untuk membersihkan sisa tombol Enter agar tidak terjadi error
		// memanggil fungsi
		tambahkontak(head, inputNama, inputHP);
		cout << "[SISTEM] Berhasil menyimpan kontak ke-" << nomorUrut << endl; // JEBAKAN 1
		
		nomorUrut++; // naikkan angka urutan untuk kontak berikutnya
		
		// menu dinamis
		cout << "\nApakah ingin menambahkan kontak lagi?(Y/N): ";
		cin >> tambahLagi;
		
		cin.ignore(10000, '\n');
		
	} while (tambahLagi == 'Y' || tambahLagi == 'y');
	
	cout << "[SISTEM] Loop input selesai, bersiap menampilkan data..." << endl; // JEBAKAN 2
	
	cout << "\n=== ISI BRANKAS SAAT INI ===" << endl;
	tampilkanKontak(head);
	
    cout << "[SISTEM] Selesai menampilkan data, bersiap membersihkan RAM..." << endl; // JEBAKAN 3
    
    cout << "\n=== FITUR PENGHAPUSAN KONTAK ===" << endl;
    char pilihanHapus;
    cout << "Apakah ada kontak yang ingin dihapus dari brankas?(Y/N): ";
    cin >> pilihanHapus;
    
    if (pilihanHapus == 'Y' || pilihanHapus == 'y') {
		char targetHapus[30];
		cout << "Masukkan nama kontak yang ingin dihapus dari brankas: ";
		
		cin.ignore(10000, '\n');
		
		cin.getline(targetHapus, 30);
		
		// jalankan fungsi penghapus
		hapusKontak(head, targetHapus);
		
		// tampilkan isi brankas
		tampilkanKontak(head);
    } else {
		cout << "[SISTEM] Penghapusan dibatalkan. Melanjutkan program..." << endl;
	}
	cout << "\n=== PROSES PENGARSIPAN ===";
	simpanKeFile(head); // tulis ke file

    // MEMBERSIHKAN RAM
    Kontak *temp;
    while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
	cout << "[SISTEM] RAM dibersihkan. Program ditutup." << endl; // JEBAKAN 4
	return 0;
}
