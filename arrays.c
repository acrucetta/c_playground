#include <stdio.h>

#define COUNT 5

int main(void)
{
    int i;
    float f[4]; // array of 4 floats
    f[0] = 1.1;
    f[1] = 1.2;
    f[2] = 1.3;
    f[3] = 1.4;

    for (i=0; i<4;i++) {
        printf("%f\n",f[i]);
    }
    
    int x[12];
    printf("%zu\n",sizeof(x)); // 48 bytes
    printf("%zu\n", sizeof(int)); // 4 bytes

    // Inititialize array
    int a[5] = {1,2,3,4,5};

    // Initialize array with 0
    int d[10] = {0};

    // Constant array
    int b[COUNT] = {1,2,3,4,5};

    // C lets you print more ints than you have
    int c[3] = {1,2,3};
    for (i=0; i<5; i++) {
      printf("%d\n",c[i]);
    }
}
