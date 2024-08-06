//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "LeituraArquivo.h"
#include <time.h>

void extrair_caminho(const char *nomearquivo, char **caminho) {
    // Encontrar o ultimo "/", porque todo caminho esta antes dele
    const char *posicao_barra = strrchr(nomearquivo, '/');
    
    if (posicao_barra != NULL) {
        size_t comprimento_caminho = posicao_barra - nomearquivo + 1; // Calcula o tamanho que o caminho do arquivo vai ter
        *caminho = malloc(comprimento_caminho + 1); // +1 para o "/n"
        if (*caminho == NULL) {
            perror("Erro ao alocar memória");
            exit(EXIT_FAILURE); //Como e void, isso garante que a execucao sera interrompida
        }
        // Copiar o caminho
        strncpy(*caminho, nomearquivo, comprimento_caminho);
        (*caminho)[comprimento_caminho] = '\0'; // Terminar a string
    } else {
        // Se nao houver "/", os arquivos estao no mesmo diretorio
        *caminho = malloc(1); // Aloca espaco para string vazia
        if (*caminho == NULL) {
            perror("Erro ao alocar memória");
            exit(EXIT_FAILURE); //Como e void, isso garante que a execucao sera interrompida
        }
        (*caminho)[0] = '\0'; // Diretorio vazio
    }
}

