#include <iostream>
#include <vector>
using namespace std;

// Function to add two matrices
vector<vector<int>> addMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> C(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] + B[i][j];
        }
    }

    return C;
}

// Function to subtract two matrices
vector<vector<int>> subtractMatrices(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rows = A.size();
    int cols = A[0].size();
    vector<vector<int>> C(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; ++i) {
        for (int j = 0; j < cols; ++j) {
            C[i][j] = A[i][j] - B[i][j];
        }
    }

    return C;
}

// Function to split a matrix into four submatrices
void splitMatrix(const vector<vector<int>>& A, vector<vector<int>>& A11, vector<vector<int>>& A12,
                                       vector<vector<int>>& A21, vector<vector<int>>& A22) {
    int rows = A.size();
    int cols = A[0].size();
    int midRow = rows / 2;
    int midCol = cols / 2;

    for (int i = 0; i < midRow; ++i) {
        for (int j = 0; j < midCol; ++j) {
            A11[i][j] = A[i][j];
            A12[i][j] = A[i][j + midCol];
            A21[i][j] = A[i + midRow][j];
            A22[i][j] = A[i + midRow][j + midCol];
        }
    }
}

// Function to merge four submatrices into one matrix
void mergeMatrix(vector<vector<int>>& C, const vector<vector<int>>& C11, const vector<vector<int>>& C12,
                                       const vector<vector<int>>& C21, const vector<vector<int>>& C22) {
    int rows = C.size();
    int cols = C[0].size();
    int midRow = rows / 2;
    int midCol = cols / 2;

    for (int i = 0; i < midRow; ++i) {
        for (int j = 0; j < midCol; ++j) {
            C[i][j] = C11[i][j];
            C[i][j + midCol] = C12[i][j];
            C[i + midRow][j] = C21[i][j];
            C[i + midRow][j + midCol] = C22[i][j];
        }
    }
}

// Function to multiply two matrices using Strassen's algorithm
vector<vector<int>> strassen(const vector<vector<int>>& A, const vector<vector<int>>& B) {
    int rowsA = A.size();
    int colsA = A[0].size();
    int rowsB = B.size();
    int colsB = B[0].size();

    if (colsA != rowsB) {
        cout << "Cannot multiply matrices with these dimensions." << endl;
        return {};
    }

    // Handle edge case for non-power of 2 dimensions
    int maxSize = max(max(rowsA, colsA), max(rowsB, colsB));
    int n = 1;
    while (n < maxSize) {
        n *= 2;
    }

    vector<vector<int>> paddedA(n, vector<int>(n, 0));
    vector<vector<int>> paddedB(n, vector<int>(n, 0));

    // Copy data into padded matrices
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsA; ++j) {
            paddedA[i][j] = A[i][j];
        }
    }

    for (int i = 0; i < rowsB; ++i) {
        for (int j = 0; j < colsB; ++j) {
            paddedB[i][j] = B[i][j];
        }
    }

    // Base case
    if (n == 1) {
        return {{paddedA[0][0] * paddedB[0][0]}};
    }

    // Divide matrices into submatrices
    vector<vector<int>> A11(n/2, vector<int>(n/2)), A12(n/2, vector<int>(n/2)),
                        A21(n/2, vector<int>(n/2)), A22(n/2, vector<int>(n/2)),
                        B11(n/2, vector<int>(n/2)), B12(n/2, vector<int>(n/2)),
                        B21(n/2, vector<int>(n/2)), B22(n/2, vector<int>(n/2));

    splitMatrix(paddedA, A11, A12, A21, A22);
    splitMatrix(paddedB, B11, B12, B21, B22);

    // Recursive steps
    vector<vector<int>> P1 = strassen(addMatrices(A11, A22), addMatrices(B11, B22));
    vector<vector<int>> P2 = strassen(addMatrices(A21, A22), B11);
    vector<vector<int>> P3 = strassen(A11, subtractMatrices(B12, B22));
    vector<vector<int>> P4 = strassen(A22, subtractMatrices(B21, B11));
    vector<vector<int>> P5 = strassen(addMatrices(A11, A12), B22);
    vector<vector<int>> P6 = strassen(subtractMatrices(A21, A11), addMatrices(B11, B12));
    vector<vector<int>> P7 = strassen(subtractMatrices(A12, A22), addMatrices(B21, B22));

    // Compute result matrix C
    vector<vector<int>> C11 = addMatrices(subtractMatrices(addMatrices(P1, P4), P5), P7);
    vector<vector<int>> C12 = addMatrices(P3, P5);
    vector<vector<int>> C21 = addMatrices(P2, P4);
    vector<vector<int>> C22 = addMatrices(subtractMatrices(addMatrices(P1, P3), P2), P6);

    // Combine submatrices into result matrix
    vector<vector<int>> C(n, vector<int>(n, 0));
    mergeMatrix(C, C11, C12, C21, C22);

    // Remove padding and return result
    vector<vector<int>> result(rowsA, vector<int>(colsB, 0));
    for (int i = 0; i < rowsA; ++i) {
        for (int j = 0; j < colsB; ++j) {
            result[i][j] = C[i][j];
        }
    }

    return result;
}

// Function to print a matrix
void printMatrix(const vector<vector<int>>& matrix) {
    for (const auto& row : matrix) {
        for (int element : row) {
            cout << element << " ";
        }
        cout << endl;
    }
}

// Function to take input for a matrix
vector<vector<int>> inputMatrix(int rows, int cols) {
    vector<vector<int>> matrix(rows, vector<int>(cols));

    cout << "Enter the elements of the matrix:" << endl;
    for (int i = 0; i < rows; ++i) {
        cout << "Row " << (i + 1) << ": ";
        for (int j = 0; j < cols; ++j) {
            cin >> matrix[i][j];
        }
    }

    return matrix;
}

int main() {
    int rowsA, colsA, rowsB, colsB;

    cout << "Enter the dimensions of matrix A (rows cols): ";
    cin >> rowsA >> colsA;
    vector<vector<int>> A = inputMatrix(rowsA, colsA);

    cout << "Enter the dimensions of matrix B (rows cols): ";
    cin >> rowsB >> colsB;
    vector<vector<int>> B = inputMatrix(rowsB, colsB);

    // Compute matrix multiplication using Strassen's algorithm
    vector<vector<int>> C = strassen(A, B);

    // Print the result matrix
    cout << "Result of matrix multiplication:" << endl;
    printMatrix(C);

    return 0;
}