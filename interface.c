#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

void MSG_MENU( )
{
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> LOJA DE DISCOS <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n");
    printf("  \n\0. SAIR");
}
void MENU(FILE *compras, FILE *clientes, FILE *funcionarios, FILE *discos) {
    int opcao;
    do {
        MSG_MENU();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 0:
                printf("Saindo...\n");
                break;
            
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}