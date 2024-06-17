// CHALLENGE 5 (complex numbers). Can you extend the derivative (Challenge 2) to
// the complex domain: that is, functions that receive and return double complex
// values?
#include <complex.h>
#include <math.h>
#include <stdio.h>

static double const eps = 1e-7;
#define PI 3.14159265358979323846

double complex F(double complex x) { return sin(x); };

double f(double complex (*f)(double complex), double complex x) {
  return ((f(x + eps) - f(x - eps)) / (2 * eps));
}

int main() {
  double complex point_1 = PI / 2 + (PI / 2) * I, point_2 = 4 + 4 * I;
  double derivative = f(F, point_1);
  printf("Numerical derivative of sin(x) at x = pi/4 is: %f\n", derivative);
  printf("Theoretical derivative (cos(x)) at x = pi/4 is: %f\n", cos(point_1));

  double deriv_2 = f(F, point_2);
  printf("Numerical derivative of sin(x) at x = pi/4 is: %f\n", deriv_2);
  printf("Theoretical derivative (cos(x)) at x = pi/4 is: %f\n", cos(point_2));
  return 0;
}
