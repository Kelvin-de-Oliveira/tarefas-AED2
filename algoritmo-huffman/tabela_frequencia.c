#include <stdio.h>

#define TAB 256 // tamamnho da tabela ASCII


void inicializar_tabela_zerada(unsigned int tab[]){
    int i;

    for(i = 0; i < TAB; i++){
        tab[i] = 0;
    }
}

void preencher_tabela(FILE *arquivo, unsigned int tab[]){
    unsigned char c;

    while (fread(&c, sizeof(unsigned char), 1, arquivo) >= 1) 
        tab[c]++;
    rewind(arquivo); 
}