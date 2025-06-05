#include <iostream>
#include <iomanip>
#include <string>
#include <algorithm>
using namespace std;

struct ResepNode {
    string kode, nama;
    float harga;
    bool bpjs;
    ResepNode* next;
    
    ResepNode(string k, string n, float h, bool b)
        : kode(k), nama(n), harga(h), bpjs(b), next(nullptr) {}
};

struct StackResep {
    ResepNode* top;
    
    StackResep() : top(nullptr) {}
    void push(string kode, string nama, float harga, bool bpjs) {
        ResepNode* nodeBaru = new ResepNode(kode, nama, harga, bpjs);
        nodeBaru->next = top;
        top = nodeBaru;
    }
    void tampil() {
        ResepNode* curr = top;
        cout << "----------------------------------------\n";
        cout << setw(10) << "Kode" << setw(25) << "Nama Obat/Perawatan" << setw(10) << "Harga" << setw(8) << "BPJS" << endl;
        cout << "----------------------------------------\n";
        while (curr) {
            cout << setw(10) << curr->kode
                 << setw(25) << curr->nama
                 << setw(10) << fixed << setprecision(2) << curr->harga
                 << setw(8) << (curr->bpjs ? "Ya" : "Tidak") << endl;
            curr = curr->next;
        }
    }
    float total() {
        float sum = 0;
        ResepNode* curr = top;
        while (curr) {
            sum += curr->harga;
            curr = curr->next;
        }
        return sum;
    }
    void popAll() {
        while (top) {
            ResepNode* temp = top;
            top = top->next;
            delete temp;
        }
    }
};

struct Obat {
    string kode, nama;
    float harga;
    bool bpjs;
    Obat *left, *right;
    Obat(string k, string n, float h, bool b)
        : kode(k), nama(n), harga(h), bpjs(b), left(nullptr), right(nullptr) {}
};

struct BSTObat {
    Obat* root;
    BSTObat() : root(nullptr) {}
    Obat* insert(Obat* node, string kode, string nama, float harga, bool bpjs) {
        if (!node) return new Obat(kode, nama, harga, bpjs);
        if (kode < node->kode)
            node->left = insert(node->left, kode, nama, harga, bpjs);
        else if (kode > node->kode)
            node->right = insert(node->right, kode, nama, harga, bpjs);
        return node;
    }
    void tambah(string kode, string nama, float harga, bool bpjs) {
        root = insert(root, kode, nama, harga, bpjs);
    }
    Obat* cari(Obat* node, string kode) {
        if (!node) return nullptr;
        if (node->kode == kode) return node;
        if (kode < node->kode)
            return cari(node->left, kode);
        return cari(node->right, kode);
    }
    Obat* cariObat(string kode) { 
        return cari(root, kode); 
    }
    void inOrder(Obat* node) {
        if (!node) return;
        inOrder(node->left);
        cout << node->kode << " - " << node->nama << endl;
        inOrder(node->right);
    }
};

struct GraphNode {
    string diagnosa;
    string kodeObat[3];
    int nObat;
    GraphNode* next;
    GraphNode(string d) : diagnosa(d), nObat(0), next(nullptr) {}
};

struct Graph {
    GraphNode* head;
    Graph() : head(nullptr) {}
    void tambah(string diag, string kode) {
        GraphNode* curr = head;
        while (curr) {
            if (curr->diagnosa == diag) {
                if (curr->nObat < 3)
                    curr->kodeObat[curr->nObat++] = kode;
                return;
            }
            curr = curr->next;
        }
        GraphNode* baru = new GraphNode(diag);
        baru->kodeObat[baru->nObat++] = kode;
        baru->next = head;
        head = baru;
    }
    GraphNode* cari(string diag) {
        GraphNode* curr = head;
        while (curr) {
            if (curr->diagnosa == diag) 
                return curr;
            curr = curr->next;
        }
        return nullptr;
    }
};


struct Jadwal {
    string hariJam;
    Jadwal* next;
    
    Jadwal(string h) : hariJam(h), next(nullptr) {}
};

struct Dokter {
    string id, nama, poli, klinik;
    Jadwal* jadwal;
    Dokter* next;
    
    Dokter(string i, string n, string p, string k)
        : id(i), nama(n), poli(p), klinik(k), jadwal(nullptr), next(nullptr) {}
};

