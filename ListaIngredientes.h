// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

/* Lista Encadeada dos Ingredientes que estão na Hash
e carregam, além da palavra, a lista encadeada dos índices invertidos*/ 

#include "IndiceInvertido.h"
#define N  100  // Tamanho maximo de uma palavra

typedef struct Celula_Ingrediente {
    char ingredinte[N];
    Lista_ID_Invertido *head_ID;
    struct Celula_Ingrediente* prox;
} Celula_Ingrediente;

typedef struct {
    Celula_Ingrediente* primeiro;
    Celula_Ingrediente* ultimo;
} Lista_Ingredientes;

void Inicializa_Lista_Ingredientes(Lista_Ingredientes* Lista_Ingredientes);
int Retorna_Tamanho_Ingrediente(Lista_Ingredientes* Lista_Ingredientes);
int Verifica_Vazio_Ingrediente(Lista_Ingredientes* Lista_Ingredientes);
//void Adiciona_Ingrediente(Lista_Ingredientes* Lista_Ingredientes, char *ingrediente, Lista_ID_Invertido *head_ID);