void Letra_Minuscula(char *str) { //Funcao para colocar os caracteres em forma minuscula (Nao eh case sensitive)
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int Frequencia_Ingrediente(char *receita_str, char *nome_ingrediente){
    /* Busca e contabiliza as aparicoes de um ingrediente no documento com auxilio da funcao strstr(),
    a qual retorna um ponteiro para a primeira ocorrencia do caracter inicial da palavra, no caso o ingrediente que estamos buscando*/

    int tam_ingrediente = strlen(nome_ingrediente); //Vai auxiliar na movimentacao do ponteiro, porque strstr retorna a posicao do primeiro caracter da palavra
    int qtd_ingrediente = 0;
    char *inicio = strstr(receita_str, nome_ingrediente);
    int *compara_hash = 0;
    while(inicio != NULL){ //O ponteiro passa sobre a receita procurando o ingrediente enquanto nao chegar no final do doc 
        qtd_ingrediente++;
        inicio += tam_ingrediente; // Atualiza o ponteiro para que ele consiga percorrer o vetor inteiro
        inicio = strstr(inicio, nome_ingrediente); /* Pesquisa novamente a palavra apos a atualizacao do ponteiro, pois a funcao
        strstr() retorna apenas a PRIMEIRA aparicao da palavra no vetor, entao tivemos que adaptar */
    }
    return qtd_ingrediente; // Retorna o qtd_ingrediente que sera utilizado na construção do indice invertido
}


int Leitura_Receita(char *nomearquivo, char **receita_str) {
    FILE *arq;
    arq = fopen(nomearquivo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        return 1;
    }

    // Determina o tamanho do arquivo
    long int tamanho_arquivo; //long pois o arquivo possui muitos caracteres
    fseek(arq, 0, SEEK_END);  // Move o ponteiro para o final do arquivo
    tamanho_arquivo = ftell(arq);  // Obtem a posicao atual do ponteiro em relacao ao inicio do arquivo, ou seja, seu tamanho
    rewind(arq);  // Volta o ponteiro para o inicio do arquivo

    // Aloca memoria para armazenar o conteudo do arquivo
    *receita_str = (char *)malloc(tamanho_arquivo + 1); // E uma boa pratica deixar o vetor com uma posicao extra 
    if (*receita_str == NULL) {
        printf("Erro ao alocar memória para o conteúdo do arquivo.\n");
        fclose(arq);
        return 1;
    }

    // Passa o conteudo do arquivo para a string, usamos fread para ignorar o espaco em branco
    fread(*receita_str, 1, tamanho_arquivo, arq);
    (*receita_str)[tamanho_arquivo] = '\0'; // Adiciona o fim de string
    Letra_Minuscula(*receita_str);
    fclose(arq);
    return 0;
}

int Leitura_Secundaria(char *nomearquivo, int id_doc, int **qtd_termos_documentos, char ***vetor_pocoes, Pesos p, Hash TabelaIngredientes, TipoArvore* Pat, int* compara_hash_insere, int* compara_pat_insere, clock_t* tempo_inicio_Pat, clock_t* tempo_inicio_Hash) {
    // Verifica se a leitura ocorreu de maneira correta
    if (Leitura_Receita(nomearquivo, &(*vetor_pocoes)[id_doc]) != 0) {
        return 1;
    }

    FILE *arq = fopen(nomearquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        return 1;
    }

    char ingrediente[N];
    char aux; //pega o "." ou ";"
    int qtd_ingrediente, total_ingredientes = 0;

    fgets(ingrediente, sizeof(ingrediente), arq); //Ignora a primeira linha do arquivo (titulo)
    total_ingredientes++;

    while (fscanf(arq, "%[^.;]", ingrediente) == 1) { //O "%[^.;]" e para ignorar os espacosn
        qtd_ingrediente = 0;
        Letra_Minuscula(ingrediente);
        qtd_ingrediente = Frequencia_Ingrediente((*vetor_pocoes)[id_doc], ingrediente); //Calcula quantas vezes um ingrediente aparece
        
        *tempo_inicio_Hash = clock(); //Calcular o tempo de insercao da hash
        Insere_Hash(ingrediente, p, TabelaIngredientes, qtd_ingrediente, id_doc, compara_hash_insere);

        *tempo_inicio_Pat = clock(); //Calcular o tempo de insercao da patricia
        *Pat = Insere_Pat(ingrediente, Pat, qtd_ingrediente, id_doc, compara_pat_insere);

        // Le o proximo caractere (tira o ; ou .)
        fscanf(arq, "%c ", &aux);
        if (aux == '.') {
            break;  // Sai do loop ao encontrar o ponto final
        }
        total_ingredientes++;
    }
    
    (*qtd_termos_documentos)[id_doc] = total_ingredientes; //Armazena a quantidade de ingredientes no documento id_doc
    fclose(arq);
    return 0;
}

int Leitura_Principal(char *nomearquivo, int** qtd_termos_documentos, int* total_de_arquivos, char ***vetor_pocoes, Pesos p, Hash TabelaIngredientes, TipoArvore* Pat, int* compara_hash_insere, int* compara_pat_insere, double* tempo_insercao_Hash, double* tempo_insercao_Pat) {
    FILE *arq = fopen(nomearquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s\n", nomearquivo);
        return 1;
    }

    fscanf(arq, "%d", total_de_arquivos);

    //Ajusta os tamanhos dos vetores para a qtd de documentos
    *vetor_pocoes = malloc((*total_de_arquivos) * sizeof(char*));
    *qtd_termos_documentos = malloc((*total_de_arquivos) * sizeof(int));

    if (*vetor_pocoes == NULL || *qtd_termos_documentos == NULL) {
        printf("Erro ao alocar memória.\n");
        fclose(arq);
        return 1;
    }

    //Calcula os tempos das insercoes
    clock_t tempo_inicio_Hash;
    clock_t tempo_inicio_Pat;


    /*se o arquivo de entrada principal estiver em outro diretorio (diferente dos arquivos de execucao), assumimos que os outros arquivos (secundarios)
    tambem estao nele, por isso eh necessario extrair o caminho*/
    char *caminho;
    extrair_caminho(nomearquivo, &caminho);
    size_t comprimento_caminho = strlen(caminho) + N + 1; // +1 para o terminador nulo e N eh o tamanho maximo de um ingrediente

    // Aloca memoria para o caminho completo
    char *caminho_completo = malloc(comprimento_caminho);
    if (caminho_completo == NULL) {
        perror("Erro ao alocar memória");
        free(caminho_completo);
        return 1;
    }

    //Realiza a leitura de cada um dos arquivos
    for (int i = 0; i < (*total_de_arquivos); i++) {
        char nome_arq[100];
        fscanf(arq, "%s", nome_arq);

        // Combinar o diretorio com o nome do arquivo
        snprintf(caminho_completo, comprimento_caminho, "%s%s", caminho, nome_arq);
        if (Leitura_Secundaria(caminho_completo, i, qtd_termos_documentos, vetor_pocoes, p, TabelaIngredientes, Pat, compara_hash_insere, compara_pat_insere, &tempo_inicio_Hash, &tempo_inicio_Pat) != 0) {
            printf("Erro ao ler o arquivo %s.\n", nome_arq);
            fclose(arq);
            return 1;
        }
    }

    clock_t tempo_final_Hash = clock(); //Marca o tempo final 
    *tempo_insercao_Hash = (double)(tempo_final_Hash-tempo_inicio_Hash) / CLOCKS_PER_SEC; //Calcula o tempo total em segundos

    clock_t tempo_final_Pat = clock(); //Marca o tempo final 
    *tempo_insercao_Pat = (double)(tempo_final_Pat-tempo_inicio_Pat) / CLOCKS_PER_SEC; //Calcula o tempo total em segundos
    
    // Liberar a memoria alocada
    free(caminho_completo);
    free(caminho);
    fclose(arq);
    return 0;
}