const int HASH_SIZE = 5;

struct HashDokter {
    Dokter* table[HASH_SIZE];
    
    HashDokter() { 
        for (int i = 0; i < HASH_SIZE; ++i) 
            table[i] = nullptr; 
    }

    int hash(string id) {
        int h = 0;
        for (char c : id) h += c;
        return h % HASH_SIZE;
    }

    void tambah(string id, string nama, string poli, string klinik, string jadwalx[], int nJadwal) {
        int idx = hash(id);
        Dokter* d = new Dokter(id, nama, poli, klinik);
        
        for (int i = 0; i < nJadwal; ++i) {
            Jadwal* j = new Jadwal(jadwalx[i]);
            j->next = d->jadwal;
            d->jadwal = j;
        }
        
        d->next = table[idx];
        table[idx] = d;
    }
    void tampilPoli(string poli) {
    string urutanHari[] = {"Senin", "Selasa", "Rabu", "Kamis", "Jumat", "Sabtu", "Minggu"};
    auto idxHari = [&](const string& h) -> int {
        for (int i = 0; i < 7; ++i)
            if (h.find(urutanHari[i]) == 0) return i;
        return 7;
    };

    // Lebar kolom
    const int wNo = 5, wId = 9, wNama = 20, wKlinik = 18, wJadwal = 22;

    cout << setfill('-') << setw(wNo + wId + wNama + wKlinik + wJadwal + 4) << "-" << endl;
    cout << setfill(' ')
         << setw(wNo) << "No."
         << setw(wId) << "ID"
         << setw(wNama) << "Nama Dokter"
         << setw(wKlinik) << "Klinik"
         << setw(wJadwal) << "Jadwal Praktik" << endl;
    cout << setfill('-') << setw(wNo + wId + wNama + wKlinik + wJadwal + 4) << "-" << endl;
    cout << setfill(' ');

    int no = 1;
    for (int i = 0; i < HASH_SIZE; ++i) {
        Dokter* d = table[i];
        while (d) {
            if (d->poli == poli) {
                string arrJadwal[16];
                int nJadwal = 0;
                Jadwal* j = d->jadwal;
                while (j && nJadwal < 16) {
                    arrJadwal[nJadwal++] = j->hariJam;
                    j = j->next;
                }
                for (int a = 0; a < nJadwal - 1; ++a) {
                    for (int b = a + 1; b < nJadwal; ++b) {
                        if (idxHari(arrJadwal[a]) > idxHari(arrJadwal[b])) {
                            string tmp = arrJadwal[a];
                            arrJadwal[a] = arrJadwal[b];
                            arrJadwal[b] = tmp;
                        }
                    }
                }
                if (nJadwal > 0) {
                    cout << setw(wNo) << no
                         << setw(wId) << d->id
                         << setw(wNama) << d->nama
                         << setw(wKlinik) << d->klinik
                         << setw(wJadwal) << arrJadwal[0] << endl;
                    for (int k = 1; k < nJadwal; ++k)
                        cout << setw(wNo) << " "
                             << setw(wId) << " "
                             << setw(wNama) << " "
                             << setw(wKlinik) << " "
                             << setw(wJadwal) << arrJadwal[k] << endl;
                } else {
                    cout << setw(wNo) << no
                         << setw(wId) << d->id
                         << setw(wNama) << d->nama
                         << setw(wKlinik) << d->klinik
                         << setw(wJadwal) << "-" << endl;
                }
                no++;
            }
            d = d->next;
        }
    }
}

    Dokter* dapatkan(string id) {
        int idx = hash(id);
        Dokter* d = table[idx];
        
        while (d) {
            if (d->id == id) 
                return d;
            d = d->next;
        }
        return nullptr;
    }

    int listPoli(string poli, Dokter* arr[]) {
        int no = 0;
        
        for (int i = 0; i < HASH_SIZE; ++i) {
            Dokter* d = table[i];
            
            while (d) {
                if (d->poli == poli) 
                    arr[no++] = d;
                d = d->next;
            }
        }
        return no;
    }
};

struct Transaksi {
    string nama, diagnosa, dokter, jadwal, jenisPembayaran;
    StackResep resep;
    float total;
    Transaksi* next;
};

