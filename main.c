#include <stdio.h>
#include <stdlib.h>


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
  FILE *file;
  do{
    menu();
    scanf ("%i", &opcao);
    switch(opcao){
      case 1:
        //import
        break;
      case 2:
        //buscar registro
        break;
      case 3:
        //inserir registro
        break;
      case 4:
        //remover registro
        break;
      case 0:
        rodando = 0;
        break;
    }
  }while(rodando);
}
