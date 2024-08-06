//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "Patricia.h"

void Inicializa_Pat(TipoArvore* arvore){
  (*arvore) = NULL;
}

TipoBit RetornaBit(TipoBit i, nome_ingrediente_pat Chave){ /* Retorna a i-esima letra da Chave a partir da esquerda */
  return Chave[i-1];
} 

short Retorna_TipoNo(TipoArvore no){ // Verifica se p e no externo
  return (no->tipoNo == Externo); //1 para Externo e 0 para Interno
}


TipoArvore CriaNoInt(int i, char letra, TipoArvore *Esq, TipoArvore *Dir) {
  TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo)); 
  pat->tipoNo = Interno; 
  pat->No.NoInterno.Esq = *Esq;
  pat->No.NoInterno.Dir = *Dir; 
  pat->No.NoInterno.BitDiferenciador = i; //Posicao onde elas se diferenciam
  pat->No.NoInterno.LetraDiferenciadora = letra; //Letra onde ocorre a difenciacao
  return pat;
} 

TipoArvore CriaNoExt(nome_ingrediente_pat Chave, int qtd_ingrediente, int id_doc) { 
  TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Externo; 
  pat->No.Chave = strdup(Chave); //Duplicando a string

  Lista_ID_Invertido_Pat* listaIdInvertido = (Lista_ID_Invertido_Pat*)malloc(sizeof(Lista_ID_Invertido_Pat)); //Alocando memoria da lista de id
  
  //Inicializa a lista
  Inicializa_Lista_ID_Pat(listaIdInvertido);
  pat->head_ID = listaIdInvertido;
  Adiciona_ID_Pat(listaIdInvertido, qtd_ingrediente, id_doc);
  return pat;
}


TipoArvore InsereEntre(nome_ingrediente_pat Chave, TipoArvore *pat, int i, char letra_diferenciadora, int qtd_ingredientes, int id_doc, int* compara_pat_insere) {
  TipoArvore pat_aux;
  int bitAtualChave, bitComparacao;
  //Analisa se o No e externo OU se temos um prefixo

  (*compara_pat_insere)+=2; //Comparacao do if (duas comparacoes)
  if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador) {
    pat_aux = CriaNoExt(Chave, qtd_ingredientes, id_doc);

    (*compara_pat_insere)++; //Comparacao do if
    // Determina o bit de comparacao, quando no eh externo vamos usar o prefixo que ja esta na arvore, pois ele eh comun aos dois,
    // ja quando nao eh, vamos precisar criar um novo, pois eles se diferenciam em algum bit antes do que ja esta armazenado
    if (Retorna_TipoNo(*pat)) {
      bitAtualChave = RetornaBit(i, (*pat)->No.Chave);
    } else {
      bitAtualChave = letra_diferenciadora;
    }

    bitComparacao = RetornaBit(i, Chave); 

    (*compara_pat_insere)++; //Comparacao do if
    // Decidir a posicao do novo no externo com base no bit na posição i
    if (bitComparacao >= bitAtualChave) { 
      /*Comparamos se a chave do bit atual eh maior que o bit comparacao, se for, criamos um no interno a direita da nossa arvore
      (lembrando que pat_aux guarda a posicao inicial da arvore, eh o lado onde nao ocorre mudanças)*/
      return CriaNoInt(i, letra_diferenciadora, pat, &pat_aux); 
    } else {
      //se nao for, criamos um no interno a esquerda da nossa arvore
      return CriaNoInt(i, letra_diferenciadora, &pat_aux, pat);
    }
    
  } else {
    // Insercao recursiva na sub-arvore
    (*compara_pat_insere)++; //Comparacao do if
    bitComparacao = RetornaBit((*pat)->No.NoInterno.BitDiferenciador, Chave); // Obtem o valor do bit na posicao diferenciadora da nova chave
    if (bitComparacao >= (*pat)->No.NoInterno.LetraDiferenciadora){ // Compara o valor do bit da nova chave com o valor de referencia do no interno
      (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora, qtd_ingredientes, id_doc, compara_pat_insere);
      //Se o bit no BitDiferenciador for maior ou igual, insere na sub-arvore direita
    }
    else {
      (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora, qtd_ingredientes, id_doc, compara_pat_insere);
      //Se o bit no BitDiferenciador for menor insere na sub-arvore esquerda
    }
    return *pat;
  }
}

