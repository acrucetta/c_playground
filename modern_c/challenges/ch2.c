#include <math.h>
#include <stdio.h>
#include <stdlib.h>

// CHALLENGE 2 (Numerical derivatives). Something we’ll deal with a lot is the
// concept of numerical algorithms. To get your hands dirty, see if you can
// implement the numerical derivative double f(double x) of a function double
// F(double x). Implement this with an example F for the function that you use
// for this exercise. A good primary choice for F would be a function for which
// you know the derivative, such as sin, cos, or sqrt. This allows to check your
// results for correctness.

double F(double x) { return sin(x); }
double f(double (*f)(double), double x) {
  double h = 1e-5;
  return ((f(x + h) - f(x - h)) / (2 * h));
}

int main() {
  double x = M_PI / 4; // M_PI is defined in <math.h>
  double derivative = f(F, x);
  printf("Numerical derivative of sin(x) at x = pi/4 is: %f\n", derivative);
  printf("Theoretical derivative (cos(x)) at x = pi/4 is: %f\n", cos(x));
  return 0;
}