struct ListTransaksi {
    Transaksi* head;
    ListTransaksi() : head(nullptr) {}

    void tambah(string nama, string diagnosa, string dokter, string jadwal, string jenisPembayaran, StackResep resep, float total) {
        Transaksi* t = new Transaksi;
        t->nama = nama;
        t->diagnosa = diagnosa;
        t->dokter = dokter;
        t->jadwal = jadwal;
        t->jenisPembayaran = jenisPembayaran;
        t->resep = resep;
        t->total = total;
        t->next = nullptr;
        
        if (!head) 
            head = t;
        else {
            Transaksi* curr = head;
            while (curr->next) 
                curr = curr->next;
            curr->next = t;
        }
    }

    void tampilDaftar() {
        cout << "  No.         Nama Pasien            Diagnosa/Perawatan   Total Biaya\n";
        cout << "--------------------------------------------------------------------\n";
        
        int no = 1;
        Transaksi* curr = head;
        while (curr) {
            cout << setw(5) << no
                 << setw(20) << curr->nama
                 << setw(25) << curr->diagnosa
                 << "    Rp" << fixed << setprecision(2) << curr->total << endl;
            curr = curr->next;
            no++;
        }
    }

    Transaksi* getByIdx(int idx) {
        int i = 1;
        Transaksi* curr = head;
        while (curr) {
            if (i == idx) 
                return curr;
            i++;
            curr = curr->next;
        }
        return nullptr;
    }

    void remove(Transaksi* t) {
        if (!head || !t) return;
        if (head == t) { 
            head = head->next; 
            delete t;
            return; 
        }
        Transaksi* curr = head;
        while (curr->next && curr->next != t) 
            curr = curr->next;
        if (curr->next) {
            curr->next = t->next;
            delete t;
        }
    }
};
struct QueueNode {
    string nama, poli, idDokter, diagnosa, jadwal, pembayaran;
    int umur;
    QueueNode* next;
    
    QueueNode(string n, string p, string idD, string d, string j, string by, int u)
        : nama(n), poli(p), idDokter(idD), diagnosa(d), jadwal(j), pembayaran(by), umur(u), next(nullptr) {}
};

struct QueuePasien {
    QueueNode* front;
    QueueNode* rear;
    
    QueuePasien() : front(nullptr), rear(nullptr) {}

    void enqueue(string nama, string poli, string idDokter, string diagnosa, string jadwal, string pembayaran, int umur) {
        QueueNode* baru = new QueueNode(nama, poli, idDokter, diagnosa, jadwal, pembayaran, umur);
        
        if (!rear) 
            front = rear = baru;
        else {
            rear->next = baru;
            rear = baru;
        }
    }

    QueueNode* dequeue() {
        if (!front) 
            return nullptr;
            
        QueueNode* q = front;
        front = front->next;
        
        if (!front) 
            rear = nullptr;
            
        return q;
    }

    bool kosong() { 
        return front == nullptr; 
    }

    void tampil() {
        QueueNode* curr = front;
        int i = 1;
        
        if (!curr) {
            cout << "(Belum ada pasien mendaftar)\n";
            return;
        }
        
        while (curr) {
            cout << i << ". " << curr->nama << " (" << curr->poli << ", " << curr->diagnosa << ")\n";
            curr = curr->next;
            i++;
        }
    }
};

struct StokObat {
    string kode;
    int jumlah;
    StokObat* next;
    
    StokObat(string k, int j) : kode(k), jumlah(j), next(nullptr) {}
};

struct ListStokObat {
    StokObat* head;
    
    ListStokObat() : head(nullptr) {}

    void tambah(string kode, int jumlah) {
        StokObat* curr = head;
        
        while (curr) {
            if (curr->kode == kode) {
                curr->jumlah += jumlah;
                return;
            }
            curr = curr->next;
        }
        
        StokObat* baru = new StokObat(kode, jumlah);
        baru->next = head;
        head = baru;
    }

    bool kurangi(string kode, int jml) {
        StokObat* curr = head;
        
        while (curr) {
            if (curr->kode == kode && curr->jumlah >= jml) {
                curr->jumlah -= jml;
                return true;
            }
            curr = curr->next;
        }
        return false;
    }

    int getStok(string kode) {
        StokObat* curr = head;
        
        while (curr) {
            if (curr->kode == kode) 
                return curr->jumlah;
            curr = curr->next;
        }
        return 0;
    }

