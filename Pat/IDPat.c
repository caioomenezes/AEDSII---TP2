//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)

#include "IDPat.h"

void Inicializa_Lista_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido){ //Estamos utilizando célula cabeça
    listaIdInvertido -> primeiro = (Celula_ID_Pat*)malloc(sizeof(Celula_ID_Pat)); 
    listaIdInvertido -> ultimo = listaIdInvertido -> primeiro; 
    listaIdInvertido -> primeiro -> prox = NULL; 
    //Para a lista estar vazia ultimo e proximo terao que apontar
    //para o mesmo elemento, a minha celula cabeca e o proximo tem que ser NULL
}

int Verifica_Vazio_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido){ // A funcao Lista Vazia retorna se a nossa lista encadeada possui elementos ou nao. 
    return(listaIdInvertido-> primeiro == listaIdInvertido-> ultimo); // Retorna 1 se esta vazia, e 0 se nao
} 

int Retorna_Tamanho_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido){
    int tamanho=0; 
    if (Verifica_Vazio_ID_Pat(listaIdInvertido)){ // Verifica se a lista e vazia, se for, a variavel tamanho recebe 0
        return 0;
    }
    Celula_ID_Pat* auxiliar = listaIdInvertido -> primeiro -> prox;
    while ( auxiliar != NULL) {
        tamanho += 1;   // Somamos um ao tamanho
        auxiliar = auxiliar -> prox; // Avancamos para a proxima Celula_ID_Pat da lista
    }
    return tamanho;
}

void Adiciona_ID_Pat(Lista_ID_Invertido_Pat* listaIdInvertido, int qtd, int id_doc){

    listaIdInvertido -> ultimo -> prox = (Celula_ID_Pat*)malloc(sizeof(Celula_ID_Pat)); //Ligando minha nova celula a anterior a ela (antiga ultima)
    
    listaIdInvertido -> ultimo = listaIdInvertido -> ultimo -> prox; //Atualizando o meu ultimo para a nova celula alocada
    
    //adicionando indice invertido:
    listaIdInvertido -> ultimo -> qtd = qtd; 
    
    listaIdInvertido -> ultimo -> id_doc = id_doc;
    
    listaIdInvertido -> ultimo -> prox = NULL; //Como o prox do ultimo nao aponta para nada, passamos NULL
    //printf("%d %d\n", listaIdInvertido->ultimo->id_doc, listaIdInvertido->ultimo->qtd);

}

void Imprime_Indice_Invertido_Pat(Lista_ID_Invertido_Pat* listaIdInvertido){
    Celula_ID_Pat *Aux = (listaIdInvertido -> primeiro->prox);
    putchar('(');
    while (Aux != NULL) { 
        printf("<%d,%d> -> ", Aux->qtd, Aux->id_doc+1);
        Aux = Aux->prox;
    }
    printf("NULL)");
    
} 
