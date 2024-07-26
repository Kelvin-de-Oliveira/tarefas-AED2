
#define CAPACIDADE_INICIAL 10

typedef struct {
  char *itens;
  int topo;
  int capacidade;
} PilhaBlocos;

PilhaBlocos *criarPilha(int capacidade);
void liberarPilha(PilhaBlocos *pilha);
void empilhar(PilhaBlocos *pilha, char item);
char desempilhar(PilhaBlocos *pilha);
char topo(PilhaBlocos *pilha);
int pilhaVazia(PilhaBlocos *pilha);
int verificarBlocosDelimitadores(const char *codigo);
