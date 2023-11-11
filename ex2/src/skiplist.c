#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "skiplist.h"

/*
  struct Node  Array di puntatori in un dato nodo della SkipList
  size_t size  Numero di puntatori in un dato nodo della SkipList
  void *item;  Dato memorizzato in un dato nodo della SkipList
*/
typedef struct _Node{
    Node **next;
    size_t size;
    void *item;
}Node;

/*definizione Struttura dati SkipList:
-   struct Nodestruct Node **heads  Puntatori di inizio della SkipList per ogni livello fino a max_height
-   size_t max_level;     massimo numero di puntatori che al momento ci sono in un singolo nodo della SkipList
-   size_t max_height;    costante che definisce il massimo numero di puntatori che possono esserci in un singolo nodo della SkipList
-   int (*compare)(const void*, const void*); criterio secondo cui ordinare i dati (dati due puntatori a elementi)
*/
typedef struct _SkipList{
    Node **heads;
    size_t max_level;
    size_t max_height;
    int (*compare)(const void *, const void *);
}SkipList;

double random_probability() {
    return (double)rand() / RAND_MAX;
}

/* Genera casualmente un numero tra 0 e 1 utilizzando la funzione random_probability.
    Se il numero generato è inferiore a 0.5 e il livello attuale è inferiore al massimo 
    consentito (max_height), aumenta il livello di 1 e ripete il processo.
    Restituisce il livello risultante.

In altre parole, la funzione determina casualmente il livello di un nodo in base a una 
probabilità. La probabilità di aumentare il livello diminuisce man mano che il livello aumenta, 
poiché il valore generato deve essere inferiore a 0.5 ad ogni passaggio. Questo aiuta a 
ottenere una distribuzione casuale dei livelli in modo che i livelli più alti siano 
meno comuni dei livelli più bassi.*/

size_t random_level(size_t max_height) {
    size_t level = 1;
    while (random_probability() < 0.5 && level < max_height) {
        level++;
    }
    return level;
}

Node *create_node(void *item, size_t level) {
    Node *newNode = (Node *)malloc(sizeof(Node));
    if (!newNode) {
        fprintf(stderr, "Errore nell'allocazione del nodo.\n");
        exit(EXIT_FAILURE);
    }
    newNode->item = item;
    newNode->size = level;
    newNode->next = (Node **)malloc(level * sizeof(Node *));
    if (!newNode->next) {
        fprintf(stderr, "Errore nell'allocazione dei puntatori successivi.\n");
        exit(EXIT_FAILURE);
    }

    // Inizializza i puntatori next
    for (size_t i = 0; i < level; i++) {
        newNode->next[i] = NULL;
    }

    return newNode;
}

void new_skiplist(SkipList **list, size_t max_height, int (*compare)(const void *, const void *)) {
    *list = (SkipList *)malloc(sizeof(SkipList));
    if (!*list) {
        fprintf(stderr, "Errore nell'allocazione della SkipList.\n");
        exit(EXIT_FAILURE);
    }
    (*list)->heads = (Node **)calloc(max_height, sizeof(Node *));
    if (!(*list)->heads) {
        fprintf(stderr, "Errore nell'allocazione dei puntatori iniziali.\n");
        exit(EXIT_FAILURE);
    }
    (*list)->max_level = 0;
    (*list)->max_height = max_height;
    (*list)->compare = compare;
    srand((unsigned int)time(NULL));
}

void clear_skiplist(SkipList **list) {
    if (*list) {
        for (size_t i = 0; i < (*list)->max_height; i++) {
            Node *current = (*list)->heads[i];
            while (current) {
                Node *temp = current;
                current = current->next[0];
                free(temp);
            }
        }
        free((*list)->heads);
        free(*list);
        *list = NULL;
    }
}

void insert_skiplist(SkipList *list, void *item) {
    size_t level = random_level(list->max_height);
    Node *newNode = create_node(item, level);

    printf("Creato nuovo nodo con valore: %d e livelli: %d\n", (int *)item, level);

    if (newNode->size > list->max_level) {
        printf("Aggiornato il massimo livello della lista da: %d a: %d\n", list->max_level, newNode->size);
        list->max_level = newNode->size;
    }

    Node **x = list->heads;

    for (size_t k = list->max_level; k > 0; k--) {
        printf("Confronto con livello %d della lista\n", k);

        while (k > 0 && x[k - 1] != NULL && list->compare(x[k - 1]->item, item) < 0) {
            printf("Confronto con nodo: %d\n", (int *)x[k - 1]->item);
            x = x[k - 1]->next;
            k--;
        }

        if (k <= newNode->size || k >= list->max_level) {
            if (x[k - 1] == NULL || k >= list->max_level) {
                printf("Inserimento all'inizio della lista su livello %d\n", k);
                newNode->next[k - 1] = NULL;
                x[k - 1] = newNode;
            } else {
                printf("Trovato il posto giusto per inserire il nodo\n");
                printf("Aggiornamento dei puntatori del predecessore e del successivo\n");
                newNode->next[k - 1] = x[k - 1];
                x[k - 1] = newNode;
            }

            // Stampa dell'array dei livelli dopo l'inserimento
            printf("Array dei livelli dopo l'inserimento: ");
            for (size_t i = 0; i < list->max_level; i++) {
                printf("%zu ", x[i] ? x[i]->size : 0);
            }
            printf("\n");

            // Stampa dei livelli dei nodi dopo l'inserimento
            for (size_t i = 0; i < list->max_level; i++) {
                printf("Livello %zu: ", i + 1);
                Node *current = list->heads[i];
                while (current != NULL) {
                    printf("%zu ", current->size);
                    current = current->next[i];
                }
                printf("\n");
            }
        }
    }
}



const void *search_skiplist(SkipList *list, void *item) {
    Node **x = list->heads;
    for (size_t i = list->max_level; i > 0; i--) {
        while (x[i] != NULL && list->compare(x[i]->item, item) < 0) {
            x = x[i]->next;
        }
    }

    if (x[1] != NULL && list->compare(x[1]->item, item) == 0) {
        return x[1]->item;
    } else {
        return NULL;
    }
}

void print_skiplist(SkipList *list, int is_string) {
    for (size_t level = list->max_level; level > 0; level--) {
        printf("Level %lu: ", level);
        Node *x = list->heads[level - 1];

        while (x) {
            if (is_string) {
                printf("%s", (char *)x->item);
            } else {
                printf("%d", *((int *)x->item));
            }

            for (size_t i = 1; i < level; i++) {
                if (is_string) {
                    printf(" lev%lu->%s", i, (char *)x->next[i - 1]->item);
                } else {
                    printf(" lev%lu->%d", i, *((int *)x->next[i - 1]->item));
                }
            }

            printf("\n");
            x = x->next[level - 1];
        }

        printf("\n");
    }
}