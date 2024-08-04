//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "LeituraArquivo.h"


void Letra_Minuscula(char *str) { // Funcao para colocar os caracteres em forma minuscula (Nao eh case sensitive)
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int Frequencia_Ingrediente(char *receita_str, char *nome_ingrediente){
    /* Busca e contabiliza as aparicoes de um ingrediente no documento com auxilio da funcao strstr(),
    que retorna um ponteiro para a primeira ocorrencia do caracter inicial da palavra (que no nosso vetorzao eh uma
    cadeia de caracteres) que estamos buscando.
    */
    int tam_ingrediente = strlen(nome_ingrediente);
    int qtd_ingrediente = 0;
    char *inicio = strstr(receita_str, nome_ingrediente);
    while(inicio != NULL){ // O ponteiro passa sobre a receita procurando o ingr. enquanto não chegar no final do doc
        qtd_ingrediente++;
        inicio += tam_ingrediente; // Atualiza o ponteiro para que ele consiga percorrer o vetor inteiro.
        inicio = strstr(inicio, nome_ingrediente); /* Pesquisa novamente a palavra apos a atualizacao do ponteiro, pois a funcao
        strstr() retorna apenas a PRIMEIRA aparicao da palavra no vetor, entao tivemos que adaptar */
    }
    return qtd_ingrediente; // Retorna o qtd_ingrediente que será utilizado na construção do índice invertido
}


int Leitura_Receita(char *nomearquivo, char **receita_str) {
    FILE *arq;
    char caminhoCompleto[100] = "ArquivosdeEntrada/"; // Caminho base

    // Concatenar o nome do arquivo ao caminho base
    strcat(caminhoCompleto, nomearquivo);

    // Abrir o arquivo para leitura
    arq = fopen(caminhoCompleto, "r");
    long int tamanho_arquivo;
    
    //arq = fopen(nomearquivo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        return 1;
    }

    // Determina o tamanho do arquivo
    fseek(arq, 0, SEEK_END);  // Move o ponteiro para o final do arquivo
    tamanho_arquivo = ftell(arq);  // Obtem a posicao atual do ponteiro (tamanho do arquivo)
    rewind(arq);  // Volta o ponteiro para o inicio do arquivo

    // Aloca memória para armazenar o conteúdo do arquivo
    *receita_str = (char *)malloc(tamanho_arquivo + 1); // E uma boa pratica deixar o vetor com uma posicaoo extra 
    if (*receita_str == NULL) {
        printf("Erro ao alocar memória para o conteúdo do arquivo.\n");
        fclose(arq);
        return 1;
    }
    // Passa o conteudo do arquivo para a string
    fread(*receita_str, 1, tamanho_arquivo, arq);
    (*receita_str)[tamanho_arquivo] = '\0'; // Adiciona o terminador de string
    
    Letra_Minuscula(*receita_str);
    
    fclose(arq);
    return 0;
}

int Leitura_Secundaria(char *nomearquivo, int id_doc, int **qtd_termos_documentos) {
    char *receita_str = NULL; 
    
    //Verifica se a leitura ocorreu de maneira correta
    if (Leitura_Receita(nomearquivo, &receita_str) != 0) {
        return 1;
    }
    
    //Imprime a receita
    //printf("%s\n\n", receita_str);
    char caminhoCompleto[100] = "ArquivosdeEntrada/"; // Caminho base

    // Concatenar o nome do arquivo ao caminho base
    strcat(caminhoCompleto, nomearquivo);
    FILE *arq;
    // Abrir o arquivo para leitura
    arq = fopen(caminhoCompleto, "r");
   
    //arq = fopen(nomearquivo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        free(receita_str); // Liberar a memória antes de sair
        return 1;
    }

    char ingrediente[N];
    char aux;
    int qtd_ingrediente, total_ingredientes = 0;
    fgets(ingrediente, sizeof(ingrediente), arq);
    total_ingredientes ++;
    while (fscanf(arq, "%[^.;]", ingrediente) == 1) {
        qtd_ingrediente = 0;
        Letra_Minuscula(ingrediente);
        qtd_ingrediente = Frequencia_Ingrediente(receita_str, ingrediente);
        //printf("Qtd do ingrediente %s no doc(%d): %d\n", ingrediente, id_doc+1, qtd_ingrediente); // TESTE FUNCAO FREQUENCIA
        Insere_Hash(ingrediente, p, TabelaIngredientes, qtd_ingrediente, id_doc);
        Pat = Insere_Pat(ingrediente, &Pat, qtd_ingrediente, id_doc);
        //printf("ok\n");

        // CHAMAR EM SEGUIDA A FUNÇAO DE CONSTRUÇAO DO INDICE INVERTIDO

        // Imprime o ingrediente lido
        //printf("Ingrediente:%s\n", ingrediente);
        
        // Le o proximo caractere (tira o ; ou .)
        fscanf(arq, "%c ", &aux);
        
        // Verifica se é o ponto final
        if (aux == '.') {
            break;  // Sai do loop ao encontrar o ponto final
        }
        total_ingredientes ++;
        
    }
    (*qtd_termos_documentos)[id_doc] = total_ingredientes;
    fclose(arq);
    free(receita_str); // Liberar a memoria alocada
    return 0;
}

int Leitura_Principal(char *nomearquivo, int** qtd_termos_documentos, int* total_de_arquivos) {
    int qtd_arquivos; 
    char nome_arq[100];
    FILE *arq;
    
    arq = fopen(nomearquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        return 1;
    }
    //Realiza a leitura do meu arquivo principal 
    fscanf(arq, "%d", total_de_arquivos);

    *qtd_termos_documentos = (int*)malloc((*total_de_arquivos) * sizeof(int)); //Ajusta o tamanho do vetor para a qtd de documentos
    for (int i = 0; i < (*total_de_arquivos); i++) {
        fscanf(arq, "%s", nome_arq);
        Leitura_Secundaria(nome_arq, i, qtd_termos_documentos); //Realiza a leitura de uma string e passa para para minusculo
    }

    fclose(arq);

    return 0;
}



int main() {
    Inicializa_Hash(TabelaIngredientes);
    Inicializa_Pat(&Pat);
    GeraPesos(p);
    int *qtd_termos_documentos; //Quantidade de ingredientes no documento ID_DOC, cada índice representa o número de cada documento
    int total_de_arquivos=0;
    char *nome = "ArquivosdeEntrada/entrada.txt";
    nome_ingrediente_hash ingredientes[] = {"pinch of unicorn horn", "water"};

    Leitura_Principal(nome, &qtd_termos_documentos, &total_de_arquivos);
    Calcular_Relevancia_Termo_Hash(ingredientes, TabelaIngredientes, qtd_termos_documentos, total_de_arquivos,p, 2);
    //float peso = Calcular_Peso_Termo_Hash(ingrediente,TabelaIngredientes, total_de_arquivos,p,12);
    //printf("%f\n", peso);

    /*for(int i = 0; i < total_de_arquivos; i++){
        printf("%d - %d\n" , i+1, qtd_termos_documentos[i]);
    }*/
    //Imprime_Hash_Ordenada(TabelaIngredientes);
    int i = 0; // Inicializa o contador de índices
    //putchar('\n');
    //Imprime_Pat(Pat, &i);
    return 0;
}

   