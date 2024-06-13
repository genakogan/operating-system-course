#include <stdio.h>

// Function prototype
int swap(int *, int *);

int main()
{
    int a = 123;
    int b =a;
    int c=a;
    c=c-1;
    int *p1 = &a;
    int *p2 = &a;
    *p1 -= 3;
//    printf("===================\n");
//    printf("*p2 = %d\n", *p2);
//    printf("*p1 = %d\n", *p1);
//    printf("===================\n");
//    printf("b = %d\n", b);
//    printf("c = %d\n", c);
//    printf("===================\n");

    int num1 = 10, num2 = 20;
    swap(&num1, &num2); // Passing addresses of num1 and num2

    printf("After swap: num1 = %d, num2 = %d\n", num1, num2);

    return 0;
}

// Function definition to swap two integers
int swap(int *a, int *b) {
    if (a == NULL || b == NULL)
        return -1;
    int temp = *a;
    *a = *b;
    *b = temp;
    return 0;
}
