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

struct Mahasiswa {
    string nama;
    string nim;
};

struct NodeRiwayat {
    string aktivitas;
    NodeRiwayat* next; // Pointer untuk menyambungkan ke riwayat selanjutnya
};


void tambahAntrean(queue<Mahasiswa>& antreanLoket);
void panggilAntrean(queue<Mahasiswa>& antreanLoket, vector<Buku>& databaseBuku, NodeRiwayat*& headRiwayat);
void catatRiwayat(NodeRiwayat*& head, string aktivitas); // <-- INI YANG BIKIN ERROR KALAU HILANG
void tampilkanRiwayat(NodeRiwayat* head);                // <-- INI JUGA
void tambahBuku(vector<Buku>& listBuku);
void pinjamBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat);
void kembalikanBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat);
void tampilkanBukuAsli(const vector<Buku>& listBuku);
void tampilkanBukuTerurut(vector<Buku> listBuku);
void cariBuku(const vector<Buku>& listBuku);


void tambahAntrean(queue<Mahasiswa>& antreanLoket) {
    Mahasiswa mhsBaru;
    cout << "\n=========================================\n";
    cout << "        REGISTRASI ANTREAN LOKET          \n";
    cout << "=========================================\n";
    cout << "Masukkan NIM Mahasiswa  : ";
    cin >> ws; // Membersihkan buffer
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
        cout << "2. Cari Buku (ID / Nama Buku) (Ariya)\n";
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
            case 3: pinjamBuku(databaseBuku, headRiwayat); break;
            case 4: kembalikanBuku(databaseBuku, headRiwayat); break;
            case 0: cout << "\nSelesai melayani " << mhsAktif.nama << ".\n"; break;
            default: cout << "Pilihan tidak tersedia.\n";
        }
    } while (opsiTransaksi != 0);
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

// --- FITUR ABDUL ---
void pinjamBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat) {
    string kataKunci;
    cout << "\n=========================================\n";
    cout << "         TRANSAKSI PEMINJAMAN BUKU        \n";
    cout << "=========================================\n";
    cout << "Masukkan ID Buku yang ingin dipinjam: "; 
    cin >> kataKunci;
    
    bool isAngka = true;
    for (char c : kataKunci) {
        if (!isdigit(c)) { isAngka = false; break; }
    }

    for (auto& b : listBuku) {
        if (isAngka && to_string(b.idBuku) == kataKunci) {
            if (b.isTersedia) {
                string inputTanggalPinjam, inputTanggalKembali;
                int dPinjam, mPinjam, yPinjam, dKembali, mKembali, yKembali;
                
                cout << "-> BUKU DITEMUKAN!\n";
                cout << "   Judul Buku : " << b.judulBuku << "\n";
                cout << "-----------------------------------------\n";
                
                cin.ignore();
                cout << "Masukkan Tanggal Pinjam (DD/MM/YYYY) : ";
                getline(cin, inputTanggalPinjam);
                sscanf(inputTanggalPinjam.c_str(), "%d/%d/%d", &dPinjam, &mPinjam, &yPinjam);

                cout << "Masukkan Tanggal Kembali (DD/MM/YYYY): ";
                getline(cin, inputTanggalKembali);
                sscanf(inputTanggalKembali.c_str(), "%d/%d/%d", &dKembali, &mKembali, &yKembali);
                
                b.isTersedia = false;
                b.tglPinjam = dPinjam; b.blnPinjam = mPinjam; b.thnPinjam = yPinjam;
                b.tglKembali = dKembali; b.blnKembali = mKembali; b.thnKembali = yKembali;
                
                string tglPinjamFull = to_string(dPinjam) + "/" + to_string(mPinjam) + "/" + to_string(yPinjam);
                string tglKembaliFull = to_string(dKembali) + "/" + to_string(mKembali) + "/" + to_string(yKembali);

                cout << "\nSukses: Buku \"" << b.judulBuku << "\" berhasil dipinjam.\n";
                catatRiwayat(headRiwayat, "Dipinjam (" + tglPinjamFull + " s/d " + tglKembaliFull + "): [ID " + to_string(b.idBuku) + "] " + b.judulBuku);
                return;
            } else {
                cout << "Info: Buku sedang dipinjam oleh orang lain.\n"; 
                return;
            }
        }
    }
    cout << "Error: Buku tidak ditemukan.\n";
}

void kembalikanBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat) {
    int idCari;
    cout << "\n=========================================\n";
    cout << "        TRANSAKSI PENGEMBALIAN BUKU       \n";
    cout << "=========================================\n";
    cout << "Masukkan ID Buku yang ingin dikembalikan: "; cin >> idCari;
    
    for (auto& b : listBuku) {
        if (b.idBuku == idCari) {
            if (!b.isTersedia) {
                char statusHilang;
                long long denda = 0;
                string catatanDenda = "Tanpa Denda";

                cout << "Apakah buku ini hilang? (y/t)  : "; cin >> statusHilang;

                long long totalHariPinjam = (b.thnPinjam * 365) + (b.blnPinjam * 30) + b.tglPinjam;
                long long totalHariKembali = (b.thnKembali * 365) + (b.blnKembali * 30) + b.tglKembali;
                long long durationPinjam = totalHariKembali - totalHariPinjam;
                if (durationPinjam < 0) durationPinjam = 0; 

                if (statusHilang == 'y' || statusHilang == 'Y') {
                    denda = b.harga;
                    catatanDenda = "Denda Buku Hilang (100% Harga Buku)";
                } 
                else if (durationPinjam > 30) {
                    denda = b.harga / 2;
                    catatanDenda = "Denda Keterlambatan " + to_string(durationPinjam) + " Hari (50% Harga Buku)";
                }

                b.isTersedia = true; 
                
                cout << "\nSukses: Pengembalian Buku Berhasil.\n";
                cout << "Status Denda     : " << catatanDenda << "\n";
                cout << "Total Denda      : Rp" << denda << "\n";

                string tglKembaliFull = to_string(b.tglKembali) + "/" + to_string(b.blnKembali) + "/" + to_string(b.thnKembali);
                catatRiwayat(headRiwayat, "Dikembalikan (" + tglKembaliFull + "): [ID " + to_string(b.idBuku) + "] " + b.judulBuku + " | Denda: Rp" + to_string(denda));
                return;
            } else {
                cout << "Info: Buku dengan ID ini belum pernah dipinjam.\n"; return;
            }
        }
    }
    cout << "Error: ID Buku salah / tidak terdaftar.\n";
}

// --- FITUR ARIYA ---
void tampilkanBukuAsli(const vector<Buku>& listBuku) {
    if (listBuku.empty()) { cout << "\nRak kosong.\n"; return; }
    
    cout << "\n===================================================================================\n";
    cout << "                    === DAFTAR KOLEKSI BUKU (URUTAN ASLI) ===                      \n";
    cout << "===================================================================================\n";
    cout << left << setw(6) << "ID" << setw(26) << "JUDUL" << setw(22) << "PENULIS" << setw(16) << "STATUS" << "HARGA\n";
    cout << "-----------------------------------------------------------------------------------\n";
    for (const auto& b : listBuku) {
        cout << left << setw(6) << b.idBuku 
             << setw(26) << b.judulBuku 
             << setw(22) << b.penulis 
             << setw(16) << (b.isTersedia ? "Tersedia" : "Dipinjam") 
             << "Rp" << b.harga << "\n";
    }
    cout << "===================================================================================\n";
}

void tampilkanBukuTerurut(vector<Buku> listBuku) { 
    if (listBuku.empty()) { cout << "\nRak kosong.\n"; return; }
    
    int n = listBuku.size();
    for (int i = 0; i < n - 1; i++) {
        for (int j = 0; j < n - i - 1; j++) {
            if (listBuku[j].judulBuku > listBuku[j+1].judulBuku) {
                swap(listBuku[j], listBuku[j+1]); 
            }
        }
    }
    
    cout << "\n===================================================================================\n";
    cout << "               === LAPORAN DATA KOLEKSI BUKU (SORTING A-Z) ===                 \n";
    cout << "===================================================================================\n";
    cout << left << setw(6) << "ID" << setw(26) << "JUDUL" << setw(22) << "PENULIS" << setw(16) << "STATUS" << "HARGA\n";
    cout << "-----------------------------------------------------------------------------------\n";
    for (const auto& b : listBuku) {
        cout << left << setw(6) << b.idBuku 
             << setw(26) << b.judulBuku 
             << setw(22) << b.penulis 
             << setw(16) << (b.isTersedia ? "Tersedia" : "Dipinjam") 
             << "Rp" << b.harga << "\n";
    }
    cout << "===================================================================================\n";
}

void cariBuku(const vector<Buku>& listBuku) {
    string kataKunci;
    cout << "\n=========================================\n";
    cout << "            PENCARIAN DATA BUKU            \n";
    cout << "=========================================\n";
    cout << "Masukkan Judul Buku: ";
    cin.ignore();
    getline(cin, kataKunci);

    if (kataKunci.empty()) { cout << "Validasi: Kata kunci tidak boleh kosong!\n"; return; }

    string kataKunciLower = kataKunci;
    transform(kataKunciLower.begin(), kataKunciLower.end(), kataKunciLower.begin(), ::tolower);

    bool ditemukan = false;
    for (const auto& b : listBuku) {
        string judulBukuLower = b.judulBuku;
        transform(judulBukuLower.begin(), judulBukuLower.end(), judulBukuLower.begin(), ::tolower);

        if (judulBukuLower.find(kataKunciLower) != string::npos) {
            cout << "-> DATA BUKU DITEMUKAN!\n";
            cout << "ID Buku    : " << b.idBuku << "\n";
            cout << "Nama Buku  : " << b.judulBuku << "\n"; 
            cout << "Penulis    : " << b.penulis << "\n";
            cout << "Harga      : Rp" << b.harga << "\n";
            cout << "Status     : " << (b.isTersedia ? "Tersedia" : "Dipinjam") << "\n";
            cout << "-----------------------------------------\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) cout << "Validasi: Buku tidak ditemukan!\n=========================================\n";
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
    queue<Mahasiswa> antreanPelayanan;
    
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
