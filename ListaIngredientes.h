// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

/* Lista Encadeada dos Ingredientes que estão na Hash
e carregam, além da palavra, a lista encadeada dos índices invertidos*/ 

#include "IndiceInvertido.h"
#include <string.h>
#define N  100 // Tamanho maximo de uma palavra

typedef struct Lista_Ingredientes *TipoApontador;
typedef char nome_ingrediente[N];

typedef struct Celula_Ingrediente {
    nome_ingrediente Chave;
    Lista_ID_Invertido *head_ID;
    struct Celula_Ingrediente* prox;
} Celula_Ingrediente;

typedef struct {
    Celula_Ingrediente* primeiro;
    Celula_Ingrediente* ultimo;
} Lista_Ingredientes;

void Inicializa_Lista_Ingredientes(Lista_Ingredientes* listaIngredientes);
int Retorna_Tamanho_Ingredientes(Lista_Ingredientes* listaIngredientes);
Celula_Ingrediente *Pesquisa_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente ingrediente);
void Adiciona_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente ingrediente, int qtd_ingredientes, int id_doc);
void Imprime_Lista_Ingredientes(Lista_Ingredientes* listaIngredientes);
int Verifica_Vazio_Ingredientes(Lista_Ingredientes* listaIngredientes);

