
#ifndef PESQUISA_HASH_H
#define PESQUISA_HASH_H
#include <math.h>
#include "Hash.h"


float Calcular_Peso_Termo_Hash(nome_ingrediente_hash ingrediente, Hash TabelaIngrediente, int total_de_arquivos, Pesos MatrizPeso, int id_doc);
void Calcular_Relevancia_Termo_Hash(nome_ingrediente_hash* ingredientes, Hash TabelaIngrediente, int *qtd_termos_documentos, int total_de_arquivos, Pesos MatrizPeso,int qtd_pesquisa);

#endif // PESQUISA_HASH_H