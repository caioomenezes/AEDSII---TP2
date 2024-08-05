// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

#include "PesquisaPat.h"
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

int Comparar_Relevancia_Pat(const void* a, const void* b) {
    const Vetor_Relevancia_Pat* valorA = (const Vetor_Relevancia_Pat*)a;
    const Vetor_Relevancia_Pat* valorB = (const Vetor_Relevancia_Pat*)b;

    if (valorA->resultado_relevancia == valorB->resultado_relevancia) {
        return 0;
    } else if (valorA->resultado_relevancia > valorB->resultado_relevancia) {
        return -1;
    } else {
        return 1;
    }
}

float Calcular_Peso_Termo_Pat(nome_ingrediente_pat ingrediente, TipoArvore pat, int total_de_arquivos, int id_doc){
  int frequencia_ingrediente;
  TipoPatNo* aux = Pesquisa_Pat(ingrediente, pat);
  if(aux == NULL){
    return 0;
  } else {
    frequencia_ingrediente = Pesquisa_ID_Pat(aux->head_ID, id_doc); //frequencia_ingrediente e o fji
  }
  int qtd_documentos = Retorna_Tamanho_ID_Pat(aux->head_ID); //qtd_documentos é o dj
  float resultado = frequencia_ingrediente*((log10(total_de_arquivos))/qtd_documentos);
  return resultado; //resultado é o W                                                 
}

Vetor_Relevancia_Pat* Calcular_Relevancia_Termo_Pat(nome_ingrediente_pat* ingredientes, TipoArvore pat, int* qtd_termos_documentos, int total_de_arquivos,int qtd_pesquisa){
  float valor_peso;
  Vetor_Relevancia_Pat* resultado = (Vetor_Relevancia_Pat*)malloc(total_de_arquivos * sizeof(Vetor_Relevancia_Pat));
    if (resultado == NULL) {
        // Tratar erro de alocação
        printf("Erro ao alocar memória\n");
        return NULL;
    }
  for(int i = 0; i< total_de_arquivos; i++){
   // Cálculo de aux com divisão em ponto flutuante
    float aux = 1.0f / qtd_termos_documentos[i];
    //printf("Quantidade de termos em %d: %d\n", i+1, qtd_termos_documentos[i]);
        
    valor_peso = 0;
        
    for (int j = 0; j < qtd_pesquisa; j++) {
      float p = Calcular_Peso_Termo_Pat(ingredientes[j], pat, total_de_arquivos, i);
      valor_peso += p;
      //printf("Peso ingrediente %s no documento %d: %f\n", ingredientes[j], i+1, p);
    }
        
    //printf("\nSoma peso documento %d: %f", i+1, valor_peso);
    resultado[i].indice = i; 
    resultado[i].resultado_relevancia = aux*valor_peso;
    //printf("\nResultado relevância do documento %d é %f\n", i+1, resultado[i].resultado_relevancia);
  }
  // Ordena o vetor de relevâncias
  qsort(resultado, total_de_arquivos, sizeof(Vetor_Relevancia_Pat), Comparar_Relevancia_Pat);

  return resultado;

}


void Pesquisa_Termos_Pat(int* qtd_termos_documentos, int total_de_arquivos, int qtd_termos_busca, nome_ingrediente_pat* ingredientes_busca, char** vetor_pocoes, TipoArvore pat){
  
  Vetor_Relevancia_Pat* relevancias = Calcular_Relevancia_Termo_Pat(ingredientes_busca, pat, qtd_termos_documentos, total_de_arquivos, qtd_termos_busca);
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


