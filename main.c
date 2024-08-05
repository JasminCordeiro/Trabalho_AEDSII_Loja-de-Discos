#include <stdio.h>
#include <stdlib.h>
#include "interface.h"

int main(int argc, char** argv) {
    FILE *compras;
    FILE *clientes;
    FILE *funcionarios;
    FILE *discos;

    if ((compras = fopen("compras.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de compras\n");
        exit(1);
    }
    if ((clientes = fopen("clientes.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de clientes\n");
        exit(1);
    }
    if ((funcionarios = fopen("funcionarios.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de funcionários\n");
        exit(1);
    }
    if ((discos = fopen("discos.dat", "w+b")) == NULL) {
        printf("Erro ao abrir arquivo de discos\n");
        exit(1);
    } else {
        MENU(compras, clientes, funcionarios, discos);
        fclose(compras);
        fclose(clientes);
        fclose(funcionarios);
        fclose(discos);
    }
}