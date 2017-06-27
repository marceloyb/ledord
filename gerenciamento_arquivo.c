#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento_arquivo.h"


char *get_rec (FILE *file){
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

void importar(){

  char *id = malloc (sizeof(char)*10);
  char *nome = malloc(sizeof(char)*30);
  char *curso = malloc(sizeof(char)*20);
  char c;
  char *nota = malloc(sizeof(char)*10);
  char string[100] = "";
  char registro[100] = "";
  char *campo;
  short tam_registro;
  char nomeregistro[50];
  int contador = 0;
  int i;
  int ret;
  int head = -1;

  if (novo_registro != NULL)
    fclose(novo_registro);

  __fpurge(stdin);
  printf ("\nInsira o nome do novo arquivo de registros\n");
  __fpurge(stdin);
  fgets(nomeregistro, sizeof(nomeregistro), stdin);
  novo_registro = fopen(nomeregistro, "w+b");

  if (novo_registro == NULL){
    printf ("Erro ao abrir o novo arquivo de registros\n");
    return;
  }

  fseek (novo_registro, 0, SEEK_SET);
  fwrite (&head, sizeof(head), 1, novo_registro);
  fseek(novo_registro, 0, SEEK_SET);
  int a;
  fread(&a, sizeof(head), 1, novo_registro);
  printf("a: %d\n", a);
    do{
      strcpy(registro, "");
      id = get_rec(REGISTROTXT);
      nome = get_rec(REGISTROTXT);
      curso = get_rec(REGISTROTXT);
      nota = get_rec(REGISTROTXT);
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

    led_start();
    fseek (REGISTROTXT, 0, SEEK_SET);
    fclose (novo_registro);
    novo_registro = NULL;
  }

int buscar(FILE *reg){
  char string[100] = "", registro[100] = "", * campo = NULL;
  int matched = 0;
  int i;
  int offset = 1;
  short rec_lgth = 2;
  char file_name[30];
  char search_key[6];
  char id[7];
  char* field, *last;


  if (reg == NULL){
    printf ("\nInsira o nome do arquivo\n");
    __fpurge(stdin);
    fgets(string, sizeof(string), stdin);
    reg = fopen(string, "r+");
  }

  printf ("\nInsira o ID\n");
  __fpurge(stdin);
  fgets(id, sizeof(id), stdin);

  fseek (reg, sizeof(int), SEEK_SET);
  fread (&rec_lgth, sizeof(rec_lgth), 1, reg);
  offset += sizeof(int) + sizeof(rec_lgth);
  fread (&search_key, sizeof(search_key), 1, reg);

  if (!strcmp(id, search_key)){
    matched = 1;
    campo = get_rec(reg);
    printf ("\n\nID: %s\n", search_key);
    campo = get_rec(reg);
    printf ("Nome do candidato: %s\n", campo);
    campo = get_rec(reg);
    printf ("Curso: %s\n", campo);
    campo = get_rec(reg);
    printf ("Nota: %s\n", campo);
  }

  while (!feof(reg) && matched != 1){
    printf ("OFFSET %i", offset);
    offset += rec_lgth + sizeof(rec_lgth);
    fseek (reg, rec_lgth - sizeof(search_key), SEEK_CUR);
    printf ("\nOffset: %i", offset);
    fread (&rec_lgth, sizeof(rec_lgth), 1, reg);
    fread (&search_key, sizeof(search_key), 1, reg);
    if (!strcmp(id, search_key)){
      matched = 1;
      campo = get_rec(reg);
      printf ("\n\nID: %s\n", search_key);
      campo = get_rec(reg);
      printf ("Nome do candidato: %s\n", campo);
      campo = get_rec(reg);
      printf ("Curso: %s\n", campo);
      campo = get_rec(reg);
      printf ("Nota: %s\n", campo);
    }
  }
  if (matched == 0){
    printf ("\nRegistro nao encontrado\n");
    return -1;
  }
  printf ("OFFSET %i\n", offset);

  return offset;
}
