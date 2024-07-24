#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

void Letra_Minuscula(char *str) { // Funcao para colocar os caracteres em forma minuscula (Nao eh case sensitive)
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

int Leitura_Secundaria(char *nomearquivo) {
    FILE *arq;
    long int tamanho_arquivo;
    char *receita_str; 
    arq = fopen(nomearquivo, "r");

    if (arq == NULL) {
        printf("Erro ao abrir o arquivo %s.\n", nomearquivo);
        return 1;
    }
    char ingrediente[100];
    char aux;
    fgets(ingrediente, sizeof(ingrediente), arq);

    
    while (fscanf(arq, "%99[^.;]", ingrediente) == 1) {
        // Imprime o ingrediente lido
        printf("Ingrediente: %s\n", ingrediente);
        
       // Lê o próximo caractere
        fscanf(arq, "%c", &aux);
        
        // Verifica se é o ponto final
        if (aux == '.') {
            break;  // Sai do loop ao encontrar o ponto final
        }
    }



/*
    // Determina o tamanho do arquivo
    fseek(arq, 0, SEEK_END);  // Move o cursor para o final do arquivo
    tamanho_arquivo = ftell(arq);  // Obtém a posição atual do cursor (tamanho do arquivo)
    rewind(arq);  // Volta o cursor para o início do arquivo

    // Aloca memória para armazenar o conteúdo do arquivo
    receita_str = (char *)malloc(tamanho_arquivo + 1);  // +1 para o caractere nulo '\0'
    if (receita_str == NULL) {
        printf("Erro ao alocar memória para o conteúdo do arquivo.\n");
        fclose(arq);
        return 1;
    
    }
    // Lê o conteúdo do arquivo para a string
    fread(receita_str, 1, tamanho_arquivo, arq);
    Letra_Minuscula(receita_str);
*/
    fclose(arq);
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

    fscanf(arq, "%d", &qtd_arquivos);
    for (int i = 0; i < qtd_arquivos; i++) {
        fscanf(arq, "%s", nome_arq);
        Leitura_Secundaria(nome_arq);
    }

    fclose(arq);

    return 0;
}

int main() {
    char *nome = "entrada.txt";
    Leitura_Principal(nome);

    return 0;
}
