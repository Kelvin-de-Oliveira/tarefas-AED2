# Compilador C
## Na verdade é um Editor / Interpretador

- Verificar blocos { } [ ] ( )  " "    ' '

- Sintaxe dos comandos

+ include

+ main

+ printf

+ scanf

+ if else

+ for

+ while

+ switch case

- Expressões

## Resolução: 
Não consegui implementar tudo que foi pedido. Consegui implementar apenas:
- Verificação dos blocos { } [ ] ( )  " "    ' '
- Análise sintática dos comandos:
1. include
2. main
3. printf
4. scanf

### Como meu código funciona: 
Implementei uma função que ler o conteúdo de um arquivo .txt e armazena em uma string (lerArquivoParaString). Depois eu implementei uma pilha que tem uma função para verificar todos so blocos { } [ ] ( )  " "    ' ', (verificarBlocosDelimitadores), caso existem qualquer bloco aberto ou fechado incorretamente, o programa retorna mensagem de erro e não avança para as análises sintáticas. 
Se todos so blocos delimitadores do código de entrada estão corretos, então existe uma função para verificar cada sintaxe da diretiva __#include__, da função __main__, da função __printf__ e da função __scanf__.

### Fluxo das análises sintáticas:

Com certeza que todos os blocos estão fechados corretamente, eu uso uma estrutura de lista chamada __listaTokens__, que usa de um função para tokenizar o conteúdo da string, em 6 tipos de tokens, sendo eles:PALAVRA_CHAVE, IDENTIFICADOR, DELIMITADOR, OPERADOR, LITERAL e ERRO. 
Depois disso eu percorro essa lista de tokens, em cada função de verificação de cada comando, e então monto uma espécie de "árvore sintática abstrata", e depois outra função para percorrer essa árvore e verificar  a sintaxe do comando. 

**Obs** : Para cada função, ou seja, cada comando eu percorro toda a lista, logo sempre qe houver o comando que a função está encarregada de analisar, ela trará uma reposta de correto ou errado. 

#### O que levei em conta nas análises:

Como o proprio enunciado pede, e conforme combinado em aula, eu só verifiquei a sintaxe dos comandos, não me preocupei com semântica, por exemplo:

 - __#include__: A diretiva include, eu verifiquei as duas formas principais usadas: arquivos do sistema: entre < e >
 e arquivos do proprio projeto: entre " ". Na pesquisa que fiz, teoricamente, a extensão do arquivo não interessa pois existe diversas extensões que podem ser usadas e como pela tokenizaçao tudo que está entre " " é interpretado como um único token do tipo LITERAL, a verificação ficou assim: Eu verifico se existe #, antes de include, se o delimitador for <, eu verifico se existe dois literais entre o proximo > (nome_arquivo e extensão). Se o delimitador for " ", apenas verifico se é seguido por uma literal.
- __main__: A função main eu verifico duas possibilidades: [int main () {}] e [int main(int argc, char *argv[]) {}], e exatamente essas, qualquer outra variação o programa provavelmente não se comportará como esperado. Verifico se existe o identificador 'int', antes da palavra_chave main e depois verifico se entre (), está vazio ou contém "int argc, char *argv[]". Conforme [aqui]([URL](https://learn.microsoft.com/pt-br/cpp/c-language/main-function-and-program-execution?view=msvc-170)), eu não verifiquei o "corpo" da função.
- __Printf__: Como disse eu não verifiquei semântica, então aqui nesta função se por exemplo você usar um especificador de formato para inteiro (%d),e nos argumentos passar um variavel double, eu não verificarei isso, eu verifico apenas o seguinte: printf("conteudo", argumento1, argumento2, ..); Verifco se o conteúdo de impressão está entre " ", se a função é finalizada com ;, e se o número de argumentos bate com o número de especificadores declarados ente as aspas duplas, mas __atenção__: Eu só verifico estes especificadores: %d, %i, %f, %c, %s e para formatação da impressão de números reais: %.2f, %.3f, etc. Se você usar qualquer outro especificador além destes, meu programa não reconhcerá e ao declarar o argumento relacionado a ele, meu program apontará erro de sintaxe.
-  __scanf__: A verificação da função scanf, se assemelha muito com a da função printf, também verifico se o número de argumentos é condizente com o numero de especificadores declarados dentro de " ", sendo os especificadores reconhecidos estes: %d, %i, %f, %c, %s, mas não me preocupei em verificar se os argumentos passados, correspondem ao tipo que o especificador referencia.

- __Outro ponto importante__: Se voce digitar qualquer das palavras_chaves: include, main, printf e scanf, errado
  meu programa apenas irá ignorar e não apontar erro algum, para "engatilhar", as funções de verificação sintatica de cada comando, é necessário pelo menos digita-las corretamente.

Junto com os arquivo está um arquivo chamado codigo.txt, onde está armazenado o último código que usei para validar o programa, para testar outras versões, cole lá seu código. 

__RECADO PARA O PROFESSOR__: Professor ❤️ ❤️  , meu computador deu erro de disco e até então não consegui concertar (vou precisar comprar outro ssd) e por isso precisei fazer todo o trabalho na plataforma replit.com pelo computado emprestado da minha namorada ou nos intervalos do estágio, tentei por lá simular um ambiente linux. Tive êxito? Só deus sabe! Tentei ao maximo empregar o conteúdo aprendido em aula, por favor tenha piedade de minha alma e se lembre disso ao corrigir 😭😭😭😭.

linha de compilação: 
> gcc -o editorC  editorC.c  pilhaBloco.c  listaTokens.c


Linha execução:
> ./editorC

Saída para entrada contida no arquivo .txt enviado:

Verificação de blocos e delimitadores concluída sem erros.

Analise sintatica comando #include: OK!

Analise sintatica comando #include: OK!

Analise sintatica da função main: OK!

Analise sintatica da função scanf:OK!

Analise sintatica da função scanf:OK!

Analise sintatica da função printf:OK!

Analise sintatica da função printf:OK!

Analise sintatica da função printf:OK!