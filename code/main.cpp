#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;

// ==============================================================================
// 1. STRUKTUR DATA UTAMA (FONDASI)
// ==============================================================================
struct Buku {
    int idBuku;
    string judulBuku;
    string penulis;
    bool isTersedia;
    long long harga; 
    long long denda; 
    int tglPinjam, blnPinjam, thnPinjam;
    int tglKembali, blnKembali, thnKembali;
};

struct Mahasiswa {
    string nama;
    string nim;
};

struct NodeRiwayat {
    string aktivitas; 
    NodeRiwayat* next; 
};

// ==============================================================================
// 2. PROTOTYPE FUNGSI
// ==============================================================================
void tambahAntrean(queue<Mahasiswa>& antreanLoket);
void panggilAntrean(queue<Mahasiswa>& antreanLoket, vector<Buku>& databaseBuku, NodeRiwayat*& headRiwayat);
void catatRiwayat(NodeRiwayat*& head, string aktivitas);
void tampilkanRiwayat(NodeRiwayat* head);
void tambahBuku(vector<Buku>& listBuku);
void pinjamBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat, Mahasiswa mhsAktif);
void kembalikanBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat, Mahasiswa mhsAktif);
void tampilkanBukuAsli(const vector<Buku>& listBuku);
void tampilkanBukuTerurut(vector<Buku> listBuku);
void cariBuku(const vector<Buku>& listBuku);

// ==============================================================================
// 3. FUNGSI-FUNGSI AREA KERJA ANGGOTA
// ==============================================================================

// --- FITUR SYAKILA ---
void tambahAntrean(queue<Mahasiswa>& antreanLoket) {
    Mahasiswa mhsBaru;
    cout << "\n=========================================\n";
    cout << "        REGISTRASI ANTREAN LOKET          \n";
    cout << "=========================================\n";
    cout << "Masukkan NIM Mahasiswa  : ";
    cin >> ws; 
    getline(cin, mhsBaru.nim);
    cout << "Masukkan Nama Mahasiswa : ";
    getline(cin, mhsBaru.nama);
    
    antreanLoket.push(mhsBaru);
    cout << "Sukses: \"" << mhsBaru.nama << "\" (NIM: " << mhsBaru.nim << ") masuk ke antrean.\n";
}

void panggilAntrean(queue<Mahasiswa>& antreanLoket, vector<Buku>& databaseBuku, NodeRiwayat*& headRiwayat) {
    if (antreanLoket.empty()) {
        cout << "\nValidasi: Antrean kosong, tidak ada pengunjung.\n";
        return;
    }
    
    Mahasiswa mhsAktif = antreanLoket.front();
    cout << "\n=========================================\n";
    cout << "[PANGGILAN LOKET] Silakan maju: " << mhsAktif.nama << " (" << mhsAktif.nim << ")\n";
    cout << "=========================================\n";
    antreanLoket.pop(); 

    int opsiTransaksi;
    do {
        cout << "\nPILIH TRANSAKSI UNTUK [" << mhsAktif.nama << "]:\n";
        cout << "1. Tampilkan Daftar Buku (Ariya)\n"; 
        cout << "2. Cari Buku (Ariya)\n";
        cout << "3. Pinjam Buku (Abdul)\n";
        cout << "4. Kembalikan Buku (Abdul)\n";
        cout << "0. Selesai Melayani & Kembali ke Menu Utama\n";
        cout << "-----------------------------------------\n";
        cout << "Pilih Opsi (0-4): ";
        
        if (!(cin >> opsiTransaksi)) {
            cout << "Peringatan: Masukkan angka yang valid!\n";
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }

        switch (opsiTransaksi) {
            case 1: tampilkanBukuAsli(databaseBuku); break;
            case 2: cariBuku(databaseBuku); break;
            case 3: pinjamBuku(databaseBuku, headRiwayat, mhsAktif); break;
            case 4: kembalikanBuku(databaseBuku, headRiwayat, mhsAktif); break;
            case 0: cout << "\nSelesai melayani " << mhsAktif.nama << ".\n"; break;
            default: cout << "Pilihan tidak tersedia.\n";
        }
    } while (opsiTransaksi != 0);
}

void catatRiwayat(NodeRiwayat*& head, string aktivitas) {
    NodeRiwayat* nodeBaru = new NodeRiwayat();
    nodeBaru->aktivitas = aktivitas;
    nodeBaru->next = nullptr;

    if (head == nullptr) {
        head = nodeBaru;
    } else {
        NodeRiwayat* temp = head;
        while (temp->next != nullptr) temp = temp->next;
        temp->next = nodeBaru;
    }
}

