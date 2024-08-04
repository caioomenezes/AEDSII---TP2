// Arquivo: IDHash.h
#ifndef IDHASH_H
#define IDHASH_H

typedef struct Celula_ID_Hash {
    int id_doc;
    int qtd;
    struct Celula_ID_Hash* prox;
} Celula_ID_Hash;

typedef struct {
    Celula_ID_Hash* primeiro;
    Celula_ID_Hash* ultimo;
} Lista_ID_Invertido_Hash;

void Inicializa_Lista_ID_Hash(Lista_ID_Invertido_Hash* listaIdInvertido);
int Retorna_Tamanho_ID_Hash(Lista_ID_Invertido_Hash* listaIdInvertido);
int Verifica_Vazio_ID_Hash(Lista_ID_Invertido_Hash* listaIdInvertido);
void Adiciona_ID_Hash(Lista_ID_Invertido_Hash* listaIdInvertido, int qtd, int id_doc);
void Imprime_Indice_Invertido_Hash(Lista_ID_Invertido_Hash* listaIdInvertido);
int Pesquisa_ID_Hash(Lista_ID_Invertido_Hash* listaIdInvertido, int id_doc);

#endif // IDHASH_H



void Pesquisa(TipoChave k, TipoArvore t)
{ if (EExterno(t)) 
  { if (k == t->NO.Chave) 
    printf("Elemento encontrado\n");
    else printf("Elemento nao encontrado\n");
    return;
  }
  if (Bit(t->NO.NInterno.Index, k) == 0) 
  Pesquisa(k, t->NO.NInterno.Esq);
  else Pesquisa(k, t->NO.NInterno.Dir);
} 

