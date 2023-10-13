#ifndef STRUCT_ARRAY_H_ispuniproject
#define STRUCT_ARRAY_H_ispuniproject

//An array of any number of elements of any kind, struct in non descending order
//according to a specific precedence relation.
typedef struct _StructArray StructArray;

//It creates an empty struct array and returns the created struct array.
//It accepts as input a pointer to a function implementing the 
//precedence relation between the array elements. 
//Such a function must accept as input two pointers to elements and
//return 0 iff the first element does not precede the second one and
//a number different from zero otherwise.
//The input parameter cannot be NULL.
StructArray *struct_array_create();

//It accepts as input a pointer to an struct array and it returns 1 iff
//the struct array is empty (0 otherwise).
//The input parameter cannot be NULL.
int struct_array_is_empty(StructArray *);

//It accepts as input a pointer to an struct array and it
//returns the number of elements currently stored into the array.
//The input parameter cannot be NULL.
unsigned long struct_array_size(StructArray *);

//It accepts as input a pointer to an struct array and a pointer to an element. It adds
//the element to the struct array in the right position. 
//The input parameters cannot be NULL.
void struct_array_add(StructArray *, void*);

//It accepts as input a pointer to an struct array and an integer "i" and
//it returns the pointer to the i-th element of the struct array
//The first parameter cannot be NULL; the second parameter must be a valid position 
//within the orderd array.
void* struct_array_get(StructArray *, unsigned long);

//It accepts as input a pointer to an struct array and an integer "index" and
//it set the value in the index position to passed element 
//The first parameter cannot be NULL; 
void struct_array_set(StructArray *, unsigned long , void* );

//It accepts as input a pointer to an struct array and 
//it frees the memory allocated to store the struct array. 
//It does not free the memory allocated to store the array elements,
//since freing that memory is responsibility of the function where
//the struct array was created.
//The input parameters cannot be NULL.
void struct_array_free_memory(StructArray *);

#endif /* STRUCT_ARRAY_H_laokjsdnbudjllvfidkfmqm */
