#include "interface.h"
#include <stdio.h>
#include <stdlib.h>

void MSG_MENU() {
    system("cls");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> LOJA DE DISCOS <<<<<<<<<<<<<<<<<<<<<<<<");
    printf("\n\n\t>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<<<<<<\n");

    printf("\n>>>>>>>>>>>>>>>>>>>>>>> DISCOS <<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\n1. Criar Base Discos Desordenada");
    printf("\n2. Cadastrar Disco");
    printf("\n3. Buscar Discos (Sequencial)");
    printf("\n4. Buscar Discos (Binaria)");
    printf("\n5. Atualizar Disco");
    printf("\n6. Ordenar Disco");

    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>> FUNCIONARIOS <<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\n7. Criar Base Funcionarios Desordenada");
    printf("\n8. Cadastrar Funcionario");
    printf("\n9. Buscar Funcionarios (Sequencial)");
    printf("\n10. Buscar Funcionarios (Binaria)");
    printf("\n11. Ordenar Funcionario");

    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>> CLIENTES <<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\n12. Criar Base Clientes Desordenada");
    printf("\n13. Cadastrar Cliente");
    printf("\n14. Buscar Cliente");

    printf("\n\n>>>>>>>>>>>>>>>>>>>>>>> COMPRAS <<<<<<<<<<<<<<<<<<<<<<<<\n");
    printf("\n15. Cadastrar Compra");
    printf("\n16. Buscar Compras");
    printf("\n17. Excluir Compra");
    printf("\n18. Gerar Relatorio de Compras");

    printf("\n\n0. Sair");
}

void MENU(FILE *compras, FILE *clientes, FILE *funcionarios, FILE *discos) {
    int opcao;
    Disco *d;
    Cliente *c;
    Funcionario * f;

    do {
        MSG_MENU();
        printf("\nEscolha uma opcao: ");
        scanf("%d", &opcao);
        
        switch(opcao) {
            case 0:
                printf("Saindo...\n");
                break;

            case 1:
                criarBaseOrdenadaDisco(discos,10);
                imprimirBaseDisco(discos);
                break;

            case 2:
               d = criaDisco(1000,"quebrado", "ze", "rock", 2000, 45.50, 5);
                salvaDisco(d, discos);
                imprimirBaseDisco(discos);
                break;
            
            case 3:
            //Busca sequencial
                break;

            case 4:
            //Busca binaria
                break;

            case 5:
            //Atualiza Disco
                break;

            case 6:
            //Ordena Disco
                break;
            
            default:
                printf("Opcao invalida!\n");
        }
    } while (opcao != 0);
}