#ifndef COMPRA_H
#define COMPRA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;             
    int disco_id;       
    char cpf_cliente[15];
    int id_funcionario; 
    int quantidade;     
    float valor_total; 
} Compra;

Compra* criaCompra(int id, int disco_id, const char *cpf_cliente, int id_funcionario, int quantidade, float valor_total);

void salvaCompra(Compra *compra, FILE *arq); 

Compra *leCompra(FILE *in);

Compra *buscaSequencialCompra(int chave, FILE *arq);

void imprimeCompra(Compra *compra);

void imprimirBaseCompra(FILE *arq);

#endif
