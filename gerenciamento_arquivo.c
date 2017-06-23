#include <stdio.h>
#include <stdlib.h>
#include "gerenciamento_arquivo.h"

void inicializa_txt(){
  REGISTROTXT = fopen("dados-inline.txt", "r");

  if (REGISTROTXT == NULL){
    printf ("\nERRO\n");
    printf ("\ndados-inline.txt nao foi encontrado\n");
    printf ("\nSAINDO\n");
    exit(1);
  }
}
void importar(){

  char string[200] = "";
  char registro[200] = "";
  char *campo;
  short tam_registro;

  if (novo_registro != NULL)
    fclose(novo_registro);


  __fpurge(stdin);
  printf ("\nInsira o nome do novo arquivo de registros\n");
  gets(string);

  novo_registro = fopen("registro", "wb+");
  if (novo_registro == NULL){
    printf ("Erro ao abrir o novo arquivo de registros\n");
    return;
  }

  while (!feof(REGISTROTXT)){
    fgets(string, 200, REGISTROTXT);
    strcpy(registro, "");
    campo = strtok(string, "|");
    while (campo != NULL){
      strcat (registro, campo);
      strcat(registro, "|");
      campo = strtok(NULL, "|\n");
    }
    tam_registro = strlen(registro);
    fwrite (&tam_registro, sizeof(tam_registro), 1, novo_registro);
    fwrite (registro, sizeof(char), tam_registro, novo_registro);
  }
  fseek (REGISTROTXT, 0, SEEK_SET);

}
