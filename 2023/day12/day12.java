import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class day12 {

    public static final int SIZE = 250;

    public static void main(String[] args){
        try {

            File file = new File("input");
            Scanner sc = new Scanner(file);

            int totalNumberOfPossibilities = 0;
            int index = 1;

            while (sc.hasNextLine()) {

                List<Character> springs = new ArrayList<Character>();
                List<Integer> rules = new ArrayList<Integer>();

                String line = sc.nextLine();
                
                String[] parts = line.split(" ");
                
                for(int i = 0; i < 5; i++) {
                    for(char c : parts[0].toCharArray()){
                        springs.add(c);
                    }
                    if (i < 4 ) {
                        springs.add('?');
                    }
                }

                //System.out.println(springs);

                String[] rulesStr = parts[1].split(",");
                
                for(int i = 0; i < 5; i++) {
                    for (String rule : rulesStr) {
                        rules.add(Integer.parseInt(rule));
                    }
                }

                //System.out.println(rules);

                int numberOfPossibilities = numberOfSolutions(springs, rules);

                System.out.println("Number of possibilities of " + index + ": " + numberOfPossibilities);

                index++;

                totalNumberOfPossibilities += numberOfPossibilities;

            }

            System.out.println("Total number of possibilities: " + totalNumberOfPossibilities);


        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static int numberOfSolutions(List<Character> springs, List<Integer> rules) throws Exception {
       
        if (springs.isEmpty()) {
            if (rules.isEmpty()) {
                //System.out.println("solution found");
                return 1;
            } else {
                return 0;
            }
        }

        if (rules.isEmpty()) {
            if (springs.contains('#')) {
                return 0;
            } else {
                //System.out.println("solution found");
                return 1;
            }
        }

        char nextSpring = springs.get(0);
        List<Character> remainingSprings = springs.subList(1, springs.size());

        if (nextSpring == '.') {
            //System.out.println("removing dot and continuing with " + remainingSprings + " and " + rules);
            return numberOfSolutions(remainingSprings, rules);
        }

        if (nextSpring == '#') {
            //System.out.println("entering group");
            int rule = rules.get(0);
            //System.out.println("rule: " + rule);

            boolean enoughSpace = (springs.size() >= rule);
            if(!enoughSpace) {
                //System.out.println("group not possible with " + springs + " and " + rules + " returning 0");
                return 0;
            }

            if (enoughSpace) {
                //System.out.println("enough space");
            } 

            boolean isPossible = true;
            for (int i = 0; i < rule; i++) {
                if (springs.get(i) == '.') {
                    isPossible = false;
                }
            }
            if(!isPossible) {
                //System.out.println("group not possible with " + springs + " and " + rules + " returning 0");
                return 0;
            }

            if (isPossible) {
                //System.out.println("is possible");
            }

            boolean isRightSize = false;
            if (enoughSpace) {
                if (springs.size() == rule) {
                    isRightSize = true;
                } else if (springs.get(rule) != '#') {
                    isRightSize = true;
                }
            }
            if(!isRightSize) {
                //System.out.println("group not possible with " + springs + " and " + rules + " returning 0");
                return 0;
            }

            if (isRightSize) {
                //System.out.println("is right size");
            }

            if (enoughSpace && isPossible && isRightSize) {
                List<Integer> remainingRules = rules.subList(1, rules.size());
                List<Character> remainingSpringsAfterGroup = springs;
                for (int i = 0; i < rule; i++) {
                    remainingSpringsAfterGroup.removeFirst();
                }
                if(!remainingSpringsAfterGroup.isEmpty()) {
                    remainingSpringsAfterGroup.removeFirst();
                }
                //System.out.println("removing group and continuing with " + remainingSpringsAfterGroup + " and " + remainingRules);
                return numberOfSolutions(remainingSpringsAfterGroup, remainingRules);
            } else {
                //System.out.println("group not possible with " + springs + " and " + rules + " returning 0");
                return 0;
            }
        }

        if (nextSpring == '?') {
            //System.out.println("entering question mark");
            // try with a dot
            List<Character> remainingSpringsDot = new ArrayList<Character>(remainingSprings);
            remainingSpringsDot.addFirst('.');
            //System.out.println("continuing as " + remainingSpringsDot + " and " + rules);
            int numberOfSolutionsDot = numberOfSolutions(remainingSpringsDot, rules);

            // try with a #
            List<Character> remainingSpringsHash = new ArrayList<Character>(remainingSprings);
            remainingSpringsHash.addFirst('#');
            //System.out.println("continuing as " + remainingSpringsHash + " and " + rules);
            int numberOfSolutionsHash = numberOfSolutions(remainingSpringsHash, rules);

            return numberOfSolutionsDot + numberOfSolutionsHash;
        }
        
        
        return 0;
    }

}