    void tampil(BSTObat& obat) {
        cout << "--------------------------------------\n";
        cout << setw(10) << "Kode" << setw(25) << "Nama Obat/Perawatan" << setw(10) << "Stok" << endl;
        cout << "--------------------------------------\n";
        
        StokObat* curr = head;
        while (curr) {
            Obat* o = obat.cariObat(curr->kode);
            cout << setw(10) << curr->kode
                 << setw(25) << (o ? o->nama : "-")
                 << setw(10) << curr->jumlah << endl;
            curr = curr->next;
        }
    }
};

struct RiwayatMedis {
    string nama, diagnosa, dokter, jadwal;
    int umur;
    RiwayatMedis* next;
    
    RiwayatMedis(string n, string d, string dok, string j, int u)
        : nama(n), diagnosa(d), dokter(dok), jadwal(j), umur(u), next(nullptr) {}
};

struct ListRiwayat {
    RiwayatMedis* head;
    
    ListRiwayat() : head(nullptr) {}

    void tambah(string nama, string diag, string dokter, string jadwal, int umur) {
        RiwayatMedis* r = new RiwayatMedis(nama, diag, dokter, jadwal, umur);
        r->next = head;
        head = r;
    }

    void tampilSortUmur() {
        int n = 0;
        RiwayatMedis* curr = head;
        
        while (curr) { 
            n++; 
            curr = curr->next; 
        }
        
        if (n == 0) {
            cout << "(Belum ada riwayat medis pasien)\n";
            return;
        }
        
        RiwayatMedis** arr = new RiwayatMedis*[n];
        curr = head;
        int i = 0;
        
        while (curr) { 
            arr[i++] = curr; 
            curr = curr->next; 
        }
        
        sort(arr, arr + n, [](RiwayatMedis* a, RiwayatMedis* b) { 
            return a->umur > b->umur; 
        });
        
        cout << "---------------------------------------------\n";
        cout << setw(20) << "Nama" << setw(10) << "Umur" << setw(15) << "Diagnosa" << setw(18) << "Dokter" << endl;
        cout << "---------------------------------------------\n";
        
        for (int j = 0; j < n; ++j) {
            cout << setw(20) << arr[j]->nama
                 << setw(10) << arr[j]->umur
                 << setw(15) << arr[j]->diagnosa
                 << setw(18) << arr[j]->dokter << endl;
        }
        delete[] arr;
    }
};

void inisialisasiObat(BSTObat& obat, Graph& graph) {
    obat.tambah("OB001", "Paracetamol", 15000, true);
    obat.tambah("OB002", "Cetirizine", 25000, true);
    obat.tambah("OB003", "Ambroxol", 20000, true);
    obat.tambah("OB004", "Dextromethorphan", 18000, true);
    obat.tambah("OB005", "Ibuprofen", 20000, true);
    obat.tambah("OB006", "Vitamin C", 24000, false);

    obat.tambah("DG004", "Pembersihan Karang Gigi", 300000, false);
    obat.tambah("DG005", "Vitamin C", 30000, false);
    obat.tambah("DG006", "Betadine Gargle", 20000, true);
    obat.tambah("DG007", "Scaling Gigi", 400000, false);
    obat.tambah("DG008", "Obat Kumur", 50000, false);
    obat.tambah("DG009", "Pemasangan Behel", 5000000, false);
    obat.tambah("DG010", "Wax Ortho", 50000, false);
    obat.tambah("DG011", "Pasta Gigi Khusus", 75000, false);

    graph.tambah("Flu", "OB001"); 
    graph.tambah("Flu", "OB002");
    graph.tambah("Batuk", "OB003"); 
    graph.tambah("Batuk", "OB004");
    graph.tambah("Demam", "OB001"); 
    graph.tambah("Demam", "OB005");
    graph.tambah("Flu, Batuk", "OB001"); 
    graph.tambah("Flu, Batuk", "OB003");
    graph.tambah("Flu, Batuk, Demam", "OB001"); 
    graph.tambah("Flu, Batuk, Demam", "OB003"); 
    graph.tambah("Flu, Batuk, Demam", "OB005");
    graph.tambah("Radang Tenggorokan", "OB005");
    graph.tambah("Kulit Gatal2", "OB002");

    // Relasi diagnosa/perawatan gigi
    graph.tambah("Perawatan Gigi Bolong", "DG004");
    graph.tambah("Perawatan Gigi Bolong", "DG005");
    graph.tambah("Perawatan Gigi Bolong", "DG006");
    graph.tambah("Perawatan Scalling", "DG007");
    graph.tambah("Perawatan Scalling", "DG008");
    graph.tambah("Perawatan Behel", "DG009");
    graph.tambah("Perawatan Behel", "DG010");
    graph.tambah("Perawatan Behel", "DG011");
}

