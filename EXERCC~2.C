#include <stdio.h>
#include <string.h>
#include <math.h>
#include <stdlib.h>

int MochilaBinaria(int nobjetos, int capacidade, int peso[], int valor[], int matriz[capacidade + 1][nobjetos + 1])
{
    int i, j, base;

    for (j = 0; j <= capacidade; j++)
    {
            matriz[j][0] = 0;
    }

    for (i = 1; i <= nobjetos; i++)
    {
        for (j = 0; j <= capacidade; j++)
        {
            base = matriz[j][i - 1];

            if (j - peso[i - 1] >= 0)
            {
                if(valor[i - 1] + matriz[j - peso[i - 1]][i - 1] > base)
                    base = valor[i - 1] + matriz[j - peso[i - 1]][i - 1];
            }
            
            matriz[j][i] = base;
        }
        
    }

    return matriz[capacidade][nobjetos];
}

int main()
{

    int capacidade, nobjetos;

    scanf("%d %d", &capacidade, &nobjetos);

    int peso[nobjetos + 1], valor[nobjetos + 1], matriz[capacidade + 1][nobjetos + 1];

    for (int i = 0; i < nobjetos; i++)
        scanf("%d %d", &peso[i], &valor[i]);

    printf("%d", MochilaBinaria(nobjetos, capacidade, peso, valor, matriz));
    
    return 0;
}
