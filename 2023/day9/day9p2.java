import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class day9p2 {

    public static List<List<Integer>> sequences = new ArrayList<List<Integer>>();

    public static void main(String[] args) {
        try {

            int total = 0;

            File input = new File("input");
            Scanner sc = new Scanner(input);

            while(sc.hasNextLine()){
                String line = sc.nextLine();
                String[] parts = line.split(" ");
                List<Integer> numbers = new ArrayList<Integer>();

                int firstvalue = 0;

                for (String part : parts){
                    numbers.add(Integer.parseInt(part));
                }

                sequences.add(numbers);

                while (!onlyZeros(sequences.getLast())) {

                    List<Integer> sequence = sequences.getLast();

                    List<Integer> newSequence = new ArrayList<Integer>();

                    for (int i = 1; i < sequence.size(); i++){
                        int left = sequence.get(i - 1);
                        int right = sequence.get(i);
                        newSequence.add(right - left);
                    }

                    sequences.add(newSequence);

                }



                for (int i = sequences.size() - 1; i >= 1; i--){
                    int diffresult = sequences.get(i).getFirst();
                    int numtosubstractto = sequences.get(i - 1).getFirst();

                    firstvalue = numtosubstractto - diffresult;
                    sequences.get(i - 1).addFirst(firstvalue);
                }

                for (int i = 0; i < sequences.size(); i++){
                    System.out.println(sequences.get(i));
                }

                System.out.println("----------------------");

                total += firstvalue;

                sequences.clear();



            }

            System.out.println("----[ Total : " + total + " ]----");


            sc.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static boolean onlyZeros(List<Integer> list){
        //check if the list is only zeros 
        boolean onlyZeros = true;
        for (int number : list){
            if (number != 0){
                onlyZeros = false;
            }
        }

        return onlyZeros;
    }

}