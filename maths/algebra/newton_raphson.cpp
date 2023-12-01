#include <iostream>
#include <cmath>

double f(double x) {
    return x*x - 5;
}

double f_prime(double x) {
    return 2*x;
}

double newton_raphson(double (*func)(double), double (*func_prime)(double), double x0, double epsilon = 1e-10, int max_iterations = 1000) {
    double x = x0;
    for (int i = 0; i < max_iterations; i++) {
        double x_next = x - func(x) / func_prime(x);
        if (std::abs(x_next - x) < epsilon) {
            return x_next;
        }
        x = x_next;
    }
    throw std::runtime_error("Newton's method did not converge (max iterations reached).");
}

int main() {
    double x0 = 2;
    double root = newton_raphson(f, f_prime, x0);
    std::cout << "Approximate root: " << root << std::endl;
    return 0;
}
