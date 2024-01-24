#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <limits.h>

#define MAX 5000

#define ANSI_COLOR_RED     "\x1b[31m"
#define ANSI_COLOR_GREEN   "\x1b[32m"
#define ANSI_COLOR_YELLOW  "\x1b[33m"
#define ANSI_COLOR_BLUE    "\x1b[34m"
#define ANSI_COLOR_MAGENTA "\x1b[35m"
#define ANSI_COLOR_CYAN    "\x1b[36m"
#define ANSI_COLOR_RESET   "\x1b[0m"

int ligneNum = 0;

int bids[MAX];
char hands[MAX][6];
int handsInt[MAX][5];
int types[MAX];
int ranks[MAX];

int find_type(char *hand) {
    
        int type = 0;
        int count_max = 0;

        //count the number of occuerences of each char
        int count[5] = {0};
        for (int i = 0; i < 5; i++) {
            char c = hand[i];
            for (int j = 0; j < 5; j++) {
                if (hand[j] == c) {
                    count[i]++;
                }
            }
        }

        //check for the type of hand
        //check for full house
        int numof3 = 0;
        int numof2 = 0;
        for (int i = 0; i < 5; i++) {
            if (count[i] == 3) {
                numof3++;
            }
            if (count[i] == 2) {
                numof2++;
            }
        }
        if (numof3 == 3 && numof2 == 2) {
            type = 5;
            return type;
        }

        //check for two pairs 
        if (numof2 == 4) {
            type = 3;
            return type;
        }

        //else return the max
        for (int i = 0; i < 5; i++) {
            if (count[i] > count_max) {
                count_max = count[i];
            }
        }

        switch (count_max) {
            case 1:
                type = 1;
                break;
            case 2:
                type = 2;
                break;
            case 3:
                type =4;
                break;
            case 4:
                type = 6;
                break;
            case 5:
                type = 7;
                break;
            default:
            exit(EXIT_FAILURE);
                break;
        }
    
        return type;
}

void translateHandsToInt() {
    for (int i = 0; i < ligneNum; i++) {
        for (int j = 0; j < 5; j++) {
            switch (hands[i][j]) {
                case 'A':
                    handsInt[i][j] = 14;
                    break;
                case 'K':
                    handsInt[i][j] = 13;
                    break;
                case 'Q':
                    handsInt[i][j] = 12;
                    break;
                case 'J':
                    handsInt[i][j] = 11;
                    break;
                case 'T':
                    handsInt[i][j] = 10;
                    break;
                default:
                    handsInt[i][j] = hands[i][j] - '0';
                    break;
            }
        }
    }
}

void orderHands() {
    //order regarding handsInt[i][0]
    for (int i = 0; i < ligneNum; i++) {
        for (int j = 0; j < 5; j++) {
            if (handsInt[i][0] > handsInt[i + 1][0]) {
                int temp = handsInt[i][0];
                handsInt[i][0] = handsInt[i + 1][0];
                handsInt[i + 1][0] = temp;
            }
        }
    }

    //order regarding handsInt[i][1] while handsInt[i][0] is the same
    for (int i = 0; i < ligneNum; i++) {
        for (int j = 0; j < 5; j++) {
            if (handsInt[i][0] == handsInt[i + 1][0]) {
                if (handsInt[i][1] > handsInt[i + 1][1]) {
                    int temp = handsInt[i][1];
                    handsInt[i][1] = handsInt[i + 1][1];
                    handsInt[i + 1][1] = temp;
                }
            }
        }
    }

    //order regarding handsInt[i][2] while handsInt[i][0] and handsInt[i][1] are the same
    for (int i = 0; i < ligneNum; i++) {
        for (int j = 0; j < 5; j++) {
            if (handsInt[i][0] == handsInt[i + 1][0] && handsInt[i][1] == handsInt[i + 1][1]) {
                if (handsInt[i][2] > handsInt[i + 1][2]) {
                    int temp = handsInt[i][2];
                    handsInt[i][2] = handsInt[i + 1][2];
                    handsInt[i + 1][2] = temp;
                }
            }
        }
    }

    //order regarding handsInt[i][3] while handsInt[i][0] and handsInt[i][1] and handsInt[i][2] are the same
    for (int i = 0; i < ligneNum; i++) {
        for (int j = 0; j < 5; j++) {
            if (handsInt[i][0] == handsInt[i + 1][0] && handsInt[i][1] == handsInt[i + 1][1] && handsInt[i][2] == handsInt[i + 1][2]) {
                if (handsInt[i][3] > handsInt[i + 1][3]) {
                    int temp = handsInt[i][3];
                    handsInt[i][3] = handsInt[i + 1][3];
                    handsInt[i + 1][3] = temp;
                }
            }
        }
    }

    //order regarding handsInt[i][4] while handsInt[i][0] and handsInt[i][1] and handsInt[i][2] and handsInt[i][3] are the same
    for (int i = 0; i < ligneNum; i++) {
        for (int j = 0; j < 5; j++) {
            if (handsInt[i][0] == handsInt[i + 1][0] && handsInt[i][1] == handsInt[i + 1][1] && handsInt[i][2] == handsInt[i + 1][2] && handsInt[i][3] == handsInt[i + 1][3]) {
                if (handsInt[i][4] > handsInt[i + 1][4]) {
                    int temp = handsInt[i][4];
                    handsInt[i][4] = handsInt[i + 1][4];
                    handsInt[i + 1][4] = temp;
                }
            }
        }
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

    char ligne[MAX];

    char **tokens = (char **)malloc(sizeof(char *) * 100);
        if (tokens == NULL) {
        fprintf(stderr, "Erreur d'allocation de mémoire.\n");
        exit(EXIT_FAILURE);
    }

    

    for (int i = 0; i < MAX; i++) {
        ranks[i] = MAX;
    }

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

        printf("ligne = %s\n", ligne);

        //ligne[strcspn(ligne, "\n")] = '\0';

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

        //store the token 0 in hands array
        strcpy(hands[ligneNum], tokens[0]);

        //store the token 1 in bids array
        bids[ligneNum] = atoi(tokens[1]);

        ligneNum++;

    }

    //translate hands to int
    translateHandsToInt();

    //print both arrays 
    for (int i = 0; i < ligneNum; i++) {
        printf("hands[%d] = %s\n", i, hands[i]);
        printf("bids[%d] = %d\n", i, bids[i]);
    }

    //determine the type
    for (int i = 0; i < ligneNum; i++) {
        types[i] = find_type(hands[i]);
        printf("types[%d] = %d\n", i, types[i]);
    }

    //order hands
    orderHands();

    //print handsInt
    for (int i = 0; i < ligneNum; i++) {
        printf("handsInt[%d] = ", i);
        for (int j = 0; j < 5; j++) {
            printf("%d ", handsInt[i][j]);
        }
        printf("\n");
    }

}