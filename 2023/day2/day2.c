#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 500

#include <stdbool.h>

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

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

    char ligne[MAX];

    char **tokens = (char **)malloc(sizeof(char *) * 10);
        if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    int powerSum = 0;
    int sumOfIds = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

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
            //printf("Token %d: %s\n",t, tokens[t]);

            // Incrémenter le compteur de tokens
            t++;

            token = strtok(NULL, " ");
        }

        //printer le tableau de tokens
        for (int i = 0; i < t; i++) {
            tokens[i][strcspn(tokens[i], ":")] = '\0';
            //printf("Token %d: %s\n",i, tokens[i]);
        }


        int gameId = atoi(tokens[1]);

        int i = 2; //inndice 

        int nbRed = 0;
        int nbBlue = 0;
        int nbGreen = 0;

        int maxRED = 12;
        int maxBLUE = 14;
        int maxGREEN = 13;

        int minRed = 0;
        int minBlue = 0;
        int minGreen = 0;

        bool gamePossible = true;
        bool roundEnded = false;

        if (strcmp(tokens[0], "Game") != 0) {
            printf("Error: Game not foundAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA\n");
        }

        

        while (i < t) {

            int nb = atoi(tokens[i]);

            if (strcmp(tokens[i + 1], "red,") == 0) {
                //printf(" %d red added\n", nb);
                nbRed += nb;
            } else if (strcmp(tokens[i + 1], "blue,") == 0) {
                //printf(" %d blue added\n", nb);
                nbBlue += nb;
            } else if (strcmp(tokens[i + 1], "green,") == 0) {
                //printf(" %d green added\n", nb);
                nbGreen += nb;
            }

            if (strcmp(tokens[i + 1], "red;") == 0 || strcmp(tokens[i + 1], "red") == 0) {
                //printf(" %d red added and end of round\n", nb);
                nbRed += nb;
                roundEnded = true;
            } else if (strcmp(tokens[i + 1], "blue;") == 0 || strcmp(tokens[i + 1], "blue") == 0) {
                //printf(" %d blue added and end of round\n", nb);
                nbBlue += nb;
                roundEnded = true;
            } else if (strcmp(tokens[i + 1], "green;") == 0 || strcmp(tokens[i + 1], "green") == 0) {
                //printf(" %d green added and end of round\n", nb);
                nbGreen += nb;
                roundEnded = true;
            }

            if (nbRed > minRed) {
                minRed = nbRed;
            }
            if (nbBlue > minBlue) {
                minBlue = nbBlue;
            }
            if (nbGreen > minGreen) {
                minGreen = nbGreen;
            }

            if (nbRed > maxRED || nbBlue > maxBLUE || nbGreen > maxGREEN) {
                gamePossible = false;
            }

            if (roundEnded) {
                printf("nbRed: %d, nbBlue: %d, nbGreen: %d\n", nbRed, nbBlue, nbGreen);
                nbRed = 0;
                nbBlue = 0;
                nbGreen = 0;
                roundEnded = false;

            }

            i++;
            i++;

        }

        if (gamePossible) {
            sumOfIds += gameId;
            printf(ANSI_COLOR_GREEN "Game %d is possible\n" ANSI_COLOR_RESET, gameId);
        }  else {
            printf(ANSI_COLOR_RED "Game %d is not possible\n" ANSI_COLOR_RESET, gameId);
        }

        printf("minRed: %d, minBlue: %d, minGreen: %d\n", minRed, minBlue, minGreen);
        int powergame = minRed * minBlue * minGreen;
        printf("power of this game: %d\n", powergame);
        minBlue = 0;
        minGreen = 0;
        minRed = 0;

        powerSum += powergame;
    }

    printf("-----------------[powerSum: %d]------------------\n", powerSum);
    printf("-----------------[sumOfIds: %d]------------------\n", sumOfIds);

}