void inisialisasiDokter(HashDokter& hd) {
    string j1[] = {"Senin 08:00-16:00", "Rabu 08:00-16:00", "Jumat 08:00-16:00"};
    string j2[] = {"Selasa 10:00-15:00", "Kamis 10:00-15:00"};
    hd.tambah("UH001", "Dr. Dea", "Umum", "Klinik Hayati", j1, 3);
    hd.tambah("UR002", "Dr. Jean", "Umum", "Klinik Royal", j2, 2);

    string jg1[] = {"Senin 13:00-19:00", "Rabu 13:00-19:00"};
    string jg2[] = {"Jumat 09:00-17:00", "Sabtu 09:00-13:00"};
    hd.tambah("GH003", "Dr. Nico", "Gigi", "Klinik Hayati", jg1, 2);
    hd.tambah("GR004", "Dr. Gavriel", "Gigi", "Klinik Royal", jg2, 2);
}

string diagnosaUmumList[] = {
    "Flu", "Batuk", "Demam", "Flu, Batuk", "Flu, Batuk, Demam", "Radang Tenggorokan", "Kulit Gatal2"
};
int diagnosaUmumCount = 7;

string perawatanGigiList[] = {
    "Perawatan Gigi Bolong",
    "Perawatan Gusi Berdarah",
    "Perawatan Scalling",
    "Perawatan Behel"
};
int perawatanGigiCount = 4;

string pembayaranList[] = {"Asuransi Swasta", "Pribadi", "BPJS"};

BSTObat dataObat;
Graph dataGraph;
HashDokter dataDokter;
ListStokObat listStok;
QueuePasien antrian;
ListTransaksi pembayaran;
ListRiwayat riwayatMedis;

void updateStokResep(StackResep& resep) {
    ResepNode* curr = resep.top;
    
    while (curr) {
        listStok.kurangi(curr->kode, 1); 
        curr = curr->next;
    }
}

