
unsigned int calcula_tamanho_codificado(char** dicionario, FILE* texto);

char* codificar(char** dicionario, FILE* texto);

void compactar(unsigned char codificado[]);

unsigned int verifica_bit(unsigned char byte, int i);

void descompactar(NO* raiz);

//*char* decodificar(NO* raiz, char* codificado)