# Andres Ibarra
## CS50 Spring 2021, Lab 3

GitHub username: @andresfibarra

### hashtable

A `hashtable` is a set of (_key_,_item_) pairs. It acts just like a `set`, but is far more efficient for large collections. 


### Usage

The _hashtable_ module, defined in `hashtable.h` and implemented in `hashtable.c`, implements an _array_ of pointers to _sets_.
It also holds an integer `num_slots` to use when the number of slots is required
The module exports the following functions: 

```c
hashtable_t* hashtable_new(const int num_slots);
bool hashtable_insert(hashtable_t* ht, const char* key, void* item);
void* hashtable_find(hashtable_t* ht, const char* key);
void hashtable_print(hashtable_t* ht, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item));
void hashtable_iterate(hashtable_t* ht, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void hashtable_delete(hashtable_t* ht, void (*itemdelete)(void* item) );
```

### Implementation


This module is implemented using an _array_. Collisions are resolved using chaining. Therefore, each entry in the _array_ is a `set` from the `set` module. Much of the code in the module is based on code from `bag` module provided with the lab 3 starter kit. 

The hash function itself was provided with the starter kit. 

The _hashtable_ itself is represented as a `struct hashtable` containing an _array_ of pointers to _sets_ and an integer holding the number of slots in the array. 

To insert a new item in the set, we loop through the slots in the _array_, calling `set_new` in each

To insert into the _hashtable_, we use the provided hashing function to determine which slot to use. Then we use call `set_insert` to insert a new node into that list. 

Finding in the hashtable uses the provided hashing function to return the associated _item_ to the provided _key_

The `hashtable_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by looping through the linked list. It prints one set per line

The `hashtable_iterate` method calls the `itemfunc` function on each item by looping through the slots in the array, then uses `set_iterate` to loop through linked list.

The `hashtable_delete` method calls the `set_delete` function on each slot. 
It concludes by freeing the `struct hashtable`.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files
* `Makefile` - compilation procedure
* `hash.h` - the inferface for provided Jenkin's hash function
* `hash.c` - the implementation of the provided Jenkin's hash function
* `hashtable.h` - the interface
* `hashtable.c` - the implementation
* `hashtabletest.c` - unit test driver
* `testWords` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compily, simple `make hashtable.o`

### Remaining Bugs

When running `make test`, according to mem_report, there is one extra free, with a -1 net. I was not able to find out the cuase of this bug. 