
#include <stdlib.h>
#include <string.h>
#include "arvore-fila.h"

#define TAB 256

/*Implementado por Kelvin de Oliveira, usando de referencia os videos do canal 
Programe seu futuro, disponivel em:  https://www.youtube.com/@programeseufuturo */

char** alocar_tabela(int colunas){ // alocar espaço necessário para a tabela-dicionario, a tabela que armazena a seqeuncia de 0 e 1 equivalente a cada caracter
    char **dicionario;
    int i;

    dicionario = (char**) malloc(sizeof(char*) * TAB);

    for( i = 0; i < TAB; i++)
        dicionario[i] = calloc(colunas, sizeof(char));
    return dicionario;
}

void preencher_dicionario(char** dicionario, NO* raiz, char *codigo, int colunas){ // preenche a tabela com cada string de 0 e 1 correspodente a cada caracter do texto 
    char esquerda[colunas], direita[colunas];
    
    if(raiz->esq == NULL && raiz->dir == NULL)
        strcpy(dicionario[raiz->caracter], codigo);
    else{
        strcpy(esquerda, codigo);
        strcpy(direita, codigo);
        strcat(esquerda, "0");
        strcat(direita, "1");
        preencher_dicionario(dicionario, raiz->esq, esquerda, colunas);
        preencher_dicionario(dicionario, raiz->dir, direita, colunas);
    }
}

/*essas funções de impressao foram criadas apenas para testes durante a implementacao do algoritimo
para verificar se as estruturas necessarias estavam sendo construidas corretamente*/

/*void imprimir_tabela_dicionario(char** dicionario){
    int i;

    for(i = 0; i < TAB; i++){
        if(strlen(dicionario[i]) > 0)
            printf("\t%4d: %s\n", i, dicionario[i]);
    }

}*/

