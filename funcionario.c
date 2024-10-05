#include "funcionario.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <math.h>
#include <stdbool.h>
#include <limits.h>

// Cria funcionario.
Funcionario *criaFuncionario(int id, const char *nome, const char *cpf) {
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));
    if (func) memset(func, 0, sizeof(Funcionario));
    func->id = id;
    strncpy(func->nome, nome, sizeof(func->nome) - 1);
    strncpy(func->cpf, cpf, sizeof(func->cpf) - 1);
    func->proximo = -1; // Inicializa o próximo como -1, indicando "NULL" (não aponta para ninguém)
    return func;
}

// Salva funcionario no arquivo arq, na posição atual do cursor
void salvaFuncionario(Funcionario *func, FILE *arq) {
    fwrite(&func->id, sizeof(int), 1, arq);
    fwrite(func->nome, sizeof(char), sizeof(func->nome), arq);
    fwrite(func->cpf, sizeof(char), sizeof(func->cpf), arq);
    
    // Salva o campo proximo como long
    long proxId = func->proximo; 
    fwrite(&proxId, sizeof(long), 1, arq); // Salva a posição do próximo funcionário
}


Funcionario *leFuncionario(FILE *in) {
    Funcionario *func = (Funcionario *) malloc(sizeof(Funcionario));
    if (0 >= fread(&func->id, sizeof(int), 1, in)) {
        free(func);
        return NULL;
    }
    fread(func->nome, sizeof(char), sizeof(func->nome), in);
    fread(func->cpf, sizeof(char), sizeof(func->cpf), in);
    fread(&func->proximo, sizeof(long), 1, in);

    return func;
}


// Imprime informações do funcionário
void imprimeFuncionario(Funcionario *func) {
    printf("**********************************************\n");
    printf("Funcionario de ID: %d\n", func->id);
    printf("Nome: %s\n", func->nome);
    printf("CPF: %s\n", func->cpf);
    // Imprime o valor do ponteiro prox
    printf("Endereco do proximo funcionario: %ld\n", func->proximo);
    printf("**********************************************\n");
}

// Retorna tamanho do funcionario em bytes
int tamanhoRegistroFuncionario() {
    return sizeof(int)                 // id
           + sizeof(char) * 50         // nome
           + sizeof(char) * 15         // cpf
           + sizeof(long);             // proximo
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
            return true;  // Há um registro não congelado e válido
        }
    }
    return false;  // Todos estão congelados ou nulos
}

int selecaoPorSubstituicao(FILE *arq, int m) {
    Funcionario *copiaFuncionarios[m];
    bool congelado[m];
    int idFuncionarioSalvo;
    int indiceMenorChave;
    int numeroParticao = 0;
    bool verifica = true;

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
            return -1;
        }

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
        printf("\nParticao %d\n", numeroParticao);
        imprimirBaseFuncionario(partFile);
        fclose(partFile);
       
        // 7.2) Descongelar os registros congelados
        for (int i = 0; i < m; i++) {
            if(copiaFuncionarios[i] != NULL) {
            congelado[i] = false;
            }
        }

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

     return numeroParticao;
}

