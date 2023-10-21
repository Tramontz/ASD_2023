#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "struct_array.h"
#include "sorting_algo.h"

/* The struct record represent the set-structure of the given file tomerge
in this case, i decided to use double typer for the floating point field 
as common practice to have more precision.
*/
typedef struct{
  int id;
  char* string_field_1;
  int integer_field_2;
  double float_field_3;
}record;


/*It takes as input two pointers to struct record.
It returns 1 if the integer field of the first record is less than 
the integer field of the second one (0 otherwise)
*/
static int precedes_record_int_field(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_int_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_int_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  record *rec1_p = ( record*)r1_p;
  record *rec2_p = ( record*)r2_p;
  if(rec1_p->integer_field_2 < rec2_p->integer_field_2){
    return(1);
  }
  return(0);
}

/*It takes as input two pointers to struct record.
It returns 1 if the string field of the first record is less than 
the string field of the second one (0 otherwise)
*/

static int precedes_record_string_field( const void* r1_p,  const void* r2_p) {
  if (r1_p == NULL || r2_p == NULL) {
    fprintf(stderr, "precedes_record_string_field: one of the parameters is a null pointer\n");
    exit(EXIT_FAILURE);
  }

  const record* rec1_p = (const record*)r1_p;
  const record* rec2_p = (const record*)r2_p;

    // Usa strcmp per confrontare le stringhe e restituisci il risultato
  return strcmp(rec1_p->string_field_1, rec2_p->string_field_1);
}

