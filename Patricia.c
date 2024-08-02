//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "Patricia.h"

//Ja alterou
TipoBit RetornaBit(TipoBit i, nome_ingrediente Chave){ /* Retorna o i-esimo TipoBit da chave k a partir da esquerda */
  return Chave[i-1];
} 

//Nao muda
short Retorna_TipoNo(TipoArvore no){ /* Verifica se p e nodo externo */
  return (no->tipoNo == Externo); //1 para Externo e 0 para Interno
}

//Temos que adicionar a lista de indices
TipoArvore CriaNoInt(int i, char letra, TipoArvore *Esq,  TipoArvore *Dir){
  TipoArvore pat;
  pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Interno; 
  pat->No.NoInterno.Esq = *Esq;
  pat->No.NoInterno.Dir = *Dir; 
  pat->No.NoInterno.BitDiferenciador = i; 
  pat->No.NoInterno.LetraDiferenciadora = letra;

  return pat;
} 

TipoArvore CriaNoExt(nome_ingrediente Chave){ 
  TipoArvore pat;
  pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Externo; 
  strcpy(pat->No.Chave, Chave);

  return pat;
}  

TipoArvore InsereEntre(nome_ingrediente Chave, TipoArvore *pat, int i, char letra_diferenciadora){
  TipoArvore pat_aux;
  if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador){ 
    /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
    pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)*/

    pat_aux = CriaNoExt(Chave);
    
    if (RetornaBit(i, Chave) >= RetornaBit(i, (*pat)->No.Chave)){ 
      return (CriaNoInt(i, letra_diferenciadora, pat, &pat_aux));
      // Se o bit for 1, cria um novo nó interno e conecta o novo no externo a direita 
    }
    else{
      return (CriaNoInt(i, letra_diferenciadora, &pat_aux, pat));
      // Se o bit for 0, cria um novo nó interno e conecta o novo no externo a esquerda
    }
  }

  else   if (i < (*pat)->No.NoInterno.BitDiferenciador){ 
    /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
    pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)*/

    pat_aux = CriaNoExt(Chave);
    
    if (RetornaBit(i, Chave) >= letra_diferenciadora){ 
      return (CriaNoInt(i, letra_diferenciadora, pat, &pat_aux));
      // Se o bit for 1, cria um novo nó interno e conecta o novo no externo a direita 
    }
    else{
      return (CriaNoInt(i, letra_diferenciadora, &pat_aux, pat));
      // Se o bit for 0, cria um novo nó interno e conecta o novo no externo a esquerda
    }
  }

  else{
    if(RetornaBit((*pat)->No.NoInterno.BitDiferenciador,Chave) >= (*pat)->No.NoInterno.LetraDiferenciadora){
      (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora);
      // Se o bit no BitDiferenciador for 1, insere na sub-arvore direita
    }
    else{
      (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora);
      // Se o bit no BitDiferenciador for 0, insere na sub-arvore esquerda
    }
    return (*pat);
  }
}


TipoArvore Insere(nome_ingrediente Chave, TipoArvore *pat){ 
  TipoArvore pat_aux; //Arvore aux para para percorrer sem efetuar modificacoes efetivas
  char letra_aux;
  char letra_diferenciadora;
  int tamanho = strlen(Chave);
  int i;

  if (*pat == NULL){
    return (CriaNoExt(Chave)); //Se for o primeiro ingrediente a ser inserido, ele automaticamente é um no externo
  }

  else{ 
    pat_aux = *pat;

    while (!Retorna_TipoNo(pat_aux)){ //Percorre enquanto for um no interno
      //Se minha chave for menor que o bit onde as palavras se diferenciam significa que eu tenho um novo prefixo, 
      //pois minha palavra a ser inserida esta fora do limite do bit diferenciador (ela menor que o prefixo que esta na arvore)
      if(tamanho < pat_aux->No.NoInterno.BitDiferenciador){
        letra_aux = Chave[tamanho]; 
      }
      /*Se minha chave for maior que o bit onde as palavras se diferenciam significa que eu tenho que encontrar 
      a letra que está no valor do bit diferenciador da minha chave a ser inserida, pois existe a possibilidade de usarmos o mesmo prefixo*/
      else {
        letra_aux = RetornaBit(pat_aux->No.NoInterno.BitDiferenciador, Chave);
      }

      //Define se eu vou para minha sub arvore esquerda (letra da chave que estou inserindo é maior que a letra diferenciadora) ou direita (letra da chave que estou inserindo é menor que a letra diferenciadora)
      if (letra_aux >= pat_aux->No.NoInterno.LetraDiferenciadora){
        pat_aux = pat_aux->No.NoInterno.Dir;
      }
      else{
        pat_aux = pat_aux->No.NoInterno.Esq;
      }
    }

    //Encontra o primeiro bit diferente 
    i = 1;
    while ((i <= tamanho) & (RetornaBit((int)i, Chave) == RetornaBit((int)i, pat_aux->No.Chave))){ //Verifica em qual bit a chave que ssera inserida se 
    //difencia do no encontrado em pat_aux (onde a nova chave sera inserida )
      i++;
    }
    if (i > tamanho){ //Se eu percorrer o tamanho maximo da minha chave e nao encontrar um bit diferente significa que elas sao iguais
      //Aqui vamos ter que apenas inserir o indice e invertido e não vai ter esse print
      printf("Erro: chave ja esta na arvore\n");
      return (*pat);
    } 
    else{ //Quando os indíces das palavras são diferentes compara qual é maior
    
      // Se o bit da palavra a ser inserida for maior que o bit da palavra que já está presente, 
      //então a letra diferenciadora receberá a letra da palavra que vai ser inserida
      if(RetornaBit(i, Chave) > (RetornaBit(i, pat_aux->No.Chave))){
        letra_diferenciadora = Chave[i - 1];
      }
      else{ 
        // Se o bit da palavra que queremos inserir for menor ou igual que o bit da palavra que já está presente, 
        //então a letra diferenciadora receberá a letra que já está presente no nó
        letra_diferenciadora = pat_aux->No.Chave[i -1];
      }
      return (InsereEntre(Chave, pat, i, letra_diferenciadora)); //O insere entre que efetua realmente a insercao na arvore é onde meu no é criado 
    }
  }
}

// Função para imprimir a árvore (Para depuração)
// Função para imprimir as chaves em ordem

void ImprimePatricia(TipoArvore arvore)
{
    // verifica se arvore nao está vazia
    if (arvore != NULL)
    {
        // se no for extrerno printa a chave
        if (arvore->tipoNo == Externo)
        {
            printf("%s ", arvore->No.Chave);
        }
        else
        { // se for nó interno, percorre recursivo tanto para esquerda como para direita
            ImprimePatricia(arvore->No.NoInterno.Esq);
            ImprimePatricia(arvore->No.NoInterno.Dir);
        }
    }
}


int main() {
    TipoArvore arvore = NULL; // Inicializa a árvore como vazia

    // Inserção de chaves
    arvore = Insere("caia", &arvore);
    arvore = Insere("caza", &arvore);
    arvore = Insere("cada", &arvore);
    arvore = Insere("caio", &arvore);
    arvore = Insere("cafe", &arvore);
    arvore = Insere("carro", &arvore);

    ImprimePatricia(arvore);
    // Imprime a árvore
    printf("\nEstrutura da árvore Patricia:\n");
    printf("\nDir:");
    ImprimePatricia(arvore->No.NoInterno.Dir);
    printf("\nEsq:");
    ImprimePatricia(arvore->No.NoInterno.Esq);

    return 0;
}