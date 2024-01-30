import java.io.File;
import java.util.Scanner;

public class day10 {

    //char matrix
    public static final int SIZE = 420;
    public static char[][] matrix = new char[SIZE][SIZE];
    public static int[][] lengthmatrix = new int[SIZE][SIZE];
    public static int[][] oldlengthmatrix = new int[SIZE][SIZE];

    public static final int finalmatrixSIZE = 140;
    public static int[][] finalmatrix = new int[finalmatrixSIZE][finalmatrixSIZE];
    


    public static void main(String[] args) {
        try{

            File file = new File("newinput");
            Scanner sc = new Scanner(file);

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    matrix[i][j] = '.';
                }
            }

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    lengthmatrix[i][j] = 0;
                }
            }

            int ci = 0;
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                char[] lineArray = line.toCharArray();

                
                for (int l = 0; l < lineArray.length; l++) {
                    matrix[ci][l] = lineArray[l];
                }
                ci++;
            }

            // look for the coordinates of the S char
            int l = 0;
            int c = 0;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    if (matrix[i][j] == 'S') {
                        l = i;
                        c = j;
                    }
                }
            }


            int previousC = c;
            int previousL = l;

            int currentC = c - 1;
            int currentL = l;

            int distance = 1;
            lengthmatrix[l][c] = 1;
            lengthmatrix[currentL][currentC] = 1;

            while(true) {
                int[] nextCoordinates = nextCoordinates(currentC, currentL, previousC, previousL);
                previousC = currentC;
                previousL = currentL;
                currentC = nextCoordinates[0];
                currentL = nextCoordinates[1];
                distance++;
                //lengthmatrix[currentL][currentC] = distance;
                lengthmatrix[currentL][currentC] = 1;

                //Thread.sleep(3000);

                if (matrix[currentL][currentC] == 'S') {

                    break;
                }
                
            }

            

            
            //make all sides of the matrix 2
            for (int i = 0; i < SIZE; i++) {
                lengthmatrix[i][0] = 2;
                lengthmatrix[i][SIZE - 1] = 2;
            }

            for (int i = 0; i < SIZE; i++) {
                lengthmatrix[0][i] = 2;
                lengthmatrix[SIZE - 1][i] = 2;
            }

            oldlengthmatrix = lengthmatrix;
            boolean change = true;

            while (change) {
                change = false;
                for (int i = 1; i < SIZE - 1; i++) {
                    for (int j = 1; j < SIZE - 1; j++){
                        if (lengthmatrix[i][j] == 0) {
                            if (lengthmatrix[i][j - 1] == 2 || lengthmatrix[i][j + 1] == 2 || lengthmatrix[i - 1][j] == 2 || lengthmatrix[i + 1][j] == 2) {
                                lengthmatrix[i][j] = 2;
                                change = true;
                            }
                        }
                    }
                }
                oldlengthmatrix = lengthmatrix;
            }
            

            //regenerate the orginal matrix 
            for (int i = 1; i < SIZE; i+=3) {
                for (int j = 1; j < SIZE; j+=3){
                    finalmatrix[(i-1)/3][(j-1)/3] = lengthmatrix[i][j];
                }
            }


            //print the final matrix with colors for 0, 1 and 2 
            for (int i = 0; i < finalmatrixSIZE; i++) {
                for (int j = 0; j < finalmatrixSIZE; j++){
                    if (finalmatrix[i][j] == 0) {
                        System.out.print("\u001B[31m" + finalmatrix[i][j] + "\u001B[0m");
                    } else if (finalmatrix[i][j] == 1) {
                        System.out.print("\u001B[32m" + finalmatrix[i][j] + "\u001B[0m");
                    } else if (finalmatrix[i][j] == 2) {
                        System.out.print("\u001B[34m" + finalmatrix[i][j] + "\u001B[0m");
                    } else {
                        System.out.print(finalmatrix[i][j]);
                    }
                }
                System.out.println();
            }
            
                        




            int count = 0;

            for (int i = 1; i < finalmatrixSIZE - 1; i++) {
                for (int j = 1; j < finalmatrixSIZE - 1; j++){
                    if (finalmatrix[i][j] == 0) {
                        count++;
                    }
                }
            } 

            System.out.println("count: " + count);
            












            sc.close();
        } catch (Exception e) {
            e.printStackTrace();
        }

    }

    public static int[] nextCoordinates(int currentC, int currentL, int previousC, int previousL) {
        int[] coordinates = new int[2];
        int nextC = 0;
        int nextL = 0;

        char currentChar = matrix[currentL][currentC];



        switch (currentChar) {
            case '|':
                if (previousL == currentL - 1) {
                    nextL = currentL + 1;
                    nextC = currentC;
                } else {
                    nextL = currentL - 1;
                    nextC = currentC;
                }
                break;

            case '-':
                if (previousC == currentC - 1) {
                    nextC = currentC + 1;
                    nextL = currentL;
                } else {
                    nextC = currentC - 1;
                    nextL = currentL;
                }
                break;

            case 'L':
                if (previousC == currentC) {
                    nextC = currentC + 1;
                    nextL = currentL;
                } else {
                    nextC = currentC;
                    nextL = currentL - 1;
                }
                break;

            case 'J':
                if (previousC == currentC) {
                    nextC = currentC - 1;
                    nextL = currentL;
                } else {
                    nextC = currentC;
                    nextL = currentL - 1;
                }
                break;

            case '7':
                if (previousC == currentC) {
                    nextC = currentC - 1;
                    nextL = currentL;
                } else {
                    nextC = currentC;
                    nextL = currentL + 1;
                }
                break;

            case 'F':
                if (previousC == currentC) {
                    nextC = currentC + 1;
                    nextL = currentL;
                } else {
                    nextC = currentC;
                    nextL = currentL + 1;
                }
                break;

        }
        coordinates[0] = nextC;
        coordinates[1] = nextL;

        return coordinates;
    }


}