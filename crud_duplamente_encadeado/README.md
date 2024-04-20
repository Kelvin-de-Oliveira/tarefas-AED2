# Crud estatico 
Consegui implementar apenas a versao estatica do problema. appCadastro é um crud em um
vetor _(apesar do professor pedir uma matriz no enunciado, conversando com ele em aula chegamos à conclusao que era possivel resolver o problema apenas com um vetor de structs)_ de structs do tipo aluno. Na verdade é definida uma outra struct Turma, que contem 50 structs alunos e a
quantidade de alunos cadastrados. 
Aluno está definido em listaCadastro.h, appCadastro.c utiliza dessa estrutura para implementar as operações do crud, que estao definidas em appCadastro.h, o menu do crud é implementando em main.c.

Linha de compilação:
>gcc main.c appCadastro.c listaCadastro.c -o crud.exe
Execução:
>.\crud.exe