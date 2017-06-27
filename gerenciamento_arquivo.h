#ifndef GERENCIAMENTO_ARQUIVO_H
#define GERENCIAMENTO_ARQUIVO_H

#include <stdio.h>

FILE *REGISTROTXT;
FILE *novo_registro;

void inicializa_txt();
void importar();
int buscar();
void inserir();
void remover();

#endif
