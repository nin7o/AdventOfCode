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

    int priority_sum = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, 100, fptr)) {

        //printf("%d\n", strlen(ligne));
        ligne[strcspn(ligne, "\n")] = '\0';
        //printf("%d\n", strlen(ligne));

        int length = strlen(ligne);

        char part1[100];
        char part2[100];

        int i = 0;
        for (i = 0; i < length/2; i++) {
            if (ligne[i] == ' ') {
                break;
            }
            part1[i] = ligne[i];
        }
        part1[i] = '\0';

        int j = 0;
        for (j = i; j < length; j++) {
            part2[j-i] = ligne[j];
        }
        part2[j-i] = '\0';

        printf("ligne : %s\n", ligne);
        printf("part1 : %s\n", part1);
        printf("part2 : %s\n", part2);

        //printf("%d\n", strcspn("azertyuib", "b"));

        int k = 0;
        int lengthPart1 = strlen(part1);
        char t;
        for (k = 0; k < lengthPart1; k++) {
            char c[2] = {part1[k], '\0'};
            if (strcspn(part2, c) != lengthPart1) {
                t = part1[k];
                printf("part1[%d] : %c\n", k, t);
                break;
            }
        }

        int l = 0;
        for (l = 0; l < 52; l++) {
            if (alphabet[l] == t) {
                printf("MATCH\n");
                break;
            }
        }

        int priority = l+1;

        printf("character priority : %d\n", priority);
        printf("character : %c\n", alphabet[l]);

        priority_sum += priority;
        
    }

    printf("\033[0;32m-------------------[Priority sum: %d]------------------\n", priority_sum);

}