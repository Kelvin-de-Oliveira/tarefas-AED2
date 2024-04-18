#include <stdio.h>
#include <stdlib.h>
#include "arvore-fila.h"

#define TAB 256 // tamamnho da tabela ASCII


struct fila{  
    NO *inicio;
    int tam;
};


Fila* inicializar_fila(){
    Fila* fila = (Fila*)malloc(sizeof(Fila));

	if(fila != NULL){
		fila->inicio = NULL;
        fila->tam = 0;
	}
    else{printf("\n\tErro ao alocar memoria para a arvore-fila");}
    return fila;
}

void inserir_ordenado_fila(Fila* fila, NO* no){ // a inserção na fila sera ordenada pela frequencia de cada caracter sendo do menor para o maior 
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

NO* remover_primeiro_na_fila(Fila* fila){
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

NO* construir_arvore_huffman(Fila* fila){ // retorna a raiz da arvore de huffman
    NO *aux1, *aux2, *noDeArvore; 

    while(fila->tam > 1){
        aux1 = remover_primeiro_na_fila(fila);
        aux2 = remover_primeiro_na_fila(fila);
        noDeArvore = (NO*) malloc(sizeof(NO));
        if(noDeArvore != NULL){
            noDeArvore->caracter = 'H';
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

int retorna_altura_arvore(NO* raiz){
    int esq, dir;

    if(raiz == NULL)
        return -1;
    else{
        esq = retorna_altura_arvore(raiz->esq) + 1;
        dir = retorna_altura_arvore(raiz->dir) + 1;
        if(esq > dir)
            return esq;
        else return dir;
    } 
}

void liberar_arvore(NO *raiz) {
    if (raiz != NULL) {
        liberar_arvore(raiz->esq); 
        liberar_arvore(raiz->dir); 
        free(raiz);                  
    }
}

/*essas funções de impressao foram criadas apenas para testes durante a implementacao do algoritimo
para verificar se as estruturas necessarias estavam sendo construidas corretamente*/

/*void imprimir_arvore(NO* raiz, int tam){
    if(raiz->esq == NULL && raiz->dir == NULL)
        printf("\tFolha: %c\tAltura: %d\n", raiz->caracter, tam);
    else{
        imprimir_arvore(raiz->esq, tam + 1);
        imprimir_arvore(raiz->dir, tam + 1);
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
}*/
