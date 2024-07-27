//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "ListaIngredientes.h"

void Inicializa_Lista_Ingredientes(Lista_Ingredientes* listaIngredientes){ //Estamos utilizando celula cabeca
    listaIngredientes -> primeiro = (Celula_Ingrediente*)malloc(sizeof(listaIngredientes)); 
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


Celula_Ingrediente *Pesquisa_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente ingrediente){
    Celula_Ingrediente* aux = listaIngredientes->primeiro;  // Começa pela cabeca da lista

    while (aux != NULL) {
        // Comparar a chave do no atual com o ingrediente buscado
        if (memcmp(aux->Chave, ingrediente, N) == 0) {
            return aux;  // Ingrediente encontrado
        }
        aux = aux->prox;  // Move para o proximo no
    }

    return NULL;  // Ingrediente nao encontrado
}


void Adiciona_Ingrediente(Lista_Ingredientes* listaIngredientes, nome_ingrediente ingrediente, int qtd_ingredientes, int id_doc){
    
    listaIngredientes -> ultimo -> prox = (Celula_Ingrediente*)malloc(sizeof(Celula_Ingrediente)); //Ligando minha nova celula a anterior a ela (antiga ultima)
    listaIngredientes -> ultimo = listaIngredientes -> ultimo -> prox; //Atualizando o meu ultimo para a nova celula alocada
    
    strcpy(listaIngredientes->ultimo->Chave, ingrediente); //strcpy para copiar o valor de ingrediente para chave

    //Eu preciso criar e inicializar minha lista de ids aqui  porque eu chamo Adiciona_Ingredientes apenas quando meu ingrediente ainda nao esta na lista 
    //encadeada (primeira vez que ele foi lido nos arquivos), logo a lista de id dessa celula ainda nao existe
    Lista_ID_Invertido *listaIdInvertido;
    Inicializa_Lista_ID(listaIdInvertido);
    listaIngredientes->ultimo->head_ID = listaIdInvertido;

    //Apos criar minha lista de ids devo adicionar as iformacoes do indice invertido nela 
    Adiciona_ID(listaIdInvertido, qtd_ingredientes, id_doc);
    printf("adicionando %d %d \n", listaIngredientes->ultimo->head_ID->ultimo->id_doc, listaIngredientes->ultimo->head_ID->ultimo->qdt);
    listaIngredientes -> ultimo -> prox = NULL; //Como o prox do ultimo nao aponta para nada, passamos NULL
}

void Imprime_Lista_Ingredientes(Lista_Ingredientes *listaIngredientes){
    Celula_Ingrediente *Aux = (listaIngredientes -> primeiro->prox);
    while (Aux != NULL) { 
        printf("%.*s ", N, Aux->Chave);
        Aux = Aux->prox;
    }
}

 