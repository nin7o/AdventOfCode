import java.io.File;
import java.util.ArrayList;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.concurrent.ConcurrentHashMap;

public class day12 {

    public static final int SIZE = 250;
    public static Map<String, Long> cache = new ConcurrentHashMap<String, Long>();

    public static void main(String[] args){
        try {

            File file = new File("input");
            Scanner sc = new Scanner(file);

            long totalNumberOfPossibilities = 0;
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
                        springs.addLast('?');
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

                long numberOfPossibilities = numberOfSolutions(springs, rules);

                System.out.println("Number of possibilities of " + index + ": " + numberOfPossibilities);

                index++;

                totalNumberOfPossibilities += numberOfPossibilities;

                cache.clear();

            }

            System.out.println("Total number of possibilities: " + totalNumberOfPossibilities);


        } catch (Exception e) {
            System.out.println(e);
        }
    }

    public static long numberOfSolutions(List<Character> springs, List<Integer> rules) throws Exception {
        
        //System.out.println(cache);
        String key = toString(springs, rules);
        if (cache.containsKey(key)) {
            //System.out.println("cache hit");
            return cache.get(key);
        } else {
            //System.out.println("cache miss");
        }
       
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
            long returnvalue = numberOfSolutions(remainingSprings, rules);
            cache.put(key, returnvalue);
            return returnvalue;
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
                long returnvalue =  numberOfSolutions(remainingSpringsAfterGroup, remainingRules);
                cache.put(key, returnvalue);
                return returnvalue;
            } else {
                //System.out.println("group not possible with " + springs + " and " + rules + " returning 0");
                cache.put(key, 0L);
                return 0;
            }
        }

        if (nextSpring == '?') {
            //System.out.println("entering question mark");
             //try with a dot
            List<Character> remainingSpringsDot = new ArrayList<Character>(remainingSprings);
            remainingSpringsDot.addFirst('.');
            //System.out.println("continuing as " + remainingSpringsDot + " and " + rules);
            long numberOfSolutionsDot = numberOfSolutions(remainingSpringsDot, rules);

             //try with a #
            List<Character> remainingSpringsHash = new ArrayList<Character>(remainingSprings);
            remainingSpringsHash.addFirst('#');
            //System.out.println("continuing as " + remainingSpringsHash + " and " + rules);
            long numberOfSolutionsHash = numberOfSolutions(remainingSpringsHash, rules);

            cache.put(key, numberOfSolutionsDot + numberOfSolutionsHash);

            return numberOfSolutionsDot + numberOfSolutionsHash;
        }
        
        
        return 0;
    }

    public static String toString(List<Character> springs, List<Integer> rules) {
        StringBuilder sb = new StringBuilder();
        for (Character c : springs) {
            sb.append(c);
        }
        for (Integer i : rules) {
            sb.append(i.toString());
        }
        return sb.toString();
    }

}