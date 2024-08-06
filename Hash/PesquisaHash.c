// Amanda (5366), Caio (5784), Letícia (5781), Melissa (5384)

#include "PesquisaHash.h"
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

// Compara o valor das relevancias dos ingredientes para ordenar pelo qsort
int Comparar_Relevancia_Hash(const void* a, const void* b) {
    // Converte os ponteiros recebidos para ponteiros do tipo vetor_relevancia_hash
    const Vetor_Relevancia_Hash* valorA = (const Vetor_Relevancia_Hash*)a;
    const Vetor_Relevancia_Hash* valorB = (const Vetor_Relevancia_Hash*)b;
    //Faz a comparacao dos valores de relevancia
    // Como queremos ordenar de acordo com o maior valor de relevancia 
    //Se forem iguais
    if (valorA->resultado_relevancia == valorB->resultado_relevancia) {
        return 0; // Indica que a posicao relativa dos dois elementos nao precisa ser trocada
    // Se a primeira palavra for maior
    } else if (valorA->resultado_relevancia > valorB->resultado_relevancia) {
        return -1; // Indica que o valor A deve aparecer primeiro que o valor B devido a ordem decrescente
    //Se a segunda palavra for maior
    } else {
        return 1; // Indica que o valor B deve aparecer primeiro que o valor A devido a ordem decrescente
    }
}
//Calcula o peso que ingrediente vai ter para a pesquisa
float Calcular_Peso_Termo_Hash(nome_ingrediente_hash ingrediente, Hash TabelaIngrediente, int total_de_arquivos, Pesos MatrizPeso, int id_doc, int* compara_hash_pesquisa){
  int posicao = HashingUniversal(ingrediente, MatrizPeso); // Encontra em qual posicao da lista de ingredientes que o termo a ser buscado esta
  int frequencia_ingrediente; // Quantidade de vezes que o termo aparece no ingrediente
  Celula_Ingrediente *aux = Pesquisa_Hash(&TabelaIngrediente[posicao], ingrediente, compara_hash_pesquisa); // Verifica se o termo buscado esta presente na lista
  (*compara_hash_pesquisa)++; //Comparacao do if
  if(aux == NULL){
    return 0; 
  } else {
    // Se estiver presente pega o valor de id_doc para saber sua frequencia
    frequencia_ingrediente = Pesquisa_ID_Hash(aux->head_ID, id_doc); //frequencia_ingrediente e o fji
  }
  //Verifica o tamnho da lista de id para saber quantos documentos contem esse termo
  int qtd_documentos = Retorna_Tamanho_ID_Hash(aux->head_ID); //qtd_documentos é o dj
  float resultado = frequencia_ingrediente*((log2(total_de_arquivos))/qtd_documentos); // operacao para calcular o peso 
  return resultado; //resultado eh o W                                                 
}

//Calcula a relevancia do termo ou termos de busca no documento
Vetor_Relevancia_Hash* Calcular_Relevancia_Termo_Hash(nome_ingrediente_hash* ingredientes, Hash TabelaIngrediente, int* qtd_termos_documentos, int total_de_arquivos, Pesos MatrizPeso,int qtd_pesquisa, int* compara_hash_pesquisa){
  float valor_peso;
  //Armazena os valores de relevancia de cada documento em um vetor
  Vetor_Relevancia_Hash* resultado = (Vetor_Relevancia_Hash*)malloc(total_de_arquivos * sizeof(Vetor_Relevancia_Hash)); 
  for(int i = 0; i< total_de_arquivos; i++){
   // Cálculo de aux com divisão em ponto flutuante
    float aux = 1.0f / qtd_termos_documentos[i]; // i/ni
        
    valor_peso = 0;
        
    for (int j = 0; j < qtd_pesquisa; j++) {
      float p = Calcular_Peso_Termo_Hash(ingredientes[j], TabelaIngrediente, total_de_arquivos, MatrizPeso, i, compara_hash_pesquisa); // Para cada termo de busca calula o seu peso
      valor_peso += p; // Vai somando o valor dos pesos encontrado  - soma de wj
    }
        
   
    resultado[i].indice = i; // Armazena o valor do indice do documento no vetor de relevancias
    resultado[i].resultado_relevancia = aux*valor_peso; // Resultado da relevancia 
    
  }
  qsort(resultado, total_de_arquivos, sizeof(Vetor_Relevancia_Hash), Comparar_Relevancia_Hash); // Ordena o vetor de maneira decrescente, da maior para menor relevancia
  return resultado; 
}

//Pesquisa o termo de busca e retorna o documento ou documentos de acordo com a relevancia
void Pesquisa_Termos_Hash(int* qtd_termos_documentos, int total_de_arquivos, int qtd_termos_busca, nome_ingrediente_hash* ingredientes_busca, char** vetor_pocoes, Hash TabelaIngredientes, Pesos MatrizPeso, double *tempo_Pesquisa_Hash, int* compara_hash_pesquisa){
  clock_t tempo_inicio_Hash = clock();
  //Armazena os calculos de relevancia de cada documento em um vetor
  Vetor_Relevancia_Hash* relevancias = Calcular_Relevancia_Termo_Hash(ingredientes_busca, TabelaIngredientes, qtd_termos_documentos, total_de_arquivos,MatrizPeso, qtd_termos_busca, compara_hash_pesquisa);
  int contador = 0;

  for(int i = 0; i < total_de_arquivos; i++){
    (*compara_hash_pesquisa)++; //Comparacao do if
    if(relevancias[i].resultado_relevancia > 0){ 
      // Se o valor da relevancia de um documento for maior que zero, esse documento é impresso 
      // Caso contrario ele nao eh considerado
      printf("\nDocumento %d:\n%s\n\n", relevancias[i].indice +1, vetor_pocoes[relevancias[i].indice]);
    }
    else{      
      contador++; // Se o valor da relevancia for 0 o contador eh incrementado
    }
  }

  clock_t tempo_final_Hash = clock(); //Marca o tempo final 
  *tempo_Pesquisa_Hash = (double)(tempo_final_Hash-tempo_inicio_Hash) / CLOCKS_PER_SEC; //Calcula o tempo total em segundos
  (*compara_hash_pesquisa)++; //Comparacao do if 
  if(contador == total_de_arquivos){ // Se o contador for igual ao valor de total de arquivos significa que o termo nao foi encontrado em nenhum documento
    printf("Sua pesquisa não encontrou nenhum documento correspondente");
  }
}

