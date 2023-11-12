#include <stdio.h>
#include <stdlib.h>
#include <string.h>

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

    char elf1[100];
    char elf2[100];

    char elf1_start_str[100];
    char elf2_start_str[100];

    char elf1_end_str[100];
    char elf2_end_str[100];

    int elf1_start = 0;
    int elf2_start = 0;

    int elf1_end = 0;
    int elf2_end = 0;

    int count = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, 100, fptr)) {

        ligne[strcspn(ligne, "\n")] = '\0';

        int index_separator = strcspn(ligne, ",");

        printf("ligne : %s\n", ligne);
        printf("index_separator : %d\n", index_separator);

        for (int i = 0; i < index_separator; i++) {
            elf1[i] = ligne[i];
        }
        printf("elf1 : %s\n", elf1);
        index_separator++;

        for (int i = index_separator ; i < strlen(ligne); i++) {
            elf2[i - index_separator] = ligne[i];
        }
        printf("elf2 : %s\n", elf2);

        int elf1_sep = strcspn(elf1, "-");
        int elf2_sep = strcspn(elf2, "-");

        for (int i = 0; i < elf1_sep; i++) {
            elf1_start_str[i] = elf1[i];
        }
        elf1_sep++;

        for (int i = elf1_sep; i < strlen(elf1); i++) {
            elf1_end_str[i - elf1_sep] = elf1[i];
        }

        for (int i = 0; i < elf2_sep; i++) {
            elf2_start_str[i] = elf2[i];
        }
        elf2_sep++;

        for (int i = elf2_sep; i < strlen(elf2); i++) {
            elf2_end_str[i - elf2_sep] = elf2[i];
        }

        elf1_start = atoi(elf1_start_str);
        elf1_end = atoi(elf1_end_str);

        elf2_start = atoi(elf2_start_str);
        elf2_end = atoi(elf2_end_str);

        printf ("elf1_start_str : %s\n", elf1_start_str);
        printf ("elf1_end_str : %s\n", elf1_end_str);
        printf ("elf2_start_str : %s\n", elf2_start_str);
        printf ("elf2_end_str : %s\n", elf2_end_str);

        // detect a complete overlap
        /*
        if (elf1_start >= elf2_start && elf1_end <= elf2_end) {
            printf("\033[0;32moverlap\033[0;0m\n");
            count++;
        } else if (elf2_start >= elf1_start && elf2_end <= elf1_end) {
            printf("\033[0;32moverlap\033[0;0m\n");

            count++;
        } else {
            printf("\033[0;31mno overlap\033[0;0m\n");
        }*/

        //detect any overlap
        if (elf1_start >= elf2_start && elf1_start <= elf2_end) {
            printf("\033[0;32moverlap\033[0;0m\n");
            count++;
        } else if (elf2_start >= elf1_start && elf2_start <= elf1_end) {
            printf("\033[0;32moverlap\033[0;0m\n");

            count++;
        } else {
            printf("\033[0;31mno overlap\033[0;0m\n");
        }

        memset(elf1,0,strlen(elf1));
        memset(elf2,0,strlen(elf2));

        memset(elf1_start_str,0,strlen(elf1_start_str));
        memset(elf2_start_str,0,strlen(elf2_start_str));

        memset(elf1_end_str,0,strlen(elf1_end_str));
        memset(elf2_end_str,0,strlen(elf2_end_str));

        elf1[0] = '\0';
        elf2[0] = '\0';

        elf1_start_str[0] = '\0';
        elf2_start_str[0] = '\0';

        elf1_end_str[0] = '\0';
        elf2_end_str[0] = '\0';

        elf1_start = 0;
        elf2_start = 0;

        elf1_end = 0;
        elf2_end = 0;

    }

    printf("\033[0;32m-------------------[nb of complete overlap: %d]------------------\n", count);

    return 0;
}