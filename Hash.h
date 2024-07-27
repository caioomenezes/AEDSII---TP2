//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)
#include "ListaIngredientes.h"

//verificar includes
#include <sys/time.h>
#define VAZIO  "!!!!!!!!!!"
#define RETIRADO  "**********" 
#define M 17 //Tamanho da tabela Hash   
#define TAMALFABETO 256


typedef unsigned Pesos[N][TAMALFABETO];
typedef Lista_Ingredientes Hash[M];

void GeraPesos(Pesos MatrizPesos);
unsigned int HashingUniversal(nome_ingrediente Chave, Pesos MatrizPesos);
void Inicializa_Hash(Hash TabelaIngredientes);
void Insere(nome_ingrediente ingrediente, Pesos p, Hash TabelaIngredientes, int qtd_ingrediente, int id_Doc);
void Imprime_Hash(Hash TabelaIngredientes);



