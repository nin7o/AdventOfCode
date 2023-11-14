#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 5000

#include <stdbool.h>

// l'initialiser a 0

int mat_passage [MAX][MAX] = {0};

//start coordinates 
int x_head = 2499;
int y_head = 2499;

int x_knot1 = 2499;
int y_knot1 = 2499;

int x_knot2 = 2499;
int y_knot2 = 2499;

int x_knot3 = 2499;
int y_knot3 = 2499;

int x_knot4 = 2499;
int y_knot4 = 2499;

int x_knot5 = 2499;
int y_knot5 = 2499;

int x_knot6 = 2499;
int y_knot6 = 2499;

int x_knot7 = 2499;
int y_knot7 = 2499;

int x_knot8 = 2499;
int y_knot8 = 2499;

int x_tail = 2499;
int y_tail = 2499;

int x;
int y;


void tail_following(int x_head, int y_head, int x_tail, int y_tail) {

    if ( sqrt( (x_head - x_tail)*(x_head - x_tail) + (y_head - y_tail)*(y_head - y_tail) ) < 2) {
        printf("\033[0;31mtail still close enough 😟\033[0;0m\n");
    } else {
        
        if (x_head == x_tail) {
            if (y_head > y_tail) {
                y_tail++;
            } else {
                y_tail--;
            }
        } else if (y_head == y_tail) {
            if (x_head > x_tail) {
                x_tail++;
            } else {
                x_tail--;
            }
        } else {
            int x_temp = x_tail - x_head;
            int y_temp = y_tail - y_head;

            if (x_temp > 0 && y_temp > 0) {
                x_tail--;
                y_tail--;
            } else if (x_temp > 0 && y_temp < 0) {
                x_tail--;
                y_tail++;
            } else if (x_temp < 0 && y_temp > 0) {
                x_tail++;
                y_tail--;
            } else if (x_temp < 0 && y_temp < 0) {
                x_tail++;
                y_tail++;
            }
        }
        printf("\033[0;32mtail following ! 🪱\033[0;0m\n");

    }

    x = x_tail;
    y = y_tail;

}



int main(int argc, char *argv[]) {


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

    char ligne[50];

    char **tokens = (char **)malloc(sizeof(char *) * 10);
        if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    

    mat_passage[x_tail][y_tail] = 1;

    int l = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, 50, fptr)) {

        ligne[strcspn(ligne, "\n")] = '\0';

        char *token = strtok(ligne, " ");
        int t = 0;

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

        // assign the first token to a char
        char *direction = tokens[0];

        // assign the second token to an int 
        int distance = atoi(tokens[1]);

        for (int i = 0; i < distance; i++) {

            if (strcmp(direction, "U") == 0) {
                y_head++;
            }
            else if (strcmp(direction, "D") == 0) {
                y_head--;
            }
            else if (strcmp(direction, "L") == 0) {
                x_head--;
            }
            else if (strcmp(direction, "R") == 0) {
                x_head++;
            }

            tail_following(x_head, y_head, x_knot1, y_knot1);
            x_knot1 = x;
            y_knot1 = y;
            tail_following(x_knot1, y_knot1, x_knot2, y_knot2);
            x_knot2 = x;
            y_knot2 = y;
            tail_following(x_knot2, y_knot2, x_knot3, y_knot3);
            x_knot3 = x;
            y_knot3 = y;
            tail_following(x_knot3, y_knot3, x_knot4, y_knot4);
            x_knot4 = x;
            y_knot4 = y;
            tail_following(x_knot4, y_knot4, x_knot5, y_knot5);
            x_knot5 = x;
            y_knot5 = y;
            tail_following(x_knot5, y_knot5, x_knot6, y_knot6);
            x_knot6 = x;
            y_knot6 = y;
            tail_following(x_knot6, y_knot6, x_knot7, y_knot7);
            x_knot7 = x;
            y_knot7 = y;
            tail_following(x_knot7, y_knot7, x_knot8, y_knot8);
            x_knot8 = x;
            y_knot8 = y;
            tail_following(x_knot8, y_knot8, x_tail, y_tail);
            x_tail = x;
            y_tail = y;

            mat_passage[x_tail][y_tail] = 1;

            printf("------------[Head coordinates : (%d,%d)]------------\n", x_head, y_head);
            printf("------------[Tail coordinates : (%d,%d)]------------\n", x_tail, y_tail);


        }

        l++;

        if (l == 10) {
            //break;
        }

    }

    // somme des valeurs de la matrice 
    int sum = 0;

    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++){
            sum += mat_passage[i][j];
        }
    }

    printf("------------[Sum : %d]------------\n", sum);

}