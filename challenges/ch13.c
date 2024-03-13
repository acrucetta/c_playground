// CHALLENGE 13 (Generic derivative). Can you extend the real and complex
// derivatives (challenges 2 and 5) such that they receive the function F and
// the value x as a parameter? Can you use the generic real derivatives to
// implement Newton’s method for finding roots? Can you find the real zeros of
// polynomials? Can you find the complex zeros of polynomials?

#include <math.h>
#include <stdio.h>
#include <stdlib.h>

#define MAX_ITER 10000
#define MAX_COEFFS 10

double F(double x) { return sin(x); }

double f(double (*f)(double), double x) {
  double h = 1e-5;
  return ((f(x + h) - f(x - h)) / (2 * h));
}

double newtons_method(double (*F)(double), double x0) {
  double x = x0;
  double tolerance = 1E-6;

  for (size_t i = 0; i < MAX_ITER; i++) {
    double fx = F(x);
    double dx = f(F, x);
    if (fabs(dx) < 1e-10) {
      printf("Derivatrive too close to zero, it will not converge");
    }
    if (fabs(fx) < tolerance) {
      return x;
    }
    if (dx) {
      x = x - fx / dx;
    }
  }
  return x;
}

// Build a polynomial structure
typedef struct Polynomial Polynomial;
struct Polynomial {
  size_t degree;
  double *coefficients;
};

// Build a function to initialize it
Polynomial *poly_init(double coef[static MAX_COEFFS]) { return 0; }

int main() {
  double x = M_PI / 4; // M_PI is defined in <math.h>
  double derivative = f(F, x);
  printf("Numerical derivative of sin(x) at x = pi/4 is: %f\n", derivative);
  printf("Theoretical derivative (cos(x)) at x = pi/4 is: %f\n", cos(x));

  // Finding the roots with newtons method
  double roots = newtons_method(F, x);
  printf("Roots of sin(x) is: %f\n", roots);

  return 0;
}
