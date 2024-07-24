#include <stdio.h>
#include <stdlib.h>

int Leitura_Principal(char *nomearquivo){
    int qtd_arquivos;
    char nome_arq;
    FILE *arq;
    arq = fopen(nomearquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }


    fscanf(arq, "%d", &qtd_arquivos);
    for(int i = 0; i ++; i<qtd_arquivos){
        fscanf(arq, "%s", nome_arq);
    }


    fclose(arq);

    return 0;
}

int Leitura_Secundaria(char *nomearquivo){
    FILE *arq;
    arq = fopen(nomearquivo, "r");
    if (arq == NULL) {
        printf("Erro ao abrir o arquivo.\n");
        return 1;
    }


}