/*It takes as input two pointers to struct record.
It returns 1 if the float field of the first record is less than 
the float field of the second one (0 otherwise)
*/
static int precedes_record_float_field(void* r1_p,void* r2_p){
  if(r1_p == NULL){
    fprintf(stderr,"precedes_record_float_field: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_record_float_field: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  record *rec1_p = ( record*)r1_p;
  record *rec2_p = ( record*)r2_p;
  if(rec1_p->float_field_3 < rec2_p->float_field_3){
    return(1);
  }
  return(0);
}
/*it take in imput a file, parse it using ';' separator to recognise the 4 field, an put them
into an array of record object
*/
static void load_array(const char* file_name, StructArray* array){
  char *read_line_p;
  char buffer[1024];
  int buf_size = 1024;
  FILE *fp;
  printf("\nLoading data from file...\n");
  fp = fopen(file_name,"r");
  if(fp == NULL){
    fprintf(stderr,"main: unable to open the file");
    exit(EXIT_FAILURE);
  }
  while(fgets(buffer,buf_size,fp) != NULL){  
    read_line_p = malloc((strlen(buffer)+1)*sizeof(char));
    if(read_line_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read line");
      exit(EXIT_FAILURE);
    }   
    strcpy(read_line_p,buffer);   
    char *id_field_in_read_line_p = strtok(read_line_p,",");
    char *string_field_in_read_line_p = strtok(NULL,",");  
    char *integer_field_in_read_line_p = strtok(NULL,","); 
    char *float_field_in_read_line_p = strtok(NULL,","); 
    char *string_field = malloc((strlen(string_field_in_read_line_p)+1)*sizeof(char));
    if(string_field == NULL){
      fprintf(stderr,"main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }  
    strcpy(string_field,string_field_in_read_line_p);
    int id_field = atoi(id_field_in_read_line_p);
    int integer_field = atoi(integer_field_in_read_line_p);
    double float_field = strtod(float_field_in_read_line_p,NULL);  
    record *record_p = malloc(sizeof(record));
    if(record_p == NULL){
      fprintf(stderr,"main: unable to allocate memory for the read record");
      exit(EXIT_FAILURE);
    }   
    record_p->id = id_field;
    record_p->integer_field_2 = integer_field;
    record_p->float_field_3 = float_field;

        // Alloca memoria per la stringa e copiala
    record_p->string_field_1 = malloc((strlen(string_field) + 1) * sizeof(char));
    if (record_p->string_field_1 == NULL) {
      fprintf(stderr, "main: unable to allocate memory for the string field of the read record");
      exit(EXIT_FAILURE);
    }
    strcpy(record_p->string_field_1, string_field);
    struct_array_add(array, record_p);
    free(read_line_p);
  }
  fclose(fp);
  printf("\nData loaded\n");
}
/*free memori from string, record and StructArray object
*/
static  void free_array(StructArray* array) {
  unsigned long  el_num =  struct_array_size(array);
  for(unsigned long i=0;i<el_num;i++){
   record **array_element = (record *)struct_array_get(array);
   free(array_element[i]->string_field_1);
   free(array_element);
 }
 struct_array_free_memory(array);
}

static void write_array(char* path, StructArray *array){
  printf("writing file...\n");
  FILE *ordered = fopen(path, "w");
  record *array_element=malloc(sizeof (record));
  void ** record_array=struct_array_get(array);    
  for (int i = 0; i < struct_array_size(array); i++){
    array_element = (record *)record_array[i];
    fprintf(ordered, "%d;%s;%d;%f\n", array_element->id,array_element->string_field_1,array_element->integer_field_2,array_element->float_field_3);
  }
  printf("file created\n");
  fclose(ordered);
}
/*it take a StructArray as imput and print all the field of 
every single object contained in the array of record
*/
static  void print_array(StructArray* array){
  unsigned long el_num =  struct_array_size(array);
  record *array_element=malloc(sizeof (record));
  void ** record_array=struct_array_get(array);
  printf("\nstruct ARRAY OF RECORDS\n");
  for(unsigned long i=0;i<el_num;i++){
    array_element = (record *)record_array[i];
    printf("<POSIZION:%d, ID:%d, String:%s, Integer:%d, Float:%lf >\n",i,array_element->id,array_element->string_field_1,array_element->integer_field_2,array_element->float_field_3); 
  }
}
/*It takes as input a StructArray, a k-value and the field reference,
and order the array of record contained in the struct array based on the field
and using k to decide when use merge sort annd when use the insertion sort
*/
static void sort_records(StructArray* array, size_t k, size_t field) {
  switch (field) {
  case 1:
    printf("sorting by string...");
    merge_binary_insertion_sort(struct_array_get(array), struct_array_size(array), k, precedes_record_string_field);
    break;
  case 2:
    printf("sorting by integer...");
    merge_binary_insertion_sort(struct_array_get(array), struct_array_size(array),  k, precedes_record_int_field);
    break;
  case 3:
    printf("sorting by float...");
    merge_binary_insertion_sort(struct_array_get(array), struct_array_size(array), k, precedes_record_float_field);
    break;
  default:
    printf("invalid field orders.\n");
    exit(EXIT_FAILURE);
    break;
  }  

}

/*It should be invoked with 4 param:
- path of the file to order
- path output file
- k value
- field reference for the ordering (1=String field, 2=Int Field, 3=float field)
*/
int main(int argc, char const *argv[]) {
  if (argc < 4) {
    printf("Usage: %s <in file>, %s <out file>, %d <K value>,%d <field ordering ref>\n", argv[1],argv[2],argv[3],argv[4]);
    exit(EXIT_FAILURE);
  }
  char *p;
  size_t k = strtol(argv[3], &p, 10);
  size_t field = strtol(argv[4], &p, 10);

  printf("\nfile to order: %s\n",argv[1]);
  printf("\noutput file location: %s\n", argv[2]);
  printf("\nK value selected: %d\n", k);
  printf("\nfield to order: %d \npress enter to start, ctrl+c to exit", field);
  getchar();
  
  StructArray* array = struct_array_create();    
  load_array(argv[1], array);
  clock_t begin = clock();
  sort_records(array, k, field);
  clock_t end = clock();
  printf("total time: %f\n",(double)(end-begin)/CLOCKS_PER_SEC); 
  write_array(argv[2],array);
  free_array(array);
  return EXIT_SUCCESS;
}
