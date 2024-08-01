#include<stdlib.h> 
#include<stdio.h>
#include <sys/time.h>
#define D 8   //Tamanho da minha chave

typedef unsigned char nome_ingrediente;
typedef unsigned char TipoBit;

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
      } NoInterno ;
      nome_ingrediente Chave;
  } No;
} TipoPatNo; 



TipoBit RetornaBit(TipoBit i, nome_ingrediente Chave){ /* Retorna o i-esimo TipoBit da chave k a partir da esquerda */
  int  c, j;
  if (i == 0)
  return 0;
  else { 
    c = Chave;
    for (j = 1; j <= D - i; j++){
      c /= 2;
    }
    return (c & 1);
  }
} 

short Retorna_TipoNo(TipoArvore no){ /* Verifica se p e nodo externo */
  return (no->tipoNo == Externo); //1 para Externo e 0 para Interno
}

TipoArvore CriaNoInt(int i, TipoArvore *Esq,  TipoArvore *Dir){
  TipoArvore pat;
  pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Interno; 
  pat->No.NoInterno.Esq = *Esq;
  pat->No.NoInterno.Dir = *Dir; 
  pat->No.NoInterno.BitDiferenciador = i; 
  return pat;
} 

TipoArvore CriaNoExt(nome_ingrediente Chave){ 
  TipoArvore pat;
  pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Externo; 
  pat->No.Chave = Chave; 
  return pat;
}  

void Pesquisa(nome_ingrediente Chave, TipoArvore pat){ 
  if (Retorna_TipoNo(pat)){ 
    if (Chave == pat->No.Chave){
      printf("Elemento encontrado\n");
    }
    else{
      printf("Elemento nao encontrado\n");
    }
    return;
  }
    
  if (RetornaBit(pat->No.NoInterno.BitDiferenciador, Chave) == 0){
    Pesquisa(Chave, pat->No.NoInterno.Esq);
  }
    
  else{
    Pesquisa(Chave, pat->No.NoInterno.Dir);
  }
} 

TipoArvore InsereEntre(nome_ingrediente Chave, TipoArvore *pat, int i){
  TipoArvore pat_aux;
  if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador){ 
    /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
    pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)*/

    pat_aux = CriaNoExt(Chave);
    
    if (RetornaBit(i, Chave) == 1){ 
      return (CriaNoInt(i, pat, &pat_aux));
      // Se o bit for 1, cria um novo nó interno e conecta o novo no externo a direita 
    }
    else{
      return (CriaNoInt(i, &pat_aux, pat));
      // Se o bit for 0, cria um novo nó interno e conecta o novo no externo a esquerda
    }
  }

  else{
    if (RetornaBit((*pat)->No.NoInterno.BitDiferenciador, Chave) == 1){
      (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i);
      // Se o bit no BitDiferenciador for 1, insere na sub-arvore direita
    }
    else{
      (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i);
      // Se o bit no BitDiferenciador for 0, insere na sub-arvore esquerda
     
    }
    return (*pat);
  }
}


TipoArvore Insere(nome_ingrediente Chave, TipoArvore *pat){ 
  TipoArvore pat_aux; //Arvore aux para para percorrer sem efetuar modificacoes efetivas
  int i;

  if (*pat == NULL){
    return (CriaNoExt(Chave)); //Se for o primeiro ingrediente a ser inserido, ele automaticamente é um no externo
  }

  else{ 
    pat_aux = *pat;
    while (!Retorna_TipoNo(pat_aux)){ //Percorre enquanto for um no interno

      //Define se eu vou para minha sub arvore esquerda (Bit = 1) ou direita (Bit = 0)
      if (RetornaBit(pat_aux->No.NoInterno.BitDiferenciador, Chave) == 1){
        pat_aux = pat_aux->No.NoInterno.Dir;
      }
      else{
        pat_aux = pat_aux->No.NoInterno.Esq;
      }
    }
    //Encontra o primeiro bit diferente 
    i = 1;
    while ((i <= D) & (RetornaBit((int)i, Chave) == RetornaBit((int)i, pat_aux->No.Chave))){ //Verifica em qual bit a chave que ssera inserida se 
    //difencia do no encontrado em pat_aux (onde a nova chave sera inserida )
      i++;
    }

    if (i > D){ //Se eu percorrer o tamanho maximo da minha chave e nao encontrar um bit diferente significa que elas sao iguais
      //Aqui vamos ter que apenas inserir o indice e invertido e não vai ter esse print
      printf("Erro: chave ja esta na arvore\n");
      return (*pat);
    } 
    else{
      return (InsereEntre(Chave, pat, i)); //O insere entre que efetua realmente a insercao na arvore é onde meu no é criado 
    }
  }
}
