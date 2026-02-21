#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Функция для умножения матрицы на вектор
vector<double> matrixVectorMultiply(const vector<vector<double>>& A, const vector<double>& x) {
    int n = A.size();
    vector<double> result(n, 0);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            result[i] += A[i][j] * x[j];
        }
    }
    return result;
}

// Функция для вычисления скалярного произведения
double dotProduct(const vector<double>& a, const vector<double>& b) {
    double result = 0;
    for (size_t i = 0; i < a.size(); i++) {
        result += a[i] * b[i];
    }
    return result;
}

// Метод сопряженных градиентов
vector<double> conjugateGradient(const vector<vector<double>>& A, const vector<double>& b, 
                                 double tolerance = 1e-10, int max_iterations = 1000) {
    int n = A.size();
    
    // Начальное приближение (нулевой вектор)
    vector<double> x(n, 0);
    
    // Вычисляем начальную невязку r = b - Ax
    vector<double> r = b;  // Так как x = 0, то r = b
    
    // Направление p = r
    vector<double> p = r;
    
    // Норма начальной невязки
    double r_norm_sq = dotProduct(r, r);
    double initial_r_norm = sqrt(r_norm_sq);
    
    cout << "Начальная норма невязки: " << initial_r_norm << endl;
    cout << "==================================================" << endl;
    
    // Итерации метода сопряженных градиентов
    for (int k = 0; k < max_iterations; k++) {
        // Вычисляем Ap
        vector<double> Ap = matrixVectorMultiply(A, p);
        
        // Вычисляем α = (rᵀr) / (pᵀAp)
        double alpha = r_norm_sq / dotProduct(p, Ap);
        
        // Обновляем решение: x = x + αp
        for (int i = 0; i < n; i++) {
            x[i] += alpha * p[i];
        }
        
        // Обновляем невязку: r = r - αAp
        vector<double> r_new = r;
        for (int i = 0; i < n; i++) {
            r_new[i] -= alpha * Ap[i];
        }
        
        // Вычисляем новую норму невязки
        double r_new_norm_sq = dotProduct(r_new, r_new);
        double r_new_norm = sqrt(r_new_norm_sq);
        
        // Проверяем критерий остановки
        if (r_new_norm < tolerance) {
            cout << "Итерация " << k+1 << ": достигнута точность, норма невязки = " 
                 << r_new_norm << endl;
            break;
        }
        
        // Вычисляем β = (r_newᵀr_new) / (rᵀr)
        double beta = r_new_norm_sq / r_norm_sq;
        
        // Обновляем направление: p = r_new + βp
        for (int i = 0; i < n; i++) {
            p[i] = r_new[i] + beta * p[i];
        }
        
        // Обновляем невязку и её норму
        r = r_new;
        r_norm_sq = r_new_norm_sq;
        
        // Выводим информацию о текущей итерации
        if (k < 10 || (k+1) % 10 == 0) {
            cout << "Итерация " << k+1 << ": норма невязки = " << r_new_norm << endl;
        }
    }
    
    return x;
}

int main() {
    // Исходная система:
    // x1 + 2x2 - 3x3 = 5
    // 2x1 - x2 - x3 = 1
    // 3x1 + 3x2 + 4x3 = 6
    
    // Для метода сопряженных градиентов нужна симметричная положительно определенная матрица
    // Умножим исходную систему слева на Aᵀ: AᵀAx = Aᵀb
    
    cout << "РЕШЕНИЕ СИСТЕМЫ ЛИНЕЙНЫХ УРАВНЕНИЙ МЕТОДОМ СОПРЯЖЕННЫХ ГРАДИЕНТОВ" << endl;
    cout << "==================================================" << endl;
    
    // Исходная матрица A
    vector<vector<double>> A = {
        {1.0, 2.0, -3.0},
        {2.0, -1.0, -1.0},
        {3.0, 3.0, 4.0}
    };
    
    // Вектор правых частей b
    vector<double> b = {5.0, 1.0, 6.0};
    
    cout << "Исходная матрица A:" << endl;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << setw(8) << fixed << setprecision(4) << A[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Вектор b: ";
    for (double bi : b) cout << bi << " ";
    cout << endl << endl;
    
    // Вычисляем AᵀA и Aᵀb для получения симметричной положительно определенной системы
    int n = A.size();
    vector<vector<double>> ATA(n, vector<double>(n, 0));
    vector<double> ATb(n, 0);
    
    // Вычисляем AᵀA
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            for (int k = 0; k < n; k++) {
                ATA[i][j] += A[k][i] * A[k][j];
            }
        }
    }
    
    // Вычисляем Aᵀb
    for (int i = 0; i < n; i++) {
        for (int k = 0; k < n; k++) {
            ATb[i] += A[k][i] * b[k];
        }
    }
    
    cout << "Матрица AᵀA (симметричная, положительно определенная):" << endl;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << setw(10) << fixed << setprecision(4) << ATA[i][j] << " ";
        }
        cout << endl;
    }
    cout << "Вектор Aᵀb: ";
    for (double bi : ATb) cout << bi << " ";
    cout << endl << endl;
    
    // Проверяем симметричность матрицы AᵀA
    bool is_symmetric = true;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            if (fabs(ATA[i][j] - ATA[j][i]) > 1e-10) {
                is_symmetric = false;
                break;
            }
        }
    }
    
    if (!is_symmetric) {
        cout << "Предупреждение: матрица AᵀA не является симметричной!" << endl;
    }
    
    cout << "==================================================" << endl;
    cout << "Запуск метода сопряженных градиентов..." << endl;
    
    // Решаем систему AᵀAx = Aᵀb методом сопряженных градиентов
    vector<double> solution = conjugateGradient(ATA, ATb);
    
    // Выводим решение
    cout << "==================================================" << endl;
    cout << "РЕШЕНИЕ СИСТЕМЫ AᵀAx = Aᵀb:" << endl;
    for (int i = 0; i < n; i++) {
        cout << "x" << i+1 << " = " << fixed << setprecision(10) << solution[i] << endl;
    }

    return 0;
}