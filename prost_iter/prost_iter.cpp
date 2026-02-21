#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1 = 0, x2 = 0, x3 = 0;
    double x1_old, x2_old, x3_old;
    double eps = 1e-4;
    int k = 0;
    int maxIter = 1000;

    cout << "Метод простой итерации (Якоби)\n";

    do {
        x1_old = x1;
        x2_old = x2;
        x3_old = x3;

        x1 = 5 - 2*x2_old + 3*x3_old;
        x2 = 2*x1_old - x3_old - 1;
        x3 = (6 - 3*x1_old - 3*x2_old) / 4;

        k++;
        cout << "Итерация " << k << ": ";
        cout << "x1=" << x1 << " x2=" << x2 << " x3=" << x3 << endl;

        if (k >= maxIter) break;

    } while (fabs(x1 - x1_old) > eps ||
            fabs(x2 - x2_old) > eps ||
            fabs(x3 - x3_old) > eps);

    return 0;
}