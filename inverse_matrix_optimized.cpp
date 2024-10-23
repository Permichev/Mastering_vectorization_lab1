/*
 
 Оптимизация достигается за счет следующих ключей компиляции:
 
 clang++ -O3 -march=armv8.4-a -ftree-vectorize inverse_matrix.cpp -o inverse_matrix_optimized
 
 
 */







#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

// Функция для вывода матрицы
void printMatrix(const vector<vector<double>>& matrix) {
    int n = matrix.size();
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cout << setw(10) << matrix[i][j] << " ";
        }
        cout << endl;
    }
}

// Функция для нахождения обратной матрицы
bool inverseMatrix(vector<vector<double>>& matrix, vector<vector<double>>& inverse) {
    int n = matrix.size();
    
    // Создаем единичную матрицу
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            inverse[i][j] = (i == j) ? 1.0 : 0.0;
        }
    }

    // Прямой ход метода Гаусса
    for (int i = 0; i < n; ++i) {
        double pivot = matrix[i][i];
        if (pivot == 0) {
            return false; // Матрица необратима
        }

        // Нормализация строки
        for (int j = 0; j < n; ++j) {
            matrix[i][j] /= pivot;
            inverse[i][j] /= pivot;
        }

        // Обнуление остальных элементов в столбце
        for (int k = 0; k < n; ++k) {
            if (k != i) {
                double factor = matrix[k][i];
                for (int j = 0; j < n; ++j) {
                    matrix[k][j] -= factor * matrix[i][j];
                    inverse[k][j] -= factor * inverse[i][j];
                }
            }
        }
    }

    return true;
}

int main() {
    int n;
    cout << "Введите размерность матрицы: ";
    cin >> n;

    vector<vector<double>> matrix(n, vector<double>(n));
    vector<vector<double>> inverse(n, vector<double>(n));

    cout << "Введите элементы матрицы:\n";
    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            cin >> matrix[i][j];
        }
    }

    if (inverseMatrix(matrix, inverse)) {
        cout << "Обратная матрица:\n";
        printMatrix(inverse);
    } else {
        cout << "Матрица необратима.\n";
    }

    return 0;
}