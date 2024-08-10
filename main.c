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
    }

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

        switch(opcao) {
            case 0:
                printf("Saindo...\n");
                break;

            case 1:
                printf("\nCriando base de discos desordenada...\n");
                criarBaseDesordenadaDisco(discos, quantidadeDiscos, quantidadeTrocas);
                imprimirBaseDisco(discos);
                break;
                break;

            case 2:
                printf("\nCadastrar Disco selecionado.\n");
                d = criaDisco(50,"novo","Anonimo", "rock",2015,50.45,5);
                salvaDisco(d, discos);
                free(d);
                imprimirBaseDisco(discos);

                break;

            case 3:
                printf("\nBuscar Discos (Sequencial) selecionado.\n");
                d = buscaSequencialDisco(5,discos);
                if(d != NULL)
                    (imprimeDisco(d));
                free(d);    
                break;

            case 4:
                printf("\nBuscar Discos (Binaria) selecionado.\n");
                int tamanho = ftell(discos) / tamanhoRegistroDisco();
                d = buscaBinariaDisco(6,discos,0,tamanho - 1);
                if(d != NULL)
                    (imprimeDisco(d));
                free(d);  
                break;

            case 5:{
                printf("\nAtualizar Disco selecionado.\n");
                
                int id;
                printf("Digite o ID do disco que deseja atualizar: ");
                scanf("%d", &id);
                
                // Busca o disco com base no ID
                Disco *d = buscaSequencialDisco(id, discos);
                if (d == NULL) {
                    printf("Disco com ID %d não encontrado!\n", id);
                    break;
                }

                printf("Disco encontrado:\n");
                 if(d != NULL)
                    (imprimeDisco(d));

                // Pedir novos dados para atualizar o disco
                printf("Digite os novos dados para o disco:\n");
                printf("Titulo: ");
                scanf("%s", d->titulo);
                printf("Artista: ");
                scanf("%s", d->artista);
                printf("Genero: ");
                scanf("%s", d->genero);
                printf("Ano: ");
                scanf("%d", &d->ano);
                printf("Preco: ");
                scanf("%f", &d->preco);
                printf("Estoque: ");
                scanf("%d", &d->estoque);

                // Reposiciona o cursor do arquivo para o início do registro
                long posicao = ftell(discos) - tamanhoRegistroDisco();
                fseek(discos, posicao, SEEK_SET);

                // Grava o disco atualizado no arquivo
                salvaDisco(d, discos);

                printf("Disco atualizado com sucesso!\n");

                free(d);
                imprimirBaseDisco(discos);
                break;
            }


            case 6:
                printf("\nOrdenar Disco selecionado.\n");
                break;

            case 7:
                printf("\nCriar Base Funcionarios Desordenada selecionado.\n");
                break;

            case 8:
                printf("\nCadastrar Funcionario selecionado.\n");
                break;

            case 9:
                printf("\nBuscar Funcionarios (Sequencial) selecionado.\n");
                break;

            case 10:
                printf("\nBuscar Funcionarios (Binaria) selecionado.\n");
                break;

            case 11:
                printf("\nOrdenar Funcionario selecionado.\n");
                break;

            case 12:
                printf("\nCriar Base Clientes Desordenada selecionado.\n");
                break;

            case 13:
                printf("\nCadastrar Cliente selecionado.\n");
                break;

            case 14:
                printf("\nBuscar Cliente selecionado.\n");
                break;

            case 15:
                printf("\nCadastrar Compra selecionado.\n");
                break;

            case 16:
                printf("\nBuscar Compras selecionado.\n");
                break;

            case 17:
                printf("\nExcluir Compra selecionado.\n");
                break;

            case 18:
                printf("\nGerar Relatorio de Compras selecionado.\n");
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 0);
    
    // fclose(compras);
    // fclose(clientes);
    // fclose(funcionarios);
    // fclose(discos);

    return 0; 

}