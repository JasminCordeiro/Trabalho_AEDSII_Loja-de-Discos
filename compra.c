#include "compra.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int obterProximoIdCompra() {
    FILE *arquivo = fopen("ultimo_id.txt", "r+");
    int id_atual = 0;

    if (arquivo != NULL) {
        fscanf(arquivo, "%d", &id_atual);
        id_atual++;
        rewind(arquivo);
        fprintf(arquivo, "%d", id_atual);
        fclose(arquivo);
    } else {
        // Se o arquivo não existe, cria um com o ID inicial 1
        arquivo = fopen("ultimo_id.txt", "w");
        if (arquivo != NULL) {
            id_atual = 1;
            fprintf(arquivo, "%d", id_atual);
            fclose(arquivo);
        }
    }

    return id_atual;
}


// Cria uma nova instância de Compra
Compra* criaCompra(int disco_id, int id_cliente, int id_funcionario, int quantidade, float valor_total) {

    Compra *compra = (Compra *)malloc(sizeof(Compra));
    if (compra) memset(compra, 0, sizeof(Compra));

    compra->id = obterProximoIdCompra();
    compra->disco_id = disco_id;
    compra->id_cliente = id_cliente;
    compra->id_funcionario = id_funcionario;
    compra->quantidade = quantidade;
    compra->valor_total = valor_total;

    return compra;
}




// Salva uma instância de Compra em um arquivo
void salvaCompra(Compra *compra, FILE *arq) {
    fwrite(&compra->id, sizeof(int), 1, arq);
    fwrite(&compra->disco_id, sizeof(int), 1, arq);
    fwrite(&compra->id_cliente, sizeof(int), 1, arq);
    fwrite(&compra->id_funcionario, sizeof(int), 1, arq);
    fwrite(&compra->quantidade, sizeof(int), 1, arq);
    fwrite(&compra->valor_total, sizeof(float), 1, arq);
}

// Imprime uma instância de Compra
void imprimeCompra(Compra *compra) {
    printf("**********************************************\n");
    printf("Compra de ID: %d\n", compra->id);
    printf("Disco ID: %d\n", compra->disco_id);
    printf("ID Cliente: %d\n", compra->id_cliente);
    printf("ID Funcionario: %d\n", compra->id_funcionario);
    printf("Quantidade: %d\n", compra->quantidade);
    printf("Valor Total: %.2f\n", compra->valor_total);
    printf("**********************************************\n");
}

// Imprime todas as compras presentes no arquivo
void imprimirBaseCompra(FILE *arq) {
    printf("Imprimindo a base de dados...\n");

    rewind(arq);
    Compra *compra;

    while ((compra = leCompra(arq)) != NULL) {
        imprimeCompra(compra);
        free(compra);
    }
}

// Lê uma instância de Compra de um arquivo
Compra *leCompra(FILE *in) {
    Compra *compra = (Compra *)malloc(sizeof(Compra));

    if (fread(&compra->id, sizeof(int), 1, in) != 1) {
        free(compra);
        return NULL;
    }
    fread(&compra->disco_id, sizeof(int), 1, in);
    fread(&compra->id_cliente, sizeof(int), 1, in);
    fread(&compra->id_funcionario, sizeof(int), 1, in);
    fread(&compra->quantidade, sizeof(int), 1, in);
    fread(&compra->valor_total, sizeof(float), 1, in);

    return compra;
}

// Busca uma Compra por ID no arquivo
Compra *buscaSequencialCompra(int chave, FILE *arq) {
    Compra *p;
    int achou = 0;
    rewind(arq);
    while ((p = leCompra(arq)) != NULL) {
        if (p->id == chave) {
            achou = 1;
            break;
        }
    }
    if (achou == 1)
        return p;
    else {
        printf("Compra não encontrada\n");
        free(p);
        return NULL;
    }
}