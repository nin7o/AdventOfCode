import java.io.File;
import java.io.FileWriter;
import java.util.Scanner;

public class modifyinput {

    public static final int SIZE = 140;
    public static char[][] matrix = new char[SIZE][SIZE];
    public static final int NEWSIZE = 420;
    public static char[][] newmatrix = new char[NEWSIZE][NEWSIZE];

    public static void main(String[] args) {

        try {

            File file = new File("input");
            Scanner sc = new Scanner(file);

            int ci = 0;
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                char[] lineArray = line.toCharArray();

                
                for (int l = 0; l < lineArray.length; l++) {
                    matrix[ci][l] = lineArray[l];
                }
                ci++;
            }

            for (int i = 0; i < NEWSIZE; i++) {
                for (int j = 0; j < NEWSIZE; j++){
                    newmatrix[i][j] = '.';
                }
            }

            for (int c = 0; c < SIZE; c++) {
                for (int l = 0; l < SIZE; l++) {
                    int newc = c * 3 + 1;
                    int newl = l * 3 + 1;

                    switch (matrix[c][l]) {
                        case '|':
                            newmatrix[newc][newl] = '|';
                            newmatrix[newc+1][newl] = '|';
                            newmatrix[newc-1][newl] = '|';
                            break;

                        case '-':
                            newmatrix[newc][newl] = '-';
                            newmatrix[newc][newl+1] = '-';
                            newmatrix[newc][newl-1] = '-';
                            break;

                        case 'L':
                            newmatrix[newc][newl] = 'L';
                            newmatrix[newc][newl + 1] = '-';
                            newmatrix[newc - 1][newl] = '|';
                            break;
                        case 'S':
                            newmatrix[newc][newl] = 'S';
                            newmatrix[newc][newl - 1] = '-';
                            newmatrix[newc - 1][newl] = '|';
                            break;
                        case 'J':
                            newmatrix[newc][newl] = 'J';
                            newmatrix[newc][newl - 1] = '-';
                            newmatrix[newc - 1][newl] = '|';
                            break;

                        case '7':
                            newmatrix[newc][newl] = '7';
                            newmatrix[newc][newl - 1] = '-';
                            newmatrix[newc + 1][newl] = '|';
                            break;

                        case 'F':
                            newmatrix[newc][newl] = 'F';
                            newmatrix[newc][newl + 1] = '-';
                            newmatrix[newc + 1][newl] = '|';
                            break;
                    }
                }
            }


            File file2 = new File("newinput");
            FileWriter writer = new FileWriter(file2);

            for (int i = 0; i < NEWSIZE; i++) {
                for (int j = 0; j < NEWSIZE; j++){
                    writer.write(newmatrix[i][j]);
                }
                writer.write("\n");
            }

            writer.close();

        } catch (Exception e) {
            System.out.println(e);
        }

    }
    
}
