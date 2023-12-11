struct Roots {
    double x1;
    double x2;
    int numRoots;
};

Roots solveQuadratic(double a, double b, double c) {
    Roots roots;

    double discriminant = b * b - 4 * a * c;

    if (discriminant > 0) {
        roots.numRoots = 2;
        roots.x1 = (-b + sqrt(discriminant)) / (2 * a);
        roots.x2 = (-b - sqrt(discriminant)) / (2 * a);
    } else if (discriminant == 0) {
        roots.numRoots = 1;
        roots.x1 = -b / (2 * a);
        roots.x2 = roots.x1;
    } else {
        roots.numRoots = 0;
    }

    return roots;
}
