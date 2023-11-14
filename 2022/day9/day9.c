#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000

#include <stdbool.h>

// l'initialiser a 0

int mat_passage [MAX][MAX] = {0};

//start coordinates 
int x_head = 2499;
int y_head = 2499;
int x_tail = 2499;
int y_tail = 2499;


void tail_following() {

    if (abs(x_head - x_tail) <= 1 || abs(y_head - y_tail) <= 1) {
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

            tail_following();

            mat_passage[x_tail][y_tail] = 1;

            printf("------------[Head coordinates : (%d,%d)]------------\n", x_head, y_head);
            printf("------------[Tail coordinates : (%d,%d)]------------\n", x_tail, y_tail);


        }

        l++;

        if (l == 10) {
            break;
        }

    }

    
}