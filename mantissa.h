#pragma once

typedef struct {
    int sinal;
    int expoente[8];
    int qtdExp;
    int mantissa[23];
    int qtdMant;
} mt;

typedef struct {
    int sinal;
    int inteira[23];
    int qtdInt;
    int fracionaria[50];
    int qtdFrac;
} binario;


binario* convertBinario(double valor);
mt* convertMantissa(binario* b);

void PrintMantissa(mt* M);
void PrintBinario(binario* b);

