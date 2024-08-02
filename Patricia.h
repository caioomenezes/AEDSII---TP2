//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include<stdlib.h> 
#include<stdio.h>
#include <sys/time.h>
#include <string.h>
#define N 100

typedef char nome_ingrediente[N];
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
      nome_ingrediente Chave;
  } No;
} TipoPatNo; 

TipoBit RetornaBit(TipoBit i, nome_ingrediente Chave);/* Retorna o i-esimo TipoBit da chave k a partir da esquerda */
short Retorna_TipoNo(TipoArvore no);
TipoArvore CriaNoInt(int i, char letra, TipoArvore *Esq,  TipoArvore *Dir);
TipoArvore CriaNoExt(nome_ingrediente Chave);
TipoArvore InsereEntre(nome_ingrediente Chave, TipoArvore *pat, int i, char letra_diferenciadora);
TipoArvore Insere(nome_ingrediente Chave, TipoArvore *pat);