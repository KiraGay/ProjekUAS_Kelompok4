#include <iostream>
#include <vector>
#include <queue>
#include <string>
#include <iomanip>
#include <algorithm>
#include <cctype>
#include <cstdio>
using namespace std;

// ==========================================
// 1. STRUKTUR DATA (CETAKAN)
// ==========================================

// Struktur data untuk Buku (Modul Aulia & Abdul)
struct Buku {
    int idBuku;
    string judulBuku;
    string penulis;
    bool isTersedia;
    long long harga; 
    // Format Tanggal Peminjaman
    int tglPinjam;
    int blnPinjam;
    int thnPinjam;
    // --- PENAMBAHAN VARIABEL TANGGAL KEMBALI DI SINI ---
    int tglKembali;
    int blnKembali;
    int thnKembali;
};
