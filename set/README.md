# Andres Ibarra
## CS50 Spring 2021, Lab 3

GitHub username: @andresfibarra

### set

A `set` maintains an unordered collection of _(key,item)_ pairs; any 
given _key_ can only occur in the `set` once. It starts out empty and 
grows as the caller inserts new _(key,item)_ pairs. The caller can 
retrieve _items_ by asking for their _key_, but cannot remove or 
update pairs. _Items_ are distinguished by their _key_.

### Usage

The _set_ module, defined in `set.h` and implemented in `set.c`, 
implements a `set` of _(key, item)_ pairs. _Items_ are of type `void*` 
while _keys_ must be of type `char*`. 
The module exports the following functions: 

```c
set_t* set_new(void);
bool set_insert(set_t* set, const char* key, void* item);
void* set_find(set_t* set, const char* key);
void set_print(set_t* set, FILE* fp, void (*itemprint)(FILE* fp, const char* key, void* item) );
void set_iterate(set_t* set, void* arg, void (*itemfunc)(void* arg, const char* key, void* item) );
void set_delete(set_t* set, void (*itemdelete)(void* item) );
```

### Implementation

We implemented this set with a linked list. Much of the code from this
module is based on the code from the `bag` module provided with the
lab 3 starter kit
The _set_ itself is represented as a `struct set` containing a pointer to the head of the list. The head pointer is NULL when the bag is empty. 

Each node in the list is a `struct setnode`, a type defined internally to the module. 
Each setnode contains a pointer to the `char* key`, a pointer to the `void* item`, and a pionter to the next setnode in the list. 

To insert a new item in the set, we create a new setnode to hold the `item` and insert it at the head of othe list. 

To find an `item` in the set, we loop through the nodes, stopping when 
the required `item` is found or when the end of the list. If the `item` 
is found, it is returned. Otherwise (or if an error is encountered), 
NULL is returned. 

The `set_print` method prints a little syntax around the list, and between items, but mostly calls the `itemprint` function on each item by looping through the linked list.

The `set_iterate` method calls the `itemfunc` function on each item by looping through the linked list.

The `set_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing bagnodes as it proceeds.
It concludes by freeing the `struct set`.

### Assumptions

No assumptions beyond those that are clear from the spec.

### Files
* `Makefile` - compilation procedure
* `set.h` - the interface
* `set.c` - the implementation
* `settest.c` - unit test driver
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compily, simple `make set.o`

### Remaining Bugs

When running `make test`, this bug appears

```
free(): double free detected in tcache 2
Makefile:28: recipe for target 'test' failed
make: *** [test] Aborted (core dumped)
```

However, `mem_report` also prints at the end of the file: `End of set_delete: 13 malloc, 13 free, 0 free(NULL), 0 net`. 
I have discovered that if line 173 of settest.c ( the line `mem_free(item);`, contained in the `stringItemDelete` function ) is commented out, this error no longer appear. 
However, commenting this line out also causes there to be memory leaks in the code. Unfortunately, I did not have enough time to debug this.