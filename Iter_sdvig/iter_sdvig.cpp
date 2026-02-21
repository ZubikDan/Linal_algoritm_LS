#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

// Решение СЛАУ методом Гаусса
vector<double> solveLinearSystem(vector<vector<double>> A, vector<double> b) {
    int n = A.size();
    
    // Прямой ход
    for (int i = 0; i < n; i++) {
        // Поиск ведущего элемента
        int maxRow = i;
        for (int k = i+1; k < n; k++)
            if (fabs(A[k][i]) > fabs(A[maxRow][i]))
                maxRow = k;
        
        // Перестановка строк
        if (maxRow != i) {
            swap(A[i], A[maxRow]);
            swap(b[i], b[maxRow]);
        }
        
        // Исключение
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

// Скалярное произведение
double dot(const vector<double>& a, const vector<double>& b) {
    return a[0]*b[0] + a[1]*b[1];
}

// Норма вектора
double norm(const vector<double>& v) {
    return sqrt(v[0]*v[0] + v[1]*v[1]);
}

int main() {
    // Матрица A
    vector<vector<double>> A = {{2, -1}, {-1, 2}};
    
    // Начальное приближение
    vector<double> x = {1, 1};
    
    // Сдвиг μ (близко к искомому собственному числу)
    // Для демонстрации: ищем λ = 1
    double mu = 0.9; // сдвиг
    
    cout << "Метод итераций со сдвигом (Shifted Inverse Iteration)\n";
    cout << "Матрица A:\n";
    cout << "[" << A[0][0] << ", " << A[0][1] << "]\n";
    cout << "[" << A[1][0] << ", " << A[1][1] << "]\n";
    cout << "Сдвиг μ = " << mu << "\n";
    cout << "Начальный вектор: [" << x[0] << ", " << x[1] << "]\n\n";
    
    // Нормализуем начальный вектор
    double nrm = norm(x);
    x[0] /= nrm; x[1] /= nrm;
    
    cout << "Итерации:\n";
    cout << "k  |        λ        |       Вектор\n";
    cout << "---|-----------------|------------------\n";
    
    for (int k = 0; k < 10; k++) {
        // Шаг 1: Создаем матрицу (A - μI)
        vector<vector<double>> A_minus_muI = A;
        A_minus_muI[0][0] -= mu;
        A_minus_muI[1][1] -= mu;
        
        // Шаг 2: Решаем (A - μI)y = x
        vector<double> y = solveLinearSystem(A_minus_muI, x);
        
        // Шаг 3: Нормализуем y -> новый x
        nrm = norm(y);
        vector<double> x_new = {y[0]/nrm, y[1]/nrm};
        
        // Шаг 4: Вычисляем оценку собственного числа
        // По формуле: λ ≈ μ + (xᵀx) / (xᵀy)
        double lambda_est = mu + dot(x, x) / dot(x, y);
        
        // Выводим результаты
        cout << setw(2) << k+1 << " | " 
             << setw(15) << setprecision(10) << lambda_est << " | "
             << "[" << setw(12) << setprecision(6) << x_new[0] 
             << ", " << setw(12) << x_new[1] << "]\n";
        
        // Обновляем вектор
        x = x_new;
        
        if (k > 0 && fabs(lambda_est - 1.0) < 1e-8) {
            break;
        }
    }
    
    vector<double> Ax = {A[0][0]*x[0] + A[0][1]*x[1], 
                        A[1][0]*x[0] + A[1][1]*x[1]};
    double lambda_final = dot(x, Ax) / dot(x, x);
    
    cout << "\n================================\n";
    cout << "Окончательный результат:\n";
    cout << "Собственное число λ ≈ " << setprecision(12) << lambda_final << "\n";
    cout << "Собственный вектор: [" << x[0] << ", " << x[1] << "]\n";
    
    
    return 0;
}