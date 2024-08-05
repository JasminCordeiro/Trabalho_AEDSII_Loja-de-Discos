#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cria cliente.
Cliente *criaCliente(int id, const char *nome, const char *cpf, const char *telefone) {
    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    cliente->id = id;
    strncpy(cliente->nome, nome, sizeof(cliente->nome) - 1);
    strncpy(cliente->cpf, cpf, sizeof(cliente->cpf) - 1);
    strncpy(cliente->telefone, telefone, sizeof(cliente->telefone) - 1);
    return cliente;
}

// Salva cliente no arquivo out, na posição atual do cursor
void salvaCliente(Cliente *cliente, FILE *out) {
    fwrite(&cliente->id, sizeof(int), 1, out);
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), out);
    fwrite(cliente->cpf, sizeof(char), sizeof(cliente->cpf), out);
    fwrite(cliente->telefone, sizeof(char), sizeof(cliente->telefone), out);
}

// Lê um cliente do arquivo na posição atual do cursor
Cliente *leCliente(FILE *in) {
    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
    if (0 >= fread(&cliente->id, sizeof(int), 1, in)) {
        free(cliente);
        return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    fread(cliente->cpf, sizeof(char), sizeof(cliente->cpf), in);
    fread(cliente->telefone, sizeof(char), sizeof(cliente->telefone), in);
    return cliente;
}

// Imprime cliente
void imprimeCliente(Cliente *cliente) {
    printf("**********************************************\n");
    printf("Cliente de ID: %d\n", cliente->id);
    printf("Nome: %s\n", cliente->nome);
    printf("CPF: %s\n", cliente->cpf);
    printf("Telefone: %s\n", cliente->telefone);
    printf("**********************************************\n");
}

// Retorna tamanho do cliente em bytes
int tamanhoRegistroCliente() {
    return sizeof(int)  // id
           + sizeof(char) * 100 // nome
           + sizeof(char) * 15  // cpf
           + sizeof(char) * 15; // telefone
}

// Retorna a quantidade de registros no arquivo
int qtdRegistrosCliente(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / tamanhoRegistroCliente();
    return tam;
}

// Cria a base de dados ordenada pelo ID do cliente
void criarBaseOrdenadaCliente(FILE *out, int tam) {
    int vet[tam];
    Cliente *cliente;

    for(int i = 0; i < tam; i++)
        vet[i] = i + 1;

    printf("\nGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        cliente = criaCliente(vet[i], "Nome", "000.000.000-00", "0000-0000");
        salvaCliente(cliente, out);
    }

    free(cliente);
}

// Embaralha base de dados
void embaralhaCliente(int *vet, int max, int trocas) {
    srand(time(NULL));
    for (int i = 0; i <= trocas; i++) {
        int j = rand() % (max - 1);
        int k = rand() % (max - 1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

// Cria a base de dados desordenada pelo ID do cliente
void criarBaseDesordenadaCliente(FILE *out, int tam, int qtdTrocas) {
    int vet[tam];
    Cliente *cliente;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    embaralhaCliente(vet, tam, qtdTrocas);

    printf("\nGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        cliente = criaCliente(vet[i], "Nome", "000.000.000-00", "0000-0000");
        salvaCliente(cliente, out);
    }

    free(cliente);
}

// Imprime a base de dados
void imprimirBaseCliente(FILE *out) {
    printf("Imprimindo a base de dados...\n");

    rewind(out);
    Cliente *cliente;

    while ((cliente = leCliente(out)) != NULL)
        imprimeCliente(cliente);

    free(cliente);
}
