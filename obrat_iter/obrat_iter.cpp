#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Решение СЛАУ методом Гаусса для обратной итерации
vector<double> solveGauss(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    
    // Прямой ход
    for (int i = 0; i < n; i++) {
        // Поиск максимального элемента в столбце
        int maxRow = i;
        for (int k = i+1; k < n; k++)
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        
        // Перестановка строк
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }
        
        // Обнуление элементов ниже диагонали
        for (int k = i+1; k < n; k++) {
            double factor = A[k][i] / A[i][i];
            for (int j = i; j < n; j++)
                A[k][j] -= factor * A[i][j];
            b[k] -= factor * b[i];
        }
    }
    
    // Обратный ход
    vector<double> x(n);
    for (int i = n-1; i >= 0; i--) {
        x[i] = b[i];
        for (int j = i+1; j < n; j++)
            x[i] -= A[i][j] * x[j];
        x[i] /= A[i][i];
    }
    
    return x;
}

int main() {
    vector<vector<double>> A = {{2, -1}, {-1, 2}};
    vector<double> x = {1, 1}; // начальное приближение
    
    // Нормализуем начальный вектор
    double norm = sqrt(x[0]*x[0] + x[1]*x[1]);
    x[0] /= norm; x[1] /= norm;
    
    // Сдвиг μ (близко к искомому собственному числу)
    // Для демонстрации: ищем λ = 1 (минимальное собственное число)
    double mu = 0.5; // сдвиг близко к 1
    
    cout << "Метод обратной итерации для A = [[2, -1], [-1, 2]]\n";
    cout << "Сдвиг μ = " << mu << " (близко к λ_min = 1)\n";
    cout << "Итерации:\n";
    
    for (int k = 1; k <= 10; k++) {
        // Формируем матрицу (A - μI)
        vector<vector<double>> B = A;
        B[0][0] -= mu;
        B[1][1] -= mu;
        
        // Решаем (A - μI)y = x
        vector<double> y = solveGauss(B, x);
        
        // Нормализуем y
        norm = sqrt(y[0]*y[0] + y[1]*y[1]);
        x[0] = y[0] / norm;
        x[1] = y[1] / norm;
        
        // Уточняем оценку собственного числа через отношение Рэлея
        vector<double> Ax = {A[0][0]*x[0] + A[0][1]*x[1], 
                            A[1][0]*x[0] + A[1][1]*x[1]};
        double lambda = (x[0]*Ax[0] + x[1]*Ax[1]) / (x[0]*x[0] + x[1]*x[1]);
        
        cout << k << ": λ ≈ " << setprecision(10) << lambda 
             << ", вектор ≈ [" << setprecision(6) << x[0] << ", " << x[1] << "]\n";
    }
    
    cout << "\nРезультат: λ_min ≈ 1\n";
    cout << "Собственный вектор для λ = 1: [0.707107, 0.707107]\n";
    
    return 0;
}