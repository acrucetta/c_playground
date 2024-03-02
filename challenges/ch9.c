
// CHALLENGE 9 (factorization). Now that we’ve covered functions, see if you can
// imple- ment a program factor that receives a number N on the command line and
// prints out where F0 and so on are all the prime factors of N. The core of
// your implementation should be a function that, given a value of type size_t,
// returns its smallest prime factor. Extend this program to receive a list of
// such numbers and output such a line for each of them.

#include <stdio.h>
#include <stdlib.h>

// Prime Factor of N
//
// E.g., 12
// Prime factors are: 1,2,3
//
// We return the smallest one for each input

int prime_factors(int n) {
  int i = 2;
  int ctr = 0;
  int factors[n];
  while (i * i <= n) { // We only need to check up to the square root of n
    if (n % i) {       // If n is not divisible by i
      i++;             // We increment i
    } else {
      n /= i; // If n is divisible by i, we divide n by i
      factors[ctr] = i;
      ctr++;
    }
  }
  return factors[0];
}

int main(int argc, char *argv[argc - 1]) {
  for (int i = 1; i < argc; i++) {
    printf("Prime factor of %s is %d\n", argv[i], prime_factors(atoi(argv[i])));
  }
  return EXIT_SUCCESS;
}
