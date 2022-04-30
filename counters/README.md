# Andres Ibarra
## CS50 Spring 2021, Lab 3

GitHub username: @andresfibarra

### counters

A `counter set` is a set of counters, each distinguished by an integer _key_. It's a set - each _key_ can only occur once in the set - and it tracks a counter for each _key_. It starts empty. Each time `counters_add` is called on a given key, the corresponding _counter_ is incremented. The current counter value can be retrieved by asking for the relevant key.

### Usage

The _counter_ module, defined in `counters.h` and implemented in `counters.c`, implements a `counter set` of _(key, count)_ pairs. Both _keys_ and _counts_ are of type `int`, with both being non-negative
The module exports the following functions: 

```c
counters_t* counters_new(void);
int counters_add(counters_t* ctrs, const int key);
int counters_get(counters_t* ctrs, const int key);
bool counters_set(counters_t* ctrs, const int key, const int count);
void counters_print(counters_t* ctrs, FILE* fp);
void counters_iterate(counters_t* ctrs, void* arg, void (*itemfunc)(void* arg, const int key, const int count));
void counters_delete(counters_t* ctrs);
```

### Implementation

We implemented this set with a linked list. Much of the code from this
module is based on the code from the `bag` module provided with the
lab 3 starter kit
The _set_ itself is represented as a `struct counters` containing a pointer to the head of the list. The head pointer is NULL when the bag is empty. 

Each node in the list is a `struct counternode`, a type defined internally to the module. 
Each _counternode_ contains an `int key`, an `int count`, and a ponter to the next _counternode_ in the list. 

The `counters_add` method acts differently depending on the key. If the key already exists in the `counter set`, then the count of that node is incremented. If it does not exist already, we create a new _counternode_ to hold that `key` and insert it at the head of the list.

To _get_ an `count` in the set, we loop through the nodes, stopping when 
the required `key` is found or when the end of the list. If the `key` 
is found, the corresponding `count` is returned. Otherwise (or if an error is encountered), NULL is returned. 

The `counters_set` method sets the _count_ with specified `key` to be `count`. If the key is not found, a new counter is initialized and set to value `count`. 

The `counters_print` method prints a comma separated list of _key_=_counter_ pairs, all in brackets

The `counters_iterate` method calls the `itemfunc` function on each item by looping through the linked list.

The `counters_delete` method calls the `itemdelete` function on each item by scanning the linked list, freeing bagnodes as it proceeds.
It concludes by freeing the `struct counters`.

### Assumptions

In `counterstest.c`, when integers are taken from stdin, the input is assumed to only be integers separated by white space. Additionally, the input is assumed to be entirely non-negative. 

### Files
* `Makefile` - compilation procedure
* `counters.h` - the interface
* `counters.c` - the implementation
* `counterstest.c` - unit test driver
* `testNums` - test data
* `testing.out` - result of `make test &> testing.out`

### Compilation

To compile, simply `make counters.o`

### Remaining Bugs

I was unable to figure out how to check if out of memory in `counters_set`