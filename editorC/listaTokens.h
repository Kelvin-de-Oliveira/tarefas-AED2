typedef enum {
  PALAVRA_CHAVE,
  IDENTIFICADOR,
  DELIMITADOR,
  OPERADOR,
  LITERAL,
  ERRO
} TipoToken;

typedef struct {
  TipoToken tipo;
  char *valor;
  int linha;
  int coluna;
} Token;

typedef struct {
  Token *tokens;
  int tamanho;
  int capacidade;
} ListaTokens;

void inicializarListaTokens(ListaTokens *lista);
void adicionarToken(ListaTokens *lista, TipoToken tipo, const char *valor,
                    int linha, int coluna);
void liberarListaTokens(ListaTokens *lista);
ListaTokens tokenizarCodigo(const char *codigo);
void imprimirTokens(ListaTokens tokens);