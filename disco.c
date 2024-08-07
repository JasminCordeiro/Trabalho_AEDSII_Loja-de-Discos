#include "disco.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>

// Cria um novo disco.
Disco *criaDisco(int id, const char *titulo, const char *artista, const char *genero, int ano, float preco, int estoque) {
    Disco *disco = (Disco *) malloc(sizeof(Disco));
    // Inicializa espaço de memória com ZEROS
    if (disco) memset(disco, 0, sizeof(Disco));
    // Copia valores para os campos do disco
    disco->id = id;
    strcpy(disco->titulo, titulo);
    strcpy(disco->artista, artista);
    strcpy(disco->genero, genero);
    disco->ano = ano;
    disco->preco = preco;
    disco->estoque = estoque;
    return disco;
}

// Salva o disco no arquivo arq, na posição atual do cursor
void salvaDisco(Disco *disco, FILE *arq) {
    fwrite(&disco->id, sizeof(int), 1, arq);
    fwrite(disco->titulo, sizeof(char), sizeof(disco->titulo), arq);
    fwrite(disco->artista, sizeof(char), sizeof(disco->artista), arq);
    fwrite(disco->genero, sizeof(char), sizeof(disco->genero), arq);
    fwrite(&disco->ano, sizeof(int), 1, arq);
    fwrite(&disco->preco, sizeof(float), 1, arq);
    fwrite(&disco->estoque, sizeof(int), 1, arq);
}

// Lê um disco do arquivo na posição atual do cursor
// Retorna um ponteiro para o disco lido do arquivo
Disco *leDisco(FILE *in) {
    Disco *disco = (Disco *) malloc(sizeof(Disco));
    if (0 >= fread(&disco->id, sizeof(int), 1, in)) {
        free(disco);
        return NULL;
    }
    fread(disco->titulo, sizeof(char), sizeof(disco->titulo), in);
    fread(disco->artista, sizeof(char), sizeof(disco->artista), in);
    fread(disco->genero, sizeof(char), sizeof(disco->genero), in);
    fread(&disco->ano, sizeof(int), 1, in);
    fread(&disco->preco, sizeof(float), 1, in);
    fread(&disco->estoque, sizeof(int), 1, in);
    return disco;
}

// Imprime disco
void imprimeDisco(Disco *disco) {
    printf("**********************************************\n");
    printf("Disco ID: %d\n", disco->id);
    printf("Titulo: %s\n", disco->titulo);
    printf("Artista: %s\n", disco->artista);
    printf("Genero: %s\n", disco->genero);
    printf("Ano: %d\n", disco->ano);
    printf("Preco: %.2f\n", disco->preco);
    printf("Estoque: %d\n", disco->estoque);
    printf("**********************************************\n");
}

// Retorna o tamanho do disco em bytes
int tamanhoRegistroDisco() {
    return sizeof(int)  // id
           + sizeof(char) * 100 // título
           + sizeof(char) * 100 // artista
           + sizeof(char) * 50 // gênero
           + sizeof(int)  // ano
           + sizeof(float)  // preço
           + sizeof(int);  // estoque
}

// Retorna a quantidade de registros no arquivo
int qtdRegistrosDisco(FILE *arq) {
    fseek(arq, 0, SEEK_END);
    int tam = ftell(arq) / tamanhoRegistroDisco();
    return tam;
}

// Cria a base de dados ordenada pelo ID do disco
void criarBaseOrdenadaDisco(FILE *arq, int tam) {
    int vet[tam];
    Disco *d;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    printf("\nGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        d = criaDisco(vet[i], "Titulo", "Artista", "Genero", 2022, 100.0 * i, 10 * i);
        salvaDisco(d, arq);
    }

    free(d);
}

// Embaralha base de dados
void embaralhaDisco(int *vet, int max, int trocas) {
    srand(time(NULL));
    for (int i = 0; i <= trocas; i++) {
        int j = rand() % (max - 1);
        int k = rand() % (max - 1);
        int tmp = vet[j];
        vet[j] = vet[k];
        vet[k] = tmp;
    }
}

// Cria a base de dados desordenada pelo ID do disco
void criarBaseDesordenadaDisco(FILE *arq, int tam, int qtdTrocas) {
    int vet[tam];
    Disco *d;

    for (int i = 0; i < tam; i++)
        vet[i] = i + 1;

    embaralhaDisco(vet, tam, qtdTrocas);

    printf("\nGerando a base de dados...\n");

    for (int i = 0; i < tam; i++) {
        d = criaDisco(vet[i], "Titulo", "Artista", "Genero", 2022, 100.0 * i, 10 * i);
        salvaDisco(d, arq);
    }

    free(d);
}

// Imprime a base de dados
void imprimirBaseDisco(FILE *arq) {
    printf("Imprimindo a base de dados...\n");

    rewind(arq);
    Disco *d;

    while ((d = leDisco(arq)) != NULL)
        imprimeDisco(d);

    free(d);
}

Disco *buscaSequencialDisco(int chave, FILE *arq){

    Disco *d;
    int achou;
    rewind(arq);
    while ((d = leDisco(arq)) != NULL){

        if(d->id == chave){
           //return d;
           achou = 1;
           break;
        }
    }
        if(achou == 1)
            return d;
        else printf("Disco nao encontrado");

        free(d);
}

Disco* buscaBinariaDisco(int id, FILE* arq, int inicio, int fim) {
    while (inicio <= fim) {
        int meio = inicio + (fim - inicio) / 2;
        fseek(arq, meio * tamanhoRegistroDisco(), SEEK_SET);

        Disco *d = leDisco(arq);

        if (d->id == id) {
            return d;
        }
         if (d->id > id) {
            fim = meio - 1;
        } else {
            inicio = meio + 1;
        }
        free(d);
    }
    return NULL;
}
