/* 
 * hashtable.c - CS50 'hashtable' module
 *
 * see hashtable.h for more information.
 * 
 * This module uses the Jenkin's Hash. See hash.c for more information
 *
 * Andres Ibarra, January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "hashtable.h"
#include "../set/set.h"
#include "hash.h"
#include "../lib/mem.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct hashtable {
  set_t** slots;  //array of slots, each slot is a pointer to a set
  int num_slots; 
} hashtable_t;

/**************** hashtable_new ****************/
/*
 * See hashtable.h for description
 */
hashtable_t* hashtable_new(const int num_slots)
{
  if (num_slots > 0) {
    hashtable_t* hashtable = malloc(sizeof(hashtable_t));
    hashtable->slots = calloc(num_slots, sizeof(set_t*));
    hashtable->num_slots = num_slots; 

    for (int i = 0; i < num_slots; i++) {
      hashtable->slots[i] = set_new(); 
    }

    if (hashtable == NULL || hashtable->slots == NULL) {
      return NULL; 
    } else {
      return hashtable; 
    }
  } else {
    return NULL; 
  }
}

/**************** hashtable_insert ****************/
/*
 * See hashtable.h for description
 */
bool hashtable_insert(hashtable_t* ht, const char* key, void* item)
{
  if (ht == NULL || key == NULL || item == NULL) {
    return false;
  } else {
    if (hashtable_find(ht, key) != NULL) {    //if key already exists
      return false; 
    } else {
      int slot = hash_jenkins(key, ht->num_slots); 

      char* keyCopy; 
      keyCopy = (char*) mem_malloc(sizeof(char) * (strlen(key) + 1)); 
      strcpy(keyCopy, key); 
      mem_free(keyCopy); 
      bool pass = set_insert(ht->slots[slot], key, item); 

      return pass; 
    }
  }
}

/**************** hashtable_find ****************/
/*
 * See hashtable.h for description
 */
void* hashtable_find(hashtable_t* ht, const char* key)
{
  if (ht == NULL || key == NULL) {
    return NULL; 
  } else {
    int slot = hash_jenkins(key, ht->num_slots); 

    return set_find(ht->slots[slot], key);
  }
}

/**************** hashtable_print ****************/
/*
 * See hashtable.h for description
 */
void hashtable_print(hashtable_t* ht, FILE* fp, 
                     void (*itemprint)(FILE* fp, const char* key, void* item))
{
  if (fp != NULL) {
    if (ht != NULL) {
      fprintf(fp, "{\n"); 
      for (int i = 0; i < ht->num_slots; i++) {
        set_print(ht->slots[i], fp, (*itemprint));
      }
      fprintf(fp, "}\n"); 
    } else {
      fprintf(fp, "(null)"); 
    }
  }
}

/**************** hashtable_iterate ****************/
/*
 * See hashtable.h for description
 */
void hashtable_iterate(hashtable_t* ht, void* arg,
                       void (*itemfunc)(void* arg, const char* key, void* item) )
{
  if (ht != NULL || itemfunc != NULL) {
    for (int i = 0; i < ht->num_slots; i++) {
      set_iterate(ht->slots[i], arg, (*itemfunc)); 
    }
  }
}


/**************** hashtable_delete ****************/
/*
 * See hashtable.h for description
 */


/* Delete hashtable, calling a delete function on each item.
 *
 * Caller provides:
 *   valid hashtable pointer,
 *   valid pointer to function that handles one item (may be NULL).
 * We do:
 *   if hashtable==NULL, do nothing.
 *   otherwise, unless itemfunc==NULL, call the itemfunc on each item.
 *   free all the key strings, and the hashtable itself.
 * Notes:
 *   We free the strings that represent key for each item, because 
 *   this module allocated that memory in hashtable_insert.
 */
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) )
{
  if (ht != NULL) {
    for (int i = 0; i < ht->num_slots; i++) {
      set_delete(ht->slots[i], (*itemdelete)); 
    }
    mem_free(ht);
  }
  #ifdef MEMTEST
  mem_report(stdout, "End of hashtable_delete");
  #endif
}
