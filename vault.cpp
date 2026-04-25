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
void save(Kontak *head);
void saveAs(Kontak *head);
void enkripsi(char teks[]);
void load(Kontak *&head);
void hapusKontak(Kontak *&head, const char *namaDiHapus);
void kosongkanBrankas(Kontak *&head);

// MENAMPILKAN KONTAK
void tampilkanKontak(Kontak *head) {
	Kontak *jalan = head;
	while (jalan != nullptr) {
		cout << "Nama  : " << jalan->nama << endl;
        cout << "No HP : " << jalan->nomerHP << endl;
        cout << "----------------------" << endl;
        jalan = jalan->next;
	}
}

// FUNGSI APPEND : MENAMBAHKAN NODE BARU DI UJUNG LINKED LIST
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

// FUNGSI DELETE : UNTUK MENGHAPUS NODE SPESIFIK BERDASARKAN PENCARIAN STRING
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

// GARBAGE COLLECTOR MANUAL AGAR TIDAK MENIMBULKAN MEMORY LEAK
void kosongkanBrankas(Kontak *&head) {
    
    Kontak *temp;
    while (head != nullptr) {
		temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
}

// FITUR LOAD UNTUK MEMBACA DATA DARI SSD KEMBALI KEDALAM RAM
void load (Kontak *&head) {
	ifstream fileBuku("DataVault.txt");
	
	if (!fileBuku.is_open()) {
		cout << "[ERROR] gagal membuka file untuk membaca data!" << endl;
		return;
	}
	
	Kontak *jalan = head;
	char bufferNama[30];
	char bufferNomor[15];
	while(jalan != nullptr) {
		cin.getline(bufferNama, sizeof(bufferNama));
		cin.ignore(10000, '\n');
		cin.getline(bufferNomor, sizeof(bufferNomor));
	}
	cout << "[SISTEM] Data berhasil di load." << endl;
}

// FITUR ENKRIPSI AGAR DATA YANG DISIMPAN HANYA BISA DIBACA OLEH KOMPUTER
void enkripsi(char teks[]) {
	char kunci = 'F';
	int i = 0;
	
	while (teks[i] != '\0') {
		teks[i] = teks[i] ^ kunci;
		i++;
	}
}

// FUNGSI FILE I/O (Overwrite): MENYIMPAN DATA DENGAN MENIMPA ULANG FILE
void save(Kontak *head) {
	
	ofstream fileBuku("DataVault.txt"); // mode default akan mereset isi file
		
	if (!fileBuku.is_open()) {
		cout << "[ERROR] gagal membuka file untuk menyimpan data!" << endl;
		return;
	}

	Kontak *jalan = head;
	// tulis data satu per satu
	while (jalan != nullptr) {
		// proses acak data
		enkripsi(jalan->nama);
		enkripsi(jalan->nomerHP);
		
		// format penulisan memisahkan koma atau baris baru
		fileBuku << jalan->nama << endl;
		fileBuku << jalan->nomerHP << endl;

		// kembalikan data ke ram
		enkripsi(jalan->nama);
		enkripsi(jalan->nomerHP);
		
		jalan = jalan -> next;
	}

	fileBuku.close();
	cout << "[SISTEM] Data berhasil diamankan ke dalam SSD (DataVault.txt)." << endl;
}

// FUNGSI FILE I/O (APPEND) : UNTUK MENYIMPAN DATA DENGAN MENAMBAHKAN KEBELAKANG FILE
void saveAs(Kontak *head) {
	
	ofstream fileBuku("DataVault.txt", ios::app); // bendera ios untuk mode append
	
	if (!fileBuku.is_open()) {
		cout << "[ERROR] gagal membuka file untuk menyimpan data!" << endl;
		return;
	}

	Kontak *jalan = head;
	// tulis data satu per satu
	while (jalan != nullptr) {
		
		// proses acak data
		enkripsi(jalan->nama);
		enkripsi(jalan->nomerHP);
		
		// tulis data dari ram sampai ujung bawah file ssd
		fileBuku << jalan->nama << endl;
		fileBuku << jalan->nomerHP << endl;

		// kembali data ke ram
		enkripsi(jalan->nama);
		enkripsi(jalan->nomerHP);
		
		jalan = jalan -> next;
	}

	fileBuku.close();
	cout << "[SISTEM] Data berhasil diamankan ke dalam SSD (DataVault.txt)." << endl;
}

int main() {
	cout << "\033[2J\033[3J\033[1;1H"; // ini untuk membersihkan layar agar tampilan menjadi enak
	Kontak *head = nullptr; // dimulai dengan kosong
	load(head);
	char keluar;
	char inputNama[30];
	char inputHP[15];
	char modeMasuk;
	char tambahLagi;
	int nomorUrut = 1;
	
	cout << "=== WELCOME TO THE VAULT ===" << endl;
	
	cout << "Pilih Mode: Tambah ke daftar yang ada(A) atau Timpa seluruh daftar(T)?:";
	cin >> modeMasuk;
	cin.ignore(10000, '\n');
	
	if (modeMasuk == 'A' || modeMasuk == 'a') {
		// tidak perlu melakukan apa-apa
		} else if (modeMasuk == 'T' || modeMasuk == 't'){
				kosongkanBrankas(head);
				cout << "[SISTEM] Brankas lama telah dihancurkan. Siap menimpa dengan data baru." << endl;
			}
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
	
	cout << "\033[2J\033[3J\033[1;1H";
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
		save(head);
		// tampilkan isi brankas
		cout << "\033[2J\033[3J\033[1;1H";
		tampilkanKontak(head);
    } else {
		cout << "[SISTEM] Penghapusan dibatalkan. Melanjutkan program..." << endl;
	}
	cout << "\n=== PROSES PENGARSIPAN ===";
	// mengecek untuk memanggil fungsi yang benar
	if (modeMasuk == 'A' || modeMasuk == 'a') {
		saveAs(head);
	} else if (modeMasuk == 'T' || modeMasuk == 't') {
			save(head);
		}
	
	cin.ignore(10000, '\n');
	
	cout << "Program selesai. Tekan enter untuk keluar...";
	cin.get();
    kosongkanBrankas(head);
    cout << "[SISTEM] RAM dibersihkan. Program ditutup." << endl;
    
	return 0;
}
