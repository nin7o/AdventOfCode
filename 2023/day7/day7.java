import java.io.File;
import java.util.ArrayList;
import java.util.Collection;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Scanner;
import java.util.logging.Handler;

@SuppressWarnings("unchecked")
public class day7 {

    public static Map<Integer, Hand> FIVE = new HashMap<Integer, Hand>();
    public static Map<Integer, Hand> FOUR = new HashMap<Integer, Hand>();
    public static Map<Integer, Hand> FULL = new HashMap<Integer, Hand>();
    public static Map<Integer, Hand> THREE = new HashMap<Integer, Hand>();
    public static Map<Integer, Hand> TWOPAIRS = new HashMap<Integer, Hand>();
    public static Map<Integer, Hand> PAIR = new HashMap<Integer, Hand>();
    public static Map<Integer, Hand> HIGHCARD = new HashMap<Integer, Hand>();
    
    public static void main(String[] args) {
        //read input with a scanner file in the form "string number"
        File input = new File("input");
        
        try {
            Scanner sc = new Scanner(input);

            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                String[] parts = line.split(" ");
                String cards = parts[0];
                int bet = Integer.parseInt(parts[1]);
                System.out.println(cards + " " + bet);

                Hand hand = new Hand(cards, bet);
                hand.computeHashMap();
                System.out.println("HashMap: " + hand.cardValues);
                String handType = hand.computeHandType();
                System.out.println(handType);
                switch (handType) {
                    case "FIVE":
                        FIVE.put(hand.convertirEnDecimal(), hand);
                        break;

                    case "FOUR":
                        FOUR.put(hand.convertirEnDecimal(), hand);
                        break;

                    case "FULL":
                        FULL.put(hand.convertirEnDecimal(), hand);
                        break;

                    case "THREE":  
                        THREE.put(hand.convertirEnDecimal(), hand);
                        break;

                    case "TWOPAIRS":
                        TWOPAIRS.put(hand.convertirEnDecimal(), hand);
                        break;

                    case "PAIR":
                        PAIR.put(hand.convertirEnDecimal(), hand);
                        break;

                    case "HIGHCARD":
                        HIGHCARD.put(hand.convertirEnDecimal(), hand);
                        break;
                }

                
            }

            //print the hashmap
            System.out.println("FIVE: " + FIVE);
            System.out.println("FOUR: " + FOUR);
            System.out.println("FULL: " + FULL);
            System.out.println("THREE: " + THREE);
            System.out.println("TWOPAIRS: " + TWOPAIRS);
            System.out.println("PAIR: " + PAIR);
            System.out.println("HIGHCARD: " + HIGHCARD);

            //sort hashmaps by key 
            List<Integer> sortedFIVEkeys = new ArrayList<Integer>(FIVE.keySet());
            List<Integer> sortedFOURkeys = new ArrayList<Integer>(FOUR.keySet());
            List<Integer> sortedFULLkeys = new ArrayList<Integer>(FULL.keySet());
            List<Integer> sortedTHREEkeys = new ArrayList<Integer>(THREE.keySet());
            List<Integer> sortedTWOPAIRSkeys = new ArrayList<Integer>(TWOPAIRS.keySet());
            List<Integer> sortedPAIRkeys = new ArrayList<Integer>(PAIR.keySet());
            List<Integer> sortedHIGHCARDkeys = new ArrayList<Integer>(HIGHCARD.keySet());

            Collections.sort(sortedFIVEkeys);
            sortedFIVEkeys = sortedFIVEkeys.reversed();
            Collections.sort(sortedFOURkeys);
            sortedFOURkeys = sortedFOURkeys.reversed();
            Collections.sort(sortedFULLkeys);
            sortedFULLkeys = sortedFULLkeys.reversed();
            Collections.sort(sortedTHREEkeys);
            sortedTHREEkeys = sortedTHREEkeys.reversed();
            Collections.sort(sortedTWOPAIRSkeys);
            sortedTWOPAIRSkeys = sortedTWOPAIRSkeys.reversed();
            Collections.sort(sortedPAIRkeys);
            sortedPAIRkeys = sortedPAIRkeys.reversed();
            Collections.sort(sortedHIGHCARDkeys);
            sortedHIGHCARDkeys = sortedHIGHCARDkeys.reversed();

            System.out.println(sortedFIVEkeys);
            System.out.println(sortedFOURkeys);
            System.out.println(sortedFULLkeys);
            System.out.println(sortedTHREEkeys);
            System.out.println(sortedTWOPAIRSkeys);
            System.out.println(sortedPAIRkeys);
            System.out.println(sortedHIGHCARDkeys);

            // Hand list 
            List<Hand> hands = new ArrayList<Hand>();
            while (sortedFIVEkeys.size() > 0) {
                hands.add(FIVE.get(sortedFIVEkeys.get(0)));
                sortedFIVEkeys.remove(0);
            }
            while (sortedFOURkeys.size() > 0) {
                hands.add(FOUR.get(sortedFOURkeys.get(0)));
                sortedFOURkeys.remove(0);
            }
            while (sortedFULLkeys.size() > 0) {
                hands.add(FULL.get(sortedFULLkeys.get(0)));
                sortedFULLkeys.remove(0);
            }
            while (sortedTHREEkeys.size() > 0) {
                hands.add(THREE.get(sortedTHREEkeys.get(0)));
                sortedTHREEkeys.remove(0);
            }
            while (sortedTWOPAIRSkeys.size() > 0) {
                hands.add(TWOPAIRS.get(sortedTWOPAIRSkeys.get(0)));
                sortedTWOPAIRSkeys.remove(0);
            }
            while (sortedPAIRkeys.size() > 0) {
                hands.add(PAIR.get(sortedPAIRkeys.get(0)));
                sortedPAIRkeys.remove(0);
            }
            while (sortedHIGHCARDkeys.size() > 0) {
                hands.add(HIGHCARD.get(sortedHIGHCARDkeys.get(0)));
                sortedHIGHCARDkeys.remove(0);
            }

            hands = hands.reversed();
            System.out.println(hands);

            int i = 1;
            int flag = 0;

            while (hands.size() > 0) {
                Hand hand = hands.get(0);
                System.out.println(hand.hand + " " + hand.bet + " " + i);
                hands.remove(0);
                flag = flag + hand.bet * i;
                i++;
            }

            System.out.println(flag);
    
        } catch (Exception e) {
            System.out.println("Error: " + e);
        }
    }



}