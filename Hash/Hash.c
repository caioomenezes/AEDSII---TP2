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
  
unsigned int HashingUniversal(nome_ingrediente_hash Chave, Pesos MatrizPesos){ 
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

void Insere_Hash(nome_ingrediente_hash ingrediente, Pesos p, Hash TabelaIngredientes, int qtd_ingrediente, int id_doc){ 
  
  unsigned int i = HashingUniversal(ingrediente, p); //Calcula a posicao onde o ingrediente vai ser inserido
  Celula_Ingrediente *aux = Pesquisa_Ingrediente(&TabelaIngredientes[i], ingrediente); // Pesquisamos se o ingrediente já existe na lista de ingredientes
  if (aux == NULL){ // Se o ingrediente não exister na lista
    
    Adiciona_Ingrediente(&TabelaIngredientes[i], ingrediente, qtd_ingrediente, id_doc); //Adiciona o ingrediente de acordo com a posicao retornada pelo hashing universal
  }
  else {
    Adiciona_ID_Hash(aux->head_ID, qtd_ingrediente, id_doc); //Caso o ingrediente já esteja em alguma posicao da hash adicionamos apenas o indice invertido
  }
  
}

//Compara os ingredientes para ordenar através do qsort
int compararIngredientes(const void* a, const void* b) {
    // Converte os ponteiros para ponteiros de Celula_Ingrediente
    const Celula_Ingrediente* celulaA = *(const Celula_Ingrediente**)a;
    const Celula_Ingrediente* celulaB = *(const Celula_Ingrediente**)b;

    // Compara as chaves das duas células(nome dos ingredientes)
    return strcmp(celulaA->Chave, celulaB->Chave);
}

//Copia os ingredientes da Hash para um vetor
void CopiaHash(Hash TabelaIngredientes, int* contador, Celula_Ingrediente** vetor_hash){
  Celula_Ingrediente* aux;
  (*contador) = 0; //Conta quantos ingredientes temos
  for (int i = 0; i < M; i++){
    // Começa a partir do primeiro ingrediente na lista ignorando a cabeça
    aux = TabelaIngredientes[i].primeiro->prox;
    while(aux != NULL){
      vetor_hash[*contador] = aux;
      aux = aux->prox;
      (*contador)++;
    } 
  }
}


void Imprime_Hash_Ordenada(Hash TabelaIngredientes){
  int contador;
  Celula_Ingrediente* vetor_hash[46];
  // Copia os valores da tabela hash para o vetor
  CopiaHash(TabelaIngredientes, &contador, vetor_hash);
  
  // Ordena o vetor de ponteiros usando qsort
  qsort(vetor_hash, contador, sizeof(Celula_Ingrediente*), compararIngredientes);
  
  // Imprime o vetor ordenado
  Imprime_Ingrediente(contador, vetor_hash);

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