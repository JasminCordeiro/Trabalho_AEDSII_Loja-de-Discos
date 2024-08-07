#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "disco.h"
#include "compra.h"
#include "funcionario.h"

int main(int argc, char** argv) {
    FILE *compras;
    FILE *clientes;
    FILE *funcionarios;
    FILE *discos;
    int quantidadeDiscos = 10;
    int quantidadeTrocas = 8;
    
    int opcao;
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

    
    Disco *d;
    Cliente *c;
    Funcionario *f;

    do {
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
        printf("\nEscolha uma opcao: ");

        // Lê a opção do usuário
        scanf("%d", &opcao);

        // Verifica se a leitura foi bem-sucedid

        switch(opcao) {
            case 0:
                printf("Saindo...\n");
                break;

            case 1:
                printf("Criando base de discos desordenada...\n");
                criarBaseDesordenadaDisco(discos, quantidadeDiscos, quantidadeTrocas);
                imprimirBaseDisco(discos);
                break;
                break;

            case 2:
                printf("Cadastrar Disco selecionado.\n");
                break;

            case 3:
                printf("Buscar Discos (Sequencial) selecionado.\n");
                break;

            case 4:
                printf("Buscar Discos (Binaria) selecionado.\n");
                break;

            case 5:
                printf("Atualizar Disco selecionado.\n");
                break;

            case 6:
                printf("Ordenar Disco selecionado.\n");
                break;

            case 7:
                printf("Criar Base Funcionarios Desordenada selecionado.\n");
                break;

            case 8:
                printf("Cadastrar Funcionario selecionado.\n");
                break;

            case 9:
                printf("Buscar Funcionarios (Sequencial) selecionado.\n");
                break;

            case 10:
                printf("Buscar Funcionarios (Binaria) selecionado.\n");
                break;

            case 11:
                printf("Ordenar Funcionario selecionado.\n");
                break;

            case 12:
                printf("Criar Base Clientes Desordenada selecionado.\n");
                break;

            case 13:
                printf("Cadastrar Cliente selecionado.\n");
                break;

            case 14:
                printf("Buscar Cliente selecionado.\n");
                break;

            case 15:
                printf("Cadastrar Compra selecionado.\n");
                break;

            case 16:
                printf("Buscar Compras selecionado.\n");
                break;

            case 17:
                printf("Excluir Compra selecionado.\n");
                break;

            case 18:
                printf("Gerar Relatorio de Compras selecionado.\n");
                break;

            default:
                printf("Opcao invalida!\n");
                break;
        }
    } while (opcao != 0);
    
    fclose(compras);
        fclose(clientes);
        fclose(funcionarios);
        fclose(discos);
}
    return 0; 

}