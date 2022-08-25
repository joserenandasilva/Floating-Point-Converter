#include "mantissa.h"
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>


//************************************************************//
//                    Function generic                       //
//**********************************************************//

int verificarSinal(double valor){

    if(valor >= 0)
        return 0;
    else 
        return 1;
}

//************************************************************//
//                    Function binario                       //
//**********************************************************//

binario* createBinario(){
        binario* novo = (binario*) malloc(sizeof(binario));
        novo->qtdInt = 0;
        novo->qtdFrac = 0;
        return novo;
}

void addInt(binario* b, int valor){
        b->inteira[b->qtdInt] = valor;
        b->qtdInt++;
}

void addFrac(binario* b, int valor){
        b->fracionaria[b->qtdFrac] = valor;
        b->qtdFrac++;
}

bool inteiraForBinario(binario* b,int valor){
    int aux;
    if (valor/2 !=  0) {
        aux = valor/2;
        inteiraForBinario(b,aux); 
        addInt(b,valor % 2);  
        
    }
    else{
        addInt(b,valor % 2); 
    }  
}

bool fracionarioForBinario(binario* b, double valor){
    
    if(b->qtdFrac < 50){
        valor *= 2;
        int resto = (int)valor;
        valor -= resto;
        addFrac(b,resto);
        fracionarioForBinario(b,valor);
    }
    return true;    
}

binario* convertBinario(double valor){

        binario* b = createBinario();
        b->sinal = verificarSinal(valor);

        if(valor < 0) valor *= -1;
        int inteira = (int)valor;
        double fracionaria = valor - inteira;

        
        inteiraForBinario(b,inteira);
        fracionarioForBinario(b,fracionaria);
        
        return b;
}

//************************************************************//
//                    Function mantissa                      //
//**********************************************************//

mt* createMantissa(){
    mt* novo =(mt*) malloc(sizeof(mt));
    novo->qtdExp = 0;
    novo->qtdMant = 0;
}

int discoverExpoente(binario* b, int* posicao){
    int exp = 0;
    int posica = 0;

    if(b->qtdInt > 0){
        for (int i = 0; i < b->qtdInt; i++)
        {
            if(b->inteira[i] == 1){
                exp = b->qtdInt - (i+1);
                posica = i + 1;
                *posicao = posica;
                return exp + 127;
            }
        }
    }

    for (int i = 0; i < b->qtdFrac; i++)
        {
            if(b->fracionaria[i] == 1){
                exp = (i+1) * -1;
                posica = i + 1;
                *posicao = posica;     
                return exp + 127;
            }
        }

};

mt* convertMantissa(binario* b){

        mt* m = createMantissa();
        int posicao = 0;
        int auxExp[8]= {0};
        int exp = discoverExpoente(b, &posicao);
        binario* expoente = convertBinario(exp);
        m->sinal = b->sinal;
        if(expoente->qtdInt < 8){

            for(int i = 8 - (expoente->qtdInt); i < 8; i++){
                auxExp[i] = expoente->inteira[i-1];
            }
        }
        else{
            for(int i = 0 ; i < 8; i++){
                auxExp[i] = expoente->inteira[i];
            }
        }


        for (int i = 0; i < 8; i++)
        {
            m->expoente[i] = auxExp[i];
            m->qtdExp++;
        }

    

            for (int i = 0; i < b->qtdInt - 1; i++)
            {
                
                m->mantissa[i] = b->inteira[i+1];
                m->qtdMant++;
            }

            int aux = m->qtdMant;
            for(int j = 0; j < 23 - aux; j++){
                m->mantissa[m->qtdMant] = b->fracionaria[j];
                m->qtdMant++;
            }   
        
       
    
        return m;
}


//************************************************************//
//                    Function prints                        //
//**********************************************************//
void PrintMantissa(mt* M){

    printf("%d ", M->sinal);
     for (int i = 0; i < M->qtdExp; i++)
        {
            printf("%d", M->expoente[i]);
        }
    printf(" ");
    for (int i = 0; i < M->qtdMant; i++)
    {
        printf("%d", M->mantissa[i]);
    }
   

}

void PrintBinario(binario* b){

        printf("qtdInt:%d  qtdFrac%d sinal:%d\n", b->qtdInt, b->qtdFrac, b->sinal);
        for(int i =0 ; i < b->qtdInt; i++){
            printf("%d", b->inteira[i]);
        }
        printf(",");
        for(int i =0 ; i < b->qtdFrac; i++){
            printf("%d", b->fracionaria[i]);
        }
};