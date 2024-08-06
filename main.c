
//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)
#include "LeituraArquivo.h"
#include <stdio.h>
#include <stdlib.h>
#include <locale.h>
#include <time.h>

void liberar_memoria_pocoes(char **vetor_pocoes, int num_pocoes) {
    if (vetor_pocoes == NULL) return; // Se o vetor for NULL, nao precisa liberar memoria

    // Liberar a memoria de cada string
    for (int i = 0; i < num_pocoes; i++) {
        if (vetor_pocoes[i] != NULL) {
            free(vetor_pocoes[i]);
        }
    }

    // Libere a memoria do vetor de ponteiros
    free(vetor_pocoes);
}

int main() {
    Pesos p;
    Hash TabelaIngredientes;
    TipoArvore Pat;

    Inicializa_Hash(TabelaIngredientes);
    Inicializa_Pat(&Pat);
    GeraPesos(p);

    setlocale(LC_ALL, ""); //Coracao
    int opcao;
    int opcao1_executada = 0; //Para garantir que ja lemos o arquivo antes de realizar as demais opcoes
    int opcao2_executada = 0; //Para garantir que ja lemos o arquivo antes de realizar impressoes e pesquisas
    char nome[100]; //Nome do arquivo
    int *qtd_termos_documentos; // Quantidade de ingredientes no documento ID_DOC
    int total_de_arquivos = 0;
    char **vetor_pocoes = NULL; //Vetor que armazena todas as pocooes

    int compara_hash_insere = 0;
    int compara_pat_insere = 0;
    int compara_hash_pesquisa = 0;
    int compara_pat_pesquisa = 0;
    double tempo_insercao_Hash;
    double tempo_insercao_Pat;
    double tempo_Pesquisa_Pat;
    double tempo_Pesquisa_Hash;

    printf(" ==================== \U0001F49A BEM-VINDE \U0001F49A =====================");

    do {
        printf("\n\n =================== \U0001F49A \U0001F49A MENU \U0001F49A \U0001F49A ====================\n");
        printf("\n1. Receber arquivo de entrada com textos a serem indexados\n");
        printf("2. Construir indices invertidos usando PATRICIA e HASH\n");
        printf("3. Imprimir indices invertidos da HASH\n");
        printf("4. Imprimir indices invertidos da PATRICIA\n");
        printf("5. Realizar buscas por termo(s) na HASH\n");
        printf("6. Realizar buscas por termo(s) na PATRICIA\n");
        printf("7. Sair\n");
        printf(" ==========================================================\n");
        printf("\n");

        printf("Escolha uma opcao: ");
        scanf("%d", &opcao);
        switch (opcao) {
          case 1:
            printf("Digite o caminho do arquivo de entrada: ");
            scanf("%s", nome);

            if(strstr(nome, ".txt") != NULL){ //Verifica se informou um arquivo txt
              printf("Arquivo lido com sucesso!! :) \U0001F49A\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
              opcao1_executada = 1;
            } else {
              printf("Arquivo Invalido!");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
              opcao1_executada = 0;
            }
            getchar() != '\n'; 
            break;
          case 2:
            if (opcao1_executada) {
              Leitura_Principal(nome, &qtd_termos_documentos, &total_de_arquivos, &vetor_pocoes, p, TabelaIngredientes, &Pat, &compara_hash_insere, &compara_pat_insere, &tempo_insercao_Hash, &tempo_insercao_Pat);
              printf("\n==========================================================\n");
              printf("\n\U0001F49A Comparações inserção Hash e Patrícia \U0001F49A\nHash: %d comparações\nPatrícia: %d comparações\n", compara_hash_insere, compara_pat_insere);
              printf("\n\U0001F49A Tempo total de inserção Hash e Patrícia \U0001F49A\nHash: %f segundos\nPatrícia: %f segundos\n", tempo_insercao_Hash, tempo_insercao_Pat);
              printf("\n==========================================================\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
              opcao2_executada = 1;
            } else {
              printf("É necessário executar a opção 1 antes de executar essa!\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }
            getchar() != '\n'; 
            break;
          case 3:
            if (opcao1_executada && opcao2_executada) {
              printf("\n======================= IMPRESSAO DOS INDICES DA TABELA HASH =========================\n\n");
              Imprime_Hash_Ordenada(TabelaIngredientes);
              printf("\n======================================================================================\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            } else if (!opcao1_executada) {
              printf("É necessário executar a opção 1 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            } else {
              printf("É necessário executar a opção 2 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }
            getchar() != '\n'; 
            break;
          case 4:
            if (opcao1_executada && opcao2_executada) {
              int i = 0; //Para imprimir os numeros de 1 a 46
              printf("\n======================= IMPRESSAO DOS INDICES DA PATRICIA =========================\n\n");
              Imprime_Pat(Pat, &i);
              printf("\n======================================================================================\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            } else if (!opcao1_executada) {
              printf("É necessário executar a opção 1 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            } else {
              printf("É necessário executar a opção 2 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }
            getchar() != '\n'; 
            break;
          case 5:
            if (opcao1_executada && opcao2_executada) {
              int qtd_termos_busca;
              printf("Digite quantos termos voce deseja buscar: ");
              scanf("%d", &qtd_termos_busca);
              while (getchar() != '\n'); //Como estamos utilizando scanf e fgets, e necessario limpar o buffer para nao ter conflito

              nome_ingrediente_hash ingredientes_busca[qtd_termos_busca];
              for (int i = 0; i < qtd_termos_busca; i++){
                printf("Digite o termo %d: ", i + 1);
                if (fgets(ingredientes_busca[i], N, stdin) != NULL) { //fgets para ler a linha inteira (incluido espacos em branco)
                  //Essa parte garante que nao vai pegar a quebra de linha
                  size_t len = strlen(ingredientes_busca[i]);
                  if (len > 0 && ingredientes_busca[i][len - 1] == '\n') { 
                    ingredientes_busca[i][len - 1] = '\0';
                  }
                  Letra_Minuscula(ingredientes_busca[i]);
                }   
              }
              
              Pesquisa_Termos_Hash(qtd_termos_documentos, total_de_arquivos, qtd_termos_busca, ingredientes_busca, vetor_pocoes, TabelaIngredientes, p, &tempo_Pesquisa_Hash, &compara_hash_pesquisa);
              printf("\n======================================================================================\n");
              printf("\n\U0001F49A Quantidade de comparações de pesquisa na Hash \U0001F49A\n%d", compara_hash_pesquisa);
              printf("\n\U0001F49A Tempo total de pesquisa na Hash \U0001F49A\nHash: %f segundos\n", tempo_Pesquisa_Hash);
              printf("\n======================================================================================\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            
            }else if (!opcao1_executada){
              printf("É necessário executar a opção 1 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }else{
              printf("É necessário executar a opção 2 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }

            break;
          case 6:
            if (opcao1_executada && opcao2_executada) {
              int qtd_termos_busca;
              printf("Digite quantos termos voce deseja buscar: ");
              scanf("%d", &qtd_termos_busca);
              nome_ingrediente_pat ingredientes_busca[qtd_termos_busca];
              
              while (getchar() != '\n'); //Como estamos utilizando scanf e fgets, e necessario limpar o buffer para nao ter conflito

              for (int i = 0; i < qtd_termos_busca; i++) {
                //Como nome_ingrediente_pat e um ponteiro para char, e necessario alocar memoria
                ingredientes_busca[i] = malloc((N) * sizeof(char));
                if (ingredientes_busca[i] == NULL) {
                    printf("Erro ao alocar memória para o ingrediente %d.\n", i + 1);
                    // Liberar a memoria ja alocada
                    for (int j = 0; j < i; j++) {
                        free(ingredientes_busca[j]);
                    }
                    return 1;
                }

                printf("Digite o termo %d: ", i + 1);
                //Essa parte garante que nao vai pegar a quebra de linha
                if (fgets(ingredientes_busca[i], N, stdin) != NULL) {
                    size_t len = strlen(ingredientes_busca[i]);
                    if (len > 0 && ingredientes_busca[i][len - 1] == '\n') {
                        ingredientes_busca[i][len - 1] = '\0';
                    }
                    Letra_Minuscula(ingredientes_busca[i]);
                }
              }
              Pesquisa_Termos_Pat(qtd_termos_documentos, total_de_arquivos, qtd_termos_busca, ingredientes_busca, vetor_pocoes, Pat, &tempo_Pesquisa_Pat, &compara_pat_pesquisa);
              printf("\n======================================================================================\n");
              printf("\n\U0001F49A Quantidade de comparações de pesquisa na Patricia \U0001F49A\n%d", compara_pat_pesquisa);
              printf("\n\U0001F49A Tempo total de pesquisa na Patrícia \U0001F49A\nPatrícia: %f segundos\n", tempo_Pesquisa_Pat);
              printf("\n======================================================================================\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
              
              //Liberar memoria alocada para o vetor
              for (int j = 0; j < qtd_termos_busca; j++) {
                free(ingredientes_busca[j]);
              }
                    
            }else if (!opcao1_executada) {
              printf("É necessário executar a opção 1 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }else {
              printf("É necessário executar a opção 2 antes de executar essa.\n");
              fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            }
            break;

          case 7:
            printf("FIM\n");
            printf("Saindo...\n");
            printf("\U0001F49A\n"); // Emoji de coracao
            fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            getchar() != '\n'; 
            break; // Adicionado para encerrar corretamente o loop
          default:
            printf("Opção inválida! Por favor, escolha uma opção válida.\n");
            fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal
            getchar() != '\n'; 
            break;
        
        }

    printf("\nPressione Enter para sair\n");
    fflush(stdout); // Garante que a mensagem seja exibida antes de limpar o terminal

    
    getchar() != '\n'; //Pegar o "\n" que for digitado
    system("clear"); // Limpa o terminal

    } while (opcao != 7); // Corrigido para encerrar o loop quando a opção 7 for escolhida

    liberar_memoria_pocoes(vetor_pocoes, total_de_arquivos);
    free_Hash(&TabelaIngredientes);
    free_Pat(Pat);
    return 0;
}
