import java.io.File;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;

public class day8 {
    
    public static Map<String, String> leftMap = new HashMap<String, String>();
    public static Map<String, String> rightMap = new HashMap<String, String>();
    public static List<String> startList = new ArrayList<String>();
    public static Map<String, String> endMap = new HashMap<String, String>();
    public static int numberOfInstructions = 0;
    public static String instructions = "";
    public static String saveinstructions = "";
    public static String position = "";

    public static List<String> startingPositionList = new ArrayList<String>();
    public static List<String> newStartingPositionList = new ArrayList<String>();

    public static List<Long> stepsList = new ArrayList<Long>();

    public static void main(String[] args) {
        //read input with a scanner file in the form "string number"
        File input = new File("input");
        
        try {
            Scanner sc = new Scanner(input);

            saveinstructions = sc.nextLine();

            System.out.println(sc.nextLine());

            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                String[] parts = line.split(" = ");
                String key = parts[0];
                startList.add(key);
                if (parts[0].endsWith("A")){
                    startingPositionList.add(key);
                }
                String composantes = parts[1];

                //Remove the first and last character of the string
                composantes = composantes.substring(1, composantes.length() - 1); 
                String[] otherparts = composantes.split(", ");
                String left = otherparts[0];
                String right = otherparts[1];

                leftMap.put(key, left);
                rightMap.put(key, right);
            }

            System.out.println("startingPositionList : " + startingPositionList);

            sc.close();

            for (String start : startList){
                int k = 0;
                instructions = saveinstructions;
                position = start;
                while (!instructions.equals("")){
                    String firstInstruction = instructions.substring(0, 1);
                    instructions = instructions.substring(1, instructions.length());

                    if (firstInstruction.equals("L")){
                        position = leftMap.get(position);
                    } else if (firstInstruction.equals("R")){
                        position = rightMap.get(position);
                    }
                    k++;

                }

                endMap.put(start, position);
                numberOfInstructions = k;;

            }

            System.out.println("numberOfInstructions : " + numberOfInstructions);
            System.out.println("endMap : " + endMap);

            long steps = 0;

            boolean found = false;

            while(!found){
                found = true;

                instructions = saveinstructions;
                String hehe = "";

                while(!instructions.equals("") ){
                    found = true;
                    String firstInstruction = instructions.substring(0, 1);
                    instructions = instructions.substring(1, instructions.length());

                    for (String start : startingPositionList){
                        if (firstInstruction.equals("L")){
                            hehe = leftMap.get(start);
                        } else if (firstInstruction.equals("R")){
                            hehe = rightMap.get(start);
                        }
                        newStartingPositionList.add(hehe);
                    }

                    steps++;
                    startingPositionList = newStartingPositionList;
                    newStartingPositionList = new ArrayList<String>();

                    for (String start : startingPositionList){
                        if(!start.endsWith("Z")){
                            found = false;;
                            newStartingPositionList.add(start);
                        } else {
                            System.out.println("found : " + start + "in steps : " + steps);
                            stepsList.add(steps);
                        }
                    }

                    startingPositionList = newStartingPositionList;
                    newStartingPositionList = new ArrayList<String>();

                    if (steps%1000000 == 0){
                        System.out.println("steps : " + steps);
                    }

                    if (found){
                        break;
                    }

                }

            }

            //find the smallest common multiple of the steps

            long ppcm = calculerPPCM(stepsList.get(0), stepsList.get(1));

            for (int i = 2; i < stepsList.size(); i++){
                ppcm = calculerPPCM(ppcm, stepsList.get(i));
            }

            System.out.println("ppcm : " + ppcm);
                


            System.out.println("position : " + position);

            System.out.println("steps : " + steps);





        } catch (Exception e) {
            e.printStackTrace();
        }
    }

     // Méthode pour calculer le PGCD de deux nombres
     private static long calculerPGCD(long a, long b) {
        while (b != 0) {
            long temp = b;
            b = a % b;
            a = temp;
        }
        return Math.abs(a);
    }

    private static long calculerPPCM(long a, long b) {
        return Math.abs(a * b) / calculerPGCD(a, b);
    }

}
