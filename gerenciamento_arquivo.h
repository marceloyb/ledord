#ifndef GERENCIAMENTO_ARQUIVO_H
#define GERENCIAMENTO_ARQUIVO_H

#include <stdio.h>

FILE *REGISTROTXT;
FILE *novo_registro;

void inicializa_txt();
void importar();
int buscar(char* id);
void inserir(char *registro);
void remover(char* id);

#endif
