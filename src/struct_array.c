#include <stdlib.h>
#include <stdio.h>
#include "struct_array.h"

//Initial capacity for the array
#define INITIAL_CAPACITY 2


//static unsigned long  get_index_to_insert(StructArray *struct_array, void* element);
//static void insert_element(StructArray *struct_array, void* element,unsigned long index);

//It represents the internal structure of this implementation of struct arrays
struct _StructArray{
  void**array;
  unsigned long el_num;
  unsigned long array_capacity;
};


StructArray *struct_array_create(){
  StructArray *struct_array = (StructArray *)malloc(sizeof(StructArray));
  if(struct_array == NULL){
    fprintf(stderr, "struct_array_create: unable to allocate memory for the struct array");
    exit(EXIT_FAILURE);
  }
  struct_array->array = (void**)malloc(INITIAL_CAPACITY*sizeof(void*));
  if(struct_array->array == NULL){
    fprintf(stderr, "struct_array_create: unable to allocate memory for the internal array");
    exit(EXIT_FAILURE);
  }
  struct_array->el_num = 0;
  struct_array->array_capacity =INITIAL_CAPACITY;

  return(struct_array);
}


int struct_array_is_empty(StructArray *struct_array){
  if(struct_array == NULL){
    fprintf(stderr,"struct_array_is_empty: struct_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(struct_array->el_num == 0)
    return(1);
  return(0);
}


unsigned long struct_array_size(StructArray *struct_array){
  if(struct_array == NULL){
    fprintf(stderr,"struct_array_size: struct_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return(struct_array->el_num);
}


void struct_array_add(StructArray *struct_array, void* element){
  if(struct_array == NULL){
    fprintf(stderr,"add_struct_array_element: struct_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(element == NULL){
    fprintf(stderr,"add_struct_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }

  if(struct_array->el_num >= struct_array->array_capacity){
    struct_array->array = (void**)realloc(struct_array->array,2*(struct_array->array_capacity)*sizeof(void*));
    if(struct_array->array == NULL){
      fprintf(stderr,"struct_array_add: unable to reallocate memory to host the new element");
      exit(EXIT_FAILURE);
    }
    struct_array->array_capacity = 2*struct_array->array_capacity;
  }

  (struct_array->array)[struct_array->el_num] = element;
  (struct_array->el_num)++;
}


void* struct_array_get(StructArray *struct_array){
  if(struct_array == NULL){
    fprintf(stderr,"struct_array_get: struct_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  return (struct_array->array);
}

void struct_array_set(StructArray *struct_array, unsigned long index, void* element){
  if(struct_array == NULL){
    fprintf(stderr,"add_struct_array_element: struct_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(element == NULL){
    fprintf(stderr,"add_struct_array_element: element parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  if(index>=struct_array->el_num){
    fprintf(stderr,"struct_array_get: Index %lu is out of the array bounds",index);
    exit(EXIT_FAILURE);
  }
  struct_array->array[index]=element;
}

void struct_array_free_memory(StructArray *struct_array){
  if(struct_array == NULL){
    fprintf(stderr,"struct_array_free_memory: struct_array parameter cannot be NULL");
    exit(EXIT_FAILURE);
  }
  free(struct_array->array);
  free(struct_array);
}