int intercalaParticoes(int qtdParticoes) { 
    int contaPartIntercalado = 0;
    int grupoSize = 4;  // Definindo o tamanho do grupo de 4 partições // Testar com mais tamanhos
    int numGrupos = (qtdParticoes + grupoSize - 1) / grupoSize;  // Calculando o número de grupos

    char nomeArqParticao[50];
    FILE *particoes[qtdParticoes];
    Funcionario *copiaFuncionarios[qtdParticoes];

    // Abrindo cada partição para leitura
    for (int i = 0; i < qtdParticoes; i++) {
        sprintf(nomeArqParticao, "particoes/part%d.dat", i);
        particoes[i] = fopen(nomeArqParticao, "rb");
        if (particoes[i] == NULL) {
            printf("Erro ao abrir o arquivo da partiçao %d\n", i);
            exit(EXIT_FAILURE);
        }
        copiaFuncionarios[i] = leFuncionario(particoes[i]);  // Lê o primeiro funcionário de cada partição
    }

    // Intercalação por grupos de no máximo 4 partições
    for (int grupo = 0; grupo < numGrupos; grupo++) {
        int tamGrupoAtual = (grupo + 1) * grupoSize > qtdParticoes ? qtdParticoes - grupo * grupoSize : grupoSize;
        Funcionario *grupoRegistros[tamGrupoAtual * 100];  // Armazena registros do grupo (100 como exemplo, depende do número de registros por partição)
        int idx = 0;

        // Processa o grupo de partições
        for (int i = grupo * grupoSize; i < (grupo + 1) * grupoSize && i < qtdParticoes; i++) {
            while (copiaFuncionarios[i] != NULL) {
                grupoRegistros[idx++] = copiaFuncionarios[i];
                copiaFuncionarios[i] = leFuncionario(particoes[i]);
            }
        }

        // Ordenação dos registros dentro do grupo
        for (int i = 0; i < idx - 1; i++) {
            for (int j = i + 1; j < idx; j++) {
                if (grupoRegistros[i]->id > grupoRegistros[j]->id) {
                    Funcionario *temp = grupoRegistros[i];
                    grupoRegistros[i] = grupoRegistros[j];
                    grupoRegistros[j] = temp;
                }
            }
        }

        // Gerar uma nova partição com os registros intercalados do grupo
        contaPartIntercalado++;
        sprintf(nomeArqParticao, "intercalacaoPart/partIntercalada%d.dat", contaPartIntercalado);
        FILE *saida = fopen(nomeArqParticao, "w+b");
        if (saida == NULL) {
            printf("Erro ao criar o arquivo de saída\n");
            exit(EXIT_FAILURE);
        }

        // Salva o grupo de registros intercalados na nova partição
        for (int i = 0; i < idx; i++) {
            salvaFuncionario(grupoRegistros[i], saida);
        }

        fclose(saida);
    }

    // Fechando os arquivos das partições originais
    for (int i = 0; i < qtdParticoes; i++) {
        fclose(particoes[i]);
    }

    return contaPartIntercalado;
}

void unirParticoesOrdenadas(int numParticoes) {
    char nomeDaParticao[50] = "intercalacaoPart/partIntercalada"; 
    FILE *saidaFinal = fopen("intercalacaoPart/saida_final_ordenada.dat", "w+b");
    if (saidaFinal == NULL) {
        printf("Erro ao criar o arquivo de saída final ordenada.\n");
        exit(1);
    }

    Funcionario *copiaFuncionarios[numParticoes];
    FILE *particoes[numParticoes];

    // Abrir todas as partições
    for (int i = 0; i < numParticoes; i++) {
        char nomeArqParticao[50];
        sprintf(nomeArqParticao, "intercalacaoPart/partIntercalada%d.dat", i + 1);  // Ajuste: começa em 1 para nome do arquivo
        particoes[i] = fopen(nomeArqParticao, "rb");
        if (particoes[i] == NULL) {
            printf("Erro ao abrir o arquivo da particao %s\n", nomeArqParticao);
            exit(1);
        }

        copiaFuncionarios[i] = leFuncionario(particoes[i]);  // Lê o primeiro funcionário de cada partição
    }

    // Processo de merge para unir as partições intercaladas
    while (1) {
        int menorId = INT_MAX;
        int idxMenor = -1;

        // Encontrar o menor funcionário entre as partições
        for (int i = 0; i < numParticoes; i++) {
            if (copiaFuncionarios[i] != NULL && copiaFuncionarios[i]->id < menorId) {
                menorId = copiaFuncionarios[i]->id;
                idxMenor = i;
            }
        }

        if (idxMenor == -1) {
            // Todos os registros foram unidos
            break;
        }

        // Salvar o menor funcionário no arquivo final
        salvaFuncionario(copiaFuncionarios[idxMenor], saidaFinal);

        // Ler o próximo funcionário da partição correspondente
        copiaFuncionarios[idxMenor] = leFuncionario(particoes[idxMenor]);
    }

    // Fechar e remover as partições
    for (int i = 0; i < numParticoes; i++) {
        fclose(particoes[i]);
        char nomeArqParticao[50];
        sprintf(nomeArqParticao, "intercalacaoPart/partIntercalada%d.dat", i + 1);  // Ajuste para remover corretamente os arquivos
        remove(nomeArqParticao);  // Remove as partições temporárias
    }

    fclose(saidaFinal);

    // Abrir o arquivo final ordenado para impressão
    FILE *saidaFinalOrdenada = fopen("intercalacaoPart/saida_final_ordenada.dat", "rb");
    if (saidaFinalOrdenada == NULL) {
        printf("Erro ao abrir o arquivo de saída final ordenada para impressão.\n");
        exit(1);
    }

    // Imprimir o conteúdo do arquivo final ordenado
    printf("SAIDA ORDENADA\n");
    imprimirBaseFuncionario(saidaFinalOrdenada);

    fclose(saidaFinalOrdenada);
}

