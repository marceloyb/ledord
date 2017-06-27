#ifndef GERENCIAMENTO_LED_H
#define GERENCIAMENTO_LED_H
#include <stdio.h>

struct{
  FILE *fp;
  int head;
} LED;

void led_start();
void led_insert();
void led_remove();

#endif
