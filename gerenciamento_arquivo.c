#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento_arquivo.h"


char *get_registro (FILE *file){
  char *buffer = malloc(sizeof(char)*50);
  int i = 0;
  char c;
  for (c = fgetc(file); c != '|'; c = fgetc(file)){
    if (c == EOF)
     return EOF;
    buffer [i] = c;
    i++;
  }
  return buffer;
}

void inicializa_txt(){
  REGISTROTXT = fopen("dados-inline.txt", "r");
  if (REGISTROTXT == NULL){
    printf ("\nERRO\n");
    printf ("\ndados-inline.txt nao foi encontrado\n");
    printf ("\nSAINDO\n");
    exit(1);
  }
}

void importar(char *nomeregistro){

  char *id = malloc (sizeof(char)*10);
  char *nome = malloc(sizeof(char)*30);
  char *curso = malloc(sizeof(char)*20);
  char *nota = malloc(sizeof(char)*10);
  char string[100] = "";
  char registro[100] = "";
  char *campo;
  short tam_registro;
  int contador = 0;
  int i;
  int ret;

  if (novo_registro != NULL)
    fclose(novo_registro);

    FILE *teste;

  novo_registro = fopen(nomeregistro, "wb+");

  if (novo_registro == NULL){
    printf ("Erro ao abrir o novo arquivo de registros\n");
    return;
  }

    do{
      strcpy(registro, "");
      id = get_registro(REGISTROTXT);
      nome = get_registro(REGISTROTXT);
      curso = get_registro(REGISTROTXT);
      nota = get_registro(REGISTROTXT);
      if (id != EOF){
        strcat (registro, id);
        strcat (registro, "|");
        strcat (registro, nome);
        strcat (registro, "|");
        strcat (registro, curso);
        strcat (registro, "|");
        strcat(registro, nota);
        strcat(registro, "|");
        tam_registro = strlen(registro);
        fwrite (&tam_registro, sizeof(tam_registro), 1, novo_registro);
        fwrite (registro, sizeof(char), tam_registro, novo_registro);
      }
    }while(id != EOF);

    fseek (REGISTROTXT, 0, SEEK_SET);
  }

char buscar(){
  char string[100] = "", registro[100] = "", * campo = NULL;
  int matched;
  short rec_lgth = 2;
  char file_name[30];
  char search_key[30];
  char* field, *last;
  int ret;

  if (novo_registro == NULL){
    printf ("novoregistronexiste");
    importar("registro");
  }

    printf ("\nInsira o numero de inscricao\n");
    __fpurge(stdin);
    printf ("vai entrar no fgets");
    fgets(search_key, sizeof(search_key), stdin);
    __fpurge(stdin);
    printf ("vai entrar no fgets");
    fgets(string,100,REGISTROTXT);
    campo = strtok(string, "|");
    ret = strcmp(search_key, campo);
    printf ("%i", ret);
    printf ("%s", campo);
    //strcat(registro, campo);
    //printf ("%s", registro);
  /*do{
    campo = get_rec(REGISTROTXT);
    printf ("\n ID Achado%s\n", campo);
    printf ("\n ID Buscado%s\n", id);
    ret = strcmp (id, campo);
    printf ("\n\n%i\n\n", ret);
    if (id == campo){
      printf ("ID: %s\n", campo);
      campo = get_rec(REGISTROTXT);
      printf ("Nome do candidato: %s\n", campo);
      campo = get_rec(REGISTROTXT);
      printf ("Curso: %s\n", campo);
      campo = get_rec(REGISTROTXT);
      printf ("Nota: %s\n", campo);
      return pos;
    }
    else{
      printf ("ID nao registrado");
      break;
    }
  }while(id != EOF);*/
}
