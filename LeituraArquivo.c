//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "LeituraArquivo.h"



void Letra_Minuscula(char *str) { // Funcao para colocar os caracteres em forma minuscula (Nao eh case sensitive)
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int Frequencia_Ingrediente(char *receita_str, char *nome_ingrediente){ // busca e contabiliza as aparições de um ingrediente no documento
    int tam_ingrediente = strlen(nome_ingrediente);
    int qtd_ingrediente = 0;
    char *inicio = strstr(receita_str, nome_ingrediente);
    while(inicio != NULL){ // O ponteiro passa sobre a receita procurando o ingr. enquanto não chegar no final do doc
        qtd_ingrediente++;
        inicio += tam_ingrediente;
        inicio = strstr(inicio, nome_ingrediente);
    }

    /*
    if (qtd_ingrediente == 0){
        printf("Ingrediente nao ta no documento (Funcao Frequencia_ingrediente)\n");
        return 0;
    }
    */
    return qtd_ingrediente; // Retorna o qtd_ingrediente que será utilizado na construção do índice invertido
}


int Leitura_Receita(char *nomearquivo, char **receita_str) {
    FILE *arq;
    long int tamanho_arquivo;
    
    arq = fopen(nomearquivo, "r");

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

int Leitura_Secundaria(char *nomearquivo, int id_doc) {
    char *receita_str = NULL; 
    
    //Verifica se a leitura ocorreu de maneira correta
    if (Leitura_Receita(nomearquivo, &receita_str) != 0) {
        return 1;
    }
    
    //Imprime a receita
    //printf("%s\n\n", receita_str);
    
    FILE *arq;
    arq = fopen(nomearquivo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        free(receita_str); // Liberar a memória antes de sair
        return 1;
    }

    char ingrediente[N];
    char aux;
    int qtd_ingrediente;
    fgets(ingrediente, sizeof(ingrediente), arq);
    
    while (fscanf(arq, "%[^.;]", ingrediente) == 1) {
        qtd_ingrediente = 0;
        Letra_Minuscula(ingrediente);
        qtd_ingrediente = Frequencia_Ingrediente(receita_str, ingrediente);
        //printf("Qtd do ingrediente %s no doc(%d): %d\n", ingrediente, id_doc+1, qtd_ingrediente); // TESTE FUNCAO FREQUENCIA
        Insere(ingrediente, p, TabelaIngredientes, qtd_ingrediente, id_doc);

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
    }

    fclose(arq);
    free(receita_str); // Liberar a memoria alocada
    return 0;
}

int Leitura_Principal(char *nomearquivo) {
    int qtd_arquivos; 
    char nome_arq[100];
    FILE *arq;
    
    arq = fopen(nomearquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        return 1;
    }
    //Realiza a leitura do meu arquivo principal 
    fscanf(arq, "%d", &qtd_arquivos);
    
    for (int i = 0; i < qtd_arquivos; i++) {
        fscanf(arq, "%s", nome_arq);
        Leitura_Secundaria(nome_arq, i); //Realiza a leitura de uma string e passa para para minusculo
    }

    fclose(arq);

    return 0;
}

int main() {
    Inicializa_Hash(TabelaIngredientes);
    GeraPesos(p);
    
    char *nome = "entrada.txt";
    
    Leitura_Principal(nome);
    Imprime_Hash(TabelaIngredientes);
    return 0;
}

void Imprime_Indice_Invertido(Lista_ID_Invertido* listaIdInvertido){
    Celula_ID *Aux = (listaIdInvertido -> primeiro->prox);
    while (Aux != NULL) { 
        printf("(<%d,%d> -> ", Aux->qdt, Aux->id_doc+1);
        Aux = Aux->prox;
    }
    printf("NULL)");
    
} 