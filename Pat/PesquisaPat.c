// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

#include "PesquisaPat.h"
#include <math.h>
#include <time.h>

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

//Compara os valores de relevancia dos ingredientes para ordenar atraves do qsort
int Comparar_Relevancia_Pat(const void* a, const void* b) {
    // Converte os ponteiros para ponteiros do tipo vetor_relevancia_pat
    const Vetor_Relevancia_Pat* valorA = (const Vetor_Relevancia_Pat*)a;
    const Vetor_Relevancia_Pat* valorB = (const Vetor_Relevancia_Pat*)b;

    // Compara os valores dos ingredientes, como queremos ordenar de forma decrescente
    if (valorA->resultado_relevancia == valorB->resultado_relevancia) {
        return 0; // Se forem iguais indica que as posicoes nao precisam ser trocadas
    } else if (valorA->resultado_relevancia > valorB->resultado_relevancia) {
        return -1; // Indica que o valor de A deve aparecer primeiro que o valor de B para manter a ordem de maior relevancia, primeiro elemento ordenado antes
      // Se valor de B for maior
    } else {
        return 1; // Indica que o valor de B deve aparecer primeiro que o valor de A para manter a ordem de maior relevancia, segundo elemento ordenado antes
    }
}

//Calcula o peso do termo a ser buscado 
float Calcular_Peso_Termo_Pat(nome_ingrediente_pat ingrediente, TipoArvore pat, int total_de_arquivos, int id_doc, int *compara_pat_pesquisa){
  
  int frequencia_ingrediente; // Quantidade de vezes queo ingrediente aparece
  TipoPatNo* aux = Pesquisa_Pat(ingrediente, pat, compara_pat_pesquisa); // Verifica se o ingrediente existe na arvore
  (*compara_pat_pesquisa) ++; //Comparacao do if
  if(aux == NULL){
    return 0;
  } else {
    // Se o ingrediente esta presente, pega o valor de id_doc para sua frequencia
    frequencia_ingrediente = Pesquisa_ID_Pat(aux->head_ID, id_doc); //frequencia_ingrediente e o fji
  }
  //Verifica o tamnho da lista de id para saber quantos documentos contem esse termo
  int qtd_documentos = Retorna_Tamanho_ID_Pat(aux->head_ID); //qtd_documentos eh o dj
  float resultado = frequencia_ingrediente*((log2(total_de_arquivos))/qtd_documentos); // vlaor do peso do ingrediente
  return resultado; //resultado eh o W                                                 
}

//Calcula a relevancia do termo ou termos de busca no documento
Vetor_Relevancia_Pat* Calcular_Relevancia_Termo_Pat(nome_ingrediente_pat* ingredientes, TipoArvore pat, int* qtd_termos_documentos, int total_de_arquivos,int qtd_pesquisa, int *compara_pat_pesquisa){

  float valor_peso;
  //Armazena os valores de relevancia de cada documento em um vetor
  Vetor_Relevancia_Pat* resultado = (Vetor_Relevancia_Pat*)malloc(total_de_arquivos * sizeof(Vetor_Relevancia_Pat));
  if (resultado == NULL) {
    // Tratar erro de alocação
    printf("Erro ao alocar memória\n");
    return NULL;
  }
  for(int i = 0; i< total_de_arquivos; i++){
    // Calculo de aux com divisão em ponto flutuante
    float aux = 1.0f / qtd_termos_documentos[i]; // 1/ni
    
        
    valor_peso = 0;
        
    for (int j = 0; j < qtd_pesquisa; j++) {
      float p = Calcular_Peso_Termo_Pat(ingredientes[j], pat, total_de_arquivos, i, compara_pat_pesquisa); // Calcula o peso de cada ingrediente
      valor_peso += p; // Vai somando o valor dos pesos encontrado  - soma de wj
    }
        
   
    resultado[i].indice = i; // Armazena o valor do indice  do documento no vetor de relevancias
    resultado[i].resultado_relevancia = aux*valor_peso; // Resultado a relevancia de cada documento
    
  }
  // Ordena o vetor de relevancias
  qsort(resultado, total_de_arquivos, sizeof(Vetor_Relevancia_Pat), Comparar_Relevancia_Pat); //ordenamos o vetor por ordem de relevancia (descrescente)

  return resultado;

}


//Pesquisa o termo de busca e retorna o documento ou documentos de acordo com a relevancia
void Pesquisa_Termos_Pat(int* qtd_termos_documentos, int total_de_arquivos, int qtd_termos_busca, nome_ingrediente_pat* ingredientes_busca, char** vetor_pocoes, TipoArvore pat, double *tempo_Pesquisa_Pat, int *compara_pat_pesquisa){

  clock_t tempo_inicio_Pat = clock();
  //Armazena os calculos de relevancia de cada documento em um vetor
  Vetor_Relevancia_Pat* relevancias = Calcular_Relevancia_Termo_Pat(ingredientes_busca, pat, qtd_termos_documentos, total_de_arquivos, qtd_termos_busca,compara_pat_pesquisa); 
  //Calculamos a relevancia do/s ingrediente/s procurado/s 
  int contador = 0;

  for(int i = 0; i < total_de_arquivos; i++){ 
    (*compara_pat_pesquisa) ++; //Comparacao do if
    if(relevancias[i].resultado_relevancia > 0){ //se a relevancia neste documento i for maior que 0, exibiremos este arquivo
      // Caso contrario ele nao eh considerado
      printf("\nDocumento %d:\n%s\n\n", relevancias[i].indice +1, vetor_pocoes[relevancias[i].indice]);
    }
    else{      
      contador++; // Se o valor da relevancia for 0 o contador eh incrementado
    }
  }

  clock_t tempo_final_Pat = clock(); //Marca o tempo final 
  
  *tempo_Pesquisa_Pat = (double)(tempo_final_Pat-tempo_inicio_Pat) / CLOCKS_PER_SEC; //Calcula o tempo total em segundos
  (*compara_pat_pesquisa) ++; //Comparacao do if
  if(contador == total_de_arquivos){ // Se o contador for igual ao valor de total de arquivos significa que o termo nao foi encontrado em nenhum documento
    printf("Sua pesquisa não encontrou nenhum documento correspondente");
  }
}


