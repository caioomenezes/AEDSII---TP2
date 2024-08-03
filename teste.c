#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* nome_ingrediente;
typedef int TipoBit;

typedef struct TipoPatNo* TipoArvore;

typedef enum { Externo, Interno } TipoNo;

typedef struct TipoPatNo {
    TipoNo tipoNo;
    union {
        struct {
            TipoArvore Esq;
            TipoArvore Dir;
            int BitDiferenciador;
            char LetraDiferenciadora;
        } NoInterno;
        nome_ingrediente Chave;
    } No;
} TipoPatNo;

// Funções auxiliares
TipoBit RetornaBit(TipoBit i, nome_ingrediente Chave) {
    return Chave[i-1];
} 

short Retorna_TipoNo(TipoArvore no) {
    return (no->tipoNo == Externo);
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

TipoArvore CriaNoExt(nome_ingrediente Chave) { 
    TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo));
    pat->tipoNo = Externo; 
    pat->No.Chave = strdup(Chave); // Duplicando a string
    return pat;
}  

TipoArvore InsereEntre(nome_ingrediente Chave, TipoArvore *pat, int i, char letra_diferenciadora) {
    TipoArvore pat_aux;
    
    if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador) { 
        pat_aux = CriaNoExt(Chave);

        if (RetornaBit(i, Chave) > RetornaBit(i, (*pat)->No.Chave)) {
            return CriaNoInt(i, letra_diferenciadora, pat, &pat_aux);
        } else {
            return CriaNoInt(i, letra_diferenciadora, &pat_aux, pat);
        }
    } else {
        if (RetornaBit(i, Chave) > RetornaBit(i, (*pat)->No.Chave)) {
            (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora);
        } else {
            (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora);
        }
        return (*pat);
    }
}

TipoArvore Insere(nome_ingrediente Chave, TipoArvore *pat) { 
    TipoArvore pat_aux;
    char letra_aux;
    char letra_diferenciadora;
    int tamanho = strlen(Chave);
    int i;

    if (*pat == NULL) {
        return CriaNoExt(Chave);
    } else { 
        pat_aux = *pat;

        while (!Retorna_TipoNo(pat_aux)) {
            if (tamanho < pat_aux->No.NoInterno.BitDiferenciador) {
                letra_aux = Chave[tamanho]; 
            } else {
                letra_aux = RetornaBit(pat_aux->No.NoInterno.BitDiferenciador, Chave);
            }

            if (letra_aux > pat_aux->No.NoInterno.LetraDiferenciadora) {
                pat_aux = pat_aux->No.NoInterno.Dir;
            } else {
                pat_aux = pat_aux->No.NoInterno.Esq;
            }
        }

        i = 1;
        while ((i <= tamanho) && (RetornaBit(i, Chave) == RetornaBit(i, pat_aux->No.Chave))) {
            i++;
        }
        if (i > tamanho) {
            printf("Erro: chave ja esta na arvore\n");
            return (*pat);
        } else {
            if (RetornaBit(i, Chave) > RetornaBit(i, pat_aux->No.Chave)) {
                letra_diferenciadora = Chave[i-1];
            } else { 
                letra_diferenciadora = pat_aux->No.Chave[i-1];
            }
            return InsereEntre(Chave, pat, i, letra_diferenciadora);
        }
    }
}

void ImprimePatricia(TipoArvore arvore) {
    if (arvore != NULL) {
        if (arvore->tipoNo == Interno) {
            ImprimePatricia(arvore->No.NoInterno.Esq);
        }

        if (arvore->tipoNo == Externo) {
            printf("%s ", arvore->No.Chave);
        }

        if (arvore->tipoNo == Interno) {
            ImprimePatricia(arvore->No.NoInterno.Dir);
        }
    }
}

int main() {
    TipoArvore arvore = NULL;

    // Array de nomes a serem inseridos
    nome_ingrediente nomes[] = {
        "caza", "caia", "cada", "caio", "cafe", "carro"
    };
    int num_nomes = sizeof(nomes) / sizeof(nomes[0]);

    // Inserção de nomes
    for (int i = 0; i < num_nomes; i++) {
        arvore = Insere(nomes[i], &arvore);
    }
    ImprimePatricia(arvore);
    // Imprime a árvore
    printf("\nEstrutura da árvore Patricia:\n");

    printf("\nDir:");
    ImprimePatricia(arvore->No.NoInterno.Dir);
    printf("\nEsq:");
    ImprimePatricia(arvore->No.NoInterno.Esq);

    return 0;
}

TipoArvore InsereEntre(nome_ingrediente Chave, TipoArvore *pat, int i, char letra_diferenciadora) {
  TipoArvore pat_aux;
  int bitAtualChave, bitComparacao;
  /*Analisa se o No é externo OU se teremos um novo prefixo (se i for menor significa que teremos este novo prefixo 
  pq se difencia antes do profeixo antigo, ou seja, temos um prefixo menor do que o anterior)*/
  if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador) {
    pat_aux = CriaNoExt(Chave);

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
      (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora);
       // Se o bit no BitDiferenciador for maior ou igual, insere na sub-arvore direita
    }
    else {
      (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora);
      // Se o bit no BitDiferenciador for menor insere na sub-arvore esquerda
    }
    return *pat;
  }
}