// Função para ler um funcionário a partir de uma posição específica no arquivo
Funcionario *leFuncionarioNaPosicao(FILE *arq, long posicao) {
    Funcionario *f = (Funcionario *) malloc(sizeof(Funcionario));
    if (f == NULL) {
        return NULL; // Verifica se a alocação foi bem-sucedida
    }

    // Move o cursor para a posição especificada
    fseek(arq, posicao, SEEK_SET);

    // Lê os dados do funcionário
    if (fread(&f->id, sizeof(int), 1, arq) < 1) {
        free(f);
        return NULL; // Se não puder ler o ID, libera e retorna NULL
    }
    
    fread(f->nome, sizeof(char), sizeof(f->nome), arq); // Lê o nome
    fread(f->cpf, sizeof(char), sizeof(f->cpf), arq);   // Lê o CPF
    fread(&f->proximo, sizeof(long), 1, arq);

    return f;
}


void salvaFuncionarioNaPosicao(FILE *arq, Funcionario *f, long posicao) {
    // Verificar se o arquivo e o funcionário são válidos
    if (arq == NULL || f == NULL) {
        printf("Erro: Arquivo ou funcionário inválido.\n");
        return;
    }

    // Move o cursor para a posição especificada
    fseek(arq, posicao, SEEK_SET);

    // Gravar os dados do funcionário no arquivo
    fwrite(&f->id, sizeof(int), 1, arq);
    fwrite(f->nome, sizeof(char), sizeof(f->nome), arq);
    fwrite(f->cpf, sizeof(char), sizeof(f->cpf), arq);
    fwrite(&f->proximo, sizeof(long), 1, arq);

    // Forçar a gravação no arquivo
    fflush(arq);

    printf("Funcionario atualizado com sucesso na posicao %ld.\n", posicao);
}




int hash(int id, int tam) {
    
    // return id;
     return tam % id;
}

void inicalizaHash(int m) {
     FILE *tabela = fopen("tabelaHash.dat", "w+b");
    if (tabela == NULL) {
        printf("Erro ao criar o arquivo de saída final ordenada.\n");
        exit(1);
    }

    long valorInicial = -1;
    for (int i = 0; i < m; i++) {
        fseek(tabela, i * sizeof(long), SEEK_SET);
        fwrite(&valorInicial, sizeof(long), 1, tabela);
    }
     fclose(tabela);
}
// Função para buscar um funcionário na tabela hash e no arquivo
Funcionario* buscaHash(int id, int tam, FILE *arqFunc) {
    FILE *tabelaHash = fopen("tabelaHash.dat", "r+b");
    if (tabelaHash == NULL) {
        printf("Erro ao abrir os arquivos.\n");
        return NULL;
    }

    long posicaoFuncionarioArq;
    long posicaoHash;
    Funcionario *f = NULL;
    Funcionario *funcAux = NULL;
    long aux;

    // Calcular a posição inicial na tabela hash
    posicaoHash = hash(id, tam);

    // Mover para a posição calculada e ler a posição do funcionário no arquivo
    fseek(tabelaHash, posicaoHash * sizeof(long), SEEK_SET);
    fread(&posicaoFuncionarioArq, sizeof(long), 1, tabelaHash);

    if (posicaoFuncionarioArq == -1) {  // Se não existir um funcionário na posição
        printf("funcionario com ID %d não encontrado na tabela hash.\n", id);
        fclose(tabelaHash);
        return NULL;
    }

    printf("posicao inicial no arquivo: %ld\n", posicaoFuncionarioArq);

    // Ler o funcionário na posição especificada
    f = leFuncionarioNaPosicao(arqFunc, posicaoFuncionarioArq);
    if (f != NULL && f->id == id) {
        printf("funcionario encontrado na posicao inicial:\n\n");
        imprimeFuncionario(f);
        fclose(tabelaHash);
        return f;
    }

     if (f != NULL && f->id != id) {
        imprimeFuncionario(f);
        aux = f->proximo;

    if(aux == -1 ) {
        return f;
    }

    // Se o ID não bater, continuar a busca nos próximos elementos
    
    // free(f);  // Liberar a memória alocada para o funcionário inicial

    while (aux != -1) {  // Iterar até encontrar o ID desejado ou fim da lista
        funcAux = leFuncionarioNaPosicao(arqFunc, aux);
        if (funcAux == NULL) {
            printf("Erro ao ler funcionario na posicao %ld. Encerrando busca.\n", aux);
            fclose(tabelaHash);
            return NULL;
        }

        printf("Verificando funcionário na posicao: %ld\n", aux);
        imprimeFuncionario(funcAux);

        if (funcAux->id == id) {  // Encontrou o funcionário com o ID desejado
            printf("funcionario com ID %d encontrado!\n", id);
            fclose(tabelaHash);
            return funcAux;
        }

        // Atualiza `aux` para a posição do próximo funcionário na lista encadeada
        aux = funcAux->proximo;
        free(funcAux);  // Liberar a memória alocada para `funcAux`
    }
    return  f;
     }

    // Se não encontrar o funcionário
    printf("funcionario com ID %d não encontrado na lista.\n", id);
    fclose(tabelaHash);
    return NULL;
}

