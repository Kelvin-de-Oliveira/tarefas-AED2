# Desafio Hash
Seu trabalho deverá ler o arquivo fornecido "numeros_aleatorios.txt", e criar uma função hash para armazenamento das chaves em um vetor com no máximo 2000 posições.

O trabalho deverá também carregar um arquivo fornecido pelo executor chamado "checkin.txt" com a mesma estrutura dos aquivo "numeros_aleatorios.txt".

Seu programa deverá buscar cada uma das chaves do arquivo "checkin.txt" na relação de chaves organizadas a partir do arquivo arquivo "numeros_aleatorios.txt".

Apresentar em tela as seguintes informações:

- Quantidade de passos necessários para encontrar a chave

- Quantidade de colisões identificadas

- Tempo necessário para encontrar


## Resolução: 

- O meu codigo, além do que é pedido, também registra o resultado da busca em um arquvivo .txt, intitulado "resultado_busca", pois a visualização de todo o resultado pode ser comprometida a depender do prompt/terminal utilizado. 
- O codigo foi testado no subsistema windows, WSL 2, com distribuição Ubuntu. Para testar criei também um arquivo "checkin.txt" e nele apenas colei o conteúdo do arquivo "numero_aleatorios.txt"
- Conforme o enunciado, e esperando que o arquivo "checkin.txt" tenha a mesma estrutura do arquivo "numeros_aleatorios.txt", o codigo foi implementado de forma que espera receber apenas números inteiros positivos (unsigned int), por motivos de maior simplicidade na implementação e eficiencia. Caso seja inserido numeros inteiros negativos, haverá erros na execução do programa. 
- Sobre o resultado da busca, é impresso uma variavel do tipo int chamada de "Encontrado", quando ela for igual a 0, é porque a chave não foi encontrada, e quando for igual a 1 é porque foi encontrada.
- Utilizei a técnica de encadeamento para lidar com as colisões e criei uma função hash utilizando o método da multiplicação, conforme: https://edisciplinas.usp.br/mod/hvp/view.php?id=3305382.

Para compilar o codigo:
> gcc - o desafioHash desafioHash.c 

