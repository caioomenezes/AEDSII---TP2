/* Para a leitura de cada palavra no arquivo, devemos primeiramente adicioná-las a um vetor
auxiliar e então fazer com que, a cada passada do ingrediente, este seja procurado no documento para
 que sejam gerados os arquivos invertidos. 
 
 - Primeira passada: Ler os ingredientes do arquivo.
 - Chamar, para cada ingrediente, a leitura do arquivo novamente para contabilizar os índices invertidos no doc
 - retornar o índice a cada leitura da frequencia do ingrediente e colocá-lo na hash juntamente do ingrediente
 - 
 
 Obs: Tornar todos os ingredientes e a descrição da receita em forma minúscula*/

 #include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_INGREDIENTES 100
#define MAX_NOME 100


// Função para converter string para minúsculas
void strToLower(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

// Função para verificar se uma string é igual a outra, ignorando maiúsculas
int comparaStrings(const char *str1, const char *str2) {
    return strcasecmp(str1, str2) == 0;
}

int main() {
    FILE *arquivo = fopen("arquivo1.txt", "r");
    if (!arquivo) {
        perror("Erro ao abrir o arquivo");
        return 1;
    }

    char linha[256];
    char *ingredientes[MAX_INGREDIENTES];
    int num_ingredientes = 0;
    int linha_atual = 0;
    int ponto_encontrado = 0;

    // Primeira leitura: identificar os ingredientes
    while (fgets(linha, sizeof(linha), arquivo)) {
        linha_atual++;
        if (linha_atual == 1) {
            continue;  // Ignorar a primeira linha na primeira leitura
        }

        // Verificar se a linha contém o ponto final
        if (ponto_encontrado == 0 && strchr(linha, '.')) {
            ponto_encontrado = 1;
            char *token = strtok(linha, ";.");
            while (token != NULL) {
                ingredientes[num_ingredientes] = malloc(MAX_NOME);
                strcpy(ingredientes[num_ingredientes], token);
                num_ingredientes++;
                token = strtok(NULL, ";.");
            }
        } else if (ponto_encontrado == 0) {
            // Processar linha inteira de ingredientes
            char *token = strtok(linha, ";");
            while (token != NULL) {
                ingredientes[num_ingredientes] = malloc(MAX_NOME);
                strcpy(ingredientes[num_ingredientes], token);
                num_ingredientes++;
                token = strtok(NULL, ";");
            }
        }
    }

    // Segunda leitura: contar a frequência dos ingredientes
    for (int i = 0; i < num_ingredientes; i++) {
        fseek(arquivo, 0, SEEK_SET);
        int frequencia = 0;
        while (fgets(linha, sizeof(linha), arquivo)) {
            char *token = strtok(linha, " ,.;");
            while (token != NULL) {
                char palavra[MAX_NOME];
                strcpy(palavra, token);
                //strToLower(palavra);
                if (comparaStrings(palavra, ingredientes[i])) {
                    frequencia++;
                }
                token = strtok(NULL, " ,.;");
            }
        }
        printf("Ingrediente: %s, Frequencia: %d\n", ingredientes[i], frequencia);
    }

    // Liberar memória
    for (int i = 0; i < num_ingredientes; i++) {
        free(ingredientes[i]);
    }

    fclose(arquivo);
    return 0;
}