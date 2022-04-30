/* 
 * hashtabletest.c - test program for CS50 hashtable module
 *
 * Usage: read words from stdin, one line at a time
 * 
 * This program is a "unit test" for the hashtable module
 *
 * Andres Ibarra, January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "hashtable.h"
#include "file.h"

void stringItemPrint(FILE* fp, const char* key, void* item);
void itemCounter(void* arg, const char* key, void* item);
void stringItemDelete(void* item);

int main() {
  hashtable_t* table = NULL; 
  hashtable_t* table2 = NULL; 
  const int num_slots = 10; 
  int bad_num_slots = -5; 
  
  char* key1 = "Dartmouth"; 
  char* item1 = "Hanover"; 

  int itemCount = 0; //number of items in set
  int lineCount = 0; //number of lines the user has input
  char* line = NULL;  //the user input line; 
  char* userKey = NULL; 
  char* newUserItem = NULL; 

  //Create copy of item1 in the heap
  char* newItem1 = malloc(strlen(item1) + 1); 
  strcpy(newItem1, item1); 


  //Test hashtable_new
  table = hashtable_new(num_slots); 
  printf("New hashtable created at: %p\n", (void*) table);
  table2 = hashtable_new(bad_num_slots); 
  printf("Hashtable created with bad num_slots: %p\n", (void*) table2);


  //Test hashtable_insert edge cases
  printf("\nTesting hashtable_insert with null table...\n");
  hashtable_insert(table2, key1, newItem1);
  printf("\nTesting hashtable_insert with null key...\n");
  hashtable_insert(table, NULL, newItem1); 
  printf("\nTesting hashtable_insert with null item...\n"); 
  hashtable_insert(table, key1, NULL); 
  //Seed table with an valid entry to test hashtable_find later
  printf("\nTesting hashtable_insert with good key, good item...\n");
  hashtable_insert(table, key1, newItem1); 


  //Testing hahstable_insert with user inputs
  printf("Type words here. "); 
  printf("Lines input will alternate between being keys and items:\n"); 
  while (!feof(stdin)) {
    line = file_readLine(stdin); 
    if (line != NULL) {
      if ((lineCount % 2) == 0) {  //if user input a key
        userKey = line; 
      } else {
        newUserItem = malloc(strlen(line)+1); 
        strcpy(newUserItem, line); 
        hashtable_insert(table, userKey, newUserItem); 
      }
    }
    lineCount++; 
  }
  printf("The hashtable created:\n");
  hashtable_print(table, stdout, stringItemPrint); 


  //Testing hashtable_find
  printf("\nTesting valid use of hashtable_find..\n"); 
  printf("The item for key='Dartmouth' is %s, stored at %p\n", 
        (char*)hashtable_find(table, "Dartmouth"), 
                hashtable_find(table, "Dartmouth")); 

  printf("Testing hashtable_find providing a null set...\n"); 
  hashtable_find(NULL, "Dartmouth");
  hashtable_find(table2, "Dartmouth"); 

  printf("Testing hashtable_find providing a null key...\n"); 
  hashtable_find(table, NULL); 

  printf("Testing hashtable_find providing an invalid key...\n"); 
  hashtable_find(table, "This key doesn't exist"); 


  //Test hashtable_print edge cases
  printf("\nnow testing hashtable_print with a null table...\n"); 
  hashtable_print(table2, stdout, stringItemPrint); 

  printf("\nNow testing hashtable_print with a null file (should print nothing)\n"); 
  hashtable_print(table, NULL, stringItemPrint); 

  printf("\nNow testing hashtable_print with a null itemprint\n"); 
  hashtable_print(table, stdout, NULL); 
  printf("\n"); 

  printf("\nCounting the items in the table...\n"); 
  hashtable_iterate(table, &itemCount, itemCounter); 
  printf("There are %d items in set1\n", itemCount); 

  printf("\nDeleting table...\n"); 
  hashtable_delete(table, stringItemDelete); 

  //free memory
  free(newItem1); 
  free(newUserItem); 
}

/*
 * Print in the form of (key, item)
*/
void stringItemPrint(FILE* fp, const char* key, void* item) 
{
  if (item == NULL) {
    fprintf(fp, "(null)"); 
  }
  else {
    fprintf(fp, "(%s,%s)", key, (char*) item); 
  }
}

/* 
 * count the non-null items in the bag.
 * note here we don't care what kind of item is in bag.
 */
void itemCounter(void* arg, const char* key, void* item) {
  int* num = arg; 
  (*num)++; 
}

/*
 * Delete a string item
 */
void stringItemDelete(void* item) 
{
  if (item != NULL) {
    free(item); 
    item = NULL; 
  }
}
