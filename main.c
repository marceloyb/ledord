#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "gerenciamento_arquivo.h"
#include "gerenciamento_led.h"


void menu (){
  printf ("\n >>>>>>> MENU <<<<<<<\n");
  printf ("\n (1) para importar\n");
  printf ("\n (2) para buscar registro pelo numero de inscricao\n");
  printf ("\n (3) para inserir novo registro\n");
  printf ("\n (4) para remover registro\n");
  printf ("\n (0) para fechar o programa\n");
}


int main (){
  int rodando = 1;
  int opcao;
  char string[50];
  char id[10];
  inicializa_txt();
  printf ("Inicializou\n");
  do{
    menu();
    scanf ("%i", &opcao);
    switch(opcao){
      case 1:
        importar();
        break;
      case 2:
        buscar(novo_registro);
        break;
      case 3:
        led_insert();
        break;
      case 4:
        led_remove();
        break;
      case 0:
        rodando = 0;
        break;
    }
  }while(rodando);
}
