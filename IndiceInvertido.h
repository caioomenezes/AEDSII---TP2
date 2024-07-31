//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)


#include <stdio.h>
#include <stdlib.h>

typedef struct Celula_ID {
    int id_doc; //Numero do arquivo em que a palavra esta presente
    int qdt; 
    struct Celula_ID* prox; 
} Celula_ID;

typedef struct {
    Celula_ID* primeiro;
    Celula_ID* ultimo;
} Lista_ID_Invertido;

void Inicializa_Lista_ID(Lista_ID_Invertido* listaIdInvertido);
int Retorna_Tamanho_ID(Lista_ID_Invertido* listaIdInvertido);
int Verifica_Vazio_ID(Lista_ID_Invertido* listaIdInvertido);
void Adiciona_ID(Lista_ID_Invertido* listaIdInvertido, int qtd, int id_doc);
void Imprime_Indice_Invertido(Lista_ID_Invertido* listaIdInvertido);


