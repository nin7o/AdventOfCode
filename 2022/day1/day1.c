#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]) {
    
    //------------------[Check for correct usage]------------------//
    if (argc != 2) {
        printf("Usage: ./day1 <input file>\n");
        exit(1);
    }

    //------------------[Open input file]------------------//
    FILE *fptr;
    fptr = fopen(argv[1], "r");

    char myString[100];
    int currval = 0;
    int sum = 0;
    int calMax3 = 0;
    int calMax1 = 0;
    int calMax2 = 0;
    //------------------[Read input file]------------------//

    while (fgets(myString, 100, fptr)) {
        currval = atoi(myString);
        sum += currval;
        if (currval == 0) {
            printf("Current sum: %d\n", sum);
            if (sum > calMax1) {
                calMax3 = calMax2;
                calMax2 = calMax1;
                calMax1 = sum;
            } else if (sum > calMax2) {
                calMax3 = calMax2;
                calMax2 = sum;
            } else if (sum > calMax3) {
                calMax3 = sum;
            }
            sum = 0;
        }
    }

    // ------------------[Close file]------------------//
    fclose(fptr);

    printf("\033[0;32m------------------[Top3 Calories: %d]------------------\n", calMax1 + calMax2 + calMax3);
    return 0;
}