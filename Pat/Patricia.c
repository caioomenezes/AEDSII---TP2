//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "Patricia.h"

void Inicializa_Pat(TipoArvore* arvore){
  (*arvore) = NULL;
}

TipoBit RetornaBit(TipoBit i, nome_ingrediente_pat Chave){ /* Retorna o i-esimo TipoBit da chave Chave a partir da esquerda */
  return Chave[i-1];
} 

short Retorna_TipoNo(TipoArvore no){ /* Verifica se p e nodo externo */
  return (no->tipoNo == Externo); //1 para Externo e 0 para Interno
}


TipoArvore CriaNoInt(int i, char letra, TipoArvore *Esq, TipoArvore *Dir) {
  TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Interno; 
  pat->No.NoInterno.Esq = *Esq;
  pat->No.NoInterno.Dir = *Dir; 
  pat->No.NoInterno.BitDiferenciador = i; 
  pat->No.NoInterno.LetraDiferenciadora = letra;
  return pat;
} 

TipoArvore CriaNoExt(nome_ingrediente_pat Chave, int qtd_ingrediente, int id_doc) { 
  TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo));
  pat->tipoNo = Externo; 
  pat->No.Chave = strdup(Chave); // Duplicando a string
  Lista_ID_Invertido_Pat* listaIdInvertido = (Lista_ID_Invertido_Pat*)malloc(sizeof(Lista_ID_Invertido_Pat));
  Inicializa_Lista_ID_Pat(listaIdInvertido); // Inicializar a lista
  pat->head_ID = listaIdInvertido;
  Adiciona_ID_Pat(listaIdInvertido, qtd_ingrediente, id_doc);
  return pat;
}


TipoArvore InsereEntre(nome_ingrediente_pat Chave, TipoArvore *pat, int i, char letra_diferenciadora, int qtd_ingredientes, int id_doc) {
  TipoArvore pat_aux;
  int bitAtualChave, bitComparacao;
  /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
  pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)*/
  if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador) {
    pat_aux = CriaNoExt(Chave, qtd_ingredientes, id_doc);

    // Determina o bit de comparação, quando no é externo vamos usar o prefixo que ja esta na arvore, pois ele é comun aos dois,
    // ja quando nao e, vamos precisar criar um novo, pois eles se diferenciam em um bit antes do que ja esta armazenado
    if (Retorna_TipoNo(*pat)) {
      bitAtualChave = RetornaBit(i, (*pat)->No.Chave);
    } else {
      bitAtualChave = letra_diferenciadora;
    }

    bitComparacao = RetornaBit(i, Chave); 

    // Decidir a posição do novo nó externo com base no bit na posição i
    if (bitComparacao >= bitAtualChave) { //Comparamos se a chave do bit atual é maior que o bit comparaçao, 
      //se for, criamos um no interno a direita da nossa arvore (lembrando que pat_aux é a variavel que a gente usou para percorrer e a insercao sera feita nela)
      return CriaNoInt(i, letra_diferenciadora, pat, &pat_aux); 
    } else {
      //se nao for, criamos um no interno a esquerda da nossa arvore
      return CriaNoInt(i, letra_diferenciadora, &pat_aux, pat);
    }
    
  } else {
    // Inserção recursiva na sub-árvore
    bitComparacao = RetornaBit((*pat)->No.NoInterno.BitDiferenciador, Chave); // Obtem o valor do bit na posicao diferenciadora da nova chave
    if (bitComparacao >= (*pat)->No.NoInterno.LetraDiferenciadora){ // Compara o valor do bit da nova chave com o valor de referência do nó interno
      (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora, qtd_ingredientes, id_doc);
       // Se o bit no BitDiferenciador for maior ou igual, insere na sub-arvore direita
    }
    else {
      (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora, qtd_ingredientes, id_doc);
      // Se o bit no BitDiferenciador for menor insere na sub-arvore esquerda
    }
    return *pat;
  }
}

