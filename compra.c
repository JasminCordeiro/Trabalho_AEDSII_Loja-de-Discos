#include "compra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

Compra* criaCompra(int id, int disco_id, const char *cpf_cliente, int id_funcionario, int quantidade, float valor_total) {
    // Aloca memória para a nova instância de Compra
    Compra *compra = (Compra *)malloc(sizeof(Compra));
    if (compra) memset(compra, 0, sizeof(Compra)); // Inicializa a memória alocada com zero

    // Preenche os campos da estrutura com os valores fornecidos
    compra->id = id;
    compra->disco_id = disco_id;
    strncpy(compra->cpf_cliente, cpf_cliente, sizeof(compra->cpf_cliente) - 1);
    compra->id_funcionario = id_funcionario;
    compra->quantidade = quantidade;
    compra->valor_total = valor_total;

    return compra;
}

void salvaCompra(Compra *compra, FILE *arq) {
    fwrite(&compra->id, sizeof(int), 1, arq);
    fwrite(&compra->disco_id, sizeof(int), 1, arq);
    fwrite(compra->cpf_cliente, sizeof(char), sizeof(compra->cpf_cliente), arq);
    fwrite(&compra->id_funcionario, sizeof(int), 1, arq);
    fwrite(&compra->quantidade, sizeof(int), 1, arq);
    fwrite(&compra->valor_total, sizeof(float), 1, arq);
}

void imprimeCompra(Compra *compra) {
    printf("**********************************************\n");
    printf("Compra de ID: %d\n", compra->id);
    printf("Disco ID: %d\n", compra->disco_id);
    printf("CPF Cliente: %s\n", compra->cpf_cliente);
    printf("ID Funcionario: %d\n", compra->id_funcionario);
    printf("Quantidade: %d\n", compra->quantidade);
    printf("Valor Total: %.2f\n", compra->valor_total);
    printf("**********************************************\n");
}

void imprimirBaseCompra(FILE *arq) {
    printf("Imprimindo a base de dados...\n");

    rewind(arq);
    Compra *compra;

    while ((compra = leCompra(arq)) != NULL) {
        imprimeCompra(compra);
        free(compra);
    }
}

Compra *leCompra(FILE *in) {
    Compra *compra = (Compra *)malloc(sizeof(Compra));
   
    // Lê os dados do arquivo para a estrutura Compra
      if (fread(&compra->id, sizeof(int), 1, in) != 1) {
        free(compra);
        return NULL;
    }
    fread(&compra->disco_id, sizeof(int), 1, in);
    fread(compra->cpf_cliente, sizeof(char), sizeof(compra->cpf_cliente), in);
    fread(&compra->id_funcionario, sizeof(int), 1, in);
    fread(&compra->quantidade, sizeof(int), 1, in);
    fread(&compra->valor_total, sizeof(float), 1, in);

    return compra;
}

Compra *buscaSequencialCompra(int chave, FILE *arq){

    Compra *p;
    int achou;
    rewind(arq);
    while ((p = leCompra(arq)) != NULL){

        if(p->id == chave){
           //return d;
           achou = 1;
           break;
        }
    }
        if(achou == 1)
            return p;
        else printf("Compra nao encontrado");

        free(p);
}