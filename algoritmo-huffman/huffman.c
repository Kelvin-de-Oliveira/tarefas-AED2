#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <windows.h>
#include "tabela_frequencia.h"
#include "arvore-lista.h"

#define TAB 256


int main (){

    FILE* file;
    unsigned int tab[TAB];
    Fila* fila_arvore;
    NO* raiz;

    setlocale(LC_ALL, "pt_BR");
    
    file = fopen ("texto.txt", "r");

    if(file == NULL){
        printf("Arquivo não foi encontrado");
        return 0;
    }

    inicializa_tabela_zerada(tab);
    preenche_tabela(file, tab);
    /*printf("Vetor:\n");
    for(int i = 0; i < TAB; i++) {
        if(tab[i] > 0)
            printf("\t %d =   %u =  %c\n", i, tab[i], i);
    }
    printf("\n");*/
    fila_arvore = inicializa_fila();
    preencher_fila(fila_arvore, tab);
    //imprimir_fila(fila_arvore);
    raiz = construir_arvore(fila_arvore);
    imprimir_arvore(raiz, 0);

   
    fclose(file);
    free(fila_arvore);

    return 0;
}