//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)


#include "ListaIngredientes.h"

void Inicializa_Lista_Ingredientes(Lista_Ingredientes* listaIngredientes){ //Estamos utilizando celula cabeca
    listaIngredientes -> primeiro = (Celula_Ingrediente*)malloc(sizeof(Celula_Ingrediente)); 
    listaIngredientes -> ultimo = listaIngredientes -> primeiro; 
    listaIngredientes -> primeiro -> prox = NULL; 
    // Para a lista estar vazia ultimo e proximo terao que apontar
    //para o mesmo elemento, a minha célula cabeca e o proximo tem que ser NULL
}

int Verifica_Vazio_Ingredientes(Lista_Ingredientes* listaIngredientes){ // A funcao Lista Vazia retorna se a nossa lista encadeada possui elementos ou nao
    return(listaIngredientes-> primeiro == listaIngredientes-> ultimo); // Retorna 1 se está vazia, e 0 se nao
} 

int Retorna_Tamanho_Ingredientes(Lista_Ingredientes* listaIngredientes){
    int tamanho=0; 
    if (Verifica_Vazio_Ingredientes(listaIngredientes)){ // Verifica se a lista e vazia, se for, a variavel tamanho recebe 0
        return 0;
    }
    Celula_Ingrediente* auxiliar = listaIngredientes -> primeiro -> prox;
    while ( auxiliar != NULL) {
        tamanho += 1;   // Somamos um ao tamanho
        auxiliar = auxiliar -> prox; // Avancamos para a proxima Celula_Ingrediente da lista
    }
    return tamanho;  
}


Celula_Ingrediente* Pesquisa_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente_hash ingrediente) {
    Celula_Ingrediente* aux = listaIngredientes->primeiro;  // Comeca pela cabeça da lista

    while (aux != NULL) {
        // Comparar a chave do no atual com o ingrediente buscado
        if (strcmp(aux->Chave, ingrediente) == 0) {
            return aux;  // Ingrediente encontrado
        }
        aux = aux->prox;  // Move para o proximo no
    }

    return NULL;  // Ingrediente nao encontrado
}

Celula_Ingrediente* Pesquisa_Hash(Lista_Ingredientes* listaIngredientes, nome_ingrediente_hash ingrediente, int *compara_hash_pesquisa) {
    Celula_Ingrediente* aux = listaIngredientes->primeiro;  // Comeca pela cabeça da lista

    while (aux != NULL) {
        (*compara_hash_pesquisa)++; //Comparacao do while
        // Comparar a chave do no atual com o ingrediente buscado
        (*compara_hash_pesquisa)++; //Comparacao do if
        if (strcmp(aux->Chave, ingrediente) == 0) {
            return aux;  // Ingrediente encontrado
        }
        aux = aux->prox;  // Move para o proximo no
    }

    return NULL;  // Ingrediente nao encontrado
}

void Adiciona_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente_hash ingrediente, int qtd_ingredientes, int id_doc) {
    // Alocar memoria para a nova celula e conectar a lista existente
    listaIngredientes->ultimo->prox = (Celula_Ingrediente*)malloc(sizeof(Celula_Ingrediente));
    listaIngredientes->ultimo = listaIngredientes->ultimo->prox;

    // Copiar o nome do ingrediente para a chave da nova celula
    strcpy(listaIngredientes->ultimo->Chave, ingrediente);

    // Inicializar a lista de IDs invertidos para esta celula
    Lista_ID_Invertido_Hash* listaIdInvertido = (Lista_ID_Invertido_Hash*)malloc(sizeof(Lista_ID_Invertido_Hash)); // Alocar memoria
    Inicializa_Lista_ID_Hash(listaIdInvertido); // Inicializar a lista
    listaIngredientes->ultimo->head_ID = listaIdInvertido;

    // Adicionar o ID do documento na lista de IDs
    Adiciona_ID_Hash(listaIdInvertido, qtd_ingredientes, id_doc);

    // Marcar o final da lista
    listaIngredientes->ultimo->prox = NULL;

    
}

void Imprime_Lista_Ingredientes(Lista_Ingredientes *listaIngredientes) {
    Celula_Ingrediente *Aux = listaIngredientes->primeiro->prox;  // Comeca no primeiro elemento real

    while (Aux != NULL) { 
        printf("[%.*s ", N, Aux->Chave);  // Imprime o nome do ingrediente
        Imprime_Indice_Invertido_Hash(Aux->head_ID);  // Imprime o indice invertido
        printf("] -> ");
        Aux = Aux->prox;  // Avança para o proximo elemento
    }
    //Indica o final da lista de ingredientes
    printf("NULL");
    
}

void Imprime_Ingrediente(int contador, Celula_Ingrediente** vetor_hash){
  // Imprime o vetor ordenado
  for (int j = 0; j < contador; j++) {
    printf("%02d: ", j+1); // printa o idice formatado, com duas casas decimais
    printf("%s ", vetor_hash[j]->Chave);
    Imprime_Indice_Invertido_Hash(vetor_hash[j]->head_ID);
    putchar('\n');
  }
}

void free_Ingredientes(Lista_Ingredientes *listaIngrediente) {
    if (listaIngrediente == NULL) return;

    Celula_Ingrediente *atual = listaIngrediente->primeiro;
    Celula_Ingrediente *aux;

    while (atual != NULL) {
        // Liberar a lista de IDs associada ao ingrediente atual
        if (atual->head_ID != NULL) {
            free_ID_Invertido_Hash(atual->head_ID);
        }
        // Avanca para o proximo ingrediente
        aux = atual;
        atual = atual->prox;

        // Liberar o ingrediente atual
        free(aux);
    }

    Inicializa_Lista_Ingredientes(listaIngrediente); //primeiro e ultimo da minha lista precisam ser null
}
