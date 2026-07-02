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
// Keterangan: Ini adalah "cetakan" data. Semua anggota bergantung pada cetakan ini.
// AULIA: JANGAN ubah bagian ini tanpa kesepakatan dengan anggota lain!
// ==============================================================================
struct Buku {
    int idBuku;
    string judulBuku;
    string penulis;
    bool isTersedia;
    long long harga; 
    int tglPinjam, blnPinjam, thnPinjam;
    int tglKembali, blnKembali, thnKembali;
};

struct NodeRiwayat {
    string aktivitas;
    NodeRiwayat* next; // Pointer untuk menyambungkan ke riwayat selanjutnya
};

// ==============================================================================
// 2. FUNGSI PLACEHOLDER (STUB) - AREA KERJA ANGGOTA
// Keterangan: Ini adalah kerangka kosong. 
// AULIA: Kalau Syakila, Abdul, atau Ariya sudah setor kode, HAPUS isi fungsi ini 
// (hapus cout-nya), lalu PASTE kodingan utuh dari mereka di dalam kurung kurawal { }
// ==============================================================================

// ------------------- AREA SYAKILA -------------------
void tambahAntrean(queue<string>& antreanLoket) {
    // AULIA: Nanti isi dari Syakila ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Registrasi Antrean Loket' sedang dikerjakan oleh Syakila.\n";
}

void panggilAntrean(queue<string>& antreanLoket, vector<Buku>& databaseBuku, NodeRiwayat*& headRiwayat) {
    // AULIA: Nanti isi dari Syakila ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Panggil Antrean & Pelayanan' sedang dikerjakan oleh Syakila.\n";
}

void tampilkanRiwayat(NodeRiwayat* head) {
    // AULIA: Nanti isi dari Syakila ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Lihat Riwayat Transaksi' sedang dikerjakan oleh Syakila.\n";
}

// ------------------- AREA ABDUL -------------------
void pinjamBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat) {
    // AULIA: Nanti isi dari Abdul ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Peminjaman Buku' sedang dikerjakan oleh Abdul Ripki.\n";
}

void kembalikanBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat) {
    // AULIA: Nanti isi dari Abdul ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Pengembalian Buku' sedang dikerjakan oleh Abdul Ripki.\n";
}

// ------------------- AREA ARIYA -------------------
void tampilkanBukuAsli(const vector<Buku>& listBuku) {
    // AULIA: Nanti isi dari Ariya ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Tampilkan Daftar Buku' sedang dikerjakan oleh Ariya.\n";
}

void tampilkanBukuTerurut(vector<Buku> listBuku) { 
    // AULIA: Nanti isi dari Ariya ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Sorting Buku (A-Z)' sedang dikerjakan oleh Ariya.\n";
}

void cariBuku(const vector<Buku>& listBuku) {
    // AULIA: Nanti isi dari Ariya ditaruh di sini
    cout << "\n[!] INFO: Fitur 'Pencarian Buku' sedang dikerjakan oleh Ariya.\n";
}

// ==============================================================================
// 3. MODUL AULIA (INPUT DATA BUKU)
// Keterangan: Ini fitur milik Aulia sendiri yang sudah berfungsi normal.
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
    cin.ignore(); 
    
    // Validasi agar tidak ada ID buku yang kembar
    for (const auto& b : listBuku) {
        if (b.idBuku == bukuBaru.idBuku) {
            cout << "Validasi: Buku ID " << bukuBaru.idBuku << " sudah ada!\n"; return;
        }
    }
    
    cout << "Masukkan Judul Buku   : "; getline(cin, bukuBaru.judulBuku);
    cout << "Masukkan Nama Penulis : "; getline(cin, bukuBaru.penulis);
    cout << "Masukkan Harga Buku   : Rp"; cin >> bukuBaru.harga;
    
    // Set default nilai awal
    bukuBaru.isTersedia = true; 
    bukuBaru.tglPinjam = 0; bukuBaru.blnPinjam = 0; bukuBaru.thnPinjam = 0;
    bukuBaru.tglKembali = 0; bukuBaru.blnKembali = 0; bukuBaru.thnKembali = 0;
    
    // Simpan ke database (vector)
    listBuku.push_back(bukuBaru);
    cout << "\nSukses: Buku \"" << bukuBaru.judulBuku << "\" ditambahkan!\n";
}


// ==============================================================================
// 4. MAIN MENU (KENDALI UTAMA - AULIA)
// Keterangan: Di sinilah aplikasi mulai berjalan. Aulia mengatur menu di sini.
// ==============================================================================
int main() {
    // 1. Variabel Global (Berlaku selama aplikasi jalan)
    // databaseBuku: Tempat nyimpen semua buku (pakai vector) -> Diisi 2 dummy data buat ngetes
    vector<Buku> databaseBuku = {
        {1, "Algoritma C++", "Andi Nugroho", true, 80000, 0, 0, 0, 0, 0, 0},
        {2, "Bahasa Indonesia", "Depdiknas", true, 60000, 0, 0, 0, 0, 0, 0}
    };
    
    // antreanPelayanan: Tempat nyimpen nama pengunjung yg antre (pakai queue FIFO)
    queue<string> antreanPelayanan;
    
    // headRiwayat: Tempat nyimpen awal mula riwayat (pakai Linked List)
    NodeRiwayat* headRiwayat = nullptr;
    
    // Pilihan menu input user
    int pilihanMenu;

    // 2. Looping Menu Utama (Berhenti kalau user pilih 0)
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
        
        // Mencegah error kalau user input huruf, bukan angka
        if (!(cin >> pilihanMenu)) {
            cout << "Peringatan: Masukkan angka yang valid!\n";
            cin.clear(); cin.ignore(10000, '\n'); continue;
        }

        // Memanggil fungsi sesuai pilihan menu
        switch (pilihanMenu) {
            case 1: tambahAntrean(antreanPelayanan); break;
            case 2: panggilAntrean(antreanPelayanan, databaseBuku, headRiwayat); break;
            case 3: tambahBuku(databaseBuku); break; // Ini punya Aulia, pasti jalan!
            case 4: tampilkanBukuAsli(databaseBuku); break;    
            case 5: tampilkanBukuTerurut(databaseBuku); break; 
            case 6: tampilkanRiwayat(headRiwayat); break;
            case 0: cout << "\nAplikasi ditutup. Terima kasih.\n"; break;
            default: cout << "Pilihan tidak tersedia.\n";
        }
    } while (pilihanMenu != 0);

    return 0; // Program selesai dengan aman
}