void insereHash(int m, FILE *arq) {
    Funcionario *f = NULL;
    Funcionario *fBusca = NULL;
    Funcionario *funcAux = NULL;
    long posicaoFuncionarioArq;
    int posicaoHash;
    long aux;

    FILE *tabela = fopen("tabelaHash.dat", "r+b");
    if (tabela == NULL) {
        printf("Erro ao abrir o arquivo tabelaHash.dat.\n");
        exit(1);
    }

    rewind(arq);  // Voltar para o início do arquivo de funcionários

    while ((f = leFuncionario(arq)) != NULL) {
        posicaoFuncionarioArq = ftell(arq) - tamanhoRegistroFuncionario();
        int codigoFuncionario = f->id;
        printf("ID do funcionario: %d, posicao no arquivo: %ld\n", codigoFuncionario, posicaoFuncionarioArq);

        // Calcular a posição no hash
        posicaoHash = hash(codigoFuncionario, m);
        printf("posicao hash para ID %d: %d\n", codigoFuncionario, posicaoHash);

        // Busca na tabela hash se o ID já está presente
        fBusca = buscaHash(codigoFuncionario, m, arq);
        if (fBusca == NULL) {  // Caso não exista, gravar na tabela
            fseek(tabela, posicaoHash * sizeof(long), SEEK_SET);
            fwrite(&posicaoFuncionarioArq, sizeof(long), 1, tabela);
            fflush(tabela);  // Forçar a gravação no arquivo
            printf("Gravado na posicao %d com sucesso.\n\n", posicaoHash);
        }else {
            printf("Funcionario com ID %d ja existe na tabela.\n", codigoFuncionario);
            printf("Inserindo na lista encadeada...\n");

         

    if (fBusca->id != codigoFuncionario) {
        // Inserir na lista encadeada se já existir um funcionário com ID diferente
        aux = fBusca->proximo;

        if (aux == -1) {
            // Caso o próximo seja -1, significa que é o final da lista
            fBusca->proximo = posicaoFuncionarioArq;
            salvaFuncionarioNaPosicao(arq, fBusca, ftell(arq) - tamanhoRegistroFuncionario());
            printf("Inserido na lista encadeada na posicao: %ld\n", fBusca->proximo);
        } else {
            // Percorrer a lista encadeada até encontrar o final
            while (aux != -1) {
                funcAux = leFuncionarioNaPosicao(arq, aux);
                
                if (funcAux == NULL) {
                    printf("Erro ao ler o funcionário na posicao %ld. Encerrando busca.\n", aux);
                    break;
                }

                // Atualiza `aux` para o próximo funcionário na lista
                aux = funcAux->proximo;

                // Libera a memória anterior para evitar vazamento
                if (aux != -1) {
                    free(funcAux);
                }
            }

            if (funcAux != NULL) {
                // Inserir no final da lista encadeada
                funcAux->proximo = posicaoFuncionarioArq;

                // Salvar o último funcionário atualizado na sua posição original
                salvaFuncionarioNaPosicao(arq, funcAux, ftell(arq) - tamanhoRegistroFuncionario());
                printf("Inserido na lista encadeada na posicao: %ld\n", funcAux->proximo);
                
                // Libera memória alocada para funcAux
                free(funcAux);
            }
        }
    }
}
        free(f);
        free(fBusca);
    }

    fclose(tabela);
}


