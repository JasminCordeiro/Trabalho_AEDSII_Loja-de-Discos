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

#endif
