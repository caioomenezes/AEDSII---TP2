//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#ifndef PESQUISA_PAT_H
#define PESQUISA_PAT_H
#include <math.h>
#include "Patricia.h"

//Como vamos ordenar o vetor de relevancia, eh necessario ter o id_doc 
typedef struct Vetor_Relevancia_Pat{
    int indice;
    float resultado_relevancia;
}Vetor_Relevancia_Pat;

float Calcular_Peso_Termo_Pat(nome_ingrediente_pat ingrediente, TipoArvore pat, int total_de_arquivos, int id_doc, int *compara_pat_pesquisa);
Vetor_Relevancia_Pat* Calcular_Relevancia_Termo_Pat(nome_ingrediente_pat* ingredientes, TipoArvore pat, int* qtd_termos_documentos, int total_de_arquivos,int qtd_pesquisa, int *compara_pat_pesquisa);
int Comparar_Relevancia_Pat(const void* a, const void* b); //Funcao usada no qsort
void Pesquisa_Termos_Pat(int* qtd_termos_documentos, int total_de_arquivos, int qtd_termos_busca, nome_ingrediente_pat* ingredientes_busca, char** vetor_pocoes, TipoArvore pat, double *tempo_Pesquisa_Pat, int* compara_pat_pesquisa);

#endif