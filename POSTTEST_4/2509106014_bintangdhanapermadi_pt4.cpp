#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

#define MAX 100

using namespace std;

struct Kereta {
    int noKereta;
    string nama;
    string asal;
    string tujuan;
    int harga;
};

struct Transaksi {
    string namaPenumpang;
    Kereta kereta;
};


struct QueueNode {
    Transaksi data;
    QueueNode *next;
};

QueueNode *qFront = nullptr;
QueueNode *qRear  = nullptr;

struct StackNode {
    Transaksi data;
    StackNode *next;
};

StackNode *sTop = nullptr;

void swapKereta(Kereta* a, Kereta* b) {
    Kereta temp = *a;
    *a = *b;
    *b = temp;
}

void tampilJadwal(Kereta* arr, int n) {
    cout << "\n===============================================================================\n";
    cout << "| No. Kereta | Nama Kereta       | Asal            | Tujuan          | Harga    |\n";
    cout << "===============================================================================\n";
    for (int i = 0; i < n; i++) {
        cout << "| " << left << setw(10) << arr[i].noKereta
            << " | " << left << setw(17) << arr[i].nama
            << " | " << left << setw(15) << arr[i].asal
            << " | " << left << setw(15) << arr[i].tujuan
            << " | Rp " << left << setw(7) << arr[i].harga << "|\n";
    }
    cout << "===============================================================================\n";
}

void tambahKereta(Kereta* arr, int* n) {
    cout << "\n--- Tambah Data Kereta Baru ---\n";
    cout << "Nomor Kereta : "; cin >> arr[*n].noKereta;
    cin.ignore();
    cout << "Nama Kereta  : "; getline(cin, arr[*n].nama);
    cout << "Asal         : "; getline(cin, arr[*n].asal);
    cout << "Tujuan       : "; getline(cin, arr[*n].tujuan);
    cout << "Harga Tiket  : "; cin >> arr[*n].harga;
    (*n)++;
    cout << "Data berhasil ditambahkan!\n";
}

void linearSearchRute(Kereta* arr, int n, string asal, string tujuan) {
    bool found = false;
    cout << "\nHasil Pencarian Rute: " << asal << " -> " << tujuan << "\n";
    cout << "===============================================================================\n";
    for (int i = 0; i < n; i++) {
        if (arr[i].asal == asal && arr[i].tujuan == tujuan) {
            cout << "- No: " << arr[i].noKereta << " | " << arr[i].nama
                << " | Rp " << arr[i].harga << "\n";
            found = true;
        }
    }
    if (!found) cout << "Kereta dengan rute tersebut tidak ditemukan.\n";
    cout << "===============================================================================\n";
}

void sortNoKereta(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++)
        for (int j = 0; j < n - i - 1; j++)
            if (arr[j].noKereta > arr[j + 1].noKereta)
                swapKereta(&arr[j], &arr[j + 1]);
}

Kereta* jumpSearchNoKereta(Kereta* arr, int n, int cariNo, bool silent = false) {
    sortNoKereta(arr, n);
    int step = sqrt(n);
    int prev = 0;
    while (arr[min(step, n) - 1].noKereta < cariNo) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            if (!silent) cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
            return nullptr;
        }
    }
    while (arr[prev].noKereta < cariNo) {
        prev++;
        if (prev == min(step, n)) {
            if (!silent) cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
            return nullptr;
        }
    }
    if (arr[prev].noKereta == cariNo) {
        if (!silent) {
            cout << "\n[Kereta Ditemukan!]\n";
            cout << "No. Kereta : " << arr[prev].noKereta << "\n"
                << "Nama       : " << arr[prev].nama << "\n"
                << "Rute       : " << arr[prev].asal << " -> " << arr[prev].tujuan << "\n"
                << "Harga      : Rp " << arr[prev].harga << "\n";
        }
        return &arr[prev];
    } else {
        if (!silent) cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
        return nullptr;
    }
}

void merge(Kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1, n2 = right - mid;
    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];
    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) { arr[k] = L[i]; i++; }
        else                         { arr[k] = R[j]; j++; }
        k++;
    }
    while (i < n1) { arr[k] = L[i]; i++; k++; }
    while (j < n2) { arr[k] = R[j]; j++; k++; }
    delete[] L;
    delete[] R;
}

void mergeSortNama(Kereta* arr, int left, int right) {
    if (left >= right) return;
    int mid = left + (right - left) / 2;
    mergeSortNama(arr, left, mid);
    mergeSortNama(arr, mid + 1, right);
    merge(arr, left, mid, right);
}

