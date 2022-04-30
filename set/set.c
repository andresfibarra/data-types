/* 
 * set.c - CS50 'set' module
 *
 * see set.h for more information.
 *
 * Andres Ibarra, January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include "set.h"
#include "../lib/mem.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct setnode {
  char* key;                  // pointer to key for this item
  void* item;                 // pointer to data for this item
  struct setnode* next;       // link to next node
} setnode_t;

/**************** global types ****************/
typedef struct set {
  struct setnode* head;       // head of the list of items in bag
} set_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see bag.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static setnode_t* setnode_new(const char* key, void* item);

/**************** set_new() ****************/
/* see set.h for description */
set_t* set_new(void)
{
  set_t* set = mem_malloc(sizeof(set_t));

  if (set == NULL) {
    return NULL;              // error allocating set
  } else {
    // initialize contents of set structure
    set->head = NULL;
    return set;
  }
}

/**************** set_insert() ****************/
/* see set.h for description */
bool set_insert(set_t* set, const char* key, void* item)
{

  if (set == NULL || key == NULL || item == NULL) {
    return false; 
  } else {
    if (set_find(set, key) != NULL) {    //check if key already exists
      return false; 
    } else {
      char* keyCopy; 
      keyCopy = (char*) mem_malloc(sizeof(char) * (strlen(key) + 1));
      strcpy(keyCopy, key);
      setnode_t* new = setnode_new(keyCopy, item);
      mem_free(keyCopy); 
      keyCopy = NULL; 
      if (new != NULL) {
        // add it to the head of the list
        new->next = set->head;
        set->head = new;
      }
      else {
        return false; 
      }
    }
  }

  #ifdef MEMTEST
    mem_report(stdout, "After set_insert");
  #endif

  return set->head != NULL; //true if successful insertion
}

/**************** setnode_new ****************/
/* 
 * Allocate and initialize a bagnode
 * not visible outside of this file
 * Caller is reponsible for: 
 *  later calling set_delete to free the memory for node
 */
static setnode_t*  setnode_new(const char* key, void* item)
{
  setnode_t* node = mem_malloc(sizeof(setnode_t));

  if (node == NULL) {
    // error allocating memory for node; return error
    return NULL;
  } else {
    node->key = mem_malloc(strlen(key)+1); 
    if (node->key == NULL) {
      //error allocating memory for key
      mem_free(node); 
      return NULL; 
    } else {
      strcpy(node->key, key); 
      node->item = item;
      node->next = NULL;
      return node;
    }
  }
}

/**************** set_extract() ****************/
/* see set.h for description */
void* set_find(set_t* set, const char* key) 
{
  if (set != NULL && key != NULL) {
    setnode_t* tempNode = set->head; 
    while (tempNode != NULL) {
      if (strcmp(key, tempNode->key) == 0) {    //if they are equal
        return tempNode->item; 
      } else {
        tempNode = tempNode->next; 
      }
    }
    return NULL;    //return NULL if the key is never found
  } else {
    return NULL; 
  }
}

/**************** set_print ****************/
/* 
 * See set.h for description
 */
void set_print(set_t* set, FILE* fp, 
               void (*itemprint)(FILE* fp, const char* key, void* item) )
{
  if (fp != NULL) {
    if (set != NULL) {
      fputc('{', fp); 
      for (setnode_t* node = set->head; node != NULL; node = node->next) {
        //print this node
        if (itemprint != NULL) {
          (*itemprint)(fp, node->key, node->item); 
          if (node->next != NULL) {
            fputc(',', fp); 
          }
        }
        else {
          break;
        }
      }
      fprintf(fp, "}\n"); 
    } else {
      fputs("(null)", fp); 
    }
  }
}

/**************** set_iterate ****************/
/* 
 * See set.h for description
 */
void set_iterate(set_t* set, void* arg,
                 void (*itemfunc)(void* arg, const char* key, void* item) )
{
  if (set != NULL && itemfunc != NULL) {
    // call itemfunc on each item
    for (setnode_t* node = set->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->item); 
    }
  }
}

/**************** set_delete ****************/
/* 
 * See set.h for description
 */
void set_delete(set_t* set, void (*itemdelete)(void* item) ) {
  if (set != NULL) {
    for (setnode_t* node = set->head; node != NULL; ) {
      if (itemdelete != NULL) {
        (*itemdelete)(node->item); 
      }
      setnode_t* next = node->next; 
      mem_free(node->key); 
      node->key = NULL; 
      mem_free(node); 
      node = NULL; 
      node = next; 
    }
    mem_free(set); 
    set = NULL; 
  }
  #ifdef MEMTEST
  mem_report(stdout, "End of set_delete");
  #endif
}