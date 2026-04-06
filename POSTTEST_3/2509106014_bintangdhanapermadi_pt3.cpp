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
    cout << "Nomor Kereta : ";
    cin >> arr[*n].noKereta;
    cin.ignore();
    cout << "Nama Kereta  : ";
    getline(cin, arr[*n].nama);
    cout << "Asal         : ";
    getline(cin, arr[*n].asal);
    cout << "Tujuan       : ";
    getline(cin, arr[*n].tujuan);
    cout << "Harga Tiket  : ";
    cin >> arr[*n].harga;

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
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if(arr[j].noKereta > arr[j + 1].noKereta) {
                swapKereta(&(arr[j]), &(arr[j + 1]));
            }
        }
    }
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
            return NULL;
        }
    }

    while (arr[prev].noKereta < cariNo) {
        prev++;
        if (prev == min(step, n)) {
            if (!silent) cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
            return NULL;
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
        return NULL;
    }
}

void merge(Kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[left + i];
    for (int j = 0; j < n2; j++) R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++; k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++; k++;
    }

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
        for (int j = i + 1; j < n; j++) {
            if (arr[j].harga < arr[min_idx].harga) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapKereta(&(arr[min_idx]), &(arr[i]));
        }
    }
}

bool isStackEmpty(int top) {
    return (top < 0);
}

void push(Transaksi stack[], int &top, Transaksi value) {
    if (top >= MAX - 1) {
        cout << "Stack overflow\n";
    } else {
        top++;
        stack[top] = value;
        cout << value.namaPenumpang << " pushed into stack\n";
    }
}

void pop(Transaksi stack[], int &top) {
    if (isStackEmpty(top)) {
        cout << "Stack underflow\n";
    } else {
        Transaksi value = stack[top];
        top--;
        cout << "[Info] Transaksi untuk " << value.namaPenumpang << " berhasil dibatalkan (Pop).\n";
    }
}

void peekStack(Transaksi stack[], int top) {
    if (isStackEmpty(top)) {
        cout << "Stack is empty\n";
    } else {
        cout << "- Riwayat Teratas : " << stack[top].namaPenumpang 
            << " (KA " << stack[top].kereta.nama << ")\n";
    }
}

void displayStack(Transaksi stack[], int top) {
    if (isStackEmpty(top)) {
        cout << "Stack is empty\n";
        return;
    }
    cout << "\n--- Riwayat Transaksi (Top to Bottom) ---\n";
    for (int i = top; i >= 0; i--) {
        cout << top - i + 1 << ". " << stack[i].namaPenumpang 
            << " | " << stack[i].kereta.asal << " -> " << stack[i].kereta.tujuan << "\n";
    }
}

bool isQueueFull(int rear) {
    return rear == MAX - 1;
}

bool isQueueEmpty(int front, int rear) {
    return front == -1 || front > rear;
}

void enqueue(Transaksi queue[], int &front, int &rear, Transaksi value) {
    if (isQueueFull(rear)) {
        cout << "Queue overflow\n";
        return;
    }
    if (front == -1) {
        front = 0;
    }
    rear++;
    queue[rear] = value;
    cout << value.namaPenumpang << " enqueued into queue\n";
}

void dequeue(Transaksi queue[], int &front, int &rear, Transaksi stack[], int &top) {
    if (isQueueEmpty(front, rear)) {
        cout << "Queue underflow\n";
        return;
    }

    Transaksi value = queue[front];
    
    cout << "\n[Proses Tiket]\n";
    cout << "Memproses tiket untuk : " << value.namaPenumpang << "\n";
    cout << "KA Pilihan            : " << value.kereta.nama << " (" << value.kereta.asal << "-" << value.kereta.tujuan << ")\n";
    
    front++;
    
    if (isQueueEmpty(front, rear)) {
        front = -1;
        rear = -1;
    }
    
    push(stack, top, value);
}

