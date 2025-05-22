#include <iostream>
#include <iomanip>
#include <cmath>

using namespace std;

// Функция уравнения: f(x) = sin(x) - 2x - 1
double f(double x) {
    return sin(x) - 2 * x - 1;
}

// Производная функции: f'(x) = cos(x) - 2
double df(double x) {
    return cos(x) - 2;
}

// Метод половинного деления
void bisection_method(double a, double b, double eps) {
    cout << "\nМетод половинного деления:\n";
    cout << "-------------------------------------------------\n";
    cout << "| N |     a_n     |     b_n     |   b_n - a_n   |\n";
    cout << "-------------------------------------------------\n";
    
    int n = 0;
    double c;
    
    while (fabs(b - a) > eps) {
        c = (a + b) / 2;
        cout << "|" << setw(3) << (n+1) << "|" << setw(12) << a << "|" << setw(12) << b << "|" << setw(15) << (b - a) << "|\n";
        
        if (f(c) == 0.0) {
            break;
        } else if (f(c) * f(a) < 0) {
            b = c;
        } else {
            a = c;
        }
        n++;
    }
    
    cout << "-------------------------------------------------\n";
    cout << "Корень: " << (a + b) / 2 << endl;
    cout << "Количество итераций: " << n << endl;
}

// Метод Ньютона
void newton_method(double x0, double eps) {
    cout << "\nМетод Ньютона:\n";
    cout << "-------------------------------------------------\n";
    cout << "| N |     X_n     |    X_{n+1}   | X_{n+1} - X_n |\n";
    cout << "-------------------------------------------------\n";
    
    int n = 0;
    double x1 = x0 - f(x0) / df(x0);
    
    while (fabs(x1 - x0) > eps) {
        cout << "|" << setw(3) << (n+1) << "|" << setw(12) << x0 << "|" << setw(12) << x1 << "|" << setw(15) << (x1 - x0) << "|\n";
        
        x0 = x1;
        x1 = x0 - f(x0) / df(x0);
        n++;
    }
    
    cout << "-------------------------------------------------\n";
    cout << "Корень: " << x1 << endl;
    cout << "Количество итераций: " << n << endl;
}

// Метод простых итераций
void simple_iteration_method(double x0, double eps) {
    cout << "\nМетод простых итераций:\n";
    cout << "-------------------------------------------------\n";
    cout << "| N |     X_n     |    X_{n+1}   | X_{n+1} - X_n |\n";
    cout << "-------------------------------------------------\n";
    
    // Приводим уравнение к виду x = phi(x): phi(x) = (sin(x) - 1)/2
    auto phi = [](double x) { return (sin(x) - 1) / 2; };
    
    int n = 0;
    double x1 = phi(x0);
    
    while (fabs(x1 - x0) > eps) {
        cout << "|" << setw(3) << (n+1) << "|" << setw(12) << x0 << "|" << setw(12) << x1 << "|" << setw(15) << (x1 - x0) << "|\n";
        
        x0 = x1;
        x1 = phi(x0);
        n++;
    }
    
    cout << "-------------------------------------------------\n";
    cout << "Корень: " << x1 << endl;
    cout << "Количество итераций: " << n << endl;
}

int main() {
    const double eps = 1e-4;
    double a = -1.0, b = 0.0; // Интервал, где находится корень
    double x0 = -0.5; // Начальное приближение
    
    // Метод половинного деления
    bisection_method(a, b, eps);
    
    // Метод Ньютона
    newton_method(x0, eps);
    
    // Метод простых итераций
    simple_iteration_method(x0, eps);
    
    return 0;
}
