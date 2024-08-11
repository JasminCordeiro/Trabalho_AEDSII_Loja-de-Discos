#include "cliente.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Cria cliente.
Cliente *criaCliente(int id, const char *nome, const char *cpf, const char *telefone) {
    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
    if (cliente) memset(cliente, 0, sizeof(Cliente));
    cliente->id = id;
    strncpy(cliente->nome, nome, sizeof(cliente->nome) - 1);
    strncpy(cliente->cpf, cpf, sizeof(cliente->cpf) - 1);
    strncpy(cliente->telefone, telefone, sizeof(cliente->telefone) - 1);
    return cliente;
}

// Salva cliente no arquivo arq, na posição atual do cursor
void salvaCliente(Cliente *cliente, FILE *arq) {
    fwrite(&cliente->id, sizeof(int), 1, arq);
    fwrite(cliente->nome, sizeof(char), sizeof(cliente->nome), arq);
    fwrite(cliente->cpf, sizeof(char), sizeof(cliente->cpf), arq);
    fwrite(cliente->telefone, sizeof(char), sizeof(cliente->telefone), arq);
}

// Lê um cliente do arquivo na posição atual do cursor
Cliente *leCliente(FILE *in) {
    Cliente *cliente = (Cliente *)malloc(sizeof(Cliente));
    if (0 >= fread(&cliente->id, sizeof(int), 1, in)) {
        free(cliente);
        return NULL;
    }
    fread(cliente->nome, sizeof(char), sizeof(cliente->nome), in);
    fread(cliente->cpf, sizeof(char), sizeof(cliente->cpf), in);
    fread(cliente->telefone, sizeof(char), sizeof(cliente->telefone), in);
    return cliente;
}

// Imprime cliente
void imprimeCliente(Cliente *cliente) {
    printf("**********************************************\n");
    printf("Cliente de ID: %d\n", cliente->id);
    printf("Nome: %s\n", cliente->nome);
    printf("CPF: %s\n", cliente->cpf);
    printf("Telefone: %s\n", cliente->telefone);
    printf("**********************************************\n");
}

// Retorna tamanho do cliente em bytes
int tamanhoRegistroCliente() {
    return sizeof(int)  // id
           + sizeof(char) * 100 // nome
           + sizeof(char) * 15  // cpf
           + sizeof(char) * 15; // telefone
}

// Retorna a quantidade de registros no arquivo
int qtdRegistrosCliente(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / tamanhoRegistroCliente();
    return tam;
}



// Embaralha base de dados
void embaralhaCliente(int *vet, int max, int trocas) {
    srand(time(NULL));
    for (int i = 0; i <= trocas; i++) {
        int j = rand() % (max - 1);
        int k = rand() % (max - 1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

// Cria a base de dados desordenada pelo ID do cliente
void criarBaseDesordenadaCliente(FILE *arq, int tam, int qtdTrocas) {
    int vet[tam];
    
    // Inicializa o gerador de números aleatórios
    srand(time(NULL));

    // Preenche o vetor com IDs
    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    // Embaralha o vetor de IDs para garantir a desordem
    embaralhaCliente(vet, tam, qtdTrocas);

    printf("\nGerando a base de dados...\n");

    // Cria e salva os clientes no arquivo
    for (int i = 0; i < tam; i++) {
        // Geração de dados aleatórios
        char cpf[15];
        char telefone[15];
        snprintf(cpf, 15, "%03d.%03d.%03d-%02d", 
                 rand() % 1000, rand() % 1000, rand() % 1000, rand() % 100);
        snprintf(telefone, 15, "(%02d) %05d-%04d",
                 rand() % 100, // Código de área (00 a 99)
                 rand() % 100000, // Número do telefone (00000 a 99999)
                 rand() % 10000); // Número final (0000 a 9999)

        // Cria o cliente com os dados aleatórios
        Cliente *cliente = criaCliente(vet[i], "Nome", cpf, telefone);

        // Salva o cliente no arquivo
        salvaCliente(cliente, arq);

        // Libera a memória alocada para o cliente
        free(cliente);
    }
}
// Imprime a base de dados
void imprimirBaseCliente(FILE *arq) {
    printf("Imprimindo a base de dados...\n");

    rewind(arq);
    Cliente *cliente;

    while ((cliente = leCliente(arq)) != NULL)
        imprimeCliente(cliente);

    free(cliente);
}

Cliente *buscaSequencialCliente(int chave, FILE *arq) {
    Cliente *c;
    int achou = 0;
    clock_t start_time, end_time;
    double cpu_time_used;

    start_time = clock(); // Captura o tempo inicial

    rewind(arq);
    while ((c = leCliente(arq)) != NULL) {
        if (c->id == chave) {
            achou = 1;
            break;
        }
    }

    end_time = clock(); // Captura o tempo final
    cpu_time_used = ((double)(end_time - start_time)) / CLOCKS_PER_SEC; // Calcula o tempo de execução

    if (achou == 1) {
        printf("Cliente encontrado em %f segundos.\n", cpu_time_used);
        return c;
    } else {
        printf("Cliente nao encontrado. Tempo de busca: %f segundos.\n", cpu_time_used);
        free(c);
        return NULL;
    }
}