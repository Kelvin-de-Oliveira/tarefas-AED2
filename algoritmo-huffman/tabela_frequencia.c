#include <stdio.h>
#include <stdlib.h> 
#include <locale.h>

#define TAB 256 // tamamnho da tabela ASCII


void inicializa_tabela_zerada(unsigned int tab[]){
    int i;
    for(i = 0; i < TAB; i++){
        tab[i] = 0;
    }
}

void preenche_tabela(FILE *arquivo, unsigned int tab[]){
    unsigned char c;

    setlocale(LC_ALL, " ");

    while (fread(&c, sizeof(unsigned char), 1, arquivo) >= 1) // a função fread sempre retorna o numero de caractere que ela conseguiu ler, nesse caso ao chegar ao fim do arquivo e nao conseguir ler nada ela retornara 0
    {
        tab[c]++;
    }
    rewind(arquivo); 
}