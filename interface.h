
#ifndef INTERFACE_H_INCLUDED
#define INTERFACE_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>

#include "cliente.h"
#include "disco.h"
#include "compra.h"
#include "funcionario.h"

void MSG_MENU(); // MENSAGEM PARA EXIBIR O MENU PRINCIPAL

void MENU(FILE *compras, FILE *clientes, FILE *funcionarios, FILE *discos); // MÓDULO DE MENU


#endif 
