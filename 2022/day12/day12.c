#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX 5000

#include <stdbool.h>

int mat[41][80] = {100};



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
    int l = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

        ligne[strcspn(ligne, "\n")] = '\0';

        printf("%s\n", ligne);

        for (int i = 0; i < strlen(ligne); i++) {

            char character = ligne[i];
            int number = 0;

            if (character >= 'a' && character <= 'z') {
                number = character - 'a' + 1;
            }

            else if (character >= 'A' && character <= 'Z') {
                number = character - 'A' + 27;
            }

            mat[l][i] = number;

        }

        l++;

    }

    

    

}