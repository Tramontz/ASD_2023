#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "skiplist.h"

int compare_string(const void *a, const void *b) {
    char **x = (char **)a;
    char **y = (char **)b;
    return strcmp(x, y);
}

void find_errors(FILE *dictfile, FILE *textfile, size_t max_height);

int main(int argc, char const *argv[]) {
  if (argc < 3) {
    printf("Usage: %s <in file>, %s <out file>, %d <K value>,\n", argv[1],argv[2],argv[3]);
    exit(EXIT_FAILURE);
}

char *p;
size_t max_height =strtol(argv[3], &p, 10);

FILE *dictfile = fopen(argv[1], "r");
if (!dictfile) {
    perror("Errore nell'apertura del file del dizionario");
    return EXIT_FAILURE;
}

FILE *textfile = fopen(argv[2], "r");
if (!textfile) {
    perror("Errore nell'apertura del file da correggere");
    fclose(dictfile);
    return EXIT_FAILURE;
}

find_errors(dictfile, textfile, max_height);

fclose(dictfile);
fclose(textfile);

return EXIT_SUCCESS;
}

void find_errors(FILE *dictfile, FILE *textfile, size_t max_height) {
    SkipList *dictionary;
    new_skiplist(&dictionary, max_height, compare_string);
    clock_t begin,end;
    char word[256];
    char text_word[256];
    char *readLine;

    begin = clock();
    while (fgets(word, sizeof(word), dictfile) != NULL) {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0'; // Rimuovi il newline
        }

        readLine = strdup(word);  // Alloca memoria per la copia della parola
        insert_skiplist(dictionary, readLine);
    }   
    end = clock();
    printf("\ntotal insert time with: max_height=%d | time: %f\n\n",max_height,(double)(end-begin)/CLOCKS_PER_SEC);

    begin = clock();
    while (fscanf(textfile, "%s", text_word) == 1) {
        size_t leng = strlen(text_word);
        if (leng > 0 && !isalpha(text_word[leng - 1])) {
            text_word[leng - 1] = '\0';
        }
        for (size_t i = 0; i < leng; i++) {
            text_word[i]=tolower(text_word[i]);//elimina eventuali Uppercase        
        }

        if (search_skiplist(dictionary, text_word) == NULL) {
            printf("%s\n", text_word);
        }          
    }
    end = clock();
    printf("\ntotal search time with: max_height=%d | time: %f\n\n",max_height,(double)(end-begin)/CLOCKS_PER_SEC);

    // Dealloca la SkipList dopo averla utilizzata
    clear_skiplist(&dictionary);
}