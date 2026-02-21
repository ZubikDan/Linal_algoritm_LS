#include <iostream>
#include <cmath>
using namespace std;

int main() {
    double x1 = 0, x2 = 0, x3 = 0;
    double r1, r2, r3;
    double lambda_min = 1.0;
    double lambda_max = 10.0;
    int m = 1000;

    cout << "Метод Чебышёва\n";

    for (int k = 1; k <= m; k++) {

        double tau = 2.0 / (
            lambda_max + lambda_min +
            (lambda_max - lambda_min) *
            cos((2.0 * k - 1) * M_PI / (2.0 * m))
        );

        r1 = 5 - (x1 + 2*x2 - 3*x3);
        r2 = 1 - (2*x1 - x2 - x3);
        r3 = 6 - (3*x1 + 3*x2 + 4*x3);

        x1 = x1 + tau * r1;
        x2 = x2 + tau * r2;
        x3 = x3 + tau * r3;

        cout << "Итерация " << k << ": ";
        cout << "x1=" << x1 << " x2=" << x2 << " x3=" << x3 << endl;
    }

    return 0;
}