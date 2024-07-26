//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "IndiceInvertido.h"

void Inicializa_Lista_ID(Lista_ID_Invertido* Lista_ID_Invertido){ //Estamos utilizando célula cabeça
    Lista_ID_Invertido -> primeiro = (Celula_ID*)malloc(sizeof(Lista_ID_Invertido)); 
    Lista_ID_Invertido -> ultimo = Lista_ID_Invertido -> primeiro; 
    Lista_ID_Invertido -> primeiro -> prox = NULL; 
    // Para a lista estar vazia ultimo e proximo terão que apontar
    //para o mesmo elemento, a minha célula cabeça e o proximo tem que ser NULL
}

int Verifica_Vazio_ID(Lista_ID_Invertido* Lista_ID_Invertido){ // A função Lista Vazia retorna se a nossa lista encadeada possui elementos ou não. 
    return(Lista_ID_Invertido-> primeiro == Lista_ID_Invertido-> ultimo); // Retorna 1 se está vazia, e 0 se não.
} 

int Retorna_Tamanho_ID(Lista_ID_Invertido* Lista_ID_Invertido){
    int tamanho=0; 
    if (Verifica_Lista_Vazia(Lista_ID_Invertido)){ // Verifica se a lista é vazia, se for, a variavel tamanho recebe 0;
        return 0;
    }
    Celula_ID* auxiliar = Lista_ID_Invertido -> primeiro -> prox;
    while ( auxiliar != NULL) {
        tamanho += 1;   // Somamos um ao tamanho
        auxiliar = auxiliar -> prox; // Avançamos para a próxima Celula_ID da lista;
    }
    return tamanho;
}

void Adiciona_ID(Lista_ID_Invertido* Lista_ID_Invertido, int qtd, int id_doc){
    Lista_ID_Invertido -> ultimo -> prox = (Celula_ID*)malloc(sizeof(Celula_ID)); //Ligando minha nova celula a anterior a ela (antiga ultima)
    Lista_ID_Invertido -> ultimo = Lista_ID_Invertido -> ultimo -> prox; //Atualizando o meu ultimo para a nova celula alocada
    
    //adicionando indice invertido:
    Lista_ID_Invertido -> ultimo -> qdt = qtd; 
    Lista_ID_Invertido -> ultimo -> id_doc = id_doc;

    Lista_ID_Invertido -> ultimo -> prox = NULL; //Como o prox do ultimo não aponta para nada, passamos NULL
}