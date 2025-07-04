#ifndef COMPRA_H
#define COMPRA_H

#include <stdlib.h>
#include <stdio.h>

typedef struct {
    int id;             
    int disco_id;       
    int id_cliente;  
    int id_funcionario; 
    int quantidade;     
    float valor_total; 
} Compra;

// Funções para manipulação de compras
Compra* criaCompra(int id_compra, int disco_id, int id_cliente, int id_funcionario, int quantidade, float valor_total) ;

void salvaCompra(Compra *compra, FILE *arq); 

Compra *leCompra(FILE *in);

Compra *buscaSequencialCompra(int chave, FILE *arq);

void imprimeCompra(Compra *compra);

void imprimirBaseCompra(FILE *arq);

int obterUltimoIdCompra(FILE *arq);

#endif
