#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 5000

#include <stdbool.h>

//create a matric of int of size 99 x 99
int mat[99][99];

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

    int i = 0;

    //------------------[Read input file]------------------//
    while (fgets(ligne, MAX, fptr)) {

        ligne[strcspn(ligne, "\n")] = '\0';

        //add each line to the matrix
        for (int j = 0; j < strlen(ligne); j++) {
            mat[i][j] = ligne[j] - '0';
        }

        i++;

    }

    //print the matrix
    for (int i = 0; i < 99; i++) {
        for (int j = 0; j < 99; j++) {
            
            printf("%d", mat[i][j]);
        }
        printf("\n");
    }

    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");
    printf("\n");

    int count = 0;
    int top_scenic_score = 0;

    for (int i = 0; i < 99; i++) {
        for (int j = 0; j < 99; j++) {

            int scenic_score_up = 0;
            int scenic_score_down = 0;
            int scenic_score_left = 0;
            int scenic_score_right = 0;
            
            int tree_size = mat[i][j];

            bool up_visible = true;
            bool down_visible = true;
            bool left_visible = true;
            bool right_visible = true;

            for (int k = i - 1; k >= 0; k--) {
                if (mat[k][j] >= tree_size) {
                    left_visible = false;
                }
            }

            for (int k = i - 1; k >= 0; k--) {
                scenic_score_left++;
                if (mat[k][j] >= tree_size) {
                    break;
                }
            }

            for (int k = i + 1; k < 99; k++) {
                if (mat[k][j] >= tree_size) {
                    right_visible = false;
                }
            }

            for (int k = i + 1; k < 99; k++) {
                scenic_score_right++;
                if (mat[k][j] >= tree_size) {
                    break;
                }
            }

            for (int k = j - 1; k >= 0; k--) {
                if (mat[i][k] >= tree_size) {
                    up_visible = false;
                }
            }

            for (int k = j - 1; k >= 0; k--) {
                scenic_score_up++;
                if (mat[i][k] >= tree_size) {
                    break;
                }
            }

            for (int k = j + 1; k < 99; k++) {
                if (mat[i][k] >= tree_size) {
                    down_visible = false;
                }
            }

            for (int k = j + 1; k < 99; k++) {
                scenic_score_down++;
                if (mat[i][k] >= tree_size) {
                    break;
                }
            }

            bool visible = up_visible || down_visible || left_visible || right_visible;

            if (visible) {
                //print in green
                printf("\033[0;32m%d\033[0;0m", tree_size);
                count++;
            } else {
                //print in red
                printf("\033[0;31m%d\033[0;0m", tree_size);
            }

            int scenic_score = scenic_score_up * scenic_score_down * scenic_score_left * scenic_score_right;

            if (scenic_score > top_scenic_score) {
                top_scenic_score = scenic_score;
            }

        }

        printf("\n");
    }

    printf("\n-------------------------[top_scenic_score : %d]-------------------------\n", top_scenic_score);

    printf("\n-------------------------[count : %d]-------------------------\n", count);

}