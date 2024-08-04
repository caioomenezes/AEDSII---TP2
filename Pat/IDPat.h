//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#ifndef IDPAT_H
#define IDPAT_H
#include <stdio.h>
#include <stdlib.h>

typedef struct Celula_ID_Pat {
    int id_doc; //Numero do arquivo em que a palavra esta presente
    int qtd; 
    struct Celula_ID_Pat* prox; 
} Celula_ID_Pat;

typedef struct {
    Celula_ID_Pat* primeiro;
    Celula_ID_Pat* ultimo;
} Lista_ID_Invertido_Pat;

void Inicializa_Lista_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido);
int Retorna_Tamanho_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido);
int Verifica_Vazio_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido);
void Adiciona_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido, int qtd, int id_doc);
void Imprime_Indice_Invertido_Pat(Lista_ID_Invertido_Pat* listaIdInvertido);
int Pesquisa_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido, int id_doc);


#endif 