#include "funcionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cria funcionario.
Funcionario *criaFuncionario(int id, const char *nome, const char *cpf) {
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));
    if (func) memset(func, 0, sizeof(Funcionario));
    func->id = id;
    strncpy(func->nome, nome, sizeof(func->nome) - 1);
    strncpy(func->cpf, cpf, sizeof(func->cpf) - 1);
    return func;
}

// Salva funcionario no arquivo out, na posição atual do cursor
void salvaFuncionario(Funcionario *func, FILE *out) {
    fwrite(&func->id, sizeof(int), 1, out);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), out);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), out);
}

// Lê um funcionário do arquivo na posição atual do cursor
// Retorna um ponteiro para funcionário lido do arquivo
Funcionario *leFuncionario(FILE *in) {
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));
    if (0 >= fread(&func->id, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    return func;
}

// Imprime funcionario
void imprimeFuncionario(Funcionario *func) {
    printf("**********************************************\n");
    printf("Funcionario de ID: %d\n", func->id);
    printf("Nome: %s\n", func->nome);
    printf("CPF: %s\n", func->cpf);
    printf("**********************************************\n");
}

// Retorna tamanho do funcionario em bytes
int tamanhoRegistroFuncionario() {
    return sizeof(int)  // id
           + sizeof(char) * 50 // nome
           + sizeof(char) * 15; // cpf
}

// Retorna a quantidade de registros no arquivo
int qtdRegistrosFuncionario(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / tamanhoRegistroFuncionario();
    return tam;
}

// Cria a base de dados ordenada pelo ID do funcionário
void criarBaseOrdenadaFuncionario(FILE *out, int tam) {
    int vet[tam];
    Funcionario *f;

    for(int i = 0; i < tam; i++)
        vet[i] = i + 1;

    printf("\nGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        f = criaFuncionario(vet[i], "A", "000.000.000-00");
        salvaFuncionario(f, out);
    }

    free(f);
}

// Embaralha base de dados
void embaralhaFuncionario(int *vet, int max, int trocas) {
    srand(time(NULL));
    for (int i = 0; i <= trocas; i++) {
        int j = rand() % (max - 1);
        int k = rand() % (max - 1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

// Cria a base de dados desordenada pelo ID do funcionário
void criarBaseDesordenadaFuncionario(FILE *out, int tam, int qtdTrocas) {
    int vet[tam];
    Funcionario *f;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    embaralhaFuncionario(vet, tam, qtdTrocas);

    printf("\nGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        f = criaFuncionario(vet[i], "A", "000.000.000-00");
        salvaFuncionario(f, out);
    }

    free(f);
}

// Imprime a base de dados
void imprimirBaseFuncionario(FILE *out) {
    printf("Imprimindo a base de dados...\n");

    rewind(out);
    Funcionario *f;

    while ((f = leFuncionario(out)) != NULL)
        imprimeFuncionario(f);

    free(f);
}
