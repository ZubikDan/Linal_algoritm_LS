#include <iostream>
#include <cmath>
#include <vector>

using namespace std;

// Функция для вычисления нормы вектора
double norm(const vector<double>& v) {
    double sum = 0;
    for (double val : v) sum += val * val;
    return sqrt(sum);
}

// Метод градиентного спуска (наискорейший спуск)
int main() {
    // Матрица A
    double A[3][3] = { {1, 2, -3},
                       {2, -1, -1},
                       {3, 3, 4} };

    // Вектор b
    double b[3] = {5, 1, 6};

    // Начальное приближение x
    vector<double> x = {0, 0, 0};
    vector<double> r(3); // остаток r = b - Ax
    vector<double> Ar(3);

    double eps = 1e-6; // точность
    int maxIter = 1000;

    for (int iter = 0; iter < maxIter; ++iter) {
        // Вычисляем r = b - Ax
        for (int i = 0; i < 3; ++i) {
            r[i] = b[i];
            for (int j = 0; j < 3; ++j) r[i] -= A[i][j] * x[j];
        }

        // Проверка на сходимость
        if (norm(r) < eps) break;

        // Вычисляем Ar = A*r
        for (int i = 0; i < 3; ++i) {
            Ar[i] = 0;
            for (int j = 0; j < 3; ++j) Ar[i] += A[i][j] * r[j];
        }

        // Вычисляем оптимальный шаг alpha = (r^T r) / (r^T A r)
        double rr = 0, rAr = 0;
        for (int i = 0; i < 3; ++i) {
            rr += r[i] * r[i];
            rAr += r[i] * Ar[i];
        }
        double alpha = rr / rAr;

        // Обновляем x
        for (int i = 0; i < 3; ++i) x[i] += alpha * r[i];
    }

    // Вывод результата
    cout << "Решение системы методом наискорейшего спуска:\n";
    for (int i = 0; i < 3; ++i) {
        cout << "x" << i+1 << " = " << x[i] << "\n";
    }

    return 0;
}