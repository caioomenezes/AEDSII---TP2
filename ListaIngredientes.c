//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "ListaIngredientes.h"
#include <stdlib.h>

void Inicializa_Lista_ID(Lista_Ingredientes* Lista_Ingredientes){ //Estamos utilizando célula cabeça
    Lista_Ingredientes -> primeiro = (Celula_Ingrediente*)malloc(sizeof(Lista_Ingredientes)); 
    Lista_Ingredientes -> ultimo = Lista_Ingredientes -> primeiro; 
    Lista_Ingredientes -> primeiro -> prox = NULL; 
    // Para a lista estar vazia ultimo e proximo terão que apontar
    //para o mesmo elemento, a minha célula cabeça e o proximo tem que ser NULL
}

int Verifica_Vazio_ID(Lista_Ingredientes* Lista_Ingredientes){ // A função Lista Vazia retorna se a nossa lista encadeada possui elementos ou não. 
    return(Lista_Ingredientes-> primeiro == Lista_Ingredientes-> ultimo); // Retorna 1 se está vazia, e 0 se não.
} 

int Retorna_Tamanho_ID(Lista_Ingredientes* Lista_Ingredientes){
    int tamanho=0; 
    if (Verifica_Lista_Vazia(Lista_Ingredientes)){ // Verifica se a lista é vazia, se for, a variavel tamanho recebe 0;
        return 0;
    }
    Celula_Ingrediente* auxiliar = Lista_Ingredientes -> primeiro -> prox;
    while ( auxiliar != NULL) {
        tamanho += 1;   // Somamos um ao tamanho
        auxiliar = auxiliar -> prox; // Avançamos para a próxima Celula_Ingrediente da lista;
    }
    return tamanho;
}

