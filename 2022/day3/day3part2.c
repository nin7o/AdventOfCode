#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char alphabet[52] = {'a', 'b', 'c', 'd', 'e', 'f', 'g', 'h', 'i',
                     'j', 'k', 'l', 'm', 'n', 'o', 'p', 'q', 'r',
                     's', 't', 'u', 'v', 'w', 'x', 'y', 'z', 'A',
                     'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 'J',
                     'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S',
                     'T', 'U', 'V', 'W', 'X', 'Y', 'Z'};

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

    char ligne[100];

    char ligne1[100];
    char ligne2[100];
    char ligne3[100];

    int N = 0;
    int grp = 0;

    int priority_sum = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, 100, fptr)) {

        //printf("%d\n", strlen(ligne));
        ligne[strcspn(ligne, "\n")] = '\0';
        //printf("%d\n", strlen(ligne));

        if (N == 0) {
            strcpy(ligne1, ligne);

            N += 1;
        } else if (N == 1) {
            strcpy(ligne2, ligne);

            N += 1;
        } else if (N == 2) {
            strcpy(ligne3, ligne);

            char c;

            // i want to find the common string in ligne1 and ligne2 and ligne3
            printf("Elf grp %d\n", grp++);
            int i = 0;
            for (i = 0; i < strlen(ligne1); i++) {
                c = ligne1[i];
                if (strcspn(ligne2, &c) != strlen(ligne2)) {
                    if (strcspn(ligne3, &c) != strlen(ligne3)) {
                        printf("common character : %c\n", c);
                        break;
                    }
                }
            }

            printf("ligne1 : %s\n", ligne1);
            printf("ligne2 : %s\n", ligne2);
            printf("ligne3 : %s\n", ligne3);

            N = 0;
        

            int l = 0;
            for (l = 0; l < 52; l++) {
                if (alphabet[l] == c) {
                    break;
                }
            }

        int priority = l+1;

        printf("character priority : %d\n", priority);

        priority_sum += priority;
        
        }

    }

    printf("\033[0;32m-------------------[Priority sum: %d]------------------\n", priority_sum);

    return 0;

}