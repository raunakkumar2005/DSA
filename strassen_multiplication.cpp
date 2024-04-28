#include <iostream>
using namespace std;

// Function to multiply two 2x2 matrices
void multiply2x2(int A[2][2], int B[2][2], int C[2][2]) {
    int a = A[0][0], b = A[0][1], c = A[1][0], d = A[1][1];
    int e = B[0][0], f = B[0][1], g = B[1][0], h = B[1][1];

    C[0][0] = a * e + b * g;
    C[0][1] = a * f + b * h;
    C[1][0] = c * e + d * g;
    C[1][1] = c * f + d * h;
}

int main() {
    int A[2][2], B[2][2], C[2][2];

    cout << "Enter the elements of matrix A (2x2):" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> A[i][j];
        }
    }

    cout << "Enter the elements of matrix B (2x2):" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cin >> B[i][j];
        }
    }

    // Compute matrix multiplication
    multiply2x2(A, B, C);

    // Print the result matrix
    cout << "Result of matrix multiplication:" << endl;
    for (int i = 0; i < 2; ++i) {
        for (int j = 0; j < 2; ++j) {
            cout << C[i][j] << " ";
        }
        cout << endl;
    }

    return 0;
}
