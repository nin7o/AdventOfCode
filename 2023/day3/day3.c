#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 180

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

#include <stdbool.h>

char mat [MAX][MAX];

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

    // Initialize the matrix
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++){
            mat[i][j] = '.';
        }
    }

    int numligne = 0;
    int sumOfParts = 0;

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

        //printf("t = %d\n", strlen(tokens[0]));

        //copy the token[0] in the first line of the matrix
        for (int i = 0; i < strlen(tokens[0]); i++) {
            mat[numligne + 10][i + 10] = tokens[0][i];
        }

        numligne++;
    }

    //print the matrix
    for (int i = 0; i < MAX; i++) {
        for (int j = 0; j < MAX; j++){
            printf("%c", mat[i][j]);
        }
        printf("\n");
    }

    for (int i = 0; i < MAX; i++) {

        for (int j = 0; j < MAX; j++){
            

        int number = 0;
        int numberlength = 0;
        int numberstart = 0;

        if (mat[i][j] == '0' || mat[i][j] == '1' || mat[i][j] == '2' || mat[i][j] == '3' || mat[i][j] == '4' || mat[i][j] == '5' || mat[i][j] == '6' || mat[i][j] == '7' || mat[i][j] == '8' || mat[i][j] == '9' ) {
            numberstart = j;
            numberlength++;
            number = mat[i][j] - '0';
            while (mat[i][j + numberlength] == '0' || mat[i][j + numberlength] == '1' || mat[i][j + numberlength] == '2' || mat[i][j + numberlength] == '3' || mat[i][j + numberlength] == '4' || mat[i][j + numberlength] == '5' || mat[i][j + numberlength] == '6' || mat[i][j + numberlength] == '7' || mat[i][j + numberlength] == '8' || mat[i][j + numberlength] == '9' ) {
                printf("number being constructed = %d\n", number);
                number = number * 10 + (mat[i][j + numberlength] - '0');
                numberlength++;
            }

            printf("number = %d\n", number);
            printf("numberlength = %d\n", numberlength);
            printf("numberstart = %d\n", numberstart);
            j = j + numberlength;
        }


        //check all the surroundings of the number to see if there is character that is not a point
        if (number != 0) {
            
            bool isPartNumber = false;

            printf("checking before the number : %c\n", mat[i][numberstart - 1]);
            if (mat[i][numberstart - 1] != '.') {
                isPartNumber = true;
                printf("BEFORE THE NUMBER THERE IS A CHARACTER\n");
            }
            printf("checking after the number : %c\n", mat[i][numberstart + numberlength]);
            if (mat[i][numberstart + numberlength] != '.') {
                isPartNumber = true;
                printf("AFTER THE NUMBER THERE IS A CHARACTER\n");
            }
            printf("Checking on top and bottom of the number\n");
            for (int k = numberstart - 1; k <= numberstart + numberlength; k++) {
                printf("top : %c\n", mat[i - 1][k]);
                if (mat[i - 1][k] != '.') {
                    isPartNumber = true;
                    printf("TOP OF THE NUMBER THERE IS A CHARACTER\n");
                }
                printf("bottom : %c\n", mat[i + 1][k]);
                if (mat[i + 1][k] != '.') {
                    isPartNumber = true;
                    printf("BOTTOM OF THE NUMBER THERE IS A CHARACTER\n");
                }
            }

            if (isPartNumber) {
                printf(ANSI_COLOR_GREEN "Part number %d is a part\n" ANSI_COLOR_RESET, number);
                sumOfParts+= number;
            } else {
                printf(ANSI_COLOR_RED "Part number %d is not a part\n" ANSI_COLOR_RESET, number);
            }

            

        }






        }
    }

    printf(ANSI_COLOR_CYAN "-----------------[SUM OF PARTS = %d]-----------------\n" ANSI_COLOR_RESET, sumOfParts);

}