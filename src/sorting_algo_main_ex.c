#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "struct_array.h"
#include "sorting_algo.h"

/* The struct record represent the set-structure of the given file tomerge
in this case, i decided to use double typer for the floating point field 
as common practice to have more precision.
*/
struct record{
  int id;
  char* string_field_1;
  int integer_field_2;
  double float_field_3;
};


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
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
  if(rec1_p->integer_field_2 < rec2_p->integer_field_2){
    return(1);
  }
  return(0);
}

/*It takes as input two pointers to struct record.
It returns 1 if the string field of the first record is less than 
the string field of the second one (0 otherwise)
*/
/*static int precedes_record_string_field(void* r1_p,void* r2_p){
  printf("sono nel precede1\n");
  if(r1_p == NULL){
    fprintf(stderr,"precedes_string: the first parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  if(r2_p == NULL){
    fprintf(stderr,"precedes_string: the second parameter is a null pointer");
    exit(EXIT_FAILURE);
  }
  struct record *rec1_p = (struct record*)r1_p;
  struct record *rec2_p = (struct record*)r2_p;
   printf("Record 1: ID=%d, String=%s, Integer=%d, Float=%lf\n", rec1_p->id, rec1_p->string_field_1, rec1_p->integer_field_2, rec1_p->float_field_3);
    printf("Record 2: ID=%d, String=%s, Integer=%d, Float=%lf\n", rec2_p->id, rec2_p->string_field_1, rec2_p->integer_field_2, rec2_p->float_field_3);

  if(strcmpi(rec1_p->string_field_1,rec2_p->string_field_1)<0){
    return(1);
  }
  return(0);
}*/
static int precedes_record_string_field( void* r1_p,  void* r2_p) {
  if (r1_p == NULL || r2_p == NULL) {
    fprintf(stderr, "precedes_record_string_field: one of the parameters is a null pointer\n");
    exit(EXIT_FAILURE);
  }
  printf("r1_p: %p\n", r1_p);
  printf("r2_p: %p\n", r2_p);

  struct record* rec1_p = r1_p;
  struct record* rec2_p = r2_p;
  printf("rec1_p: %p\n", rec1_p);
  printf("rec2_p: %p\n", rec2_p);
  printf("Record 1: ID=%d",rec1_p->id);
  printf("Record 2: ID=%d, ", rec2_p->id);

  printf("Record 1: ID=%d, String=%s, Integer=%d, Float=%f\n", rec1_p->id, rec1_p->string_field_1, rec1_p->integer_field_2, rec1_p->float_field_3);
  sleep(1);
  printf("Record 2: ID=%d, String=%s, Integer=%d, Float=%f\n", rec2_p->id, rec2_p->string_field_1, rec2_p->integer_field_2, rec2_p->float_field_3);
  sleep(20);

    // Usa strcmp per confrontare le stringhe e restituisci il risultato
    return; //strcmp(rec1_p->string_field_1, rec2_p->string_field_1);
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
    struct record *rec1_p = (struct record*)r1_p;
    struct record *rec2_p = (struct record*)r2_p;
    if(rec1_p->float_field_3 < rec2_p->float_field_3){
      return(1);
    }
    return(0);
  }

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
      printf("inizio a leggere: Read Line: %s\n", read_line_p);
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

      struct record *record_p = malloc(sizeof(struct record));
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
      printf("sto aggiungendo la stringa: %s\n", record_p->string_field_1);
      printf("IN POSIZIONE%d\n", struct_array_size(array));
      struct_array_add(array, record_p);
      printf("SIZE DELL'ARRAY%d\n\n\n\n", struct_array_size(array));

      free(read_line_p);
    }
    fclose(fp);
    printf("\nData loaded\n");
  }

  static  void free_array(StructArray* array) {
    unsigned long  el_num =  struct_array_size(array);
    for(unsigned long i=0;i<el_num;i++){
      struct record *array_element = (struct record *)struct_array_get(array, i);
      free(array_element->string_field_1);
      free(array_element);
    }
    struct_array_free_memory(array);
  }

  static  void print_array(StructArray* array){
    unsigned long el_num =  struct_array_size(array);

    struct record *array_element;

    printf("\nstruct ARRAY OF RECORDS\n");

    for(unsigned long i=0;i<el_num;i++){
      array_element = (struct record *)struct_array_get(array, i);
      printf("<POSIZION:%d, ID:%d, String:%s, Integer:%d, Float:%lf >\n",i,array_element->id,array_element->string_field_1,array_element->integer_field_2,array_element->float_field_3); 
    }
  }

  static void sort_records(FILE *infile, FILE *outfile, size_t k, size_t field) {
    StructArray* array = struct_array_create();
    load_array(infile, array);
    print_array(array);
    printf("prima dello switch\n");
    printf("quanti elementi ha array? %d\n", struct_array_size(array));

    switch (field) {
    case 1:
      merge_binary_insertion_sort(struct_array_get(array,0), struct_array_size(array), sizeof(struct record), k, precedes_record_string_field);
      printf("selezione per char");
      break;
    case 2:
      merge_binary_insertion_sort(array, struct_array_size(array), sizeof(int), k, precedes_record_int_field);
      printf("selezione per int");

      break;
    case 3:
      merge_binary_insertion_sort(array, struct_array_size(array), sizeof(double), k, precedes_record_float_field);
      printf("selezione per float");

      break;
    default:
      printf("invalid field orders.\n");
          // Qui inserisci il codice per gestire un'opzione non valida
      break;
    }  
    print_array(array);
  //da creare infile outfile;
    free_array(array);
  }

//It should be invoked with one parameter specifying the filepath of the data file
  int main(int argc, char const *argv[]) {
    if (argc < 2) {
      printf("Utilizzo: %s <nome_file>\n", argv[0]);
      exit(EXIT_FAILURE);
    }

    int field = 0;
    size_t k = 0;
    char* outFile[1024];

    do {
      printf("Seleziona il campo per l'ordinamento:\n1. Campo Stringa\n2. Campo Intero\n3. Campo Float\n");
      scanf("%d", &field);
    } while (field < 1 || field > 3);

    printf("Inserisci il percorso del file di output: ");
    scanf("%s", outFile);

    printf("Inserisci un valore appropriato per 'k': ");
    scanf("%lu", &k);

    sort_records(argv[1], outFile, k, field);

    return EXIT_SUCCESS;

/*struct record *record_p = malloc(sizeof(struct record));
struct record *record_t = malloc(sizeof(struct record));

  StructArray* array = struct_array_create();
    record_p->id = 01;
    record_p->string_field_1 = "prova";
    record_p->integer_field_2 = 40;
    record_p->float_field_3 = 12.33;
struct_array_add(array,record_p);
record_t=struct_array_get(array,0);
printf("%s\n", record_p->string_field_1);
printf("%d\n", record_p->integer_field_2);
printf("%f\n", record_p->float_field_3);
free(record_p);
free(record_t);
free(array);*/
  }
