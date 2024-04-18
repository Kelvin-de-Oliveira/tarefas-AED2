typedef struct no{
    unsigned char  caracter;
    int frequencia;
    struct no *esq, *dir, *prox;
}NO; // como varias outras estruturas vao manipular o tipo no precisei deixar ele visivel na interface da estrutura 

typedef struct fila Fila;

Fila* inicializar_fila();

void inserir_ordenado_fila(Fila* fila, NO* no);

void preencher_fila(Fila* fila, unsigned int tab[]);

NO* construir_arvore_huffman(Fila* fila);

int retorna_altura_arvore(NO* raiz);

void liberar_arvore(NO *raiz);

//void imprimir_fila(Fila* fila);

//void imprimir_arvore(NO* raiz, int tam);