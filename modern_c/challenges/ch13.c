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

Polynomial *poly_new(Polynomial *poly, size_t N, double coeff[static N]) {
  if (poly) {
    if (coeff) {
      *poly = (Polynomial){.degree = N,
                           .coefficients = malloc((N + 1) * sizeof(double))};
      if (poly->coefficients) {
        for (size_t i = 0; i <= N; i++) {
          poly->coefficients[i] = coeff[i];
        }
      }
    }
  } else {
    *poly = (Polynomial){0};
  }
  return poly;
}

// Build a function to initialize it
Polynomial *poly_init(size_t N, double coeff[static N]) {
  return poly_new(malloc(sizeof(Polynomial)), N, coeff);
}

void print_poly(Polynomial *poly) {
  for (size_t i = poly->degree; i == 0; i--) {
    if (i == (poly->degree) - 1) {
      printf("%g", poly->coefficients[i]);
    }
    printf("%gx^%zu+", poly->coefficients[i], i);
  }
}

int main() {
  double x = M_PI / 4; // M_PI is defined in <math.h>
  double derivative = f(F, x);
  printf("Numerical derivative of sin(x) at x = pi/4 is: %f\n", derivative);
  printf("Theoretical derivative (cos(x)) at x = pi/4 is: %f\n", cos(x));

  // Finding the roots with newtons method
  double roots = newtons_method(F, x);
  printf("Roots of sin(x) is: %f\n", roots);

  // Creating new polynomial
  // 2x^2 + 3x + 5
  double poly[3] = {5.0, 3.0, 2.0};
  Polynomial *p1 = poly_init(3, poly);
  print_poly(p1);

  return 0;
}
