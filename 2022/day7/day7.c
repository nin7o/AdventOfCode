#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000

struct node {
    char name[MAX_LINE_LENGTH];
    bool isDirectory;
    int size;
    struct node *next;
    struct node *child;
    struct node *parent;
};

typedef struct node node;

// create the global root node of the tree that we'll build
node *root = NULL;

// create a new node
node *create_node(char *name, bool isDirectory, int size) {
    node *new_node = malloc(sizeof(node));
    strcpy(new_node->name, name);
    new_node->isDirectory = isDirectory;
    new_node->size = size;
    new_node->next = NULL;
    new_node->child = NULL;
    new_node->parent = NULL;
    return new_node;
}

// add a node to the tree as a sibling of the current_node passed as argument
void add_sibling(node *current_node, node *sibling) {
    while (current_node->next != NULL) {
        current_node = current_node->next;
    }
    current_node->next = sibling;
}

// add a node to the tree as a child of the current_node passed as argument
void add_child(node *current_node, node *child) {
    if (current_node->child == NULL) {
        current_node->child = child;
    } else {
        add_sibling(current_node->child, child);
    }
}


int main (int argc, char *argv[]) {
    
    //------------------[Check for correct usage]------------------//
    if (argc != 2) {
        printf("Usage: ./day2 <input file>\n");
        exit(1);
    }

    //------------------[Open input file]------------------//
    FILE *fptr;
    if ((fptr = fopen(argv[1], "r")) == NULL) {
        printf("Error opening file\n");
        exit(1);
    }

    char ligne[MAX_LINE_LENGTH];

    // Allouer de l'espace pour un tableau de pointeurs de caractères
    char **tokens = (char **)malloc(sizeof(char *) * 10);  // Supposons que nous ayons au plus 10 tokens

    if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    // ptr towards the current node, initialised to the root node
    node *current_node = root;

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX_LINE_LENGTH, fptr)) {

        printf("--------[ligne]--------\n");

        //------------------[Tokenize]------------------//
        // Supprimer le caractère de nouvelle ligne
        ligne[strcspn(ligne, "\n")] = '\0';

        // Premier appel à strtok
        char *token = strtok(ligne, " ");
        int t = 0;

        //Les appels suivants à strtok
        while (token != NULL) {
            // Allouer de l'espace pour chaque token et le copier
            tokens[t] = (char *)malloc(strlen(token) + 1);

            // Vérifier si l'allocation a réussi
            if (tokens[t] == NULL) {
                fprintf(stderr, "Erreur d'allocation de mémoire.\n");
                exit(EXIT_FAILURE);
            }

            // Copier le token dans le tableau
            strcpy(tokens[t], token);

            // Afficher le token
            printf("Token: %s\n", tokens[t]);

            // Incrémenter le compteur de tokens
            t++;

            
            token = strtok(NULL, " ");
        }

        printf("--------[ligne]--------\n");
        memset(ligne, 0, sizeof(ligne));

        if (strcmp(tokens[0], "$") == 0) {
        
            if (strcmp(tokens[1], "cd") == 0) {

                if (strcmp(tokens[2], "..") == 0) {
                    //*current_node = *current_node->parent;
                } else {
                    printf("cd %s\n", tokens[2]);
                }

            }

        }

    }



}