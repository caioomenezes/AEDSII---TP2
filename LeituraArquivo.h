//Amanda(5366), Caio(5784), Leticia(5781), Melissa(5384)
//retirar comentario quando fizer o include do hash.h e apagar os includes do LeituraArquivo.c
/*
#include <string.h>
#include <ctype.h>
*/

#ifndef LEITURA_ARQUIVO_H
#define LEITURA_ARQUIVO_H
#include "Hash/Hash.h"
#include "Hash/PesquisaHash.h"
#include "Pat/Patricia.h"
#include "Pat/PesquisaPat.h"
#include <ctype.h>

Pesos p;
Hash TabelaIngredientes;
TipoArvore Pat;

void Letra_Minuscula(char *str); // Transforma todas as letras da string em minusculas
int Leitura_Receita(char *nomearquivo, char **receita_str); //  Le a receita e copia para uma string
int Leitura_Secundaria(char *nomearquivo, int i, int **qtd_termos_documentos); // Le o arquivo secundario e conta a frequencia dos ingredientes
int Leitura_Principal(char *nomearquivo, int **qtd_termos_documentos, int* total_de_arquivos); // Le o arquivo de entrada e confere a qtd de receitas
int Frequencia_Ingrediente(char *receita_str, char *nome_ingrediente); // Conta a frequencia do ingrediente no arquivo


#endif // LEITURA_ARQUIVO_H