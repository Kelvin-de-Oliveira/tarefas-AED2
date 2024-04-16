#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include "arvore-lista.h"

#define TAB 256


struct no{
    unsigned char  caracter;
    int frequencia;
    struct no *esq, *dir, *prox;
};

struct estrutura{
    NO *inicio;
    int tam;
};


Fila* inicializa_fila(){
    Fila* fila = (Fila*)malloc(sizeof(Fila));
	if(fila != NULL){
		fila->inicio = NULL;
        fila->tam = 0;
	}
    else{printf("\n\tErro ao alocar memoria para a fila");}
	
    return fila;
}


void inserir_ordenado_fila(Fila* fila, NO* no){
    NO* aux;
    
    if(fila->inicio == NULL){
        fila->inicio = no;
    }
    else if(no->frequencia < fila->inicio->frequencia){
        no->prox = fila->inicio;
        fila->inicio = no;
    }
    else{
        aux = fila->inicio;
        while(aux->prox != NULL && aux->prox->frequencia <= no->frequencia)
            aux = aux->prox;
        no->prox = aux->prox;
        aux->prox = no;
    }

    fila->tam++;
}

void preencher_fila(Fila* fila, unsigned int tab[]){
    int i;
    NO* novo;

    for(i = 0; i < TAB; i++){
        if(tab[i] > 0){
            novo = (NO*) malloc(sizeof(NO));
            if(novo != NULL){
                novo->caracter = i;
                novo->frequencia = tab[i];
                novo->prox = NULL;
                novo->esq = NULL;
                novo->dir = NULL;
                inserir_ordenado_fila(fila, novo);
            }
            else{
                printf("\n\tErro para alocar memoria ao preencher lista de frequencia");
                break;
            }

        }
    }
    
}

void imprimir_fila(Fila* fila){
    if(fila->inicio == NULL)
        printf("\n\ta fila esta vazia\n");

    NO* aux;
    aux = fila->inicio;

    while(aux != NULL){
        printf("\tCaracter: %c Frequencia: %d\n", aux->caracter, aux->frequencia);
        aux = aux->prox;
    }
}


NO* remover_primeiro_no_fila(Fila* fila){
    NO* aux;
    aux = NULL; // por segurança, caso a lista esteja vazia não retorna lixo de memoria 

    if(fila->inicio != NULL){
        aux = fila->inicio;
        fila->inicio = fila->inicio->prox;
        aux->prox = NULL;
        fila->tam--;
    }

    return aux;
}


NO* construir_arvore(Fila* fila){ // retorna a raiz da arvore de huffman
    NO *aux1, *aux2, *noDeArvore; 
    while(fila->tam > 1){
        aux1 = remover_primeiro_no_fila(fila);
        aux2 = remover_primeiro_no_fila(fila);
        noDeArvore = (NO*) malloc(sizeof(NO));
        if(noDeArvore != NULL){
            noDeArvore->caracter = ' ';
            noDeArvore->frequencia = aux1->frequencia + aux2->frequencia;
            noDeArvore->esq = aux1;
            noDeArvore->dir = aux2;
            noDeArvore->prox = NULL;
            inserir_ordenado_fila(fila, noDeArvore);
        }
        else{
            printf("\n\tNão foi possivel alocar memoria para o no da arvore");
            break;
        }
    }
    return fila->inicio;
    
}

void imprimir_arvore(NO* raiz, int tam){
    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\tFolha: %c \tAltura: %d\n", raiz->caracter, tam);
    else{
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
    }
}

