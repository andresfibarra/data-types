/* 
 * counters.c - CS50 'counters' module
 *
 * see counters.h for more information.
 *
 * Andres Ibarra, January 2022
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <limits.h>
#include "counters.h"
#include "mem.h"

/**************** file-local global variables ****************/
/* none */

/**************** local types ****************/
typedef struct counternode {
  int key; 
  int count; 
  struct counternode* next;   //link to next node
} counternode_t;

/**************** global types ****************/
typedef struct counters {
  struct counternode* head;       // head of the list of items in bag
} counters_t;

/**************** global functions ****************/
/* that is, visible outside this file */
/* see bag.h for comments about exported functions */

/**************** local functions ****************/
/* not visible outside this file */
static counternode_t* counternode_new(int key);

/**************** counters_new() ****************/
/* 
 * see counters.h for description 
 */
counters_t* counters_new(void)
{
  counters_t* ctrs = mem_malloc(sizeof(counters_t)); 

  if (ctrs == NULL) {
    return NULL; 
  } else {
    ctrs->head = NULL; 
    return ctrs; 
  }
}

/**************** counternode_new ****************/
/* 
 * Allocate and initialize a counternode
 * count is initialized to 1
 * not visible outside of this file
 */
static counternode_t* counternode_new(int key)
{
  counternode_t* node = mem_malloc(sizeof(counternode_t)); 

  if (node == NULL) {
    return NULL; 
  } else {
    node->key = key; 
    node->count = 1; 
    return node; 
  }
}

/**************** counters_add ****************/
/* 
 * see counters.h for description
 */
int counters_add(counters_t* ctrs, const int key)
{
  if (ctrs == NULL || key < 0) {
    return 0; 
  } else {
    if (counters_get(ctrs, key) == 0) { //if key not found
      counternode_t* new = counternode_new(key); 
      if (new != NULL) {
        new->next = ctrs->head; 
        ctrs->head = new; 
        return new->count; 
      }
      return 0; 
    } else {                            //if key found
      for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
        if (node->key == key) {
          if (node->count < INT_MAX) {
            node->count++;
          } else {
            fprintf(stderr, "count for key = %d at max", key); 
          }
          return node->count; 
        }
      }
    }
  }

  #ifdef MEMTEST
  mem_report(stdout, "End of counters_add");
  #endif

  return 0; 
}

/**************** counters_get ****************/
/*
 * see counters.h for description
 */
int counters_get(counters_t* ctrs, const int key)
{
  if (key < 0) {
    fprintf(stderr, "Please provide a key >= 0\n"); 
    return 0; 
  } else if (ctrs == NULL) {
    return 0; 
  } else {
    for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key) {
        return node->count; 
      }
    }
  }
  return 0;     //return 0 if key not found
}

/**************** counters_set ****************/
/*
 * see counters.h for description
 */
bool counters_set(counters_t* ctrs, const int key, const int count)
{
  if (ctrs == NULL || key < 0 || count < 0) {
    return false;
  } else {
    if (counters_get(ctrs, key) == 0) { 
      counters_add(ctrs, key); //create counter if key does not yet exist
    }
    for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
      if (node->key == key) {
         node->count = count; 
         return true; 
      }
    }
    return false; 
  }
}

/**************** counters_print ****************/
/*
 * see counters.h for description
 */
void counters_print(counters_t* ctrs, FILE* fp) {
  if (fp != NULL) {
    if (ctrs != NULL) {
      fputc('{', fp); 
      for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
        fprintf(fp, "(%d=%d)", node->key, node->count); 
        if (node->next != NULL) {
          fputc(',', fp); 
        }
      }
      fprintf(fp, "}\n"); 
    } else {
      printf("(null)\n"); 
    }
  }
}

/**************** counters_iterate ****************/
/* 
 * See counters.h for description
 */
void counters_iterate(counters_t* ctrs, void* arg, 
                      void (*itemfunc)(void* arg, 
                                       const int key, const int count))
{
  if (ctrs != NULL && itemfunc != NULL) {
    //call itemfunc on each item
    for (counternode_t* node = ctrs->head; node != NULL; node = node->next) {
      (*itemfunc)(arg, node->key, node->count); 
    }
  }
}

/**************** counters_delete ****************/
/* 
 * See counters.h for description
 */


/* Delete the whole counterset.
 *
 * Caller provides:
 *   a valid pointer to counterset.
 * We do:
 *   we ignore NULL ctrs.
 *   we free all memory we allocate for this counterset.
 */
void counters_delete(counters_t* ctrs)
{
  if (ctrs != NULL) {
    for (counternode_t* node = ctrs->head; node != NULL; ) {
      counternode_t* next = node->next; 
      mem_free(node); 
      node = NULL; 
      node = next; 
    }
    mem_free(ctrs); 
    ctrs = NULL; 
  }

  #ifdef MEMTEST
  mem_report(stdout, "End of counters_delete");
  #endif
}