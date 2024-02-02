import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class day13 {

    public static List<String> columns = new ArrayList<String>();
    public static List<String> lines = new ArrayList<String>();
    public static String line;
    public static long flag = 0;

    public static void main(String[] args){
        try {

            File file = new File("input");
            Scanner sc = new Scanner(file);

            while (sc.hasNextLine()) {

                System.out.println("--------------------[NEW TILE]--------------------");

                while (sc.hasNextLine() && !(line = sc.nextLine()).isEmpty()) {
                    lines.add(line);
                }

                int lineNum = 0;
                int columnNum = 0;
                for (String l : lines) {
                    for (char c : l.toCharArray()) {
                        if (lineNum == 0){
                            columns.add(Character.toString(c));
                        } else {
                            columns.set(columnNum, columns.get(columnNum) + Character.toString(c));
                        }
                        columnNum++;
                    }
                    lineNum++;
                    columnNum = 0;
                }

                System.out.println("Tile parsed");
                for (String l : lines) {
                    System.out.println(l);
                }

                int reflexionIndex = 0;

                for (int i = 1; i < lines.size(); i++) {
                    if (testReflection1(i, lines)) {
                        reflexionIndex = i;
                        System.out.println("Reflexion index lines: " + reflexionIndex);
                        System.out.println("adding " + 100 * reflexionIndex + " to flag");
                        flag += 100 * reflexionIndex;
                        break;
                    }
                }

                if (reflexionIndex == 0) {
                    for (int i = 1; i < columns.size(); i++) {
                        if (testReflection1(i, columns)) {
                            reflexionIndex = i;
                            System.out.println("Reflexion index columns: " + reflexionIndex);
                            System.out.println("adding " + reflexionIndex + " to flag");
                            flag += reflexionIndex;
                            break;
                        }
                    }
                }

                lines.clear();
                columns.clear();

            }

            System.out.println("Flag: " + flag);

            
            sc.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static boolean testReflection(int reflexionIndex, List<String> set) {
        System.out.println("Testing reflexion index " + reflexionIndex + " of " + set.size() + " elements.");
        if (reflexionIndex == 0 || reflexionIndex == set.size()) {
            return false;
        }
        
        boolean isReflection = true;
        for (int i = 0; i < reflexionIndex; i++) {
            int rightIndex = 2*reflexionIndex - 1 - i;

            System.out.println("comparing " + i + " and " + rightIndex + " of " + set.size() + " elements.");

            if (rightIndex < set.size()) {
                String left = set.get(i);
                String right = set.get(rightIndex);
                System.out.println("comparing " + left + " and " + right + " of " + set.size() + " elements.");
                if (!left.equals(right)) {
                    isReflection = false;
                    break;
                }
            }
        }
        return isReflection;
    }

    public static boolean testReflection1(int reflexionIndex, List<String> set) {
        System.out.println("Testing reflexion w/ 1 error index " + reflexionIndex + " of " + set.size() + " elements.");
        int errorCount = 0;
        if (reflexionIndex == 0 || reflexionIndex == set.size()) {
            return false;
        }

        for (int i = 0; i < reflexionIndex; i++) {
            int rightIndex = 2*reflexionIndex - 1 - i;

            System.out.println("comparing " + i + " and " + rightIndex + " of " + set.size() + " elements.");

            if (rightIndex < set.size()) {
                String left = set.get(i);
                String right = set.get(rightIndex);
                System.out.println("comparing " + left + " and " + right + " of " + set.size() + " elements.");
                for (int j = 0; j < left.length(); j++) {
                    if (left.charAt(j) != right.charAt(j)) {
                        errorCount++;
                    }
                }
            }
        }

        if (errorCount == 1) {
            return true;
        } else {
            return false;
        }
        
    }

}