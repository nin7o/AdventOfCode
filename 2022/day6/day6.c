#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000

#include <stdbool.h>

bool check_same_char(char a, char b, char c, char d) {
    if (a != b && a != c && a != d && b != c && b != d && c != d) {
        return true;
    } else {}
        return false;}

bool areAllCharDifferent(char *str) {
    int i, j, len = strlen(str);
    for (i = 0; i < len; i++) {
        for (j = i + 1; j < len; j++) {
            if (str[i] == str[j]) {
                return false;
            }
        }
    }
    return true;
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

    char ligne[MAX];

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

        printf("ligne : %s\n", ligne);

    }

    char sequence[100];

    for (int i = 0; i < 14; i++) {
        sequence[i] = ligne[i];
    }

    int n = 14;
    int i = 1;

    while (!areAllCharDifferent(sequence)) {

        for (int j = i; j < 14 + i; j++) {
            sequence[j - i] = ligne[j];
        }

        n++;
        i++;

    }

    printf("n : %d\n", n);
    printf("i : %d\n", i);
    
    printf("sequence : %s\n", sequence);

    return 0;
}