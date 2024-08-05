#ifndef CLIENTE_H
#define CLIENTE_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;             
    char nome[100];     
    char cpf[15];       
    char telefone[15];  
} Cliente;

// Cria cliente.
Cliente *criaCliente(int id, const char *nome, const char *cpf, const char *telefone);

// Salva cliente no arquivo out, na posição atual do cursor
void salvaCliente(Cliente *cliente, FILE *out);

// Lê um cliente do arquivo na posição atual do cursor
// Retorna um ponteiro para o cliente lido do arquivo
Cliente *leCliente(FILE *in);

// Imprime cliente
void imprimeCliente(Cliente *cliente);

// Retorna tamanho do cliente em bytes
int tamanhoRegistroCliente();

// Retorna a quantidade de registros no arquivo
int qtdRegistrosCliente(FILE *arq);

// Cria a base de dados ordenada pelo ID do cliente
void criarBaseOrdenadaCliente(FILE *out, int tam);

// Embaralha base de dados
void embaralhaCliente(int *vet, int max, int trocas);

// Cria a base de dados desordenada pelo ID do cliente
void criarBaseDesordenadaCliente(FILE *out, int tam, int qtdTrocas);

// Imprime a base de dados
void imprimirBaseCliente(FILE *out);

#endif
