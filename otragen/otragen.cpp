#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> householderReflection(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    vector<double> result(n, 0);
    
    // Прямой ход: приведение к верхнетреугольному виду методом Хаусхолдера
    for (int k = 0; k < n; k++) {
        // Вычисляем норму столбца для определения знака
        double sigma = 0;
        for (int i = k; i < n; i++) {
            sigma += A[i][k] * A[i][k];
        }
        sigma = sqrt(sigma);
        
        // Выбираем знак для устойчивости
        double sign = (A[k][k] >= 0) ? 1.0 : -1.0;
        double x1 = A[k][k] + sign * sigma;
        
        // Вычисляем вектор отражения u
        vector<double> u(n, 0);
        u[k] = x1;
        for (int i = k + 1; i < n; i++) {
            u[i] = A[i][k];
        }
        
        // Вычисляем норму вектора u и β
        double norm_u_sq = 0;
        for (int i = k; i < n; i++) {
            norm_u_sq += u[i] * u[i];
        }
        
        if (norm_u_sq < 1e-12) continue; // пропускаем нулевой вектор
        
        double beta = 2.0 / norm_u_sq;
        
        // Применяем преобразование Хаусхолдера к матрице A
        for (int j = k; j < n; j++) {
            double dot = 0;
            for (int i = k; i < n; i++) {
                dot += u[i] * A[i][j];
            }
            
            for (int i = k; i < n; i++) {
                A[i][j] -= beta * u[i] * dot;
            }
        }
        
        // Применяем преобразование к вектору b
        double dot_b = 0;
        for (int i = k; i < n; i++) {
            dot_b += u[i] * b[i];
        }
        
        for (int i = k; i < n; i++) {
            b[i] -= beta * u[i] * dot_b;
        }
        
        // Обнуляем элементы ниже диагонали (для красивого вывода)
        for (int i = k + 1; i < n; i++) {
            A[i][k] = 0;
        }
        
        // Выводим промежуточные результаты
        cout << "\nШаг " << k + 1 << ":" << endl;
        cout << "Вектор отражения u: ";
        for (int i = 0; i < n; i++) {
            cout << setw(8) << fixed << setprecision(4) << u[i] << " ";
        }
        cout << "\nβ = " << beta << endl;
        cout << "Матрица после преобразования:" << endl;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                cout << setw(8) << fixed << setprecision(4) << A[i][j] << " ";
            }
            cout << " | " << setw(8) << b[i] << endl;
        }
    }
    
    // Выводим окончательную верхнетреугольную матрицу
    cout << "\n==================================================" << endl;
    cout << "Финальная верхнетреугольная матрица:" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(6) << A[i][j] << " ";
        }
        cout << " | " << setw(10) << b[i] << endl;
    }
    
    // Обратный ход (обратная подстановка)
    result[n-1] = b[n-1] / A[n-1][n-1];
    
    for (int i = n - 2; i >= 0; i--) {
        double sum = 0;
        for (int j = i + 1; j < n; j++) {
            sum += result[j] * A[i][j];
        }
        result[i] = (b[i] - sum) / A[i][i];
    }
    
    return result;
}

int main() {
    // Исходная система уравнений:
    // x1 + 2x2 - 3x3 = 5
    // 2x1 - x2 - x3 = 1
    // 3x1 + 3x2 + 4x3 = 6
    
    vector<vector<double>> A = {
        {1.0, 2.0, -3.0},
        {2.0, -1.0, -1.0},
        {3.0, 3.0, 4.0}
    };
    
    vector<double> b = {5.0, 1.0, 6.0};
    
    cout << "РЕШЕНИЕ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ МЕТОДОМ ОТРАЖЕНИЙ (ХАУСХОЛДЕРА)" << endl;
    cout << "==================================================" << endl;
    cout << "Исходная система:" << endl;
    cout << "x1 + 2x2 - 3x3 = 5" << endl;
    cout << "2x1 - x2 - x3 = 1" << endl;
    cout << "3x1 + 3x2 + 4x3 = 6" << endl;
    cout << "==================================================" << endl;
    
    cout << "Исходная расширенная матрица:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << fixed << setprecision(4) << A[i][j] << " ";
        }
        cout << " | " << setw(8) << b[i] << endl;
    }
    cout << "==================================================" << endl;
    
    // Решаем систему методом отражений
    vector<double> solution = householderReflection(A, b);
    
    // Выводим решение
    cout << "\n==================================================" << endl;
    cout << "РЕШЕНИЕ СИСТЕМЫ:" << endl;
    for (int i = 0; i < solution.size(); i++) {
        cout << "x" << i+1 << " = " << fixed << setprecision(10) << solution[i] << endl;
    }

    
    return 0;
}