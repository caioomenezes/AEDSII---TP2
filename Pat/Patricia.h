//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#ifndef PATRICIA_H
#define PATRICIA_H
#include <sys/time.h>
#include <string.h>
#define N 100

#include "IDPat.h"
typedef char* nome_ingrediente_pat;
typedef char TipoBit;

typedef enum {
  Interno, Externo //O no externo guarda apenas a chave final, o interno as informacoes de onde tem um prefixo e as arvores esq e dir
} TipoNo;


typedef struct TipoPatNo* TipoArvore; 
typedef struct TipoPatNo {
    
  TipoNo tipoNo; //guarda se é interno ou externo
  union {  //A union permite armazenar diferentes tipos de dados no mesmo espaço de memória. 
    struct {
      TipoBit BitDiferenciador;
      TipoArvore Esq, Dir; //Arvore esq e dir, significa que o resto da palavra depois do prefixo
      char LetraDiferenciadora;
    } NoInterno ;
    //Lista_ID_Invertido_Pat *head_ID;
    nome_ingrediente_pat Chave;
  } No;
  Lista_ID_Invertido_Pat *head_ID;
} TipoPatNo; 


TipoBit RetornaBit(TipoBit i, nome_ingrediente_pat Chave);/* Retorna o i-esimo TipoBit da chave k a partir da esquerda */
short Retorna_TipoNo(TipoArvore no);
TipoArvore CriaNoInt(int i, char letra, TipoArvore *Esq,  TipoArvore *Dir);
TipoArvore CriaNoExt(nome_ingrediente_pat Chave, int qtd_ingredientes, int id_doc);
TipoArvore InsereEntre(nome_ingrediente_pat Chave, TipoArvore *pat, int i, char letra_diferenciadora, int qtd_ingredientes, int id_doc);
TipoArvore Insere_Pat(nome_ingrediente_pat Chave, TipoArvore *pat, int qtd_ingredientes, int id_doc);
void Imprime_Pat(TipoArvore arvore, int* i);
void Inicializa_Pat(TipoArvore* arvore);
TipoPatNo* Pesquisa_Pat(nome_ingrediente_pat Chave, TipoArvore Pat);

#endif 