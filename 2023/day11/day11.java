import java.io.File;
import java.util.Map;
import java.util.Scanner;
import java.util.concurrent.ConcurrentHashMap;

public class day11 {

    public final static int SIZE = 140;
    public static int originalsize = SIZE;
    public static long[][] matrix = new long[SIZE][SIZE];

    public static Map<Long, Long[]> galaxies = new ConcurrentHashMap<Long, Long[]>();

    public static void main(String[] args) {
        try {

            File file = new File("input");
            Scanner sc = new Scanner(file);

            long numberOfGalaxies = 1;

            int c = 0;
            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                char[] lineArray = line.toCharArray();

                
                for (int l = 0; l < lineArray.length; l++) {
                    if (lineArray[l] == '.') {
                        matrix[c][l] = 0;
                    } else if (lineArray[l] == '#') {
                        matrix[c][l] = numberOfGalaxies;
                        galaxies.put((long) numberOfGalaxies, new Long[]{(long) c, (long) l});
                        numberOfGalaxies++;
                    }
                }
                c++;
            }
            numberOfGalaxies--;
            System.out.println("Number of galaxies: " + numberOfGalaxies);
            System.out.println("adding missing lines");

            boolean galaxyEncountered = false;
            long offset = 0;

            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    if (matrix[i][j] != 0) {
                        galaxyEncountered = true;
                    }
                }
                if (!galaxyEncountered) {
                    System.out.println("No galaxy encountered at line" + i);
                    for (Map.Entry<Long, Long[]> entry : galaxies.entrySet()) {
                        Long[] coordinates = entry.getValue();
                        if (coordinates[0] > i + offset) {
                            System.out.println("Galaxy " + entry.getKey() + " is being moved down from l :" + coordinates[0] + ", c :" + coordinates[1]);
                            coordinates[0] = coordinates[0] + 1000000 - 1;
                            System.out.println("Galaxy " + entry.getKey() + " is now at l " + coordinates[0] + ", c " + coordinates[1]);
                        }
                    }
                    offset+=1000000 - 1;
                    
                }
                galaxyEncountered = false;
            }

            offset = 0;
            for (int i = 0; i < SIZE; i++) {
                for (int j = 0; j < SIZE; j++){
                    if (matrix[j][i] != 0) {
                        galaxyEncountered = true;
                    }
                }
                if (!galaxyEncountered) {
                    System.out.println("No galaxy encountered at column " + i);
                    for (Map.Entry<Long, Long[]> entry : galaxies.entrySet()) {
                        Long[] coordinates = entry.getValue();
                        if (coordinates[1] > i + offset) {
                            System.out.println("Galaxy " + entry.getKey() + " is being moved right from l :" + coordinates[0] + ", c :" + coordinates[1]);
                            coordinates[1] = coordinates[1] + 1000000 - 1;
                            System.out.println("Galaxy " + entry.getKey() + " is now at " + coordinates[0] + ", " + coordinates[1]);
                        }
                    }
                    offset+=1000000 - 1;
                    
                }
                galaxyEncountered = false;
            }

            for (Map.Entry<Long, Long[]> entry : galaxies.entrySet()) {
                Long[] coordinates = entry.getValue();
                System.out.println("Galaxy " + entry.getKey() + " is at " + coordinates[0] + ", " + coordinates[1]);
            }

            System.out.println("Calculating distances");

            long sumOfDistances = 0;

            for (Map.Entry<Long, Long[]> entry : galaxies.entrySet()) {
                Long[] coordinates = entry.getValue();
                long key = entry.getKey();
                galaxies.remove(key);

                for (Map.Entry<Long, Long[]> entry2 : galaxies.entrySet()) {
                    Long[] coordinates2 = entry2.getValue();
                    long key2 = entry2.getKey();

                    long xdiff = Math.abs(coordinates[0] - coordinates2[0]);
                    long ydiff = Math.abs(coordinates[1] - coordinates2[1]);

                    long distance = xdiff + ydiff;

                    System.out.println("Distance between " + key + " and " + key2 + " is " + distance);

                    sumOfDistances += distance;
                }
            }

            System.out.println("Sum of distances: " + sumOfDistances);
            sc.close();
        } catch (Exception e) {
            System.out.println(e);
        }
    }
}