void tampilkanRiwayat(NodeRiwayat* head) {
    cout << "\n===============================================================================\n";
    cout << "                     RIWAYAT TRANSAKSI PERPUSTAKAAN                            \n";
    cout << "===============================================================================\n";
    cout << left << setw(5) << "NO" << "DETAIL AKTIVITAS" << "\n";
    cout << "-------------------------------------------------------------------------------\n";
    if (head == nullptr) {
        cout << "Belum ada transaksi yang tercatat.\n"; 
    } else {
        NodeRiwayat* temp = head;
        int no = 1;
        while (temp != nullptr) {
            cout << left << setw(5) << no << temp->aktivitas << "\n";
            temp = temp->next; no++;
        }
    }
    cout << "===============================================================================\n";
}


// ==============================================================================
// 3. MODUL AULIA (INPUT DATA BUKU)
// ==============================================================================
void tambahBuku(vector<Buku>& listBuku) {
    Buku bukuBaru;
    cout << "\n=========================================\n";
    cout << "       INPUT DATA KOLEKSI BUKU BARU        \n";
    cout << "=========================================\n";
    cout << "Masukkan ID Buku (Angka): ";
    if (!(cin >> bukuBaru.idBuku)) {
        cout << "Error: ID harus angka!\n";
        cin.clear(); cin.ignore(10000, '\n'); return;
    }
    
    for (const auto& b : listBuku) {
        if (b.idBuku == bukuBaru.idBuku) {
            cout << "Validasi: Buku ID " << bukuBaru.idBuku << " sudah ada!\n"; return;
        }
    }
    
    cout << "Masukkan Judul Buku   : "; cin >> ws; getline(cin, bukuBaru.judulBuku);
    cout << "Masukkan Nama Penulis : "; getline(cin, bukuBaru.penulis);
    cout << "Masukkan Harga Buku   : Rp"; cin >> bukuBaru.harga;
    
    bukuBaru.isTersedia = true; 
    bukuBaru.denda = 0; 
    bukuBaru.tglPinjam = 0; bukuBaru.blnPinjam = 0; bukuBaru.thnPinjam = 0;
    bukuBaru.tglKembali = 0; bukuBaru.blnKembali = 0; bukuBaru.thnKembali = 0;
    
    listBuku.push_back(bukuBaru);
    cout << "\nSukses: Buku \"" << bukuBaru.judulBuku << "\" ditambahkan!\n";
}

// ==============================================================================
// 4. MAIN MENU
// ==============================================================================
int main() {
    vector<Buku> databaseBuku = {
        {1, "Algoritma C++", "Andi Nugroho", true, 80000, 0, 0, 0, 0, 0, 0, 0}, 
        {2, "Bahasa Indonesia", "Depdiknas", true, 60000, 0, 0, 0, 0, 0, 0, 0}
    };
    
    queue<Mahasiswa> antreanPelayanan; 
    NodeRiwayat* headRiwayat = nullptr;
    int pilihanMenu;

    do {
        cout << "\n=========================================\n";
        cout << "  SISTEM INFORMASI PERPUSTAKAAN MODERN   \n";
        cout << "         KELOMPOK 4 - INFORMATIKA        \n";
        cout << "=========================================\n";
        cout << "1. Registrasi Antrean Loket (Syakila)\n";
        cout << "2. Panggil Antrean Terdepan (Syakila)\n";
        cout << "3. Tambah Koleksi Buku (Aulia)\n";
        cout << "4. Tampilkan Daftar Buku Asli (Ariya)\n"; 
        cout << "5. Cetak Laporan Buku [A-Z] (Ariya)\n";   
        cout << "6. Lihat Riwayat Transaksi (Syakila)\n";
        cout << "0. Keluar Aplikasi\n";
        cout << "-----------------------------------------\n";
        cout << "Pilih Opsi Menu (0-6): ";
        
        if (!(cin >> pilihanMenu)) {
            cout << "Peringatan: Masukkan angka yang valid!\n";
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }

        switch (pilihanMenu) {
            case 1: tambahAntrean(antreanPelayanan); break;
            case 2: panggilAntrean(antreanPelayanan, databaseBuku, headRiwayat); break;
            case 3: tambahBuku(databaseBuku); break; 
            case 4: tampilkanBukuAsli(databaseBuku); break;    
            case 5: tampilkanBukuTerurut(databaseBuku); break; 
            case 6: tampilkanRiwayat(headRiwayat); break;
            case 0: cout << "\nAplikasi ditutup. Terima kasih.\n"; break;
            default: cout << "Pilihan tidak tersedia.\n";
        }
    } while (pilihanMenu != 0);

    return 0; 
}
