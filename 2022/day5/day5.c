#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 100

/*
[J]             [F] [M]            
[Z] [F]     [G] [Q] [F]            
[G] [P]     [H] [Z] [S] [Q]        
[V] [W] [Z] [P] [D] [G] [P]        
[T] [D] [S] [Z] [N] [W] [B] [N]    
[D] [M] [R] [J] [J] [P] [V] [P] [J]
[B] [R] [C] [T] [C] [V] [C] [B] [P]
[N] [S] [V] [R] [T] [N] [G] [Z] [W]
 1   2   3   4   5   6   7   8   9 
*/

char pile1[MAX] = {'N', 'B', 'D', 'T', 'V', 'G', 'Z', 'J'};
char pile2[MAX] = {'S', 'R', 'M', 'D', 'W', 'P', 'F'};
char pile3[MAX] = {'V', 'C', 'R', 'S', 'Z'};
char pile4[MAX] = {'R', 'T', 'J', 'Z', 'P', 'H', 'G'};
char pile5[MAX] = {'T', 'C', 'J', 'N', 'D', 'Z', 'Q', 'F'};
char pile6[MAX] = {'N', 'V', 'P', 'W', 'G', 'S', 'F', 'M'};
char pile7[MAX] = {'G', 'C', 'V', 'B', 'P', 'Q'};
char pile8[MAX] = {'Z', 'B', 'P', 'N'};
char pile9[MAX] = {'W', 'P', 'J'};

// move the top card from one pile to another pile
void move(char *from, char *to) {
    int lenf = strlen(from);
    int lent = strlen(to);
    to[lent] = from[lenf - 1];
    from[lenf - 1] = '\0';
}

// move a stack of cards from one pile to another pile without changing the order of the cards moved
void move_stack(char *from, char *to, int number) {

    int lenf = strlen(from);
    int lent = strlen(to);

    char temp[MAX];

    for (int i = 0; i < number; i++) {
        temp[i] = from[lenf - number + i];
    }

    for (int i = 0; i < number; i++) {
        from[lenf - number + i] = '\0';
    }

    for (int i = 0; i < number; i++) {
        to[lent + i] = temp[i];
    }

}

// give the pile associated with the int 
char *get_pile(int pile) {
    switch (pile) {
        case 1:
            return pile1;
        case 2:
            return pile2;
        case 3:
            return pile3;
        case 4:
            return pile4;
        case 5:
            return pile5;
        case 6:
            return pile6;
        case 7:
            return pile7;
        case 8:
            return pile8;
        case 9:
            return pile9;
        default:
            exit(1);
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

    char ligne[100];

    //------------------[Read input file]------------------//
    while (fgets(ligne, 100, fptr)) {

        int length = strlen(ligne);

        char number_string[100];
        int number;

        char from_string[100];
        int from;

        char to_string[100];
        int to;

        // ligne type : move 11 from 7 to 9 // on veut séparer les 11, 7 et 9

        // on récupère le nombre
        int n = 0;
        int index_separator = strcspn(ligne, " ");
        int i = index_separator + 1;
        for (i ; i < length; i++) {

            if (ligne[i] == ' ') {
                break;
            }

            number_string[n] = ligne[i];
            n++;

        }

        printf("number_string : %s\n", number_string);
        number = atoi(number_string);
        printf("number : %d\n", number);

        // on récupère le from
        n = 0;
        int j = i + 6;
        for ( j ; j < length; j++) {

            if (ligne[j] == ' ') {
                break;
            }

            from_string[n] = ligne[j];
            n++;

        }

        printf("from_string : %s\n", from_string);
        from = atoi(from_string);
        printf("from : %d\n", from);

        // on récupère le to
        n = 0;
        int k = j + 4;
        for ( k ; k < length; k++) {

            if (ligne[k] == ' ') {
                break;
            }

            to_string[n] = ligne[k];
            n++;

        }

        printf("to_string : %s\n", to_string);
        to = atoi(to_string);
        printf("to : %d\n", to);

        printf("----------------------------------------\n");

        memset(to_string, 0, sizeof(to_string));
        
        memset(from_string, 0, sizeof(from_string));

        memset(number_string, 0, sizeof(number_string));

        // on déplace la carte
        move_stack(get_pile(from), get_pile(to), number);

        // print all piles 
        for (int i = 0; i < 9; i++) {
            printf("pile%d : %s\n", i + 1, get_pile(i + 1));
        }

    }

}