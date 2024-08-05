
#ifndef disco_H_INCLUDED
#define disco_H_INCLUDED

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;             
    char titulo[100];   
    char artista[100];  
    char genero[50];   
    int ano;            
    float preco;        
    int estoque;       
} Disco;

// Cria disco.
Disco *criaDisco(int id, const char *titulo, const char *artista, const char *genero, int ano, float preco, int estoque);

// Salva disco no arquivo out, na posição atual do cursor
void salvaDisco(Disco *disco, FILE *out);

// Lê um disco do arquivo na posição atual do cursor
// Retorna um ponteiro para o disco lido do arquivo
Disco *leDisco(FILE *in);

// Imprime disco
void imprimeDisco(Disco *disco);

// Retorna o tamanho do disco em bytes
int tamanhoRegistroDisco();

// Retorna a quantidade de registros no arquivo
int qtdRegistrosDisco(FILE *arq);

// Cria a base de dados ordenada pelo ID do disco
void criarBaseOrdenadaDisco(FILE *out, int tam);

// Embaralha base de dados
void embaralhaDisco(int *vet, int max, int trocas);

// Cria a base de dados desordenada pelo ID do disco
void criarBaseDesordenadaDisco(FILE *out, int tam, int qtdTrocas);

// Imprime a base de dados
void imprimirBaseDisco(FILE *out);

#endif