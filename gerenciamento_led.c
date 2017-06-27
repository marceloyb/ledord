#include <stdio.h>
#include <string.h>
#include "gerenciamento_arquivo.h"
#include "gerenciamento_led.h"

void led_start(FILE *reg){;
  LED.fp = reg;
  LED.head = -1;
}

void led_insert(){
  char registro[100] = "";
  char *id = malloc (sizeof(char)*10);
  char *nome = malloc(sizeof(char)*30);
  char *curso = malloc(sizeof(char)*20);
  char *nota = malloc(sizeof(char)*10);
  short tam_registro;
  short tam_registroled;
  short tam_fragment;
  char string[50];
  int cabeca;
  int posicaohead;
  FILE *novo_registro;

  if (novo_registro == NULL){
    printf ("\nInsira o nome do arquivo\n");
    __fpurge(stdin);
    fgets(string, sizeof(string), stdin);
    novo_registro = fopen(string, "r+");
  }

  fseek (novo_registro, 0, SEEK_SET);   // lendo o valor da cabeça
  fread (&cabeca, sizeof(cabeca), 1, novo_registro);


  strcpy(registro, "");
  __fpurge(stdin);
  printf ("\nInsira o ID do registro\n");
  scanf ("%s", id);
  __fpurge(stdin);
  printf ("\nInsira o nome do registro\n");
  scanf ("%s", nome);
  __fpurge(stdin);
  printf ("\nInsira o curso do registro\n");
  scanf ("%s", curso);
  __fpurge(stdin);
  printf ("\nInsira a nota do registro\n");
  scanf ("%s", nota);
  strcat (registro, id);
  strcat (registro, "|");
  strcat (registro, nome);
  strcat (registro, "|");
  strcat (registro, curso);
  strcat (registro, "|");
  strcat(registro, nota);
  strcat(registro, "|");
  tam_registro = strlen(registro);
  free (id);
  free (nome);
  free (curso);
  free (nota);
  if (cabeca == -1){
    fseek(novo_registro, 0, SEEK_END);
    fwrite (&tam_registro, sizeof(tam_registro), 1, novo_registro);
    fwrite (registro, sizeof(char), tam_registro, novo_registro);
  }
  else{
    fseek (novo_registro, cabeca-3, SEEK_SET);
    fread (&tam_registroled, sizeof(tam_registroled), 1, novo_registro);
    fseek (novo_registro, 2, SEEK_CUR);
    fread (&posicaohead, sizeof(posicaohead), 1, novo_registro);
    if (tam_registro <= tam_registroled + sizeof(short)){
      tam_fragment = tam_registroled - tam_registro - sizeof(short);
      fseek (novo_registro, cabeca-3, SEEK_SET);
      fwrite (&tam_registro, sizeof(tam_registro), 1, novo_registro); // inserindo o tamanho do registro na posição da led
      fwrite (registro, sizeof(char), tam_registro, novo_registro);  // inserindo o registro na posição da led
      fwrite (&tam_fragment, sizeof(tam_fragment), 1, novo_registro);  // colocando tamanho da fragmentacao após inserçao na led
      fseek (novo_registro, 0, SEEK_SET);
      fwrite (&posicaohead, sizeof(posicaohead), 1, novo_registro);
    }
  }
  printf ("\nAdicionado com sucesso!\n");
  fclose(novo_registro);
  novo_registro = NULL;
}

void led_remove(){
  int offset = 0;
  int opcao;
  short tam_reg;
  char string[50] = "";
  char nomearq[50];
  char a;
  int cabeca;

  printf ("\nInsira o nome do arquivo\n");
  __fpurge(stdin);
  fgets(nomearq, sizeof(nomearq), stdin);
  novo_registro = fopen(nomearq, "r+");

  offset = buscar(novo_registro);
  if (LED.fp == NULL){
    led_start(novo_registro);
  }

  fseek (novo_registro, 0, SEEK_SET);
  fread (&cabeca, sizeof(cabeca), 1, novo_registro);
  printf ("VALOR HEAD: %i\n", cabeca);
  if (offset != -1){
    printf ("\nDeseja remover do arquivo?\n");
    printf ("\n<1> Sim\n");
    printf ("\n<2> Nao\n");
    __fpurge(stdin);
    scanf ("%i", &opcao);
    if (opcao == 1){
      strcat (string, ".");

      fseek (novo_registro, 0, SEEK_SET);   // lendo o valor da cabeça
      fread (&cabeca, sizeof(cabeca), 1, novo_registro);
      fseek (novo_registro, 0, SEEK_SET);  // atualizando a cabeça com o byte offset do registro que está sendo removido
      fwrite(&offset, sizeof(offset), 1, novo_registro);
      fseek(novo_registro, offset-3, SEEK_SET);
      fread (&tam_reg, sizeof(tam_reg), 1, novo_registro);  // lendo o tamanho do registro que esta sendo removido

      fseek (novo_registro, offset-1, SEEK_SET);      // sobrescrevendo o registro com o valor da cabeça e .
      fwrite ("|", sizeof(char), 1, novo_registro);
      fwrite ("*", sizeof(char), 1, novo_registro);
      fwrite(&cabeca, sizeof(cabeca), 1, novo_registro);
      fwrite (string, sizeof(char), tam_reg-sizeof(cabeca)-3, novo_registro);
      fwrite ("|", sizeof(char), 1, novo_registro);
      printf ("\nRemovido com sucesso!");
    }
    else {
      return;
    }
  }
  else{
    printf ("\nRegistro nao esta no arquivo\n");
  }
  //

  fclose (novo_registro);
  novo_registro = NULL;
}
