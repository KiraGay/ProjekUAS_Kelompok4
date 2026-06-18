### SIPM-KEL4-TiD
### 🟨 Aulia Bilbina
* **Fitur & Modul:** Master Data & Koleksi Buku Utama.
* **Implementasi:** Merancang struktur objek data menggunakan `struct Buku` dan mengimplementasikannya ke dalam wadah penyimpanan dinamis **`std::vector`**.
* **Fitur Validasi:** Menyusun fungsi *Duplicate ID Check* untuk mendeteksi sekaligus mencegah terjadinya duplikasi nomor ID buku saat penginputan data baru.

### 🟪 Abdul Ripki
* **Fitur & Modul:** Kerangka Utama Aplikasi (`main.cpp`) & CRUD Transaksi.
* **Implementasi:** Membangun struktur navigasi menu utama (pilihan 1-5) berbasis perulangan (*looping console*) serta menyusun logika inti pada modul **Peminjaman** dan **Pengembalian** buku.
* **Fitur Validasi:** Memanfaatkan metode **Pointer / Reference C++** untuk memanipulasi status ketersediaan buku di memori secara *real-time* sekaligus mengamankan transaksi agar buku tidak dapat dipinjam ganda.

### 🟫 Ariya Wijaya
* **Fitur & Modul:** Searching, Sorting, & Laporan Koleksi Buku.
* **Implementasi:** Mengoptimalkan algoritma urut data laporan menggunakan **Sorting (Bubble/Insertion Sort)** dari A-Z berdasarkan judul/ID serta mempercepat pencarian buku dengan algoritma **Linear Search**.
* **Fitur Validasi:** Menyusun *Error Handling Search Validation* untuk memastikan sistem memberikan umpan balik (notifikasi terstruktur) jika buku tidak ditemukan, guna mencegah program mengalami *crash*.

### 🟧 Syakila Nadia Dermawan
* **Fitur & Modul:** Manajemen Antrean Loket & Riwayat Transaksi.
* **Implementasi:** Mengatur alur sirkulasi pengunjung loket pelayanan dengan struktur data antrean **`std::queue`** (Prinsip FIFO). Selain itu, mencatat riwayat aktivitas transaksi secara kronologis menggunakan struktur data **Linked List**.
* **Fitur Validasi:** Memasang mekanisme pengaman *Underflow Queue Check* (validasi ketika antrean kosong) dan penanganan kesalahan tipe data input (*Error Handling Type*).

---

## 🚀 Alur Kerja Kolaborasi (Git Workflow)
Untuk menjaga kebersihan *source code* utama di branch `main`, seluruh anggota tim wajib mengikuti alur kerja berikut:
1. Melakukan `git clone` terhadap repositori ini.
2. Membuat dan berpindah ke cabang fitur masing-masing (`git checkout -b feature-nama-fitur`).
