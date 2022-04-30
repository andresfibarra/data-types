/* 
 * settest.c - test program for CS50 set module=
 *
 * This program is a "unit test" for the set module, using preset tests
 *
 * Andres Ibarra, January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "set.h"
#include "file.h"
#include "../lib/mem.h"

void stringItemPrint(FILE* fp, const char* key, void* item);
void itemCounter(void* arg, const char* key, void* item); 
void itemClear(void* arg, const char* key, void* item);
void stringItemDelete(void* item); 

/* **************************************** */
int main() 
{ 
  set_t* set1 = NULL; 
  set_t* set2 = NULL;
  char* key1 = "Dartmouth"; 
  char* nullKey = NULL;   
  char* key2 = "Yale"; 
  char* key3 = "Harvard"; 
  char* nullItem = NULL; 
  char* item1 = "Hanover"; 
  char* item2 = "Wherever Yale is"; 
  char* item3 = "Cambridge"; 

  char* newItem1 = mem_malloc(strlen(item1) + 1); 
  strcpy(newItem1, item1); 
  char* newItem2 = mem_malloc(strlen(item2) + 1); 
  strcpy(newItem2, item2); 
  char* newItem3 = mem_malloc(strlen(item3) + 1); 
  strcpy(newItem3, item3); 
  
  int itemCount = 0; //number of items in set


  printf("Creating first set...\n"); 
  set1 = set_new();

  if (set1 == NULL) {
    fprintf(stderr, "bag_new failed for bag1\n");
    return 1;
  }

  //Testing set_insert
  printf("\nTest with null set, good key, good item...\n");
  //should print out false
  printf(set_insert(set2, key1, newItem1) ? "true\n" : "false\n"); 

  printf("\nTest with null key, good item...\n"); 
  //should print out false
  printf(set_insert(set1, nullKey, newItem1) ? "true\n" : "false\n"); 

  printf("\nTest with null key, null item...\n"); 
  //should print out false
  printf(set_insert(set1, nullKey, nullItem) ? "true\n" : "false\n"); 

  printf("\nTest with good key, good item...\n"); 
  //should print out true
  printf(set_insert(set1, key1, newItem1) ? "true\n" : "false\n");
  
  printf("\nTest with existing key...\n"); 
  //should print out false
  printf(set_insert(set1, key1, newItem2) 
        ? "true\n" : "false\n");

  printf("\nAdding 2 more items to the set...\n");
  set_insert(set1, key2, newItem2); 
  set_insert(set1, key3, newItem3); 
  set_print(set1, stdout, stringItemPrint); 


  //Testing set_find
  printf("\nTesting valid use of set_find..\n"); 
  printf("The item for key='Dartmouth' is %s, stored at %p\n", 
        (char*)set_find(set1, "Dartmouth"), set_find(set1, "Dartmouth")); 

  printf("Testing set_find providing null sets...\n"); 
  //Should print (nil)
  printf("%p\n", set_find(NULL, "Dartmouth"));
  //Should print (nil)
  printf("%p\n", set_find(set2, "Dartmouth")); 

  printf("Testing set_find providing a null key...\n"); 
  //Should print (nil)
  printf("%p\n\n", set_find(set1, NULL)); 

  printf("Testing set_find providing an invalid key...\n"); 
  //Should print (nil)
  printf("%p\n", set_find(set1, "This key doesn't exist")); 


  //Testing set_print
  printf("\nNow printing set1:\n");
  set_print(set1, stdout, stringItemPrint);

  printf("\nNow testing set_print with a null set\n"); 
  set_print(set2, stdout, stringItemPrint);

  printf("\nNow testing set_print with a null file (should print nothing)\n"); 
  set_print(set1, NULL, stringItemPrint);

  printf("\nNow testing set_print with a null itemprint\n"); 
  set_print(set1, stdout, NULL);

  //Testing set_iterate
  printf("\nCounting the items in set1...\n"); 
  set_iterate(set1, &itemCount, itemCounter); 
  printf("There are %d items in set1\n", itemCount); 

  printf("\nClearing items in set1...\n"); 
  set_iterate(set1, NULL, itemClear);
  printf("Now print the set after clearing items:\n"); 
  set_print(set1, stdout, stringItemPrint); 

  printf("\nDeleting set1...\n"); 
  set_delete(set1, stringItemDelete); 

  mem_free(newItem1); 
  mem_free(newItem2); 
  mem_free(newItem3); 
  
  return 0; 
}

/*
 * Print in the form of (key,item)
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
  if (num != NULL && item != NULL) {
    (*num)++; 
  }
}

/*
 * Alter the value of item to be an empty string
 */ 
void itemClear(void* arg, const char* key, void* item) {
  if (item != NULL && strlen(item) > 0) {
    strcpy(item, ""); 
  }
}

/*
 * Delete a string item
 */
void stringItemDelete(void* item) 
{
  if (item != NULL) {
    mem_free(item); 
    item = NULL; 
  }
}
