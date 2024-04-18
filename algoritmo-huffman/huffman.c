#include <stdio.h>
#include <stdlib.h>
#include<string.h>
#include "tabela_frequencia.h"
#include "arvore-fila.h"
#include "tabela_dicionario.h"


unsigned int calcula_tamanho_codificado(char** dicionario, FILE* texto){
    unsigned int tam = 0;
    unsigned char c;
       
    while (fread(&c, sizeof(unsigned char), 1, texto) >= 1)
        tam = tam + strlen(dicionario[c]);
    rewind(texto);
    return tam + 1;
}

char* codificar(char** dicionario, FILE* texto){// cria a a string de 0 e 1 que representa todo o texto do arquivo compactado
    unsigned int tam = calcula_tamanho_codificado(dicionario, texto);
    char* codificado = calloc(tam, sizeof(char));
    unsigned char c;

    if(codificado == NULL){
        printf("\nErro ao alocar memoria para o texto codificado");
        return 0;
    }

    while (fread(&c, sizeof(unsigned char), 1, texto) >= 1)
        strcat(codificado, dicionario[c]);
    rewind(texto);
    return codificado;
}

/*Funcao a baixo foi implementada apenas para verificar se a funcao de codificar estava correta*/

/*char* decodificar(NO* raiz, char* codificado){// traduz a string de 0 e 1 de voltar para texto
    NO* aux = raiz;
    int i = 0;
    char texto_aux[2];
    char *decodificado = calloc(strlen(codificado), sizeof(char));

    while (codificado[i] != '\0'){
        if(codificado[i] == '0')
            aux = aux->esq;
        else 
            aux = aux->dir;

        if(aux->esq == NULL && aux->dir == NULL){
            texto_aux[0] = aux->caracter;
            texto_aux[1] = '\0';
            strcat(decodificado, texto_aux);
            aux = raiz;
        }
        i++;
    }
    return decodificado;
}*/

void compactar(unsigned char codificado[]){
    FILE* compactado = fopen("compactado.dat", "wb");
    int i = 0, j = 7;
    unsigned char mascara, byte = 0;
    
    if(compactado == NULL){
        printf("\nErro ao abrir/gerar arquivo compactado em 'compactar'");
        return;
    }
    else{
        while(codificado[i] != '\0'){
            mascara = 1;
            if(codificado[i] == '1'){
                mascara = mascara << j;
                byte = byte | mascara;
            }
            j--;
            if(j < 0){
                fwrite(&byte, sizeof(unsigned char), 1, compactado);
                byte = 0;
                j = 7;
            }
            i++;
        }
        if(j != 7)
            fwrite(&byte, sizeof(unsigned char), 1, compactado);
        fclose(compactado);
    }
}

unsigned int verifica_bit(unsigned char byte, int i){
    unsigned char mascara = (1 << i);
    return  byte  & mascara;
} 


void descompactar(NO* raiz){
    FILE* compactado = fopen("compactado.dat", "rb");
    FILE* descompactado = fopen("descompactado.txt", "w");
    NO* aux = raiz;
    int i = 0;
    unsigned char byte;

     if(compactado == NULL){
        printf("\nErro ao abrir  arquivo compactado em 'descompactar");
        return;
    }
    else{
        while(fread(&byte, sizeof(unsigned char), 1, compactado) >= 1){
            for(i = 7; i >= 0; i--){
                if(verifica_bit(byte, i))
                    aux = aux->dir;
                else
                    aux = aux->esq;
                if(aux->esq == NULL && aux->dir == NULL){
                    fwrite(&(aux->caracter), sizeof(unsigned char), 1, descompactado);
                    aux = raiz;
                }
            }
        }
        fclose(compactado);
        fclose(descompactado);
    }
}


