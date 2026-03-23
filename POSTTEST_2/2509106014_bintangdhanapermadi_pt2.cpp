#include <iostream>
#include <string>
#include <cmath>
#include <iomanip>

using namespace std;

struct Kereta {
    int noKereta;
    string nama;
    string asal;
    string tujuan;
    int harga;
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
        cout << "| " << left << setw(10) << (arr + i)->noKereta
             << " | " << left << setw(17) << (arr + i)->nama
             << " | " << left << setw(15) << (arr + i)->asal
             << " | " << left << setw(15) << (arr + i)->tujuan
             << " | Rp " << left << setw(7) << (arr + i)->harga << "|\n";
    }
    cout << "===============================================================================\n";
}

void tambahKereta(Kereta* arr, int* n) {
    cout << "\n--- Tambah Data Kereta Baru ---\n";
    cout << "Nomor Kereta : ";
    cin >> (arr + *n)->noKereta;
    cin.ignore();
    cout << "Nama Kereta  : ";
    getline(cin, (arr + *n)->nama);
    cout << "Asal         : ";
    getline(cin, (arr + *n)->asal);
    cout << "Tujuan       : ";
    getline(cin, (arr + *n)->tujuan);
    cout << "Harga Tiket  : ";
    cin >> (arr + *n)->harga;

    (*n)++;
    cout << "Data berhasil ditambahkan!\n";
}

void linearSearchRute(Kereta* arr, int n, string asal, string tujuan) {
    bool found = false;
    cout << "\nHasil Pencarian Rute: " << asal << " -> " << tujuan << "\n";
    cout << "===============================================================================\n";
    for (int i = 0; i < n; i++) {
        if ((arr + i)->asal == asal && (arr + i)->tujuan == tujuan) {
            cout << "- No: " << (arr + i)->noKereta << " | " << (arr + i)->nama
                 << " | Rp " << (arr + i)->harga << "\n";
            found = true;
        }
    }
    if (!found) cout << "Kereta dengan rute tersebut tidak ditemukan.\n";
    cout << "===============================================================================\n";
}

void sortNoKereta(Kereta* arr, int n) {
    for(int i = 0; i < n - 1; i++) {
        for(int j = 0; j < n - i - 1; j++) {
            if((arr + j)->noKereta > (arr + j + 1)->noKereta) {
                swapKereta(&(arr[j]), &(arr[j + 1]));
            }
        }
    }
}

void jumpSearchNoKereta(Kereta* arr, int n, int cariNo) {
    sortNoKereta(arr, n);


    int step = sqrt(n);
    int prev = 0;

    while ((arr + min(step, n) - 1)->noKereta < cariNo) {
        prev = step;
        step += sqrt(n);
        if (prev >= n) {
            cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
            return;
        }
    }

    while ((arr + prev)->noKereta < cariNo) {
        prev++;
        if (prev == min(step, n)) {
            cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
            return;
        }
    }

    if ((arr + prev)->noKereta == cariNo) {
        cout << "\n[Kereta Ditemukan!]\n";
        cout << "No. Kereta : " << (arr + prev)->noKereta << "\n"
             << "Nama       : " << (arr + prev)->nama << "\n"
             << "Rute       : " << (arr + prev)->asal << " -> " << (arr + prev)->tujuan << "\n"
             << "Harga      : Rp " << (arr + prev)->harga << "\n";
    } else {
        cout << "Kereta dengan nomor " << cariNo << " tidak ditemukan.\n";
    }
}

void merge(Kereta* arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    Kereta* L = new Kereta[n1];
    Kereta* R = new Kereta[n2];

    for (int i = 0; i < n1; i++) L[i] = *(arr + left + i);
    for (int j = 0; j < n2; j++) R[j] = *(arr + mid + 1 + j);

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i].nama <= R[j].nama) {
            *(arr + k) = L[i];
            i++;
        } else {
            *(arr + k) = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        *(arr + k) = L[i];
        i++; k++;
    }

    while (j < n2) {
        *(arr + k) = R[j];
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
            if ((arr + j)->harga < (arr + min_idx)->harga) {
                min_idx = j;
            }
        }
        if (min_idx != i) {
            swapKereta(&(arr[min_idx]), &(arr[i]));
        }
    }
}

int main() {
    Kereta daftarKereta[100] = {
        {101, "Argo Bromo", "Jakarta", "Surabaya", 600000},
        {205, "Parahyangan", "Bandung", "Yogyakarta", 550000},
        {112, "Turangga", "Surabaya", "Cirebon", 450000},
        {302, "Matarmaja", "Malang", "Jakarta", 250000}
    };
    int jumlahKereta = 4;
    int pilihan;
    

    do {
        cout << "\n============================================\n";
        cout << "  SISTEM MANAJEMEN KEBERANGKATAN KERETA API \n";
        cout << "============================================\n";
        cout << "1. Tampil Jadwal Semua Kereta\n";
        cout << "2. Tambah Data Kereta\n";
        cout << "3. Cari Kereta (Linear Search - Rute)\n";
        cout << "4. Cari Kereta (Jump Search - No. Kereta)\n";
        cout << "5. Urutkan Nama Kereta A-Z (Merge Sort)\n";
        cout << "6. Urutkan Harga Termurah (Selection Sort)\n";
        cout << "0. Keluar\n";
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
                cout << "Masukkan Stasiun Asal   : ";
                getline(cin, asal);
                cout << "Masukkan Stasiun Tujuan : ";
                getline(cin, tujuan);
                linearSearchRute(daftarKereta, jumlahKereta, asal, tujuan);
                break;
            }
            case 4: {
                int no;
                cout << "Masukkan Nomor Kereta yang dicari: ";
                cin >> no;
                jumpSearchNoKereta(daftarKereta, jumlahKereta, no);
                break;
            }
            case 5:
                mergeSortNama(daftarKereta, 0, jumlahKereta - 1);
                cout << "\n[Info] Data berhasil diurutkan berdasarkan Nama Kereta (A-Z)!\n";
                tampilJadwal(daftarKereta, jumlahKereta);
                break;
            case 6:
                selectionSortHarga(daftarKereta, jumlahKereta);
                cout << "\n[Info] Data berhasil diurutkan berdasarkan Harga Termurah!\n";
                tampilJadwal(daftarKereta, jumlahKereta);
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