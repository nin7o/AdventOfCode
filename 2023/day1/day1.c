#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 5000

#include <stdbool.h>

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

    char ligne[500];

    char **tokens = (char **)malloc(sizeof(char *) * 10);
        if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    int sum = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, 500, fptr)) {

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
            printf("Token %d: %s\n",t, tokens[t]);

            // Incrémenter le compteur de tokens
            t++;

            token = strtok(NULL, " ");
        }

        int lentoken = strlen(tokens[0]);

        // len 3 => one, two, six, ten
        int debut3 = 0;
        int fin3 = 3;
        int offset = 0;

        char trois[3];

        while (fin3 + offset <= lentoken) {

            strncpy(trois, tokens[0] + debut3 + offset, 3);
            trois[3] = '\0';

            if (strcmp(trois, "one") == 0) {
                printf("----------------------------------------------------------");
                //replace "one" by 1
                tokens[0][debut3 + offset + 1] = '1';
                t = debut3 + offset + 1;
            }

            if (strcmp(trois, "two") == 0) {
                printf("----------------------------------------------------------");
                //replace "two" by 2
                tokens[0][debut3 + offset + 1] = '2';
                t = debut3 + offset + 1;
            }

            if (strcmp(trois, "six") == 0) {
                printf("----------------------------------------------------------");
                //replace "six" by 6
                tokens[0][debut3 + offset + 1] = '6';
                t = debut3 + offset + 1;
            }

            offset++;
        }

        // len 4 => four, five, nine
        int debut4 = 0;
        int fin4 = 4;
        offset = 0;

        char quatre[4];

        while (fin4 + offset <= lentoken) {

            strncpy(quatre, tokens[0] + debut4 + offset, 4);
            quatre[4] = '\0';

            if (strcmp(quatre, "four") == 0) {
                printf("----------------------------------------------------------");
                //replace 'four" by 4
                tokens[0][debut4 + offset + 1] = '4';
                t = debut4 + offset + 1;
            }

            if (strcmp(quatre, "five") == 0) {
                printf("----------------------------------------------------------");
                //replace "five" by 5
                tokens[0][debut4 + offset] = '5';
                t = debut4 + offset + 1;
            }

            if (strcmp(quatre, "nine") == 0) {
                printf("----------------------------------------------------------");
                //replace "nine" by 9
                tokens[0][debut4 + offset + 1] = '9';
                t = debut4 + offset + 1;
            }

            offset++;
        }

        // len 5 => three, seven, eight

        int debut5 = 0;
        int fin5 = 5;
        offset = 0;

        char cinq[5];

        while (fin5 + offset <= lentoken) {

            strncpy(cinq, tokens[0] + debut5 + offset, 5);
            cinq[5] = '\0';

            if (strcmp(cinq, "three") == 0) {
                printf("----------------------------------------------------------");
                //replace "three" by 3
                tokens[0][debut5 + offset + 1] = '3';
                t = debut5 + offset + 1;
            }

            if (strcmp(cinq, "seven") == 0) {
                printf("----------------------------------------------------------");
                //replace "seven" by 7
                tokens[0][debut5 + offset + 1] = '7';
                t = debut5 + offset + 1;
            }

            if (strcmp(cinq, "eight") == 0) {
                printf("----------------------------------------------------------");
                //replace "eight" by 8
                tokens[0][debut5 + offset + 1] = '8';
                t = debut5 + offset + 1;
            }

            offset++;
        }

        printf("Token SANS ONE RMLT 0: %s\n", tokens[0]);

        int length0 = strlen(tokens[0]);
        bool startfound = false;
        int start = 0;
        int end = 0;
        char chiffre[1];

        for (int i = 0; i < length0; i++) {
            if (tokens[0][i] == '0' || tokens[0][i] == '1' || tokens[0][i] == '2' || tokens[0][i] == '3' || tokens[0][i] == '4' || tokens[0][i] == '5' || tokens[0][i] == '6' || tokens[0][i] == '7' || tokens[0][i] == '8' || tokens[0][i] == '9') {
                if (startfound == false) {
                    printf("tokenchiffre : %c\n", tokens[0][i]);
                    char ptr[2] = { tokens[0][i], '\0' };
                    start = atoi(ptr);
                    startfound = true;
                }
                end = atoi(&tokens[0][i]);
            }
        }

        printf("start: %d\n", start);
        printf("end: %d\n", end);

        int value = start * 10 + end;

        printf("value: %d\n", value);

        sum += value;


    }

    printf("sum: %d\n", sum);

}