TipoArvore Insere_Pat(nome_ingrediente_pat Chave, TipoArvore *pat, int qtd_ingredientes, int id_doc, int* compara_pat_insere){ 
  TipoArvore pat_aux; //Arvore aux para para percorrer sem efetuar modificacoes efetivas
  char letra_aux;
  char letra_diferenciadora;
  int tamanho = strlen(Chave);
  int i;
  (*compara_pat_insere)++; //comparacao do if
  if (*pat == NULL){
      //Se a arvore esta vazia, cria um novo nó externo
      return CriaNoExt(Chave, qtd_ingredientes, id_doc); 
  } else { 
    pat_aux = *pat;
    // Percorre a arvore ate encontrar um no externo
    while (!Retorna_TipoNo(pat_aux)){ 
      (*compara_pat_insere)++; //comparacao do while

      (*compara_pat_insere)++; //Comparacao do if
      if(tamanho < pat_aux->No.NoInterno.BitDiferenciador){
        letra_aux = Chave[tamanho]; 
      } else {
        letra_aux = RetornaBit(pat_aux->No.NoInterno.BitDiferenciador, Chave);
      }

      (*compara_pat_insere)++; //Comparacao do if
      // Define se vai para a sub-arvore esquerda ou direita
      if (letra_aux >= pat_aux->No.NoInterno.LetraDiferenciadora){
        pat_aux = pat_aux->No.NoInterno.Dir;
      } else {
        pat_aux = pat_aux->No.NoInterno.Esq;
      }
    }

    // Encontra o primeiro bit diferente entre a chave nova e a existente
    i = 1;
    while ((i <= tamanho) && (RetornaBit(i, Chave) == RetornaBit(i, pat_aux->No.Chave))) {
      (*compara_pat_insere)+= 2; //Comparacao do while (temos duas comparacoes)
      i++;
    }
    (*compara_pat_insere)++; //Comparacao do if
    // Se a chave ja existe, adiciona o ID ao no existente
    if (strcmp(Chave, pat_aux->No.Chave) == 0){
      Adiciona_ID_Pat(pat_aux->head_ID, qtd_ingredientes, id_doc);
      return (*pat);
    } else {
      // Determina a letra diferenciadora
      (*compara_pat_insere)++; //Comparacao do if
      if (RetornaBit(i, Chave) >= RetornaBit(i, pat_aux->No.Chave)){
        letra_diferenciadora = Chave[i - 1];
      } else { 
        letra_diferenciadora = pat_aux->No.Chave[i - 1];
      }
      return InsereEntre(Chave, pat, i, letra_diferenciadora, qtd_ingredientes, id_doc, compara_pat_insere);
    }
  }
}


void Imprime_Pat(TipoArvore arvore, int* i) {
  if (arvore != NULL) {
      if (arvore->tipoNo == Externo) {
          printf("%02d: ", (*i) + 1); // Imprime o indice formatado com duas casas decimais
          printf("%s ", arvore->No.Chave);
          Imprime_Indice_Invertido_Pat(arvore->head_ID);
          putchar('\n');
          (*i)++;
      } else {
          // Percorre recursivamente para a esquerda e direita
          Imprime_Pat(arvore->No.NoInterno.Esq, i);
          Imprime_Pat(arvore->No.NoInterno.Dir, i);
      }
  } else {
    printf("Arvore vazia");
  }
}



TipoPatNo* Pesquisa_Pat(nome_ingrediente_pat Chave, TipoArvore Pat, int *compara_pat_pesquisa) {
  (*compara_pat_pesquisa) ++; //Comparacao do if
  // Verifica se o no atual eh nulo
  if (Pat == NULL) {
    printf("Árvore vazia ou elemento não encontrado\n");
    return NULL;
  }

  (*compara_pat_pesquisa) ++; //Comparacao do if
  // Verifica se o no atual eh um no externo e se a chave eh igual
  if (Retorna_TipoNo(Pat)) { 
    (*compara_pat_pesquisa) ++; //Comparacao do if
    if (strcmp(Chave, Pat->No.Chave) == 0) {
      return Pat;
    } else {
      return NULL;
    }
  }

  (*compara_pat_pesquisa) ++; //Comparacao do if
  // Se o no nao eh externo, decide para qual filho seguir
  if (RetornaBit(Pat->No.NoInterno.BitDiferenciador, Chave) < Pat->No.NoInterno.LetraDiferenciadora) {
    return Pesquisa_Pat(Chave, Pat->No.NoInterno.Esq, compara_pat_pesquisa); // Pesquisa no filho esquerdo
  } else {
    return Pesquisa_Pat(Chave, Pat->No.NoInterno.Dir, compara_pat_pesquisa); // Pesquisa no filho direito
  }
}

void free_Pat(TipoArvore arvore) {
    if (arvore == NULL) return;

    // Verificar se o no eh interno ou externo
    if (Retorna_TipoNo) {
        // Liberar as sub-arvores
        free_Pat(arvore->No.NoInterno.Esq);
        free_Pat(arvore->No.NoInterno.Dir);
    }

    // Liberar a lista de IDs associada ao no
    if (arvore->head_ID != NULL) {
        free_ID_Invertido_Pat(arvore->head_ID);
    }

    // Liberar o proprio no
    free(arvore);
}