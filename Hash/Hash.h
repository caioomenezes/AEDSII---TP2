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
unsigned int HashingUniversal(nome_ingrediente_hash Chave, Pesos MatrizPesos);
void Inicializa_Hash(Hash TabelaIngredientes);
void Insere_Hash(nome_ingrediente_hash ingrediente, Pesos p, Hash TabelaIngredientes, int qtd_ingrediente, int id_Doc);
void Imprime_Hash(Hash TabelaIngredientes);
void Imprime_Hash_Ordenada(Hash TabelaIngredientes);
int compararIngredientes(const void* a, const void* b);
void CopiaHash(Hash TabelaIngredientes, int* contador, Celula_Ingrediente** vetor_hash);

/*
N = total de arquivos -> total_de_arquivos
Ni = total de ingredientes em cada arquivo -> vem do *qtd_termos_documentos
Calcular peso (wi) do ingrediente de busca:
Descobrir a posicao na tabela hash e assim pesquisar o ingrediente
Ao descobrir o ingrediente: 
fij = quantidade de vezes que o ingrediente aparece -> pesquisar dentro da lista de indice invertidos: fazer essa funcao
dj = quantidade de ceĺulas da lista de indice invertido -> utilizar o retorna_tamanho_id_hash
Após esses passos -> calcular ri = relevancia
Imprimir os textos de acordo com a relevancia -> imprimir todos que possuem o termo buscado
*/