// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

#include "PesquisaHash.h"
#include <math.h>

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


float Calcular_Peso_Termo_Hash(nome_ingrediente_hash ingrediente, Hash TabelaIngrediente, int total_de_arquivos, Pesos MatrizPeso, int id_doc){
  int posicao = HashingUniversal(ingrediente, MatrizPeso);
  int frequencia_ingrediente;
  Celula_Ingrediente *aux = Pesquisa_Ingrediente(&TabelaIngrediente[posicao], ingrediente);
  if(aux == NULL){
    return 0;
  } else {
    frequencia_ingrediente = Pesquisa_ID_Hash(aux->head_ID, id_doc); //frequencia_ingrediente e o fji
  }
  int qtd_documentos = Retorna_Tamanho_ID_Hash(aux->head_ID); //qtd_documentos é o dj
  float resultado = frequencia_ingrediente*((log10(total_de_arquivos))/qtd_documentos);
  return resultado; //resultado é o W                                                 
}

void Calcular_Relevancia_Termo_Hash(nome_ingrediente_hash* ingredientes, Hash TabelaIngrediente, int* qtd_termos_documentos, int total_de_arquivos, Pesos MatrizPeso,int qtd_pesquisa){
  float valor_peso;
  float resultado[total_de_arquivos];
  for(int i = 0; i< total_de_arquivos; i++){
   // Cálculo de aux com divisão em ponto flutuante
    float aux = 1.0f / qtd_termos_documentos[i];
    printf("Quantidade de termos em %d: %d\n", i, qtd_termos_documentos[i]);
        
    valor_peso = 0;
        
    for (int j = 0; j < qtd_pesquisa; j++) {
      float p = Calcular_Peso_Termo_Hash(ingredientes[j], TabelaIngrediente, total_de_arquivos, MatrizPeso, i);
      valor_peso += p;
      printf("Peso ingrediente %s no documento %d: %f\n", ingredientes[j], i+1, p);
    }
        
    printf("\nSoma peso documento %d: %f", i+1, valor_peso);
    resultado[i] = aux * valor_peso;
    printf("\nResultado relevância do documento %d é %f\n", i+1, resultado[i]);
  }
}

