// Amanda (5366), Caio (5784), Leticia (5781), Melissa (5384)
#include "Hash.h"


void GeraPesos(Pesos MatrizPesos){ 
  //Gera valores randomicos entre 1 e 10.000 
  struct timeval semente;
  // Utilizar o tempo como semente para a funcao srand() 
  gettimeofday(&semente, NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  for (int i = 0; i < N; i++){
    for (int j = 0; j < TAMALFABETO; j++){
      MatrizPesos[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0));
    }
  }
}

unsigned int HashingUniversal(nome_ingrediente Chave, Pesos MatrizPesos){ 
  unsigned int soma = 0; 

  int tamanho = strlen(Chave); //Tamanho da minha string (chave e um nome)

  for (int i = 0; i < tamanho; i++){
    soma += MatrizPesos[i][(unsigned int)Chave[i]]; 
  }
  return (soma % M); //o mod vai me dá a posicao
}

void Inicializa_Hash(Hash TabelaIngredientes){ 
  for(int i = 0; i < M; i++){
    Inicializa_Lista_Ingredientes(&TabelaIngredientes[i]);
  } 
}

void Insere(nome_ingrediente ingrediente, Pesos p, Hash TabelaIngredientes, int qtd_ingrediente, int id_doc){ 
  
  unsigned int i = HashingUniversal(ingrediente, p);
  Celula_Ingrediente *aux = Pesquisa_Ingrediente(&TabelaIngredientes[i], ingrediente);
  if (aux == NULL){
    Adiciona_Ingrediente(&TabelaIngredientes[i], ingrediente, qtd_ingrediente, id_doc);
  }
  else {
    Adiciona_ID(aux->head_ID, qtd_ingrediente, id_doc);
  }
  printf("Ingrediente: %s na posição %d \n", TabelaIngredientes[i].ultimo->Chave, i);
  putchar('\n');
}

void Imprime_Hash(Hash TabelaIngredientes) {
    for(int i = 0; i < M; i ++){
      printf("%d: \n", i);
      printf("Primeiro: %s\n", TabelaIngredientes[i].primeiro->prox->Chave);
      printf("Ultimo: %s\n", TabelaIngredientes[i].ultimo->Chave);
    }

    /*printf("%d: \n", 14);
    printf("Primeiro: %s\n", TabelaIngredientes[14].primeiro->prox->Chave);
    printf("Ultimo: %s\n", TabelaIngredientes[14].ultimo->Chave);
    printf("%d: ", 15);
    printf("Primeiro: %s\n", TabelaIngredientes[15].primeiro->prox->Chave);
    printf("Ultimo: %s\n", TabelaIngredientes[15].ultimo->Chave);
    */
    /*if (!Verifica_Vazio_Ingredientes(&TabelaIngredientes[i])) {
        Imprime_Lista_Ingredientes(&TabelaIngredientes[i]);
    }*/
    putchar('\n');
}