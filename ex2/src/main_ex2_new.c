#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "skiplist.h"

void find_errors(FILE *dictfile, FILE *textfile, size_t max_height);

int main(int argc, char *argv[]) {
    if (argc != 4) {
        fprintf(stderr, "Utilizzo: %s <dictfile> <textfile> <max_height>\n", argv[0]);
        return EXIT_FAILURE;
    }

    const char *dictfile_name = argv[1];
    const char *textfile_name = argv[2];
    size_t max_height = (size_t)atoi(argv[3]);

    FILE *dictfile = fopen(dictfile_name, "r");
    if (!dictfile) {
        perror("Errore nell'apertura del file del dizionario");
        return EXIT_FAILURE;
    }

    FILE *textfile = fopen(textfile_name, "r");
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
    new_skiplist(dictionary, max_height, (int(*)(const void *, const void *))strcmp);

    char word[256];
    while (fgets(word, sizeof(word), dictfile)) {
        size_t len = strlen(word);
        if (len > 0 && word[len - 1] == '\n') {
            word[len - 1] = '\0'; // Rimuovi il newline
        }printf("%s",len);
        insert_skiplist(dictionary, word);
    }void print_skiplist(dictionary);

    char text_word[256];
    while (fscanf(textfile, "%s", text_word) == 1) {
        if (search_skiplist(dictionary, text_word) == NULL) {
            printf("%s\n", text_word);
        }
    }

    clear_skiplist(dictionary);
}