#include "LeituraArquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <unistd.h>  // pra dar um tempo no terminal antes de utilizar o system clear

int main() {
    Pesos p;
    Hash TabelaIngredientes;
    TipoArvore Pat;
    Inicializa_Hash(TabelaIngredientes);
    Inicializa_Pat(&Pat);
    GeraPesos(p);
    setlocale(LC_ALL, ""); //Coracao
    int opcao;
    int opcao1_executada = 0;
    int opcao2_executada = 0; 
    char nome[100]; // Alocação de memória para a variável nome, que deve ser um array de char
    int *qtd_termos_documentos; // Quantidade de ingredientes no documento ID_DOC
    int total_de_arquivos = 0;
    char **vetor_pocoes = NULL;

    printf(" ==================== \U0001F49A BEM-VINDE \U0001F49A =====================");

    do {
        printf("\n\n =================== \U0001F49A \U0001F49A MENU \U0001F49A \U0001F49A ====================\n");
        printf("\n1. Receber arquivo de entrada com textos a serem indexados\n");
        printf("2. Construir índices invertidos usando PATRICIA e HASH\n");
        printf("3. Imprimir índices invertidos da HASH\n");
        printf("4. Imprimir índices invertidos da PATRICIA\n");
        printf("5. Realizar buscas por termo(s) na HASH\n");
        printf("6. Realizar buscas por termo(s) na PATRICIA\n");
        printf("7. Sair\n");
        printf(" ==========================================================");
        printf("\n");
        printf("Escolha uma opção: ");
        scanf("%d", &opcao);
        switch (opcao) {
            case 1:
                printf("Digite o nome do arquivo de entrada: ");
                scanf("%s", nome);
                printf("Arquivo lido com sucesso!! :)\n");
                opcao1_executada = 1;
                break;
            case 2:
                if (opcao1_executada) {
  
                    Leitura_Principal(nome, &qtd_termos_documentos, &total_de_arquivos, &vetor_pocoes, p, TabelaIngredientes, &Pat);
                    opcao2_executada = 1;
                } else {
                    printf("É necessário executar a opção 1 antes de executar essa.\n");
                }
                break;
            case 3:
                if (opcao1_executada && opcao2_executada) {
                    Imprime_Hash_Ordenada(TabelaIngredientes);
                } else if (!opcao1_executada) {
                    printf("É necessário executar a opção 1 antes de executar essa.\n");
                } else {
                    printf("É necessário executar a opção 2 antes de executar essa.\n");
                }
                break;
            case 4:
                if (opcao1_executada && opcao2_executada) {
                  int i = 0;
                  Imprime_Pat(Pat, &i);
                } else if (!opcao1_executada) {
                    printf("É necessário executar a opção 1 antes de executar essa.\n");
                } else {
                    printf("É necessário executar a opção 2 antes de executar essa.\n");
                }
                break;
            case 5:
                if (opcao1_executada && opcao2_executada) {
                    int qtd_termos_busca;
                    printf("Digite quantos termos voce deseja buscar: ");
                    scanf("%d", &qtd_termos_busca);
                    nome_ingrediente_hash ingredientes_busca[qtd_termos_busca];
                    for (int i = 0; i < qtd_termos_busca; i++) {
                        printf("Digite o termo %d: ", i + 1);
                        scanf("%s", ingredientes_busca[i]);
                        Letra_Minuscula(ingredientes_busca[i]);
                    }
                    Pesquisa_Termos_Hash(qtd_termos_documentos, total_de_arquivos, qtd_termos_busca, ingredientes_busca, vetor_pocoes, TabelaIngredientes, p);
                } else if (!opcao1_executada) {
                    printf("É necessário executar a opção 1 antes de executar essa.\n");
                } else {
                    printf("É necessário executar a opção 2 antes de executar essa.\n");
                }
                break;
            case 6:
                if (opcao1_executada && opcao2_executada) {
                  int qtd_termos_busca;
                  printf("Digite quantos termos voce deseja buscar: ");
                  scanf("%d", &qtd_termos_busca);
                  nome_ingrediente_pat ingredientes_busca[qtd_termos_busca];
                  // Aloca memória para cada string
                  for (int i = 0; i < qtd_termos_busca; i++) {
                    ingredientes_busca[i] = malloc((N) * sizeof(char));
                    if (ingredientes_busca[i] == NULL) {
                        printf("Erro ao alocar memória para o ingrediente %d.\n", i + 1);
                        // Libere a memória já alocada
                        for (int j = 0; j < i; j++) {
                            free(ingredientes_busca[j]);
                        }
                        return 1;
                    }
                    printf("Digite o termo %d (máximo %d caracteres): ", i + 1, N);
                    scanf("%s", ingredientes_busca[i]);
                    Letra_Minuscula(ingredientes_busca[i]); // Transformar em minúsculas se necessário
                  }
                  Pesquisa_Termos_Pat(qtd_termos_documentos, total_de_arquivos, qtd_termos_busca, ingredientes_busca, vetor_pocoes, Pat);
                
                } else if (!opcao1_executada) {
                  printf("É necessário executar a opção 1 antes de executar essa.\n");
                } else {
                  printf("É necessário executar a opção 2 antes de executar essa.\n");
                }
                break;
            case 7:
              setlocale(LC_ALL, "");
              printf("FIM\n");
              printf("Saindo...\n");
              printf("\U0001F49A\n"); // Emoji de coração minascoders
              break; // Adicionado para encerrar corretamente o loop
            default:
              printf("Opção inválida! Por favor, escolha uma opção válida.\n");
              break;
        
        }
    sleep(3);
    system("clear");
    } while (opcao != 7); // Corrigido para encerrar o loop quando a opção 7 for escolhida
    return 0;
}
