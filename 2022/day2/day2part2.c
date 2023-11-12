#include <stdio.h>
#include <stdlib.h>

char ElfMoves[3] = { 'A', 'B', 'C'};
char MeMoves[3] = { 'X', 'Y', 'Z'};

int getMove(char move) {
    int i;
    for (i = 0; i < 3; i++) {
        if (move == ElfMoves[i]) {
            return i + 1;
        }
        if (move == MeMoves[i]) {
            return i + 1;
        }
    }
    return -1;
}

int minusModulo(int a) {
    int c = a - 1;
    if (c <= 0) {
        c = 3;
    }
    return c;
}

// Result : 1 lose 2 draw 3 win

int determineMove (int move, int result) {
    if (result == 1) {
        return minusModulo(move);
    }
    else if (result == 2) {
        return move;
    }
    else {
        return minusModulo(minusModulo(move));
    }

}



int getWinner(int Elf, int Me) {
    if (Elf == Me) {
        return 0;
    }

    if (Elf == minusModulo(Me)) {
        return 1; // Me wins
    }
    else {
        return 2; // Elf wins
    }
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

    char ligne[5];

    int roundPointsElf = 0;
    int roundPointsMe = 0;

    int totalPointsElf = 0;
    int totalPointsMe = 0;

    int expectedResult = 0;

    char Elf;
    char Me;

    while (fgets(ligne, 5, fptr)) {
        printf("%c - %c \n", ligne[0],ligne[2]);
        Elf = ligne[0];
        Me = ligne[2];

        roundPointsElf = getMove(Elf);
        expectedResult = getMove(Me);

        roundPointsMe = determineMove(roundPointsElf, expectedResult);

        if (getWinner(roundPointsElf, roundPointsMe) == 1) {
            roundPointsMe += 6;
        }
        else if (getWinner(roundPointsElf, roundPointsMe) == 2) {
            roundPointsElf += 6;
        } else {
            roundPointsElf += 3;
            roundPointsMe += 3;
        }

        printf("Elf: %d\n", roundPointsElf);
        printf("Me: %d\n", roundPointsMe);

        totalPointsElf += roundPointsElf;
        totalPointsMe += roundPointsMe;

    }

    printf("\033[0;32m------------------[Total Points Me perfect: %d]------------------\n", totalPointsMe);
}