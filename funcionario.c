#include "funcionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>

// Cria funcionario.
Funcionario *criaFuncionario(int id, const char *nome, const char *cpf) {
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));
    if (func) memset(func, 0, sizeof(Funcionario));
    func->id = id;
    strncpy(func->nome, nome, sizeof(func->nome) - 1);
    strncpy(func->cpf, cpf, sizeof(func->cpf) - 1);
    return func;
}

// Salva funcionario no arquivo arq, na posição atual do cursor
void salvaFuncionario(Funcionario *func, FILE *arq) {
    fwrite(&func->id, sizeof(int), 1, arq);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), arq);
}

// Lê um funcionário do arquivo na posição atual do cursor
// Retorna um ponteiro para funcionário lido do arquivo
Funcionario *leFuncionario(FILE *in) {
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));
    if (0 >= fread(&func->id, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    return func;
}

// Imprime funcionario
void imprimeFuncionario(Funcionario *func) {
    printf("**********************************************\n");
    printf("Funcionario de ID: %d\n", func->id);
    printf("Nome: %s\n", func->nome);
    printf("CPF: %s\n", func->cpf);
    printf("**********************************************\n");
}

// Retorna tamanho do funcionario em bytes
int tamanhoRegistroFuncionario() {
    return sizeof(int)  // id
           + sizeof(char) * 50 // nome
           + sizeof(char) * 15; // cpf
}


// Retorna a quantidade de registros no arquivo
int qtdRegistrosFuncionario(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / tamanhoRegistroFuncionario();
    return tam;
}

// Embaralha base de dados
void embaralhaFuncionario(int *vet, int max, int trocas) {
    srand(time(NULL));
    for (int i = 0; i <= trocas; i++) {
        int j = rand() % (max - 1);
        int k = rand() % (max - 1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

// Cria a base de dados desordenada pelo ID do funcionário
void criarBaseDesordenadaFuncionario(FILE *arq, int tam, int qtdTrocas) {
    int vet[tam];
    Funcionario *f;

    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o vetor com IDs
    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    // Embaralha o vetor de IDs para garantir a desordem
    embaralhaFuncionario(vet, tam, qtdTrocas);

    printf("\nGerando a base de dados...\n");

    // Cria e salva os funcionários no arquivo
    for (int i = 0; i < tam; i++) {
        // Geração de dados aleatórios
        char cpf[15];
        snprintf(cpf, 15, "%03d.%03d.%03d-%02d", 
                 rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);

        // Cria o funcionário com dados aleatórios
        f = criaFuncionario(vet[i], "Nome", cpf);

        // Salva o funcionário no arquivo
        salvaFuncionario(f, arq);

        // Libera a memória alocada para o funcionário
        free(f);
    }
}

// Imprime a base de dados
void imprimirBaseFuncionario(FILE *arq) {
    printf("Imprimindo a base de dados...\n");

    rewind(arq);
    Funcionario *f;

    while ((f = leFuncionario(arq)) != NULL)
        imprimeFuncionario(f);

    free(f);
}

Funcionario *buscaSequencialFuncionario(int chave, FILE *arq) {
    Funcionario *f;
    int achou = 0;
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock(); // Captura o tempo inicial

    rewind(arq);
    while ((f = leFuncionario(arq)) != NULL) {
        if (f->id == chave) {
            achou = 1;
            break;
        }
    }

    end_time = clock(); // Captura o tempo final
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Calcula o tempo de execução

    if (achou == 1) {
        printf("Funcionario encontrado em %f segundos.\n", cpu_time_used);
        return f;
    } else {
        printf("Funcionario nao encontrado. Tempo de busca: %f segundos.\n", cpu_time_used);
        free(f);
        return NULL;
    }
}

Funcionario* buscaBinariaFuncionario(int id, FILE* arq, int inicio, int fim) {
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock(); // Captura o tempo inicial

    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(arq, meio * tamanhoRegistroFuncionario(), SEEK_SET);

        Funcionario *f = leFuncionario(arq);

        if (f->id == id) {
            end_time = clock(); // Captura o tempo final
            cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Calcula o tempo de execução
            printf("Funcionario encontrado em %f segundos.\n", cpu_time_used);
            return f;
        }

        if (f->id > id) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
        free(f);
    }

    end_time = clock(); // Captura o tempo final
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Calcula o tempo de execução
    printf("Funcionario nao encontrado. Tempo de busca: %f segundos.\n", cpu_time_used);
    
    return NULL;
}

// Função para ordenar os funcionários no arquivo usando o Bubble Sort
void bubbleSortFuncionarios(FILE *arq, int tam) {
    Funcionario *funcAtual = NULL;
    Funcionario *funcProximo = NULL;
    int trocou;

    // Executa o Bubble Sort
    for (int i = 0; i < tam - 1; i++) {
        trocou = 0;
        for (int j = 0; j < tam - i - 1; j++) {
            // Posiciona o cursor no início do funcionário atual
            fseek(arq, j * tamanhoRegistroFuncionario(), SEEK_SET);
            funcAtual = leFuncionario(arq);

            // Posiciona o cursor no início do próximo funcionário
            fseek(arq, (j + 1) * tamanhoRegistroFuncionario(), SEEK_SET);
            funcProximo = leFuncionario(arq);

            // Compara os IDs dos funcionários
            if (funcAtual->id > funcProximo->id) {
                // Troca os funcionários de lugar no arquivo
                fseek(arq, j * tamanhoRegistroFuncionario(), SEEK_SET);
                salvaFuncionario(funcProximo, arq);

                fseek(arq, (j + 1) * tamanhoRegistroFuncionario(), SEEK_SET);
                salvaFuncionario(funcAtual, arq);

                trocou = 1;
            }

            // Libera a memória alocada para os funcionários
            free(funcAtual);
            free(funcProximo);
        }

        // Se nenhuma troca foi feita, a lista já está ordenada
        if (!trocou) {
            break;
        }
    }
}

bool existeNaoCongelado(bool congelado[], int tamanho) {
    for (int i = 0; i < tamanho; i++) {
        if (!congelado[i]) {  
            return true;
        }
    }
    return false;  
}


void selecaoPorSubstituicao(FILE *arq, int m) {
    Funcionario *copiaFuncionarios[m];
    bool congelado[m];
    int idFuncionarioSalvo;
    int indiceMenorChave;
    int numeroParticao = 1;

    rewind(arq);

    // 1) Ler M registros do arquivo para a memória
    for (int i = 0; i < m; i++) {
        copiaFuncionarios[i] = leFuncionario(arq);
        congelado[i] = false;    
    }

    while (true) {
        // 7) Criar nova partição 
        char nomeParticao[50];
        sprintf(nomeParticao, "particoes/part%d.dat", numeroParticao);
        

        FILE *partFile = fopen(nomeParticao, "w+b");
        rewind(partFile);
        if (partFile == NULL) {
            printf("Erro ao abrir o arquivo");
            return;
        }
         printf("Criou o arquivo  %d", numeroParticao);

        while (existeNaoCongelado(congelado, m)) {
        

            indiceMenorChave = -1; // 2) Selecionar registro de menor chave
            for (int i = 0; i < m; i++) {
                if (!congelado[i] && copiaFuncionarios[i] != NULL &&
                    (indiceMenorChave == -1 || copiaFuncionarios[i]->id < copiaFuncionarios[indiceMenorChave]->id)) {
                    indiceMenorChave = i;
                }
            }

            if (indiceMenorChave != -1) {
                // 3) Gravar o registro r na partição de saída
                idFuncionarioSalvo = copiaFuncionarios[indiceMenorChave]->id;
                salvaFuncionario(copiaFuncionarios[indiceMenorChave], partFile);

                // 4) Substituir o registro r pelo próximo do arquivo de entrada
                copiaFuncionarios[indiceMenorChave] = leFuncionario(arq);

                // 5) Congelar se o novo registro tiver uma chave menor que a salva
                if (copiaFuncionarios[indiceMenorChave] == NULL || idFuncionarioSalvo > copiaFuncionarios[indiceMenorChave]->id) {
                    congelado[indiceMenorChave] = true;
                }
            }
        }

        // 7.1) Fechar a partição de saída
        rewind(partFile);
        printf("\nParticao %d\n", numeroParticao);
        imprimirBaseFuncionario(partFile);
        fclose(partFile);



        // 7.2) Descongelar os registros congelados
        for (int i = 0; i < m; i++) {
            if(copiaFuncionarios[i] != NULL) {
            printf("descongelados: %d\n" ,copiaFuncionarios[i]->id); }
            congelado[i] = false;
        }

        // 7.3) Preparar para a próxima partição
        numeroParticao++;

        // Verificar se ainda há registros no array para continuar o processo
        bool registrosRestantes = false;
        for (int i = 0; i < m; i++) {
            if (copiaFuncionarios[i] != NULL) {
                registrosRestantes = true;
                break;
            }
        }
        if (!registrosRestantes) {
            printf("encerrou");
            break;
        }
     }

    
}






