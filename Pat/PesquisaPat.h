
#ifndef PESQUISA_PAT_H
#define PESQUISA_PAT_H
#include <math.h>
#include "Patricia.h"

typedef struct Vetor_Relevancia_Pat{
    int indice;
    float resultado_relevancia;
}Vetor_Relevancia_Pat;

float Calcular_Peso_Termo_Pat(nome_ingrediente_pat ingrediente, TipoArvore pat, int total_de_arquivos, int id_doc);
Vetor_Relevancia_Pat* Calcular_Relevancia_Termo_Pat(nome_ingrediente_pat* ingredientes, TipoArvore pat, int* qtd_termos_documentos, int total_de_arquivos,int qtd_pesquisa);
int Comparar_Relevancia_Pat(const void* a, const void* b);

#endif