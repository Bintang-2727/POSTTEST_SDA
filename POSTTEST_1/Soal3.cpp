#include <iostream>
using namespace std;

void reverseArray(int* arr, int n) {
    int* start = arr;          
    int* end = arr + n - 1;    

    while (start < end) {
        int temp = *start;
        *start = *end;
        *end = temp;

        start++;
        end--;
    }
}

int main() {

    int arr[7] = {2, 3, 5, 7, 11, 13, 17};
    int n = 7;

    cout << "Array sebelum dibalik:\n";
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(arr + i)
             << " | Alamat: " << (arr + i) << endl;
    }


    reverseArray(arr, n);

    cout << "\nArray setelah dibalik:\n";
    for (int i = 0; i < n; i++) {
        cout << "Nilai: " << *(arr + i)
             << " | Alamat: " << (arr + i) << endl;
    }

    return 0;
}