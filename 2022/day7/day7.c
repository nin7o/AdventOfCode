#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX_LINE_LENGTH 1000

struct node {
    char name[MAX_LINE_LENGTH];
    bool isMainNode;
    bool isDirectory;
    int size;
    struct node *next;
    struct node *child;
    struct node *parent;
};

typedef struct node node;



// create a new node
node *create_node(char *name, bool isDirectory, int size, node *parent, bool isMainNode) {
    node *new_node = malloc(sizeof(node));
    strcpy(new_node->name, name);
    new_node->isDirectory = isDirectory;
    new_node->isMainNode = isMainNode;
    new_node->size = size;
    new_node->next = NULL;
    new_node->child = NULL;
    new_node->parent = parent;
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
        child->isMainNode = true;
        current_node->child = child;
    } else {
        add_sibling(current_node->child, child);
    }
}

// print the tree
void print_tree(node *current_node, int level) {
    if (current_node == NULL) {
        return;
    }
    for (int i = 0; i < level; i++) {
        printf("  ");
    }
    if (current_node->isMainNode) {
        printf("\033[0;32m%s\033[0;0m\n", current_node->name);
    } else {
    printf("%s\n", current_node->name);}
    
    print_tree(current_node->child, level + 1);

    print_tree(current_node->next, level);
}








int determine_sizes(node *current_node) {
    if (current_node == NULL) {
        return 0;
    }
    if (current_node->isDirectory == true) {
        return determine_sizes(current_node->child) + determine_sizes(current_node->next);
    } else {
        return current_node->size + determine_sizes(current_node->next);
    }
}














int main (int argc, char *argv[]) {

    // create the global root node of the tree that we'll build
    node *root = create_node("/", true, 0, NULL, true);
    
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

    //knowing if ure in ls state
    bool ls = false;

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

            printf("wsh");

            ls = false;
        
            if (strcmp(tokens[1], "cd") == 0) {

                if (strcmp(tokens[2], "..") == 0) {

                    current_node = current_node->parent;

                    /*if (current_node->isMainNode == true) {
                        printf("lol\n");
                        
                    } else {
                        printf("lolilol\n");
                        while (current_node->isMainNode == false) {
                            current_node = current_node->parent;
                        }
                        printf("loul\n");
                        
                    }*/
                    printf("cd %s\n", tokens[2]);
                } else if (strcmp(tokens[2], "/") == 0) {
                    printf("cd %s\n", tokens[2]);
                    current_node = root;
                } else {
                    printf("cd %s\n", tokens[2]);

                    /*while (current_node->isMainNode == false) {
                        current_node = current_node->parent;
                    }*/

                    if (current_node->child == NULL) {
                        printf("\033[0;32mNo such file or directory\033[0;0m\n");
                    } else {
                        current_node = current_node->child;
                        while (strcmp(current_node->name, tokens[2]) != 0) {
                            if (current_node->next == NULL) {
                                printf("\033[0;32mNo such file or directory\033[0;0m\n");
                                break;
                            }
                            current_node = current_node->next;
                        }
                    }

                }

            } else if (strcmp(tokens[1], "ls") == 0) {
                printf("ls\n");
                ls = true;
            }

        } else {

            printf("bahaha");

            if (strcmp(tokens[0], "dir") == 0) {

                printf("lol");

                // create a new directory node 
                node *new_node = create_node(tokens[1], true, 0, current_node, false);

                printf("haha");

                // add the new node as a child of the current node
                add_child(current_node, new_node);
                
            } else {

                // create a new file node
                node *new_node = create_node(tokens[1], false, atoi(tokens[0]), current_node, false);

                // add the new node as a child of the current node
                add_child(current_node, new_node);

            }
        }
        if (ls == false) {
            printf("-------------[name of current node : %s]-------------\n", current_node->name);
        }
        
        if (current_node->isMainNode == true) {
            printf("\033[0;32m-------------[name of current node : %s]-------------\033[0;0m\n", current_node->name);
            print_tree(root, 0);
        }

    }

    print_tree(root, 0);

    
    


}