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


int Comparar_Relevancia_Hash(const void* a, const void* b) {
    const Vetor_Relevancia_Hash* valorA = (const Vetor_Relevancia_Hash*)a;
    const Vetor_Relevancia_Hash* valorB = (const Vetor_Relevancia_Hash*)b;

    if (valorA->resultado_relevancia == valorB->resultado_relevancia) {
        return 0;
    } else if (valorA->resultado_relevancia > valorB->resultado_relevancia) {
        return -1;
    } else {
        return 1;
    }
}

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

Vetor_Relevancia_Hash* Calcular_Relevancia_Termo_Hash(nome_ingrediente_hash* ingredientes, Hash TabelaIngrediente, int* qtd_termos_documentos, int total_de_arquivos, Pesos MatrizPeso,int qtd_pesquisa){
  float valor_peso;
  Vetor_Relevancia_Hash* resultado = (Vetor_Relevancia_Hash*)malloc(total_de_arquivos * sizeof(Vetor_Relevancia_Hash));
  for(int i = 0; i< total_de_arquivos; i++){
   // Cálculo de aux com divisão em ponto flutuante
    float aux = 1.0f / qtd_termos_documentos[i];
    //printf("Quantidade de termos em %d: %d\n", i, qtd_termos_documentos[i]);
        
    valor_peso = 0;
        
    for (int j = 0; j < qtd_pesquisa; j++) {
      float p = Calcular_Peso_Termo_Hash(ingredientes[j], TabelaIngrediente, total_de_arquivos, MatrizPeso, i);
      valor_peso += p;
      //printf("Peso ingrediente %s no documento %d: %f\n", ingredientes[j], i+1, p);
    }
        
    //printf("\nSoma peso documento %d: %f", i+1, valor_peso);
    resultado[i].indice = i; 
    resultado[i].resultado_relevancia = aux*valor_peso;
    //printf("\nResultado relevância do documento %d é %f\n", i+1, resultado[i].resultado_relevancia);
  }
  qsort(resultado, total_de_arquivos, sizeof(Vetor_Relevancia_Hash), Comparar_Relevancia_Hash);
  return resultado;
}

void Pesquisa_Termos_Hash(int* qtd_termos_documentos, int total_de_arquivos, int qtd_termos_busca, nome_ingrediente_hash* ingredientes_busca, char** vetor_pocoes, Hash TabelaIngredientes, Pesos MatrizPeso){
  
  Vetor_Relevancia_Hash* relevancias = Calcular_Relevancia_Termo_Hash(ingredientes_busca, TabelaIngredientes, qtd_termos_documentos, total_de_arquivos,MatrizPeso, qtd_termos_busca);
  int contador = 0;
  for(int i = 0; i < total_de_arquivos; i++){
    printf("%02d - %f\n", relevancias[i].indice +1, relevancias[i].resultado_relevancia);
  }
  for(int i = 0; i < total_de_arquivos; i++){
    if(relevancias[i].resultado_relevancia > 0){
      printf("Documento %d:\n%s\n\n", relevancias[i].indice +1, vetor_pocoes[relevancias[i].indice]);
    }
    else{      
      contador++;    
    }
  }
  if(contador == total_de_arquivos){
    printf("Sua pesquisa não encontrou nenhum documento correspondente");
  }
}

