#include <stdio.h>
#include <stdlib.h>
#include "cliente.h"
#include "disco.h"
#include "compra.h"
#include "funcionario.h"

int main(int argc, char** argv) {
    const char *verde = "\x1b[32m"; 
    const char *resetar = "\x1b[0m";   // Resetar cor
    const char *azul = "\x1b[34m";  // azul

    FILE *compras;
    FILE *clientes;
    FILE *funcionarios;
    FILE *discos;
    int quantidadeDeRegistros = 100;
    int quantidadeTrocas = 26;
    
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
    int id_cadastro;

    do { 
        printf("\n\n%s>>>>>>>>>>>>>>>>>>>>>>> LOJA DE DISCOS <<<<<<<<<<<<<<<<<<<%s", verde, resetar);
        printf("\n\n%s>>>>>>>>>>>>>>>>>>>>>>> OPCOES DE MENU <<<<<<<<<<<<<<<<<<<\n%s", verde, resetar);

        printf("\n%s>>>>>>>>>>>>>>>>>>>>>>> DISCOS <<<<<<<<<<<<<<<<<<<<<<<<%s\n", azul, resetar);
        printf("\n1. Criar Base Discos Desordenada");
        printf("\n2. Cadastrar Disco");
        printf("\n3. Buscar Discos (Sequencial)");
        printf("\n4. Buscar Discos (Binaria)");
        printf("\n5. Atualizar Disco");
        printf("\n6. Ordenar Disco");

        printf("\n\n%s>>>>>>>>>>>>>>>>>>>>>>> FUNCIONARIOS <<<<<<<<<<<<<<<<<<<<<<<<%s\n", azul, resetar);
        printf("\n7. Criar Base Funcionarios Desordenada");
        printf("\n8. Cadastrar Funcionario");
        printf("\n9. Buscar Funcionarios (Sequencial)");
        printf("\n10. Buscar Funcionarios (Binaria)");
        printf("\n11. Ordenar Funcionario");

        printf("\n\n%s>>>>>>>>>>>>>>>>>>>>>>> CLIENTES <<<<<<<<<<<<<<<<<<<<<<<<%s\n", azul, resetar);
        printf("\n12. Criar Base Clientes Desordenada");
        printf("\n13. Cadastrar Cliente");
        printf("\n14. Buscar Cliente");

        printf("\n\n%s>>>>>>>>>>>>>>>>>>>>>>> COMPRAS <<<<<<<<<<<<<<<<<<<<<<<<%s\n", azul, resetar);
        printf("\n15. Cadastrar Compra");
        printf("\n16. Buscar Compras");
        printf("\n17. Gerar Relatorio de Compras");

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
                printf("\nInforme o id:\n");
                scanf("%d" , &id_cadastro );
                d = buscaSequencialDisco(id_cadastro,discos);
                if(d == NULL) {
                free(d);
                d = criaDisco(id_cadastro,"novo","Anonimo", "rock",2015,50.45,5);
                salvaDisco(d, discos);
                imprimirBaseDisco(discos);
                }
                else {
                    printf("Id ja existe ");
                }
                free(d);
                
                break;

            case 3:
                printf("\nBuscar Discos (Sequencial) selecionado.\n");
                d = buscaSequencialDisco(1001,discos);
                if(d != NULL)
                    (imprimeDisco(d));
                free(d);    
                break;

            case 4:
                printf("\nBuscar Discos (Binaria) selecionado.\n");
                tamanho = qtdRegistrosDisco(discos);
                d = buscaBinariaDisco(1000,discos,0,tamanho - 1);
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
                printf("\nInforme o id:\n");
                scanf("%d" , &id_cadastro );
                f = buscaSequencialFuncionario(id_cadastro, funcionarios);
                if(f == NULL) {
                free(f);
                f = criaFuncionario(id_cadastro, "novo", "000.000.000-01");
                salvaFuncionario(f, funcionarios);
                imprimirBaseFuncionario(funcionarios);
                } else {
                printf("Id ja existe\n");
                }
                free(f);
                break;

            case 9:
                printf("\nBuscar Funcionarios (Sequencial) selecionado.\n");
                f = buscaSequencialFuncionario(600,funcionarios);
                if(f != NULL)
                    (imprimeFuncionario(f));
                free(f);  
                break;

            case 10:
                printf("\nBuscar Funcionarios (Binaria) selecionado.\n");
                tamanho = ftell(funcionarios) / tamanhoRegistroFuncionario();
                f = buscaBinariaFuncionario(600,funcionarios,0,tamanho - 1);
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
                printf("\nInforme o id:\n");
                scanf("%d" , &id_cadastro );
                c = buscaSequencialCliente(id_cadastro, clientes);
                if(c == NULL) {
                    free(c);
                    c = criaCliente(id_cadastro, "constantino", "144.000.000-00", "4454-4544");
                    salvaCliente(c, clientes);
                    imprimirBaseCliente(clientes);
                } else {
                    printf("Id ja existe\n");
                }
                free(c);
                break;

            case 14:
                printf("\nBuscar Cliente selecionado.\n");
                  printf("\nBuscar Cliente (Sequencial) selecionado.\n");
                c = buscaSequencialCliente(754,clientes);
                if(c != NULL)
                    (imprimeCliente(c));
                free(c);    
                break;

            case 15:
                printf("\nCadastrar Compra selecionado.\n");

                int quantidade;
                int id_disco, id_cliente, id_funcionario,id_compra;
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
                        id_compra = obterUltimoIdCompra(compras);
                        compra = criaCompra(id_compra + 1, id_disco, id_cliente, id_funcionario, quantidade, d->preco*quantidade);
                        

                        salvaCompra(compra, compras);
                        d->estoque -= quantidade;

                        long posicao = ftell(discos) - tamanhoRegistroDisco();
                        fseek(discos, posicao, SEEK_SET);
                        
                        salvaDisco(d, discos);

                        printf("\nCompra realizada com sucesso!\n");
                        imprimirBaseCompra(compras);
                        imprimeDisco(d);
                        free(compra);
                    } else {
                        printf("\nFalha na compra. Verifique o estoque e as informacoes fornecidas.\n");
                    }

                free(d);
                free(c);
                free(f);
                
                break;

            case 16:
                printf("\nBuscar Compras selecionado.\n");
                p = buscaSequencialCompra(3,compras);
                 if(p != NULL)
                    (imprimeCompra(p));
                free(p);
                
                break;

            case 17:
                printf("\nGerar Relatorio de Compras selecionado.\n");
                imprimirBaseCompra(compras);
                break;

            case 18:
                printf("\n Selecao com Substituicao Funcionarios.\n");
                selecaoPorSubstituicao(funcionarios,4);
                break;
            // case 19:
            //     printf("\n IMprime Selecao com Substituicao Funcionarios.\n");
            //     imprimirBaseFuncionario(funcionarios,2);
            //     break;
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