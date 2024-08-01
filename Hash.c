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
      MatrizPesos[i][j] = 1 + (int)(10000.0 * rand() / (RAND_MAX + 1.0)); // Cria uma matriz de pesos 
    }
  }
}
  
unsigned int HashingUniversal(nome_ingrediente Chave, Pesos MatrizPesos){ 
  unsigned int soma = 0; 

  int tamanho = strlen(Chave); //Tamanho da minha string (chave e um nome)

  for (int i = 0; i < tamanho; i++){
    soma += MatrizPesos[i][(unsigned int)Chave[i]]; 
  }
  return (soma % M); //o mod vai me dar a posicao
}

// Inicializa a hash e inicializa a lista que armazena os ingredientes
void Inicializa_Hash(Hash TabelaIngredientes){ 
  for(int i = 0; i < M; i++){
    Inicializa_Lista_Ingredientes(&TabelaIngredientes[i]);
  } 
}

void Insere(nome_ingrediente ingrediente, Pesos p, Hash TabelaIngredientes, int qtd_ingrediente, int id_doc){ 
  
  unsigned int i = HashingUniversal(ingrediente, p); //Calcula a posicao onde o ingrediente vai ser inserido
  Celula_Ingrediente *aux = Pesquisa_Ingrediente(&TabelaIngredientes[i], ingrediente); // Pesquisamos se o ingrediente já existe na lista de ingredientes
  if (aux == NULL){ // Se o ingrediente não exister na lista
    Adiciona_Ingrediente(&TabelaIngredientes[i], ingrediente, qtd_ingrediente, id_doc); //Adciona o ingrediente de acordo com a posicao retornada pelo hashing universal
  }
  else {
    Adiciona_ID(aux->head_ID, qtd_ingrediente, id_doc); //Caso o ingrediente já esteja em alguma posicao da hash adcionamos apenas o indice invertido
  }
  
}

void Imprime_Hash(Hash TabelaIngredientes){
   
  for (int i = 0; i < M; i++){ 
    printf("%02d: ", i+1); // printa o idice formatado, com duas casas decimais
    if (!Verifica_Vazio_Ingredientes(&TabelaIngredientes[i])){ // Se a posicao não estiver vazia imprime a lista de ingredientes em cada posicao da hash
      Imprime_Lista_Ingredientes(&TabelaIngredientes[i]);
    }
    putchar('\n');
  }
} 