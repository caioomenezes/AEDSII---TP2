//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384) 

#ifndef PESQUISA_HASH_H
#define PESQUISA_HASH_H
#include <math.h>
#include "Hash.h"

typedef struct Vetor_Relevancia_Hash{
    int indice;
    float resultado_relevancia;

} Vetor_Relevancia_Hash;

float Calcular_Peso_Termo_Hash(nome_ingrediente_hash ingrediente, Hash TabelaIngrediente, int total_de_arquivos, Pesos MatrizPeso, int id_doc);
Vetor_Relevancia_Hash* Calcular_Relevancia_Termo_Hash(nome_ingrediente_hash* ingredientes, Hash TabelaIngrediente, int *qtd_termos_documentos, int total_de_arquivos, Pesos MatrizPeso,int qtd_pesquisa);
int Comparar_Relevancia_Hash(const void* a, const void* b);

void Pesquisa_Termos_Hash(int* qtd_termos_documentos, int total_de_arquivos, int qtd_termos_busca, nome_ingrediente_hash* ingredientes_busca, char** vetor_pocoes, Hash TabelaIngredientes, Pesos MatrizPeso);

#endif // PESQUISA_HASH_H