void excluiHash(int id, int tam, FILE *arqFunc ) {

  FILE *tabelaHash = fopen("tabelaHash.dat", "r+b");
    if (tabelaHash == NULL) {
        printf("Erro ao abrir o arquivo tabelaHash.dat.\n");
        exit(1);
    }

    long posicaoFuncionarioArq;
    long posicaoHash = hash(id, tam);
    Funcionario *f = NULL;
    Funcionario *anterior = NULL;

    // Ler a posição do funcionário na tabela hash
    fseek(tabelaHash, posicaoHash * sizeof(long), SEEK_SET);
    fread(&posicaoFuncionarioArq, sizeof(long), 1, tabelaHash);

    if (posicaoFuncionarioArq == -1) {
        printf("Funcionario com ID %d nao encontrado na tabela.\n", id);
        fclose(tabelaHash);
        return;
    }

    // Ler o primeiro funcionário na posição inicial
    f = leFuncionarioNaPosicao(arqFunc, posicaoFuncionarioArq);

    // Caso o funcionário seja o primeiro da posição hash
    if (f != NULL && f->id == id) {
        if (f->proximo == -1) {
            // Caso não haja mais ninguém na lista, marcar a posição como vazia
            long valorVazio = -1;
            fseek(tabelaHash, posicaoHash * sizeof(long), SEEK_SET);
            fwrite(&valorVazio, sizeof(long), 1, tabelaHash);
            printf("Funcionario com ID %d removido da posicao inicial.\n", id);
        } else {
            // Atualizar a posição inicial para o próximo funcionário na lista
            fseek(tabelaHash, posicaoHash * sizeof(long), SEEK_SET);
            fwrite(&f->proximo, sizeof(long), 1, tabelaHash);
            printf("Funcionario com ID %d removido. Novo inicio e ID %ld.\n", id, f->proximo);
        }
    }
    else {
        // Se não for o primeiro, buscar o elemento na lista encadeada
        long posicaoAnterior = -1; // Variável para armazenar a posição do anterior
        while (f != NULL && f->id != id) {
            posicaoAnterior = ftell(arqFunc); // Armazena a posição atual do 'anterior'
            anterior = f;
            f = leFuncionarioNaPosicao(arqFunc, f->proximo);
        }

        if (f == NULL) {
            printf("Funcionario com ID %d nao encontrado na lista encadeada.\n", id);
            fclose(tabelaHash);
            return;
        }

        // Encontrou o funcionário, ajustar a lista
        anterior->proximo = f->proximo;

        // Salvar as alterações do anterior no arquivo
        salvaFuncionarioNaPosicao(arqFunc, anterior, posicaoAnterior);
        printf("Funcionario com ID %d removido da lista encadeada.\n", id);
    }

    free(f);
    fclose(tabelaHash);
}


    void imprimeTabelaHash(int m) {
    FILE *tabela = fopen("tabelaHash.dat", "rb");
    if (tabela == NULL) {
        printf("Erro ao abrir o arquivo tabelaHash.dat para leitura.\n");
        exit(1);
    }

    long posicao;
    int valor;
    
    printf("Conteudo da tabela Hash:\n");
    for (int i = 0; i < m; i++) {
        // Mover o ponteiro do arquivo para a posição correspondente
        fseek(tabela, i * sizeof(long), SEEK_SET);
        
        // Ler o valor da posição
        fread(&valor, sizeof(long), 1, tabela);
        
        // Exibir a posição e o valor
        printf("indice %d: ", i + 1);
        if (valor == -1) {
            printf("Vazio\n");
        } else {
            printf("posicao do Funcionario: %ld\n", valor);
        }
    }

    fclose(tabela);
}
