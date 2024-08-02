#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef char* nome_ingrediente;
typedef int TipoBit;

typedef struct TipoPatNo* TipoArvore;

typedef enum { Externo, Interno } TipoNo;

typedef struct TipoPatNo {
    TipoNo tipoNo;
    union {
        struct {
            TipoArvore Esq;
            TipoArvore Dir;
            int BitDiferenciador;
            char LetraDiferenciadora;
        } NoInterno;
        nome_ingrediente Chave;
    } No;
} TipoPatNo;

// Funções auxiliares
TipoBit RetornaBit(TipoBit i, nome_ingrediente Chave) {
    return Chave[i-1];
} 

short Retorna_TipoNo(TipoArvore no) {
    return (no->tipoNo == Externo);
}

TipoArvore CriaNoInt(int i, char letra, TipoArvore *Esq, TipoArvore *Dir) {
    TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo));
    pat->tipoNo = Interno; 
    pat->No.NoInterno.Esq = *Esq;
    pat->No.NoInterno.Dir = *Dir; 
    pat->No.NoInterno.BitDiferenciador = i; 
    pat->No.NoInterno.LetraDiferenciadora = letra;
    return pat;
} 

TipoArvore CriaNoExt(nome_ingrediente Chave) { 
    TipoArvore pat = (TipoArvore)malloc(sizeof(TipoPatNo));
    pat->tipoNo = Externo; 
    pat->No.Chave = strdup(Chave); // Duplicando a string
    return pat;
}  

TipoArvore InsereEntre(nome_ingrediente Chave, TipoArvore *pat, int i, char letra_diferenciadora) {
    TipoArvore pat_aux;
    
    if (Retorna_TipoNo(*pat) || i < (*pat)->No.NoInterno.BitDiferenciador) { 
        pat_aux = CriaNoExt(Chave);

        if (RetornaBit(i, Chave) > RetornaBit(i, (*pat)->No.Chave)) {
            return CriaNoInt(i, letra_diferenciadora, pat, &pat_aux);
        } else {
            return CriaNoInt(i, letra_diferenciadora, &pat_aux, pat);
        }
    } else {
        if (RetornaBit(i, Chave) > RetornaBit(i, (*pat)->No.Chave)) {
            (*pat)->No.NoInterno.Dir = InsereEntre(Chave, &(*pat)->No.NoInterno.Dir, i, letra_diferenciadora);
        } else {
            (*pat)->No.NoInterno.Esq = InsereEntre(Chave, &(*pat)->No.NoInterno.Esq, i, letra_diferenciadora);
        }
        return (*pat);
    }
}

TipoArvore Insere(nome_ingrediente Chave, TipoArvore *pat) { 
    TipoArvore pat_aux;
    char letra_aux;
    char letra_diferenciadora;
    int tamanho = strlen(Chave);
    int i;

    if (*pat == NULL) {
        return CriaNoExt(Chave);
    } else { 
        pat_aux = *pat;

        while (!Retorna_TipoNo(pat_aux)) {
            if (tamanho < pat_aux->No.NoInterno.BitDiferenciador) {
                letra_aux = Chave[tamanho]; 
            } else {
                letra_aux = RetornaBit(pat_aux->No.NoInterno.BitDiferenciador, Chave);
            }

            if (letra_aux > pat_aux->No.NoInterno.LetraDiferenciadora) {
                pat_aux = pat_aux->No.NoInterno.Dir;
            } else {
                pat_aux = pat_aux->No.NoInterno.Esq;
            }
        }

        i = 1;
        while ((i <= tamanho) && (RetornaBit(i, Chave) == RetornaBit(i, pat_aux->No.Chave))) {
            i++;
        }
        if (i > tamanho) {
            printf("Erro: chave ja esta na arvore\n");
            return (*pat);
        } else {
            if (RetornaBit(i, Chave) > RetornaBit(i, pat_aux->No.Chave)) {
                letra_diferenciadora = Chave[i-1];
            } else { 
                letra_diferenciadora = pat_aux->No.Chave[i-1];
            }
            return InsereEntre(Chave, pat, i, letra_diferenciadora);
        }
    }
}

void ImprimePatricia(TipoArvore arvore) {
    if (arvore != NULL) {
        if (arvore->tipoNo == Interno) {
            ImprimePatricia(arvore->No.NoInterno.Esq);
        }

        if (arvore->tipoNo == Externo) {
            printf("%s ", arvore->No.Chave);
        }

        if (arvore->tipoNo == Interno) {
            ImprimePatricia(arvore->No.NoInterno.Dir);
        }
    }
}

int main() {
    TipoArvore arvore = NULL;

    // Array de nomes a serem inseridos
    nome_ingrediente nomes[] = {
        "caza", "caia", "cada", "caio", "cafe", "carro"
    };
    int num_nomes = sizeof(nomes) / sizeof(nomes[0]);

    // Inserção de nomes
    for (int i = 0; i < num_nomes; i++) {
        arvore = Insere(nomes[i], &arvore);
    }
    ImprimePatricia(arvore);
    // Imprime a árvore
    printf("\nEstrutura da árvore Patricia:\n");

    printf("\nDir:");
    ImprimePatricia(arvore->No.NoInterno.Dir);
    printf("\nEsq:");
    ImprimePatricia(arvore->No.NoInterno.Esq);

    return 0;
}
