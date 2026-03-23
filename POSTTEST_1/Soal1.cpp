#include <iostream>
using namespace std;


int FindMin(int A[], int n, int &indexMin) {
    int min = A[0];
    indexMin = 0;

    for (int i = 1; i < n; i++) {
        if (A[i] < min) {
            min = A[i];
            indexMin = i;
        }
    }
    return min;
}

int main() {
    int A[8] = {1, 1, 2, 3, 5, 8, 13, 21};
    int indexMin;

    int minValue = FindMin(A, 8, indexMin);

    cout << "Nilai minimum : " << minValue << endl;
    cout << "Indeks minimum: " << indexMin << endl;

    return 0;
}