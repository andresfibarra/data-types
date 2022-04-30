/* 
 * counterstest.c - test program for CS50 counters module
 *
 * usage: read integers from stdin, separated by white space
 * 
 * This program is a "unit test" for the counter module
 *
 * Andres Ibarra, January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "counters.h"
#include "file.h"

/* **************************************** */
int main() 
{
  counters_t* ctr1 = NULL; 
  counters_t* ctr2 = NULL; 

  int nextKey = 0; 

  printf("Creating the first counter...\n"); 
  ctr1 = counters_new();


  //Testing counters_add
  printf("\nAdding key=1 to ctr1...\n");
  counters_add(ctr1, 1); 
  counters_print(ctr1, stdout); 
  printf("Adding key=1 to ctr1 again...\n");
  counters_add(ctr1, 1); 
  //Nothing should be different
  counters_print(ctr1, stdout); 
  
  printf("\nAdding more keys now. "); 
  printf("Type in numbers separated by white space...\n");
  //ASSUMING ALL NUMBERS THE USER PROVIDES ARE INTEGERS
  while(scanf("%d", &nextKey) != EOF) {
    counters_add(ctr1, nextKey); 
  }


  //Testing counters_print
  counters_print(ctr1, stdout); 

  printf("\nTesting counters_print with a null file (nothing should print)\n"); 
  counters_print(ctr1, NULL); 
  printf("Testing counters_print with null ctr...\n"); 
  counters_print(ctr2, stdout); 

  printf("\nSetting key=1 to -10 (this shouldn't do anything)...\n");
  counters_print(ctr1, stdout); 
  printf("\nSetting key=1 to 200...\n"); 
  counters_set(ctr1, 1, 200); 
  counters_print(ctr1, stdout); 


  //testing counters_delete
  printf("\nDeleting ctr1...\n"); 
  counters_delete(ctr1); 

}