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
    int quantidadeDeRegistros = 10;
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
    Compra *p;
    int tamanho;
    int quantidade =2;

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
                criarBaseDesordenadaDisco(discos, quantidadeDeRegistros, quantidadeTrocas);
                imprimirBaseDisco(discos);
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
                tamanho = qtdRegistrosDisco(discos);
                d = buscaBinariaDisco(6,discos,0,tamanho - 1);
                if(d != NULL)
                    (imprimeDisco(d));
                free(d);  
                break;

            case 5:
                printf("\nAtualizar Disco selecionado.\n");
                atualizaDisco(discos);
                imprimirBaseDisco(discos);
                break;
            

            case 6:
                printf("\nOrdenar Disco selecionado.\n");
                tamanho = qtdRegistrosDisco(discos);
                printf("Tamanho: %d\n", tamanho);
                bubbleSortDiscos(discos, tamanho);
                printf("Base de dados ordenada:\n");
                imprimirBaseDisco(discos);
                break;

            case 7:
                printf("\nCriar Base Funcionarios Desordenada selecionado.\n");
                printf("\nCriando base de funcionario desordenada...\n");
                criarBaseDesordenadaFuncionario(funcionarios, quantidadeDeRegistros, quantidadeTrocas);
                imprimirBaseFuncionario(funcionarios);
                break;

            case 8:
                printf("\nCadastrar Funcionario selecionado.\n");
                f = criaFuncionario(50,"novo","000.000.000-01");
                salvaFuncionario(f, funcionarios);
                free(f);
                imprimirBaseFuncionario(funcionarios);
                break;

            case 9:
                printf("\nBuscar Funcionarios (Sequencial) selecionado.\n");
                f = buscaSequencialFuncionario(5,funcionarios);
                if(f != NULL)
                    (imprimeFuncionario(f));
                free(f);  
                break;

            case 10:
                printf("\nBuscar Funcionarios (Binaria) selecionado.\n");
                tamanho = ftell(funcionarios) / tamanhoRegistroFuncionario();
                f = buscaBinariaFuncionario(6,funcionarios,0,tamanho - 1);
                if(f != NULL)
                    (imprimeFuncionario(f));
                free(f);  
                break;

            case 11:
                printf("\n11. Ordenar Funcionario selecionada.\n");
                printf("Base de dados ordenada:\n");
                bubbleSortFuncionarios(funcionarios, quantidadeDeRegistros);
                imprimirBaseFuncionario(funcionarios);
                break;

            case 12:
                printf("\nCriar Base Clientes Desordenada selecionado.\n");
                printf("\nCriando base de discos desordenada...\n");
                criarBaseDesordenadaCliente(clientes, quantidadeDeRegistros, quantidadeTrocas);
                imprimirBaseCliente(clientes);
                break;

            case 13:
                printf("\nCadastrar Cliente selecionado.\n");
                c = criaCliente(50,"constantino","144.000.000-00","4454-4544");
                salvaCliente(c, clientes);
                free(c);
                imprimirBaseCliente(clientes);

                break;

            case 14:
                printf("\nBuscar Cliente selecionado.\n");
                  printf("\nBuscar Cliente (Sequencial) selecionado.\n");
                c = buscaSequencialCliente(5,clientes);
                if(c != NULL)
                    (imprimeCliente(c));
                free(c);    
                break;

            case 15:
                printf("\nCadastrar Compra selecionado.\n");

                int quantidade;
                int id_disco, id_cliente, id_funcionario;
                Compra *compra;

                    printf("\nCadastrar nova Compra\n");
                    printf("Informe o ID do disco: ");
                    scanf("%d", &id_disco);
                    printf("Informe o ID do cliente: ");
                    scanf("%d", &id_cliente);
                    printf("Informe o ID do funcionario: ");
                    scanf("%d", &id_funcionario);
                    printf("Informe a quantidade de discos comprados: ");
                    scanf("%d", &quantidade);

                    Disco *d = buscaSequencialDisco(id_disco, discos);
                    Cliente *c = buscaSequencialCliente(id_cliente, clientes);
                    Funcionario *f = buscaSequencialFuncionario(id_funcionario, funcionarios);

                    if (d != NULL && c != NULL && f != NULL && d->estoque >= quantidade) {
                        compra = criaCompra(id_disco, id_cliente, id_funcionario, quantidade, d->preco*quantidade);

                        salvaCompra(compra, compras);
                        d->estoque -= quantidade;

                        long posicao = ftell(discos) - tamanhoRegistroDisco();
                        fseek(discos, posicao, SEEK_SET);
                        
                        salvaDisco(d, discos);

                        printf("\nCompra realizada com sucesso!\n");
                        free(compra);
                    } else {
                        printf("\nFalha na compra. Verifique o estoque e as informacoes fornecidas.\n");
                    }

                    imprimirBaseCompra(compras);

                    if (d != NULL) imprimeDisco(d);

                    if (d != NULL) free(d);
                    if (c != NULL) free(c);
                    if (f != NULL) free(f);
                
                break;

            case 16:
                printf("\nBuscar Compras selecionado.\n");
                p = buscaSequencialCompra(3,compras);
                 if(p != NULL)
                    (imprimeCompra(p));
                free(p);
                
                break;

            case 17:
                printf("\nExcluir Compra selecionado.\n");
                break;

            case 18:
                printf("\nGerar Relatorio de Compras selecionado.\n");
                 imprimirBaseFuncionario(funcionarios);
                break;

            default:
                printf("\nOpcao invalida!\n");
                break;
        }
    } while (opcao != 0);
    
    fclose(compras);
    fclose(clientes);
    fclose(funcionarios);
    fclose(discos);

    return 0; 

}