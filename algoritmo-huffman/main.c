#include <stdio.h>
#include <stdlib.h>
// #include<windows.h> /*meu sistema operacional é o windows e preciso incluir essa bilbioteca para mudar o padroa de saida do console e nao ter problemas com caracteres especiais e acentuaçao*/
#include<string.h>
#include "tabela_frequencia.h"
#include "arvore-fila.h"
#include "tabela_dicionario.h"
#include "huffman.h"

#define TAB 256

/*Implementado por Kelvin de Oliveira, usando de referencia os videos do canal 
Programe seu futuro, disponivel em:  https://www.youtube.com/@programeseufuturo 
As adptações aqui feitas foram para se ler o texto diretamente de um arquivo de texto, modularizar as estruturas
e adapta-las para o problema especifico. */


int main (){

    FILE* file;
    unsigned int tab[TAB];
    Fila* fila_arvore;
    NO* arvore_huffman;
    char** tabela_dicionario;
    char *codificado;
    int i, colunas;
    
    

    file = fopen ("texto.txt", "r");

    if(file == NULL){
        printf("Arquivo nao foi encontrado");
        return 0;
    }

    inicializar_tabela_zerada(tab);
    preencher_tabela(file, tab);
    fila_arvore = inicializar_fila();
    preencher_fila(fila_arvore, tab);
    arvore_huffman = construir_arvore_huffman(fila_arvore);
    colunas = retorna_altura_arvore(arvore_huffman);
    tabela_dicionario = alocar_tabela(colunas);
    preencher_dicionario(tabela_dicionario, arvore_huffman,"", colunas);
    codificado = codificar(tabela_dicionario, file);
    compactar(codificado);
    descompactar(arvore_huffman);
    
    fclose(file);
    free(fila_arvore);  // precisa de procedimento 
    free(arvore_huffman); // precisa de procedimento
    free(tabela_dicionario); // precisa de procedimento


    return 0;
}