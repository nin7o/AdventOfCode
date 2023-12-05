#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 500

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdbool.h>

int card [10];
int numbers [25];

int numOfCards [211];
int lineNum = 0;

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

    int pointSum = 0;

    for (int i = 0; i < 211; i++) {
        numOfCards[i] = 1;
    }


    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

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

        for (int i = 0; i < t; i++) {
            tokens[i][strcspn(tokens[i], ":")] = '\0';
        }

        int GameNumber = atoi(tokens[1]);

        printf("Game %d\n", GameNumber);

        for (int i = 0; i < 10; i++) {
            card[i] = atoi(tokens[i+2]);
        }

        //print the card 
        //printf("Card: ");
        for (int i = 0; i < 10; i++) {
            //printf("%d ", card[i]);
        }
        //printf("\n");

        

        //getthe numbers }
        for (int i = 0; i < 25; i++) {
            numbers[i] = atoi(tokens[i+13]);
        }

        memset(tokens, 0, sizeof(tokens));

        // print the numbers 
        //printf("Numbers: ");
        for (int i = 0; i < 25; i++) {
            //printf("%d ", numbers[i]);
        }
        //printf("\n");

        //check how many numbers are both in the card and in the numbers 
        int sum = 0;
        for (int i = 0; i < 25; i++) {
            for (int j = 0; j < 10; j++) {
                if (numbers[i] == card[j]) {
                    printf (ANSI_COLOR_GREEN "%d " ANSI_COLOR_RESET, numbers[i]);
                    sum++;
                }
            }
        }

        //printf("sum = %d\n", sum);

        int point = sum;

        printf("point = %d\n", point);
    
        for (int i = 1; i<= sum; i++ ) {
            numOfCards[lineNum + i] += numOfCards[lineNum]; 
        }

        

        lineNum++;

    }

    printf("pointSum = %d\n", pointSum);

    int finalSum = 0;

    for (int i = 0; i < 211; i++) {
        printf("%d ", numOfCards[i]);
        finalSum += numOfCards[i];
    }

    printf("final sum : %d", finalSum);

}