#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> rotation(vector<vector<double>> square_mat, vector<double> answ) {
    int n = square_mat.size();
    vector<double> result(n, 0);
    
    // Прямой ход: приведение к верхнетреугольному виду
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            // Вычисление коэффициентов вращения
            double denom = sqrt(square_mat[i][i] * square_mat[i][i] + square_mat[j][i] * square_mat[j][i]);
            if (fabs(denom) < 1e-10) continue; // избегаем деления на 0
            
            double c = square_mat[i][i] / denom;
            double s = square_mat[j][i] / denom;
            
            // Применяем вращение к строкам i и j
            for (int k = 0; k < n; k++) {
                double temp_i = square_mat[i][k];
                double temp_j = square_mat[j][k];
                square_mat[i][k] = c * temp_i + s * temp_j;
                square_mat[j][k] = -s * temp_i + c * temp_j;
            }
            
            // Применяем вращение к правой части
            double temp_answ_i = answ[i];
            double temp_answ_j = answ[j];
            answ[i] = c * temp_answ_i + s * temp_answ_j;
            answ[j] = -s * temp_answ_i + c * temp_answ_j;
        }
    }
    
    cout << "Преобразованная верхнетреугольная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(6) << square_mat[i][j] << " ";
        }
        cout << " | " << setw(10) << answ[i] << endl;
    }
    cout << endl;
    
    // Обратный ход (обратная подстановка)
    result[n-1] = answ[n-1] / square_mat[n-1][n-1];
    
    for (int i = n - 2; i >= 0; i--) {
        double to_result = 0;
        for (int j = i + 1; j < n; j++) {
            to_result += result[j] * square_mat[i][j];
        }
        result[i] = (answ[i] - to_result) / square_mat[i][i];
    }
    
    return result;
}

int main() {
    // Исходная система уравнений:
    // x1 + 2x2 - 3x3 = 5
    // 2x1 - x2 - x3 = 1
    // 3x1 + 3x2 + 4x3 = 6
    
    // Матрица коэффициентов
    vector<vector<double>> A = {
        {1.0, 2.0, -3.0},
        {2.0, -1.0, -1.0},
        {3.0, 3.0, 4.0}
    };
    
    // Вектор правых частей
    vector<double> b = {5.0, 1.0, 6.0};
    
    cout << "Решение системы линейных уравнений методом вращений" << endl;
    cout << "Исходная система:" << endl;
    cout << "x1 + 2x2 - 3x3 = 5" << endl;
    cout << "2x1 - x2 - x3 = 1" << endl;
    cout << "3x1 + 3x2 + 4x3 = 6" << endl;
    cout << "==================================================" << endl;
    
    // Выводим исходную матрицу
    cout << "Исходная расширенная матрица:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << fixed << setprecision(4) << A[i][j] << " ";
        }
        cout << " | " << setw(8) << b[i] << endl;
    }
    cout << endl;
    
    // Решаем систему
    vector<double> solution = rotation(A, b);
    
    // Выводим решение
    cout << "==================================================" << endl;
    cout << "Решение системы:" << endl;
    for (int i = 0; i < solution.size(); i++) {
        cout << "x" << i+1 << " = " << fixed << setprecision(6) << solution[i] << endl;
    }
    
    return 0;
}