//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)
#ifndef HASH_H
#define HASH_H

#include "ListaIngredientes.h"

//verificar includes
#include <sys/time.h>
#define VAZIO  "!!!!!!!!!!"
#define RETIRADO  "**********" 
#define M 17 //Tamanho da tabela Hash   
#define TAMALFABETO 256

typedef unsigned Pesos[N][TAMALFABETO];
typedef Lista_Ingredientes Hash[M];

void GeraPesos(Pesos MatrizPesos);
unsigned int HashingUniversal(nome_ingrediente_hash Chave, Pesos MatrizPesos);
void Inicializa_Hash(Hash TabelaIngredientes);
void Insere_Hash(nome_ingrediente_hash ingrediente, Pesos p, Hash TabelaIngredientes, int qtd_ingrediente, int id_Doc);
void Imprime_Hash(Hash TabelaIngredientes);
void Imprime_Hash_Ordenada(Hash TabelaIngredientes);
int compararIngredientes(const void* a, const void* b);
void CopiaHash(Hash TabelaIngredientes, int* contador, Celula_Ingrediente** vetor_hash);

#endif // HASH_H