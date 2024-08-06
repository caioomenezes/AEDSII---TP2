// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

/* Lista Encadeada dos Ingredientes que estão na Hash
e carregam, além da palavra, a lista encadeada dos índices invertidos*/ 
// Arquivo: ListaIngredientes.h
#ifndef LISTA_INGREDIENTES_H
#define LISTA_INGREDIENTES_H

#include "IDHash.h"
#include <string.h>
#define N  100 // Tamanho maximo de uma palavra

typedef struct Lista_Ingredientes *TipoApontador;
typedef char nome_ingrediente_hash[N];

typedef struct Celula_Ingrediente {
    nome_ingrediente_hash Chave;
    Lista_ID_Invertido_Hash *head_ID;
    struct Celula_Ingrediente* prox;
} Celula_Ingrediente;

typedef struct {
    Celula_Ingrediente* primeiro;
    Celula_Ingrediente* ultimo;
} Lista_Ingredientes;

void Inicializa_Lista_Ingredientes(Lista_Ingredientes* listaIngredientes);
int Retorna_Tamanho_Ingredientes(Lista_Ingredientes* listaIngredientes);
Celula_Ingrediente *Pesquisa_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente_hash ingrediente); //Usada na insercao
Celula_Ingrediente* Pesquisa_Hash(Lista_Ingredientes* listaIngredientes, nome_ingrediente_hash ingrediente, int *compara_hash_pesquisa); //Usada na busca por um termo pesquisado no main
void Adiciona_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente_hash ingrediente, int qtd_ingredientes, int id_doc);
void Imprime_Lista_Ingredientes(Lista_Ingredientes* listaIngredientes);
int Verifica_Vazio_Ingredientes(Lista_Ingredientes* listaIngredientes);
void Imprime_Ingrediente(int contador, Celula_Ingrediente** vetor_hash);
void free_Ingredientes(Lista_Ingredientes *listaIngrediente);
#endif // LISTA_INGREDIENTES_H