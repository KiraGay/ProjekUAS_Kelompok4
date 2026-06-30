# 📚 Sistem Perpustakaan Modern - Kelompok 4 INFORMATIKA

Aplikasi manajemen perpustakaan berbasis *console* yang dirancang menggunakan bahasa C++ untuk memenuhi tugas Projek Ujian Akhir Semester (UAS) Praktikum Algoritma dan Struktur Data. Sistem ini berfokus pada efisiensi pengelolaan data, otomatisasi transaksi, serta ketertiban pelayanan antrean sirkulasi buku.

---

## 👥 Struktur Tim & Pembagian Tugas Anggota

1. 👑 Arif Nur Fatahillah (Lead Project Manager & Git Reviewer)
Peran Utama: Manajemen Proyek, Pengawas Repositori, dan Quality Assurance (QA).
Deskripsi Tugas Berdasarkan Kode:
Bertindak murni sebagai pengatur alur kerja tim dan tidak memegang kodingan fitur secara langsung.
Bertanggung jawab penuh atas arsitektur repositori Git (ProjekUAS_Kelompok4), pembuatan ruleset perlindungan branch main, serta melakukan Code Review pada setiap Pull Request yang diajukan oleh anggota.
Memantau jalannya kolaborasi antar-anggota agar tidak terjadi code conflict saat penyatuan kode akhir.

2. 👩‍💻 Aulia Bilbina (Lead Developer, Integrator Utama & Master Data Engineer)
Peran Utama: Pemegang Kerangka Aplikasi (main.cpp), Kontrol Menu Utama, dan Manajemen Validasi Objek.
Deskripsi Tugas Berdasarkan Kode:
Bertanggung jawab menjaga struktur utama program di file main.cpp (mengelola struktur data global struct Buku, do-while loop menu, dan penanganan kesalahan input menu).
Fitur Spesifik: Membangun dan mengaktifkan Menu 3 (Tambah Koleksi Buku) dengan menyimpannya ke dalam std::vector secara dinamis.
Mengimplementasikan fungsi Duplicate ID Check di Menu 3 untuk memastikan data buku yang dimasukkan memiliki ID unik sebelum diolah oleh modul anggota lain.
Bertanggung jawab menerima pecahan kode dari Syakila, Abdul, dan Ariya untuk ditempelkan ke dalam fungsi placeholder di file master.

3. 🟧 Syakila Nadia Dermawan (Queue & Linked List Specialist)
Peran Utama: Pengelola Alur Antrean Pengunjung dan Log Aktivitas Perpustakaan.
Deskripsi Tugas Berdasarkan Kode:
Fitur Spesifik: Membangun logika Menu 1 (Registrasi Antrean Loket) dan Menu 2 (Panggil Antrean Terdepan) menggunakan struktur data Queue (FIFO - First In, First Out) melalui objek antreanPelayanan.
Membangun struktur data dinamis struct NodeRiwayat menggunakan Linked List (Insert at Tail & Traversal) untuk Menu 6 (Lihat Riwayat Semua Transaksi).
Menyediakan fungsi utilitas catatRiwayat agar bisa dipanggil secara otomatis oleh modul transaksi milik Abdul setiap kali peminjaman atau pengembalian sukses dilakukan.

4. 🟫 Abdul Ripki (Transaction & Business Logic Engineer)
Peran Utama: Pengembang Logika Inti Transaksi, Durasi Waktu, dan Sistem Penalti (Denda).
Deskripsi Tugas Berdasarkan Kode:
Fitur Spesifik: Membangun fungsi logika transaksional untuk opsi pelayanan di dalam loket, yaitu Opsi 3 (Pinjam Buku) dan Opsi 4 (Kembalikan Buku).
Membuat algoritma State Management untuk mengubah status boolean isTersedia pada objek buku secara real-time (menolak pinjaman jika buku sedang kosong).
Mengembangkan formula perhitungan matematika untuk menghitung selisih hari peminjaman (kalkulasi tanggal tenggat) serta menerapkan Business Logic penalti denda (Denda 50% jika telat >30 hari, dan Denda 100% seharga buku jika status buku dinyatakan Hilang).

5. 🟦 Ariya Wijaya (Data Search & Sorting Specialist)
Peran Utama: Pengembang Algoritma Pencarian Fleksibel dan Pengurutan Laporan Koleksi Buku.
Deskripsi Tugas Berdasarkan Kode:
Fitur Spesifik: Membangun fungsi Menu 4 (Tampilkan Daftar Buku Urutan Asli) dan Menu 5 (Cetak Laporan Seluruh Buku A-Z).
Mengimplementasikan algoritma Bubble Sort / Merge Sort pada Menu 5 untuk mengurutkan string judulBuku secara Ascending (A-Z) di dalam salinan std::vector agar data asli tidak rusak.
Mengembangkan fungsi pencarian pintar (Flexible & Case-Insensitive Search) pada menu pencarian buku yang mampu mendeteksi input pengguna baik berupa angka (ID Buku) maupun teks kata kunci (Judul Buku) secara otomatis.
---

## 🚀 Alur Kerja Kolaborasi (Git Workflow)
Untuk menjaga kebersihan *source code* utama di branch `main`, seluruh anggota tim wajib mengikuti alur kerja berikut:
1. Melakukan `git clone` terhadap repositori ini.
2. Membuat dan berpindah ke cabang fitur masing-masing (`git checkout -b feature-nama-fitur`).
3. Melakukan *coding* dan pengujian lokal di perangkat masing-masing.
4. Melakukan komit dan unggah perubahan ke cabang personal (`git push origin feature-nama-fitur`).
5. Membuat **Pull Request (PR)** di halaman web GitHub untuk ditinjau dan digabungkan (*merge*) oleh Ketua Tim.
