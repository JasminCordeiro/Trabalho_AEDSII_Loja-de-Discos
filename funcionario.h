#ifndef funcionario_H
#define funcionario_H

#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>

typedef struct {
    int id;             
    char nome[50];     
    char cpf[15];       
} Funcionario;

// Cria funcionario.
Funcionario *criaFuncionario(int id, const char *nome, const char *cpf);

// Função para salvar um funcionário em um arquivo
void salvaFuncionario(Funcionario *func, FILE *arq);

// Função para ler um funcionário de um arquivo
Funcionario *leFuncionario(FILE *in);

// Função para imprimir os dados de um funcionário
void imprimeFuncionario(Funcionario *func);

// Função para obter o tamanho de um registro de funcionário em bytes
int tamanhoRegistroFuncionario();

// Função para obter a quantidade de registros em um arquivo
int qtdRegistrosFuncionario(FILE *arq);

// Função para embaralhar uma base de dados
void embaralhaFuncionario(int *vet, int max, int trocas);

// Função para criar uma base de dados desordenada pelo ID do funcionário
void criarBaseDesordenadaFuncionario(FILE *arq, int tam, int qtdTrocas);

// Função para imprimir a base de dados
void imprimirBaseFuncionario(FILE *arq);

// Realiza Busca sequencial em Funcionarios
Funcionario *buscaSequencialFuncionario(int id, FILE *arq);

// Realiza Busca Binaria em Funcionarios
Funcionario *buscaBinariaFuncionario(int id, FILE *arq, int inicio, int fim);

void bubbleSortFuncionarios(FILE *arq, int tam);

bool existeNaoCongelado(bool congelado[], int tamanho);

int selecaoPorSubstituicao(FILE * arq, int m);

void arvoreBinariaDeVencedores(int numeroParticao);
#endif
