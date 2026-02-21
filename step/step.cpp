#include <iostream>
#include <vector>
#include <cmath>
#include <iomanip>

using namespace std;

vector<double> multiply(const vector<vector<double>>& A, const vector<double>& x) {
    int n = A.size();
    vector<double> result(n, 0);
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            result[i] += A[i][j] * x[j];
    return result;
}

double dot(const vector<double>& a, const vector<double>& b) {
    double r = 0;
    for (size_t i = 0; i < a.size(); i++) r += a[i] * b[i];
    return r;
}

void normalize(vector<double>& v) {
    double norm = sqrt(dot(v, v));
    if (norm > 1e-10)
        for (size_t i = 0; i < v.size(); i++) v[i] /= norm;
}

int main() {
    vector<vector<double>> A = {{2, -1}, {-1, 2}};
    vector<double> x = {1, 1};
    
    normalize(x);
    double lambda_old = 0, lambda = 0;
    
    cout << "Степенной метод для A = [[2, -1], [-1, 2]]\n";
    cout << "Итерации:\n";
    
    for (int k = 0; k < 50; k++) {
        vector<double> y = multiply(A, x);
        lambda = dot(x, y);
        normalize(y);
        
        if (fabs(lambda - lambda_old) < 1e-10) {
            cout << k+1 << ": λ = " << setprecision(10) << lambda 
                 << ", вектор = [" << x[0] << ", " << x[1] << "]\n";
            break;
        }
        
        if (k < 3 || k % 5 == 4)
            cout << k+1 << ": λ ≈ " << setprecision(10) << lambda << endl;
        
        x = y;
        lambda_old = lambda;
    }
    
    cout << "\nРезультат: λ_max ≈ " << setprecision(10) << lambda 
         << "\nТеоретическое значение: λ = 3\n";
    
    return 0;
}