# Sistem-Manajemen-Klinik-Project
Perkenalkan, saya Gizelle Mathilda Mamentu dengan NIM 24051204146 dari Teknik Informatika E 2024 Universitas Negeri Surabaya.
Project ini bertujuan untuk memenuhi Final Project struktur data yang berjudul Sistem Manajemen Klinik.

Sistem ini menggabungkan beberapa implementasi struktur data , seperti Binary Search Tree (BST) untuk daftar obat, Hash Table untuk data dokter, Graph untuk menghubungkan diagnosis dan obat, serta Linked List dan Stack untuk transaksi pasien.
Dengan menggunakan BST pada katalog obat, pencarian dan penambahan data obat menjadi jauh lebih efisien dibanding cara biasa. Sementara itu, Hash Table dengan metode chaining dipakai untuk menyimpan data dokter dan jadwal praktik, memungkinkan akses instan berdasarkan ID dokter, bahkan ketika jumlah data terus bertambah. Untuk mendukung diagnosis, struktur Graph membantu memetakan hubungan antara penyakit dan obat yang dianjurkan, di mana setiap diagnosis terhubung dengan maksimal tiga jenis obat, sesuai standar praktik medis. 

Antrian pasien diatur menggunakan prinsip Queue (FIFO) agar semua mendapat pelayanan secara adil, sedangkan riwayat medis disimpan dalam Linked List yang bisa diurutkan berdasarkan usia pasien. Pada bagian pembayaran, Stack digunakan untuk mengelola resep obat, memudahkan proses transaksi dan pembatalan jika diperlukan. Sistem ini juga dilengkapi fitur pengelolaan stok obat berbasis Linked List yang diperbarui secara otomatis, mencegah kehabisan obat penting
