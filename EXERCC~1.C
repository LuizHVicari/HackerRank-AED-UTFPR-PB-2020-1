#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int MochilaBinariaBackTracking(int capacidade, int nobjetos, int peso[], int valor[])
{
    if (nobjetos < 0)
        return 0;
    else
    {
        int aux1 = 0, aux2 = 0;

        if(capacidade >= peso[nobjetos])
        {
           aux1 = valor[nobjetos] + MochilaBinariaBackTracking(capacidade - peso[nobjetos], nobjetos - 1, peso, valor);
        }
        
         aux2 = MochilaBinariaBackTracking(capacidade, nobjetos - 1, peso, valor);
         if (aux1 > aux2)
                return aux1;

            else
                return aux2;
    }
}

int main(void)
{
    int capacidade, nobjetos;

    scanf("%d %d", &capacidade, &nobjetos);

    int i = 0;
    int peso[nobjetos], valor[nobjetos];

    for (; i < nobjetos; i++)
    {
        scanf("%d %d", &peso[i], &valor[i]);
    }

    printf("%d", MochilaBinariaBackTracking(capacidade, nobjetos - 1, peso, valor));

        return 0;
}