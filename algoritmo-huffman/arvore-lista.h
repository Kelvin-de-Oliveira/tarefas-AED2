
typedef struct no NO;

typedef struct estrutura Fila;

Fila* inicializa_fila();

void inserir_ordenado_fila(Fila* fila, NO* no);

void preencher_fila(Fila* fila, unsigned int tab[]);

void imprimir_fila(Fila* fila);

NO* construir_arvore(Fila* fila);

void imprimir_arvore(NO* raiz, int tam);