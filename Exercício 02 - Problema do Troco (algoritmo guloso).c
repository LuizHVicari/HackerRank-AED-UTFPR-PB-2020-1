#include <stdio.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>

int main (void)
{
    int troco, quantidade, i, j, c;

    //Informa o valor do troco
    scanf("%d", &troco);

    //Informa a quantidade de moedas
    scanf("%d", &quantidade);

    //Cria um vetor com o tamannho da quantidade de moedas
    int moedas[quantidade];

    for(i = 0; i < quantidade; i++)
    {
        scanf("%d", &moedas[i]);
    }

    for(i = 0; i < quantidade; i++)
    {
        for (j = 0; j < i; j++)
        {
            if(moedas[j] < moedas[j+1])
            {
                c = moedas[j];
                moedas[j] = moedas[j+1];
                moedas[j+1] = c;
            }
        }
    }
    i = 0;
    while(i < quantidade && troco > 0)
    {
        if(troco - moedas[i] >= 0)
        {
            troco = troco - moedas[i];
            printf("%d\n", moedas[i]);
        }

        else
            i++;
    }

    return 0;
}

