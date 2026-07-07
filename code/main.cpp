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

// --- FITUR ABDUL ---
void pinjamBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat, Mahasiswa mhsAktif) {
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
                
                cout << "Masukkan Tanggal Pinjam (DD/MM/YYYY)  : ";
                cin >> ws; 
                getline(cin, inputTanggalPinjam);
                sscanf(inputTanggalPinjam.c_str(), "%d/%d/%d", &dPinjam, &mPinjam, &yPinjam);

                // FIX: Penamaan diperjelas menjadi TENGGAT WAKTU
                cout << "Masukkan Tenggat Kembali (DD/MM/YYYY) : ";
                cin >> ws;
                getline(cin, inputTanggalKembali);
                sscanf(inputTanggalKembali.c_str(), "%d/%d/%d", &dKembali, &mKembali, &yKembali);
                
                b.isTersedia = false;
                b.tglPinjam = dPinjam; b.blnPinjam = mPinjam; b.thnPinjam = yPinjam;
                
                // Disimpan sebagai batas waktu (Tenggat)
                b.tglKembali = dKembali; b.blnKembali = mKembali; b.thnKembali = yKembali; 
                
                string tglPinjamFull = to_string(dPinjam) + "/" + to_string(mPinjam) + "/" + to_string(yPinjam);
                string tglKembaliFull = to_string(dKembali) + "/" + to_string(mKembali) + "/" + to_string(yKembali);

                cout << "\nSukses: Buku \"" << b.judulBuku << "\" berhasil dipinjam.\n";
                
                string logAktivitas = "[PINJAM] Peminjam: " + mhsAktif.nama + " (NIM: " + mhsAktif.nim + ") | Buku: " + b.judulBuku + " (ID: " + to_string(b.idBuku) + ") | Tgl: " + tglPinjamFull + " s/d " + tglKembaliFull;
                catatRiwayat(headRiwayat, logAktivitas);
                return;
            } else {
                cout << "Info: Buku sedang dipinjam oleh orang lain.\n"; 
                return;
            }
        }
    }
    cout << "Error: Buku tidak ditemukan.\n";
}

