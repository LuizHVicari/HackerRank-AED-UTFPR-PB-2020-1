#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>
int Soma (int a, int b)
{
    return a+b;
}
int main() {
    
    int a, b;
    scanf("%d %d", &a, &b);
    printf("%d", Soma(a, b));
    return 0;
}