void selectionSortHarga(Kereta* arr, int n) {
    for (int i = 0; i < n - 1; i++) {
        int min_idx = i;
        for (int j = i + 1; j < n; j++)
            if (arr[j].harga < arr[min_idx].harga)
                min_idx = j;
        if (min_idx != i) swapKereta(&arr[min_idx], &arr[i]);
    }
}


bool isQueueEmpty(QueueNode *front) {
    return front == nullptr;
}

void enqueue(QueueNode *&front, QueueNode *&rear, Transaksi dataBaru) {
    // Buat node baru
    QueueNode *nodeBaru = new QueueNode;
    nodeBaru->data = dataBaru;
    nodeBaru->next = nullptr;

    if (isQueueEmpty(front)) {
        front = nodeBaru;
        rear  = nodeBaru;
    } else {
        rear->next = nodeBaru;
        rear       = nodeBaru;
    }
    cout << "[Antrian] " << dataBaru.namaPenumpang
        << " berhasil masuk antrian (KA " << dataBaru.kereta.nama << ").\n";
}

void dequeue(QueueNode *&front, QueueNode *&rear, StackNode *&top) {
    // Cek apakah antrian kosong
    if (isQueueEmpty(front)) {
        cout << ">> Antrian kosong, tidak ada yang bisa diproses. <<\n";
        return;
    }

    QueueNode *temp = front;
    Transaksi value = temp->data;

    cout << "\n[Proses Tiket]\n";
    cout << "Memproses tiket untuk : " << value.namaPenumpang << "\n";
    cout << "KA Pilihan            : " << value.kereta.nama
        << " (" << value.kereta.asal << " -> " << value.kereta.tujuan << ")\n";

    front = front->next;
    if (front == nullptr) rear = nullptr;

    delete temp;

    StackNode *nodeBaru = new StackNode;
    nodeBaru->data = value;
    nodeBaru->next = top;
    top = nodeBaru;
    cout << "[Riwayat] " << value.namaPenumpang << " ditambahkan ke riwayat.\n";
}

void peekQueue(QueueNode *front) {
    if (isQueueEmpty(front)) {
        cout << "  Antrian kosong.\n";
    } else {
        cout << "  Antrian Terdepan : " << front->data.namaPenumpang
            << " (KA " << front->data.kereta.nama << ")\n";
    }
}

void displayQueue(QueueNode *front) {
    if (isQueueEmpty(front)) {
        cout << ">> Antrian kosong <<\n";
        return;
    }
    cout << "\n--- Daftar Antrian Tiket ---\n";
    QueueNode *temp = front;
    int no = 1;
    while (temp != nullptr) {
        cout << no++ << ". " << temp->data.namaPenumpang
            << " | " << temp->data.kereta.asal
            << " -> " << temp->data.kereta.tujuan
            << " | KA " << temp->data.kereta.nama << "\n";
        temp = temp->next;
    }
    cout << "NULL\n";
}


bool isStackEmpty(StackNode *top) {
    return top == nullptr;
}

void push(StackNode *&top, Transaksi dataBaru) {
    // Buat node baru
    StackNode *nodeBaru = new StackNode;
    nodeBaru->data = dataBaru;
    nodeBaru->next = top;
    top = nodeBaru;
    cout << "[Stack] " << dataBaru.namaPenumpang << " di-push ke riwayat.\n";
}

void pop(StackNode *&top) {
    if (isStackEmpty(top)) {
        cout << ">> Riwayat kosong, tidak ada yang bisa dibatalkan. <<\n";
        return;
    }

    StackNode *temp = top;
    Transaksi value = temp->data;

    top = top->next;
    delete temp;

    cout << "[Info] Transaksi untuk " << value.namaPenumpang
        << " (KA " << value.kereta.nama << ") berhasil dibatalkan dari riwayat.\n";
}

void peekStack(StackNode *top) {
    if (isStackEmpty(top)) {
        cout << "  Riwayat kosong.\n";
    } else {
        cout << "  Riwayat Teratas  : " << top->data.namaPenumpang
            << " (KA " << top->data.kereta.nama << ")\n";
    }
}

