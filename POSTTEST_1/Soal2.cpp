#include <iostream>
using namespace std;

struct Mahasiswa {
    string nama;
    string nim;
    float ipk;
};

int main() {
    const int JUMLAH = 5;
    Mahasiswa mhs[JUMLAH];

    for (int i = 0; i < JUMLAH; i++) {
        cout << "\nMahasiswa ke-" << i + 1 << endl;
        cout << "Nama : ";
        getline(cin >> ws, mhs[i].nama);
        cout << "NIM  : ";
        getline(cin, mhs[i].nim);
        cout << "IPK  : ";
        cin >> mhs[i].ipk;
    }

    int indexMax = 0;
    for (int i = 1; i < JUMLAH; i++) {
        if (mhs[i].ipk > mhs[indexMax].ipk) {
            indexMax = i;
        }
    }

    cout << "\n=== Mahasiswa dengan IPK Tertinggi ===" << endl;
    cout << "Nama : " << mhs[indexMax].nama << endl;
    cout << "NIM  : " << mhs[indexMax].nim << endl;
    cout << "IPK  : " << mhs[indexMax].ipk << endl;

    return 0;
}