#include "mantissa.h"
#include<stdlib.h>
#include<stdio.h>


int main(int argc, char const *argv[])
{

    double valor = 0.0;
    printf("Enter the value you want to convert (exp:10.5): ");
    scanf("%lf", &valor);


    if(valor == 0){
        printf("0 00000000 00000000000000000000000");
        return 0;
    }

    binario* B = convertBinario(valor);
    //PrintBinario(B);

    mt* M = convertMantissa(B);
    PrintMantissa(M);
    return 0;
}