void displayStack(StackNode *top) {
    if (isStackEmpty(top)) {
        cout << ">> Riwayat kosong <<\n";
        return;
    }
    cout << "\n--- Riwayat Transaksi (Top -> Bottom) ---\n";
    StackNode *temp = top;
    int no = 1;
    while (temp != nullptr) {
        cout << no++ << ". " << temp->data.namaPenumpang
            << " | " << temp->data.kereta.asal
            << " -> " << temp->data.kereta.tujuan
            << " | KA " << temp->data.kereta.nama << "\n";
        temp = temp->next;
    }
    cout << "NULL\n";
}

int main() {
    Kereta daftarKereta[MAX] = {
        {101, "Argo Bromo",  "Jakarta",  "Surabaya",   600000},
        {205, "Parahyangan", "Bandung",  "Yogyakarta", 550000},
        {112, "Turangga",    "Surabaya", "Cirebon",    450000},
        {302, "Matarmaja",   "Malang",   "Jakarta",    250000}
    };
    int jumlahKereta = 4;


    int pilihan;

    do {
        cout << "\n============================================\n";
        cout << "  SISTEM MANAJEMEN KEBERANGKATAN KERETA API \n";
        cout << "============================================\n";
        cout << "1.  Tampil Jadwal Semua Kereta\n";
        cout << "2.  Tambah Data Kereta\n";
        cout << "3.  Cari Kereta (Rute)\n";
        cout << "4.  Cari Kereta (No. Kereta)\n";
        cout << "5.  Urutkan Nama Kereta A-Z\n";
        cout << "6.  Urutkan Harga Termurah\n";
        cout << "--- TRANSAKSI (QUEUE & STACK - Single Linked List) ---\n";
        cout << "7.  Masuk Antrian Tiket  (Enqueue)\n";
        cout << "8.  Proses Tiket         (Dequeue -> Push Stack)\n";
        cout << "9.  Lihat Daftar Antrian (Display Queue)\n";
        cout << "10. Lihat Riwayat Proses (Display Stack)\n";
        cout << "11. Batalkan Riwayat     (Pop Stack)\n";
        cout << "12. Lihat Elemen Ujung   (Peek Queue & Stack)\n";
        cout << "0.  Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1:
                tampilJadwal(daftarKereta, jumlahKereta);
                break;

            case 2:
                tambahKereta(daftarKereta, &jumlahKereta);
                break;

            case 3: {
                string asal, tujuan;
                cin.ignore();
                cout << "Masukkan Stasiun Asal   : "; getline(cin, asal);
                cout << "Masukkan Stasiun Tujuan : "; getline(cin, tujuan);
                linearSearchRute(daftarKereta, jumlahKereta, asal, tujuan);
                break;
            }

            case 4: {
                int no;
                cout << "Masukkan Nomor Kereta: "; cin >> no;
                jumpSearchNoKereta(daftarKereta, jumlahKereta, no);
                break;
            }

            case 5:
                mergeSortNama(daftarKereta, 0, jumlahKereta - 1);
                cout << "\n[Info] Data diurutkan berdasarkan Nama Kereta (A-Z)!\n";
                tampilJadwal(daftarKereta, jumlahKereta);
                break;

            case 6:
                selectionSortHarga(daftarKereta, jumlahKereta);
                cout << "\n[Info] Data diurutkan berdasarkan Harga Termurah!\n";
                tampilJadwal(daftarKereta, jumlahKereta);
                break;

            case 7: {
                int noKA;
                Transaksi tBaru;
                cin.ignore();
                cout << "Nama Penumpang : "; getline(cin, tBaru.namaPenumpang);
                cout << "No. Kereta     : "; cin >> noKA;
                Kereta* ka = jumpSearchNoKereta(daftarKereta, jumlahKereta, noKA, true);
                if (ka != nullptr) {
                    tBaru.kereta = *ka;
                    enqueue(qFront, qRear, tBaru);
                } else {
                    cout << "Kereta tidak ditemukan, gagal masuk antrian.\n";
                }
                break;
            }

            case 8:
                dequeue(qFront, qRear, sTop);
                break;

            case 9:
                displayQueue(qFront);
                break;

            case 10:
                displayStack(sTop);
                break;

            case 11:
                pop(sTop);
                break;

            case 12:
                cout << "\n--- PEEK ---\n";
                peekQueue(qFront);
                peekStack(sTop);
                break;

            case 0:
                cout << "\nTerima kasih telah menggunakan sistem ini.\n";
                break;

            default:
                cout << "\nPilihan tidak valid, silakan coba lagi!\n";
        }
    } while (pilihan != 0);

    return 0;
}