void kembalikanBuku(vector<Buku>& listBuku, NodeRiwayat*& headRiwayat, Mahasiswa mhsAktif) {
    int idCari;
    cout << "\n=========================================\n";
    cout << "        TRANSAKSI PENGEMBALIAN BUKU       \n";
    cout << "=========================================\n";
    cout << "Masukkan ID Buku yang ingin dikembalikan: "; cin >> idCari;
    
    for (auto& b : listBuku) {
        if (b.idBuku == idCari) {
            if (!b.isTersedia) {
                // FIX FITUR KETERLAMBATAN: Meminta tanggal hari ini (saat buku dikembalikan)
                string inputTglDikembalikan;
                int dAktual, mAktual, yAktual;
                
                cout << "Masukkan Tgl Dikembalikan (DD/MM/YYYY): ";
                cin >> ws;
                getline(cin, inputTglDikembalikan);
                sscanf(inputTglDikembalikan.c_str(), "%d/%d/%d", &dAktual, &mAktual, &yAktual);

                // Konversi tanggal ke hari untuk mencari selisih
                long long hariTenggat = (b.thnKembali * 365) + (b.blnKembali * 30) + b.tglKembali;
                long long hariDikembalikan = (yAktual * 365) + (mAktual * 30) + dAktual;
                long long hariTelat = hariDikembalikan - hariTenggat;
                if (hariTelat < 0) hariTelat = 0; // Kalau dibalikin sebelum tenggat, hitung 0
                
                cout << "\nData Peminjaman Ditemukan:\n";
                cout << "- Judul Buku      : " << b.judulBuku << "\n";
                cout << "- Tenggat Kembali : " << b.tglKembali << "/" << b.blnKembali << "/" << b.thnKembali << "\n";

                char statusHilang;
                cout << "\nApakah buku ini hilang? (y/t)  : "; cin >> statusHilang;

                long long dendaHitung = 0;
                string catatanDenda = "Tanpa Denda";

                cout << "\n=========================================\n";
                cout << "Sukses: Pengembalian Buku Berhasil.\n";

                // LOGIKA DENDA KETERLAMBATAN
                if (statusHilang == 'y' || statusHilang == 'Y') {
                    dendaHitung = b.harga;
                    catatanDenda = "Buku Hilang (Denda 100% harga buku)";
                    cout << "Status Buku      : BUKU INI HILANG\n";
                    cout << "Keterangan Denda : " << catatanDenda << "\n";
                } 
                else if (hariTelat > 0) {
                    // Denda Rp 2.000 per hari
                    long long dendaPerHari = 2000;
                    dendaHitung = hariTelat * dendaPerHari;
                    catatanDenda = "Telat " + to_string(hariTelat) + " Hari (Denda Rp2.000/hari)";
                    
                    cout << "Status Buku      : BUKU INI TERLAMBAT\n";
                    cout << "Keterangan Denda : " << catatanDenda << "\n";
                } 
                else {
                    cout << "Status Buku      : TEPAT WAKTU\n";
                    cout << "Keterangan Denda : " << catatanDenda << "\n";
                }

                b.denda = dendaHitung; 
                b.isTersedia = true; 
                
                cout << "Total Denda      : Rp" << b.denda << "\n";

                string logAktivitas = "[KEMBALI] Peminjam: " + mhsAktif.nama + " (NIM: " + mhsAktif.nim + ") | Buku: " + b.judulBuku + " (ID: " + to_string(b.idBuku) + ") | Denda: Rp" + to_string(b.denda);
                catatRiwayat(headRiwayat, logAktivitas);
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
    
    cout << "\n=================================================================================================\n";
    cout << "                         === DAFTAR KOLEKSI BUKU (URUTAN ASLI) ===                               \n";
    cout << "=================================================================================================\n";
    cout << left << setw(6) << "ID" << setw(26) << "JUDUL" << setw(22) << "PENULIS" << setw(14) << "STATUS" << setw(12) << "HARGA" << "DENDA\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    for (const auto& b : listBuku) {
        cout << left << setw(6) << b.idBuku 
             << setw(26) << b.judulBuku 
             << setw(22) << b.penulis 
             << setw(14) << (b.isTersedia ? "Tersedia" : "Dipinjam") 
             << "Rp" << setw(10) << b.harga
             << "Rp" << b.denda << "\n";
    }
    cout << "=================================================================================================\n";
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
    
    cout << "\n=================================================================================================\n";
    cout << "                        === LAPORAN DATA KOLEKSI BUKU (SORTING A-Z) ===                          \n";
    cout << "=================================================================================================\n";
    cout << left << setw(6) << "ID" << setw(26) << "JUDUL" << setw(22) << "PENULIS" << setw(14) << "STATUS" << setw(12) << "HARGA" << "DENDA\n";
    cout << "-------------------------------------------------------------------------------------------------\n";
    for (const auto& b : listBuku) {
        cout << left << setw(6) << b.idBuku 
             << setw(26) << b.judulBuku 
             << setw(22) << b.penulis 
             << setw(14) << (b.isTersedia ? "Tersedia" : "Dipinjam") 
             << "Rp" << setw(10) << b.harga
             << "Rp" << b.denda << "\n";
    }
    cout << "=================================================================================================\n";
}

void cariBuku(const vector<Buku>& listBuku) {
    string kataKunci;
    cout << "\n=========================================\n";
    cout << "            PENCARIAN DATA BUKU            \n";
    cout << "=========================================\n";
    cout << "Masukkan Judul Buku: ";
    cin >> ws; 
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
            cout << "Denda      : Rp" << b.denda << "\n";
            cout << "Status     : " << (b.isTersedia ? "Tersedia" : "Dipinjam") << "\n";
            cout << "-----------------------------------------\n";
            ditemukan = true;
        }
    }

    if (!ditemukan) cout << "Validasi: Buku tidak ditemukan!\n=========================================\n";
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