/*int main() {
    TipoArvore arvore = NULL; // Inicializa a árvore como vazia

    // Inserção de chaves Horn 
    /*arvore = Insere("caia", &arvore);
    arvore = Insere("caza", &arvore);
    arvore = Insere("cada", &arvore);
    arvore = Insere("caio", &arvore);
    arvore = Insere("cafe", &arvore);
    arvore = Insere("carro", &arvore);*/

    // Inserção de chaves
    //arvore = Insere("orelha", &arvore);
    /*arvore = Insere("orelhudo", &arvore);
    arvore = Insere("orca", &arvore);
    arvore = Insere("oraculo", &arvore);
    arvore = Insere("oreo", &arvore);
    arvore = Insere("oscar", &arvore);

    ImprimePatricia(arvore);
    // Imprime a árvore
    printf("\nEstrutura da árvore Patricia:\n");
    printf("\nDir:");
    ImprimePatricia(arvore->No.NoInterno.Dir);
    printf("\nEsq:");
    ImprimePatricia(arvore->No.NoInterno.Esq);

    return 0;
}

int main(){

  TipoArvore arvore = NULL;

    // Array de nomes a serem inseridos
    nome_ingrediente nomes[] = {
        //"ana", "aranha", "pedro", "amar", "amor", "perder"
        "Bezoar", "Standard Ingredient Measurements", "Pinch of Unicorn Horn", "Mistletoe Berries"
    };
    int num_nomes = sizeof(nomes) / sizeof(nomes[0]);

    // Inserção de nomes
    for (int i = 0; i < num_nomes; i++) {
        arvore = Insere(nomes[i], &arvore);
    }
    printf("\n");
    ImprimePatricia(arvore);
    // Imprime a arvore
    printf("\n\nEstrutura da árvore Patricia:\n");

    printf("\nDir:");
    ImprimePatricia(arvore->No.NoInterno.Dir);
    printf("\nEsq:");
    ImprimePatricia(arvore->No.NoInterno.Esq);


  return 0;

}/*


int main(int argc, char *argv[])
{ TipoArvore a = NULL;
  TipoChave c;
  int  i, j, k, n;
  int  min = 32, max = 126;
  TipoChave vetor[95];
  /* Gera uma permutacao aleatoria de chaves dos caracteres ASCII 32 a  126 */
  struct timeval semente;
  gettimeofday(&semente,NULL);
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));  
  for (i = min; i <= max; i++)
  vetor[i - 32] = i;
  for (i = min; i <= max; i++) 
    { k = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0)); 
      j = min + (int) ((float)(max - min) * rand()/(RAND_MAX + 1.0));
      n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n; 
    }
  /* Insere cada chave na arvore */
  for (i = min; i <= max; i++) 
    { c = vetor[i - 32]; printf("Inserindo chave: %c\n", c);
      a = Insere(c, &a);
    }
  /* Gera outra permutacao aleatoria de chaves */
  for (i = min; i <= max; i++) 
    { k = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
      j = min + (int) ((float)(max-min) * rand()/(RAND_MAX + 1.0));
      n = vetor[k - 32]; vetor[k - 32] = vetor[j - 32]; vetor[j - 32] = n;
    }
  /* Pesquisa cada chave na arvore */
  for (i = min; i <= max; i++) 
    { c = vetor[i - 32]; printf("Pesquisando chave: %c\n", c);
      Pesquisa(c, a);
    }
  return 0;
} 

TipoArvoreApontador InsereEntrePatricia(char *palavra, TipoArvoreApontador *arvore, int indice, char letraQueDifere, int idDoc)
{
    TipoArvoreApontador arvoreAux;
    if (VerificaSeNoExterno(*arvore))
    {

        arvoreAux = InicializaNoExterno(palavra,idDoc);
        // se a letra da palavra que veio for maior que a letra da palavra que tá no nó
        if (Bit(indice, palavra) >= Bit(indice, (*arvore)->NO.Chave))
        { // cria um nó interno com a arvore a esquerda e uma arvore auxiliar a direita

            return (InicializaNoInterno(arvore, &arvoreAux, letraQueDifere, indice));
        }
        else
        { // cria um nó interno com uma arvore auxiliar a esquerda e a arvore auxiliar a direita

            return (InicializaNoInterno(&arvoreAux, arvore, letraQueDifere, indice));
        }
    }
    else if (indice < (*arvore)->NO.NInterno.Index)
    {
        // se o índice da letra que difere for menor que o indice do nó interno, cria um externo
        arvoreAux = InicializaNoExterno(palavra, idDoc);
        // se a letra for maior ou igual cria o nó interno com a arvore a esquerda e arvore auxiliar a direita
        if (Bit(indice, palavra) >= letraQueDifere)
        {

            return (InicializaNoInterno(arvore, &arvoreAux, letraQueDifere, indice));
        }
        else
        { // se for menor, cria um nó interno com uma arvore auxiliar a esquerda e a arvore a direita

            return (InicializaNoInterno(&arvoreAux, arvore, letraQueDifere, indice));
        }
    }
    else
    { // se o indice for maior ou igual que o indice do nó interno

        if (Bit((*arvore)->NO.NInterno.Index, palavra) >= (*arvore)->NO.NInterno.LetraComparada)
        {
            // se a letra da palavra for maior ou igual do que a letra comparada, chamar recursivo o insereEntrePatricia para nó direito
            (*arvore)->NO.NInterno.Dir = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Dir, indice, letraQueDifere,idDoc);
        }
        else
        {
            // se a letra da palavra for menor do que a letra comparada, chamar recursivo o insereEntrePatricia para o nó esquerdo
            (*arvore)->NO.NInterno.Esq = InsereEntrePatricia(palavra, &(*arvore)->NO.NInterno.Esq, indice, letraQueDifere, idDoc);
        }
    }

    return (*arvore);
}