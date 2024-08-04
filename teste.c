#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define M 10 // Defina M como o número máximo de ingredientes

typedef struct Celula_Ingrediente {
    char* Chave;
    struct Celula_Ingrediente* prox;
    // Adicione outros campos conforme necessário
    void* head_ID; // Substitua por tipo adequado
} Celula_Ingrediente;

int compararIngredientes(const void* a, const void* b) {
    const Celula_Ingrediente* celulaA = *(const Celula_Ingrediente**)a;
    const Celula_Ingrediente* celulaB = *(const Celula_Ingrediente**)b;
    return strcmp(celulaA->Chave, celulaB->Chave);
}

Celula_Ingrediente** ColetarIngredientes(Celula_Ingrediente* TabelaIngredientes[], int tamanho, int* contador) {
    Celula_Ingrediente** vetor_hash = malloc(sizeof(Celula_Ingrediente*) * tamanho);
    if (vetor_hash == NULL) {
        perror("Erro ao alocar memória");
        exit(EXIT_FAILURE);
    }

    *contador = 0;
    for (int i = 0; i < tamanho; i++) {
        Celula_Ingrediente* aux = TabelaIngredientes[i].primeiro->prox;
        while (aux != NULL) {
            vetor_hash[*contador] = aux;
            aux = aux->prox;
            (*contador)++;
        }
    }
    
    return vetor_hash;
}

void OrdenarIngredientes(Celula_Ingrediente* vetor_hash[], int contador) {
    qsort(vetor_hash, contador, sizeof(Celula_Ingrediente*), compararIngredientes);
}

void ImprimirIngredientes(Celula_Ingrediente* vetor_hash[], int contador) {
    for (int j = 0; j < contador; j++) {
        printf("%02d: ", j + 1); // printa o idice formatado, com duas casas decimais
        printf("%s ", vetor_hash[j]->Chave);
        // Adicione a chamada da função para imprimir head_ID se necessário
        putchar('\n');
    }
}

void Imprime_Hash(Celula_Ingrediente* TabelaIngredientes[], int tamanho) {
    int contador;
    
    // Coleta os ingredientes
    Celula_Ingrediente** vetor_hash = ColetarIngredientes(TabelaIngredientes, tamanho, &contador);
    
    // Ordena os ingredientes
    OrdenarIngredientes(vetor_hash, contador);
    
    // Imprime os ingredientes
    ImprimirIngredientes(vetor_hash, contador);
    
    // Libera a memória alocada
    free(vetor_hash);
}

int main() {
    // Exemplo de uso (substitua com dados reais)
    Celula_Ingrediente ing1 = {"Apple", NULL, NULL};
    Celula_Ingrediente ing2 = {"Banana", NULL, NULL};
    Celula_Ingrediente ing3 = {"Cherry", NULL, NULL};

    Celula_Ingrediente* TabelaIngredientes[M] = {NULL};
    TabelaIngredientes[0] = &ing1;
    TabelaIngredientes[1] = &ing2;
    TabelaIngredientes[2] = &ing3;

    int tamanho = 3; // Número de itens na tabela

    Imprime_Hash(TabelaIngredientes, tamanho);

    return 0;
}
