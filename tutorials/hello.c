#include <stdio.h>

void increment(int *p) 
{
    *p = *p + 1;
}

int main(void) {
    int i = 2;
    float f = 3.14;
    char *s = "Hello World!";

    printf("%s i = %d and f = %f!\n",s , i , f);

    // Pointers Tutorial
    
    int j = 10;
    printf("The value of i is %d\n",j);
    printf("And its address is %p\n", (void *)&i); 

    int x; 
    int *p; // p is a pointer, but is uninitialized
    p = &x; // p is assigned to the address of i--p now "points to" i
    x = 10;
    *p = 20;
    printf("x is %d\n",x);
    printf("x is %d\n", *p);

    int y = 5;
    int *z = &y;

    // Simple example
    increment(z);
    printf("y is %d\n", y);

    // Concise example
    increment(&y);
    printf("y is %d\n", y);

    // Printing sizeof
    printf("%zu\n", sizeof(int)); // size of an int
    printf("%zu\n", sizeof p); // size of int*
    printf("%zu\n", sizeof *p); // size of int
}