void peekQueue(Transaksi queue[], int front, int rear) {
    if (isQueueEmpty(front, rear)) {
        cout << "Queue is empty\n";
    } else {
        cout << "- Antrian Terdepan: " << queue[front].namaPenumpang 
             << " (KA " << queue[front].kereta.nama << ")\n";
    }
}

void displayQueue(Transaksi queue[], int front, int rear) {
    if (isQueueEmpty(front, rear)) {
        cout << "Queue is empty\n";
        return;
    }
    cout << "\nQueue elements: \n";
    for (int i = front; i <= rear; i++) {
        cout << i - front + 1 << ". Penumpang: " << queue[i].namaPenumpang 
            << " | Tujuan: " << queue[i].kereta.tujuan << "\n";
    }
}

int main() {
    Kereta daftarKereta[MAX] = {
        {101, "Argo Bromo", "Jakarta", "Surabaya", 600000},
        {205, "Parahyangan", "Bandung", "Yogyakarta", 550000},
        {112, "Turangga", "Surabaya", "Cirebon", 450000},
        {302, "Matarmaja", "Malang", "Jakarta", 250000}
    };
    int jumlahKereta = 4;
    
    Transaksi queueAntrian[MAX];
    int qFront = -1, qRear = -1;
    
    Transaksi stackRiwayat[MAX];
    int sTop = -1;
    
    int pilihan;
    
    do {
        cout << "\n============================================\n";
        cout << "  SISTEM MANAJEMEN KEBERANGKATAN KERETA API \n";
        cout << "============================================\n";
        cout << "1. Tampil Jadwal Semua Kereta\n";
        cout << "2. Tambah Data Kereta\n";
        cout << "3. Cari Kereta (Rute)\n";
        cout << "4. Cari Kereta (No. Kereta)\n";
        cout << "5. Urutkan Nama Kereta A-Z\n";
        cout << "6. Urutkan Harga Termurah\n";
        cout << "--- TRANSAKSI (QUEUE & STACK) ---\n";
        cout << "7. Masuk Antrian Tiket (Enqueue)\n";
        cout << "8. Proses Tiket (Dequeue -> Push Stack)\n";
        cout << "9. Lihat Daftar Antrian (Display Queue)\n";
        cout << "10. Lihat Riwayat Proses (Display Stack)\n";
        cout << "11. Batalkan Riwayat Terakhir (Pop Stack)\n";
        cout << "12. Lihat Elemen Ujung (Peek)\n";
        cout << "0. Keluar\n";
        cout << "Pilih menu: ";
        cin >> pilihan;

        switch (pilihan) {
            case 1: tampilJadwal(daftarKereta, jumlahKereta); break;
            case 2: tambahKereta(daftarKereta, &jumlahKereta); break;
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
                cout << "Masukkan Nomor Kereta yang dicari: "; cin >> no;
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
                if (ka != NULL) {
                    tBaru.kereta = *ka;
                    enqueue(queueAntrian, qFront, qRear, tBaru);
                } else {
                    cout << "Kereta tidak ditemukan, gagal masuk antrian.\n";
                }
                break;
            }
            case 8: 
                dequeue(queueAntrian, qFront, qRear, stackRiwayat, sTop); 
                break;
            case 9: 
                displayQueue(queueAntrian, qFront, qRear); 
                break;
            case 10: 
                displayStack(stackRiwayat, sTop); 
                break;
            case 11: 
                pop(stackRiwayat, sTop); 
                break;
            case 12: 
                cout << "\n--- PEEK ---\n";
                peekQueue(queueAntrian, qFront, qRear);
                peekStack(stackRiwayat, sTop);
                break;
            case 0: cout << "\nTerima kasih telah menggunakan sistem ini.\n"; break;
            default: cout << "\nPilihan tidak valid, silakan coba lagi!\n";
        }
    } while (pilihan != 0);

    return 0;
}