int main() {
    inisialisasiObat(dataObat, dataGraph);
    inisialisasiDokter(dataDokter);

    string allKode[] = {"OB001","OB002","OB003","OB004","OB005","OB006",
                        "DG004","DG005","DG006","DG007","DG008","DG009","DG010","DG011"};
    int nObat = 14;
    
    for (int i = 0; i < nObat; ++i) 
        listStok.tambah(allKode[i], 10);

    int pil;
    do {
        cout << "\n=== Sistem Manajemen Klinik ===\n";
        cout << "1. Tenaga Medis\n2. Pasien\n3. Kasir\n4. Keluar\n";
        cout << "Pilihan (1-4): "; 
        cin >> pil; 
        cin.ignore();
        
        if (pil == 1) {
            int pilMedis;
            do {
                cout << "\n=== MENU TENAGA MEDIS ===\n";
                cout << "1. Data Pendaftaran Pasien\n";
                cout << "2. Jadwal Dokter\n";
                cout << "3. Stock Obat\n";
                cout << "4. Pembelian Obat\n";
                cout << "5. Riwayat Medis Pasien\n";
                cout << "6. Kembali\n";
                cout << "Pilihan (1-6): "; 
                cin >> pilMedis; 
                cin.ignore();
                
                if (pilMedis == 1) {
                    cout << "\n=== Data Pendaftaran Pasien ===\n";
                    antrian.tampil();
                } 
                else if (pilMedis == 2) {
                    cout << "\n=== Jadwal Dokter ===\n";
                    cout << "-- Dokter Umum --\n"; 
                    dataDokter.tampilPoli("Umum");
                    cout << "-- Dokter Gigi --\n"; 
                    dataDokter.tampilPoli("Gigi");
                } 
                else if (pilMedis == 3) {
                    cout << "\n=== Stock Obat ===\n";
                    listStok.tampil(dataObat);
                } 
                else if (pilMedis == 4) {
                    cout << "\n=== Pembelian Obat (Penambahan Stock) ===\n";
                    listStok.tampil(dataObat);
                    cout << "Input kode obat untuk ditambah stok: "; 
                    string kode; 
                    getline(cin, kode);
                    
                    Obat* o = dataObat.cariObat(kode);
                    if (!o) { 
                        cout << "Obat tidak ada!\n"; 
                        continue; 
                    }
                    
                    cout << "Tambah stok berapa: "; 
                    int jml; 
                    cin >> jml; 
                    cin.ignore();
                    listStok.tambah(kode, jml);
                    cout << "Stok berhasil ditambah.\n";
                } 
                else if (pilMedis == 5) {
                    cout << "\n=== Riwayat Medis Pasien ===\n";
                    riwayatMedis.tampilSortUmur();
                }
            } while (pilMedis != 6);
        }
        else if (pil == 2) {
            int pilPasien;
            do {
                cout << "\n=== MENU PASIEN ===\n";
                cout << "1. Pendaftaran Pasien Baru\n";
                cout << "2. Proses Pemeriksaan Pasien\n";
                cout << "3. Kembali\n";
                cout << "Pilihan (1-3): "; 
                cin >> pilPasien; 
                cin.ignore();
                
                if (pilPasien == 1) {
                    cout << "\n=== Pendaftaran Pasien ===\n";
                    string nama, jk, riwayat;
                    int umur;
                    
                    cout << "Nama Pasien: "; 
                    getline(cin, nama);
                    cout << "Jenis Kelamin (L/P): "; 
                    getline(cin, jk);
                    cout << "Umur: "; 
                    cin >> umur; 
                    cin.ignore();
                    cout << "Riwayat Penyakit: "; 
                    getline(cin, riwayat);
                    
                    int jenisD;
                    cout << "\nPilih Jenis Dokter:\n1. Dokter Umum\n2. Dokter Gigi\nPilihan (1-2): "; 
                    cin >> jenisD; 
                    cin.ignore();
                    
                    string poli = (jenisD == 1) ? "Umum" : "Gigi";
                    Dokter* arr[5]; 
                    int nDok = dataDokter.listPoli(poli, arr);
                    
                    cout << "\nDaftar Dokter " << poli << ":\n";
                    dataDokter.tampilPoli(poli);
                    
                    cout << "\nPilih dokter (1-" << nDok << "): "; 
                    int idx; 
                    cin >> idx; 
                    cin.ignore();
                    
                    Dokter* d = arr[idx - 1];
                    cout << "\nJadwal Praktik " << d->nama << ":\n";
                    
                    Jadwal* j = d->jadwal;
                    string jadwalArr[10]; 
                    int nJad = 0;
                    
                    while (j) { 
                        cout << nJad + 1 << ". " << j->hariJam << endl; 
                        jadwalArr[nJad++] = j->hariJam; 
                        j = j->next;
                    }
                    
                    cout << "Pilih jadwal (1-" << nJad << "): "; 
                    int jdx; 
                    cin >> jdx; 
                    cin.ignore();
                    
                    string jwl = jadwalArr[jdx - 1];
                    string diagnosa;
                    
                    if (poli == "Umum") {
                        cout << "\nPilih Diagnosa:\n";
                        for (int i = 0; i < diagnosaUmumCount; ++i)
                            cout << i + 1 << ". " << diagnosaUmumList[i] << endl;
                            
                        cout << "Pilihan (1-" << diagnosaUmumCount << "): "; 
                        int dx; 
                        cin >> dx; 
                        cin.ignore();
                        diagnosa = diagnosaUmumList[dx - 1];
                    } 
                    else {
                        cout << "\nPilih Jenis Perawatan:\n";
                        for (int i = 0; i < perawatanGigiCount; ++i)
                            cout << i + 1 << ". " << perawatanGigiList[i] << endl;
                            
                        cout << "Pilihan (1-" << perawatanGigiCount << "): "; 
                        int dx; 
                        cin >> dx; 
                        cin.ignore();
                        diagnosa = perawatanGigiList[dx - 1];
                    }
                    
                    cout << "\nPilih Jenis Pembayaran:\n";
                    for (int i = 0; i < 3; ++i) 
                        cout << i + 1 << ". " << pembayaranList[i] << endl;
                        
                    cout << "Pilihan (1-3): "; 
                    int py; 
                    cin >> py; 
                    cin.ignore();
                    
                    string by = pembayaranList[py - 1];
                    antrian.enqueue(nama, poli, d->id, diagnosa, jwl, by, umur);
                    cout << "\nPendaftaran berhasil!\n";
                } 
                else if (pilPasien == 2) {
                    cout << "\n=== Proses Pemeriksaan ===\n";
                    
                    if (antrian.kosong()) { 
                        cout << "Tidak ada pasien dalam antrian.\n"; 
                        continue; 
                    }
                    
                    QueueNode* q = antrian.dequeue();
                    Dokter* d = dataDokter.dapatkan(q->idDokter);
                    
                    cout << "Nama Pasien: " << q->nama << endl;
                    cout << "Diagnosa/Perawatan: " << q->diagnosa << endl;
                    cout << "Dokter: " << (d ? d->nama : "-") << endl;
                    cout << "Waktu Berobat: " << q->jadwal << endl;
                    cout << "Jenis Pembayaran: " << q->pembayaran << endl;
                    
                    GraphNode* g = dataGraph.cari(q->diagnosa);
                    StackResep resep;
                    
                    if (g) {
                        for (int i = 0; i < g->nObat; ++i) {
                            Obat* o = dataObat.cariObat(g->kodeObat[i]);
                            if (o && listStok.getStok(o->kode) > 0)
                                resep.push(o->kode, o->nama, o->harga, o->bpjs);
                        }
                    }
                    
                    cout << "\nResep/Perawatan:\n";
                    resep.tampil();
                    
                    float total = resep.total();
                    if (q->pembayaran == "BPJS") 
                        total = 0;
                        
                    cout << "\nTotal Biaya: Rp" << fixed << setprecision(2) << total << endl;
                    cout << "\nSilakan menuju kasir untuk pembayaran.\n";
                    
                    pembayaran.tambah(q->nama, q->diagnosa, (d ? d->nama : "-"), q->jadwal, q->pembayaran, resep, total);
                    riwayatMedis.tambah(q->nama, q->diagnosa, (d ? d->nama : "-"), q->jadwal, q->umur);
                }
            } while (pilPasien != 3);
        }
        else if (pil == 3) {
            cout << "\n=== Daftar Pasien yang Perlu Pembayaran ===\n";
            
            if (!pembayaran.head) { 
                cout << "Tidak ada pembayaran tertunda.\n"; 
                continue; 
            }
            
            pembayaran.tampilDaftar();
            cout << "\nPilih pasien untuk diproses (1-99): "; 
            int idx; 
            cin >> idx; 
            cin.ignore();
            
            Transaksi* t = pembayaran.getByIdx(idx);
            if (!t) { 
                cout << "Pasien tidak ditemukan.\n"; 
                continue; 
            }
            
            cout << "\n=== Detail Pembayaran ===\n";
            cout << "Nama Pasien: " << t->nama << endl
                 << "Diagnosa/Perawatan: " << t->diagnosa << endl
                 << "Jenis Pembayaran: " << t->jenisPembayaran << endl;
                 
            cout << "\nRincian Obat/Perawatan:\n";
            t->resep.tampil();
            
            cout << "\nTotal Biaya: Rp" << fixed << setprecision(2) << t->total << endl;
            cout << "\nPilih metode pembayaran:\n1. Tunai\n2. Kartu Debit/Kredit\n3. Transfer Bank\nPilihan (1-3): ";
            int mtd; 
            cin >> mtd; 
            cin.ignore();
            
            if (t->total > 0) {
                cout << "Masukkan jumlah uang yang dibayarkan: Rp"; 
                float byr; 
                cin >> byr; 
                cin.ignore();
                
                if (byr < t->total) { 
                    cout << "Uang tidak cukup!\n"; 
                    continue; 
                }
            }
            
            updateStokResep(t->resep);
            cout << "\nPembayaran berhasil diproses. Terima kasih.\n";
            pembayaran.remove(t);
        }
    } while (pil != 4);
    
    cout << "Terima kasih telah menggunakan sistem kami.\n";
    return 0;
}
