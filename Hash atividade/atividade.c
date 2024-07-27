//Letícia Cristina - 5781

#include <sys/time.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#define VAZIO  "!!!!!!!!!!"
#define RETIRADO  "**********" 
#define M  7   // Lembrando que os indices vao de 0 até M-1, por isso a pesquisa retorna M quando nao encontra o valor
#define N  11   // Tamanho da chave 


//usigned é pq sao numeros sem sinais
typedef char nome_ingrediente[N]; //Nome do tribulante
typedef unsigned Pesos[N]; //Vetor de pesos que vai ser usado no calculo da posicao que uma chave vai ocupar na tabela


typedef struct Tribulante {
  nome_ingrediente Chave; //Nome do tribulante
  char Codigo[10];
} Tribulante;

typedef Tribulante vetorTribulantes[M]; 


//Gerar os pesos usando numeros aleatorios
void GeraPesos(Pesos VetorPesos){  
  struct timeval semente;
  gettimeofday(&semente,NULL); 
  srand((int)(semente.tv_sec + 1000000 * semente.tv_usec));
  
  for (int i = 0; i < N; i++){
    VetorPesos[i] = 1 + (int) (10000.0 * rand()/(RAND_MAX + 1.0));
  }

}

//Funcao que realiza a conversao da chave e calcula h(k) (indice da chave k na tabela)
unsigned int HashingUniversal(nome_ingrediente Chave, Pesos VetorPesos){ 
  unsigned int soma = 0; 

  int tamanho = strlen(Chave); //Tamanho da minha string (chave e um nome)

  for (int i = 0; i < tamanho; i++){
    soma += (unsigned int)Chave[i] * VetorPesos[i]; //Faz o calculo, multiplica o valor de cada letra (segundo ASCII) pelo peso correspondente
  }
  return (soma % M); //o mod vai me dá a posicao
}

//Inicializa cada tribulante como vazio, ou seja, inicializa minha tabela
void Inicializa(vetorTribulantes T){ 
  for (int i = 0; i < M; i++){
    memcpy(T[i].Chave, VAZIO, N);
  }
} 


unsigned int Pesquisa(nome_ingrediente chave, Pesos VetorPesos, vetorTribulantes T){ 
  unsigned int j = 0, qtd = 0; 
  //Estamos usando tratamento de colisoes linear, então incial é o h(x), ou seja, a posicao que teoricamente a chave estaria, isso se nao occorrer colisoes
  //(h(x)+j) % M - formula do tratamento linear 
  unsigned int  Inicial = HashingUniversal(chave, VetorPesos); 

  //Esse while verifica se ocorreu colisoes, se ocorrer existem duas possibilidade: a posicao ta vazia ou com outro valor diferente da chave
  //existe ainda a possibilidade da chave nao esta na tabela, por isso o j < M  
  while(strcmp(T[(Inicial + j) % M].Chave,VAZIO) != 0 && 
        strcmp(T[(Inicial + j) % M].Chave, chave) != 0 && j < M){
    j++;
    qtd++;
  }
  printf("Quantidade de seekings na pesquisa por %s: %d\n", chave, qtd);
  if(strcmp(T[(Inicial + j) % M].Chave, chave) == 0){
    printf("Chave %s encontrada! Código: %s\n",T[(Inicial + j) % M].Chave, T[(Inicial + j) % M].Codigo);
    return ((Inicial + j) % M);
  }
  else{
    //printf("Tribulante %s não encontrado!",  chave); //eu preferi não colocar esse print aqui, para ficar mais bonito na hora de inserir os elementos
    return M;  // Pesquisa sem sucesso, por isso a tabela tem uma posicao a mais 
  }
} 

//O imprime pesquisa é pra usar fora do insere, quando a pessoa quer printar quando encontrou pu nao
void ImprimePesquisa(nome_ingrediente chave, Pesos VetorPesos, vetorTribulantes T){ 
  if(Pesquisa(chave, VetorPesos, T) == M){
    printf("Chave %s não está na tabela!\n", chave);
  }
}

void Insere(Tribulante x, Pesos VetorPesos,  vetorTribulantes T){ 
  unsigned int j = 0, qtd = 0; 
  unsigned int Inicial; 

  if(Pesquisa(x.Chave, VetorPesos, T) < M){ //Lembrando que retorna M quando o elemento nao foi encontrado 
    printf("Elemento já está presente!\n\n"); 
    return; 
  }

  //assim como na pesquisa, é utilizado tratamento linear 
  //(h(x)+j) % M - formula do tratamento linear (inicial é h(x))
  Inicial = HashingUniversal(x.Chave, VetorPesos);
  while(strcmp(T[(Inicial + j) % M].Chave,VAZIO) != 0 &&
        strcmp(T[(Inicial + j) % M].Chave, RETIRADO) != 0 && j < M){
    j++;
    qtd++;
  }
  printf("Quantidade de seekings na inserção da chave %s: %d\n", x.Chave, qtd);
  printf("\n");
  if(j < M) { 
    strcpy(T[(Inicial + j) % M].Chave, x.Chave);
    strcpy(T[(Inicial + j) % M].Codigo, x.Codigo);
  }
  else printf("Tabela cheia\n");
} 

void Imprime(vetorTribulantes tabela){
  printf("Tabela: \n");
  for (int i = 0; i < M; i++){
    printf("%d  ", i);
    printf("%s\n", tabela[i].Chave);
  }
  printf("\n");
}


int main(int argc, char *argv[]) { 
  vetorTribulantes Tabela; //Minha tabela é um vetor de tribulantes
  Pesos VetorPesos;
  Tribulante Elemento;

  FILE *arq;
  arq = fopen("tribulacao.txt", "r");
  if (arq == NULL) {
      printf("Erro ao abrir o arquivo.\n");
      return 1;
  }
  Inicializa(Tabela);
  GeraPesos(VetorPesos);

  int qtdElementos = 0, i = 0;
  while(qtdElementos <= M){
      if (fscanf(arq, "%s %s", Elemento.Chave, Elemento.Codigo) != 2) {
          break; // isso é pra quando eu tiver um arquivo com menos de 7 elementos
      }
      Insere(Elemento, VetorPesos, Tabela);
      i++; 
      qtdElementos++; //isso pra quando eu tiver mais de 7 elementos, mas tem elementos repetidos e eu quero preencher o maximo da minha tabela
  }

  Imprime(Tabela);
  nome_ingrediente nome1 = "leticia";
  ImprimePesquisa(nome1, VetorPesos, Tabela);
  nome_ingrediente nome2 = "Ana";
  ImprimePesquisa(nome2, VetorPesos, Tabela);

  fclose(arq);
  return 0;
}
