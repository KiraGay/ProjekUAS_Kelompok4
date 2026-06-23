// Data sampel koleksi buku
let dataBuku = [
    { id: 103, judul: "Struktur Data C++" },
    { id: 101, judul: "sistem oprasi" },
    { id: 104, judul: "jenis jenis data c++" },
    { id: 102, judul: "teori logika dasar" }
];

// ==========================================
// 1. FITUR SORTING (Insertion Sort) - A-Z berdasarkan Judul
// ==========================================
function insertionSortBuku(arr) {
    let n = arr.length;
    for (let i = 1; i < n; i++) {
        let key = arr[i];
        let j = i - 1;

        // Membandingkan string judul secara alfabetis (A-Z)
        while (j >= 0 && arr[j].judul.localeCompare(key.judul) > 0) {
            arr[j + 1] = arr[j];
            j = j - 1;
        }
        arr[j + 1] = key;
    }
    return arr;
}

// ==========================================
// 2. FITUR SEARCHING & VALIDATION (Linear Search)
// ==========================================
function cariBukuDenganValidasi(arr, kataKunci) {
    try {
        // Validasi 1: Memastikan input tidak kosong atau hanya spasi
        if (!kataKunci || kataKunci.trim() === "") {
            throw new Error("Input pencarian tidak boleh kosong!");
        }

        let hasilPencarian = [];
        let kueri = kataKunci.toLowerCase();

        // Proses Linear Search (Mengecek satu per satu)
        for (let i = 0; i < arr.length; i++) {
            if (arr[i].judul.toLowerCase().includes(kueri) || arr[i].id.toString() === kueri) {
                hasilPencarian.push(arr[i]);
            }
        }

        // Validasi 2: Jika proses selesai tapi data tidak ditemukan
        if (hasilPencarian.length === 0) {
            throw new Error(`Buku dengan kata kunci "${kataKunci}" tidak ditemukan.`);
        }

        // Jika berhasil ditemukan
        return {
            status: "success",
            data: hasilPencarian
        };

    } catch (error) {
        // Fitur Validasi / Error Handling: Menangkap error agar program tidak crash
        return {
            status: "error",
            pesan: error.message
        };
    }
}

// ==========================================
// UJI COBA PROGRAM
// ==========================================

console.log("=== LAPORAN SEBELUM DIURUTKAN ===");
console.log(dataBuku);

console.log("\n=== LAPORAN SETELAH DIURUTKAN (A-Z) ===");
let laporanTerurut = insertionSortBuku([...dataBuku]); // Menggunakan spread operator supaya data asli tidak rusak
console.table(laporanTerurut);

console.log("\n=== UJI COBA PENCARIAN ===");

// Kasus 1: Pencarian Berhasil
let cari1 = cariBukuDenganValidasi(laporanTerurut, "Bumi");
console.log("Hasil Cari 'Bumi':", cari1);

// Kasus 2: Pencarian Gagal (Buku Tidak Ada) - Menghasilkan Notifikasi Struktur Error
let cari2 = cariBukuDenganValidasi(laporanTerurut, "Harry Potter");
console.log("Hasil Cari 'Harry Potter':", cari2);

// Kasus 3: Validasi Input Kosong
let cari3 = cariBukuDenganValidasi(laporanTerurut, "   ");
console.log("Hasil Cari Input Kosong:", cari3);