/*TipoArvore InsereEntre(nome_ingrediente_pat Chave, TipoArvore *pat, int i, char letra_diferenciadora, int qtd_ingredientes, int id_doc){
  TipoArvore pat_aux;
  if (Retorna_TipoNo(*pat)){ 
    /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
    pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)

    pat_aux = CriaNoExt(Chave, 1, 0);

    if (RetornaBit(i, Chave) >= RetornaBit(i, (*pat)->No.Chave)){ 
      return (CriaNoInt(i, letra_diferenciadora, pat, &pat_aux));
      // Se o bit for 1, cria um novo nó interno e conecta o novo no externo a direita 
    }
    else{
      return (CriaNoInt(i, letra_diferenciadora, &pat_aux, pat));
      // Se o bit for 0, cria um novo nó interno e conecta o novo no externo a esquerda
    }
  }
 
  else if (i < (*pat)->No.NoInterno.BitDiferenciador){ 
    /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
    pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)

    pat_aux = CriaNoExt(Chave, 1, 0);

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
      (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora, 0, 0);
      // Se o bit no BitDiferenciador for 1, insere na sub-arvore direita
    }
    else{
      (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora, 0, 0);
      // Se o bit no BitDiferenciador for 0, insere na sub-arvore esquerda
    }
    return (*pat);
  }
}*/


TipoArvore Insere_Pat(nome_ingrediente_pat Chave, TipoArvore *pat, int qtd_ingredientes, int id_doc){ 
    TipoArvore pat_aux; //Arvore aux para para percorrer sem efetuar modificacoes efetivas
    char letra_aux;
    char letra_diferenciadora;
    int tamanho = strlen(Chave);
    int i;
  
    if (*pat == NULL){
        // Se a árvore está vazia, cria um novo nó externo
        return CriaNoExt(Chave, qtd_ingredientes, id_doc); 
    } else { 
        pat_aux = *pat;

        // Percorre a árvore até encontrar um nó externo
        while (!Retorna_TipoNo(pat_aux)){ 
            if(tamanho < pat_aux->No.NoInterno.BitDiferenciador){
                letra_aux = Chave[tamanho]; 
            } else {
                letra_aux = RetornaBit(pat_aux->No.NoInterno.BitDiferenciador, Chave);
            }

            // Define se vai para a sub-árvore esquerda ou direita
            if (letra_aux >= pat_aux->No.NoInterno.LetraDiferenciadora){
                pat_aux = pat_aux->No.NoInterno.Dir;
            } else {
                pat_aux = pat_aux->No.NoInterno.Esq;
            }
        }

        // Encontra o primeiro bit diferente entre a chave nova e a existente
        i = 1;
        while ((i <= tamanho) && (RetornaBit(i, Chave) == RetornaBit(i, pat_aux->No.Chave))) {
            i++;
        }

        // Se a chave já existe, adiciona o ID ao nó existente
        if (strcmp(Chave, pat_aux->No.Chave) == 0){
            Adiciona_ID_Pat(pat_aux->head_ID, qtd_ingredientes, id_doc);
            return (*pat);
        } else {
            // Determina a letra diferenciadora e cria um novo nó se necessário
            if (RetornaBit(i, Chave) > RetornaBit(i, pat_aux->No.Chave)){
                letra_diferenciadora = Chave[i - 1];
            } else { 
                letra_diferenciadora = pat_aux->No.Chave[i - 1];
            }
            return InsereEntre(Chave, pat, i, letra_diferenciadora, qtd_ingredientes, id_doc);
        }
    }
}


// Função para imprimir as chaves em ordem
void Imprime_Pat(TipoArvore arvore, int* i) {
    if (arvore != NULL) {
        if (arvore->tipoNo == Externo) {
            printf("%02d: ", (*i) + 1); // Imprime o índice formatado com duas casas decimais
            printf("%s ", arvore->No.Chave);
            Imprime_Indice_Invertido_Pat(arvore->head_ID); // Descomente se necessário
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



TipoPatNo* Pesquisa_Pat(nome_ingrediente_pat Chave, TipoArvore Pat) {
    // Verifica se o nó atual é nulo
    if (Pat == NULL) {
        printf("Árvore vazia ou elemento não encontrado\n");
        return NULL;
    }

    // Verifica se o nó atual é um nó terminal e se a chave corresponde
    if (Retorna_TipoNo(Pat)) { 
        if (strcmp(Chave, Pat->No.Chave) == 0) {
            return Pat;
        } else {
            return NULL;
        }
    }

    // Se o nó não é terminal, decide para qual filho seguir
    if (RetornaBit(Pat->No.NoInterno.BitDiferenciador, Chave) < Pat->No.NoInterno.LetraDiferenciadora) {
        return Pesquisa_Pat(Chave, Pat->No.NoInterno.Esq); // Pesquisa no filho esquerdo
    } else {
        return Pesquisa_Pat(Chave, Pat->No.NoInterno.Dir); // Pesquisa no filho direito
    }
}
