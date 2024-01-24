#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX 500

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

long time;
long distance_max;

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

    char **tokens = (char **)malloc(sizeof(char *) * 100);
        if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    int ligneNum = 0;

    

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

        ligneNum++;

        printf("ligne = %s\n", ligne);

        //ligne[strcspn(ligne, "\n")] = '\0';

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

        if (ligneNum == 1) {
            time = atol(tokens[1]);
            printf("time = %ld\n", time);
        }

        if (ligneNum == 2) {
            distance_max = atol(tokens[1]);
            printf("distance_max = %ld\n", distance_max);
            printf("distance_max = %ld\n", LONG_MAX);
        } 

    }

    long number_of_times = 0;

    for (long k = 0; k <= time; k++) {
        long time_button_pressed = k;
        long speed = time_button_pressed;

        long time_travelling = time - time_button_pressed;

        long distance = speed * time_travelling;

        //printf(ANSI_COLOR_RED "time_button_pressed = %ld\n" ANSI_COLOR_RESET, time_button_pressed);
        //printf(ANSI_COLOR_GREEN "distance = %d\n" ANSI_COLOR_RESET, distance);

        if (distance < 0L ) {
            return 1;
        }

        

        if (distance >= distance_max) {
            number_of_times++;
        }
    }

    printf(ANSI_COLOR_CYAN "Number of times: %d\n" ANSI_COLOR_RESET, number_of_times);

}