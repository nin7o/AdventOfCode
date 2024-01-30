import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Map;

public class Hand {

    public String hand = "";
    public int bet = 0;
    public HashMap<String, Integer> cardValues = new HashMap<String, Integer>();

    public Hand(String hand, int bet){
        this.hand = hand;
        this.bet = bet;
    }

    // Définir les poids pour chaque symbole
    private static Map<Character, Integer> poidsSymboles = new HashMap<>();

    static {
        poidsSymboles.put('A', 14);
        poidsSymboles.put('K', 13);
        poidsSymboles.put('Q', 12);
        poidsSymboles.put('J', 1);
        poidsSymboles.put('T', 10);
        poidsSymboles.put('9', 9);
        poidsSymboles.put('8', 8);
        poidsSymboles.put('7', 7);
        poidsSymboles.put('6', 6);
        poidsSymboles.put('5', 5);
        poidsSymboles.put('4', 4);
        poidsSymboles.put('3', 3);
        poidsSymboles.put('2', 2);
    }

    public int convertirEnDecimal(){
        int decimalValue = 0;

        for (int i = 0; i < hand.length(); i++){
            char symbole = hand.charAt(i);
            int valeur = poidsSymboles.get(symbole);
            decimalValue += decimalValue * 15 + valeur;
        }

        return decimalValue;
    }

    public void computeHashMap(){
        //get the card values from the hand 
        //and put them in a hashmap
        for (int i = 0; i < hand.length(); i++){
            String card = hand.substring(i, i+1);
            if (cardValues.containsKey(card)){
                cardValues.put(card, cardValues.get(card) + 1);
            } else {
                cardValues.put(card, 1);
            }
        }
    }

    public String computeHandType(){

        //get the number of jokers 
        int jokers = 0;
        if (cardValues.containsKey("J")){
            jokers = cardValues.get("J");
        }

        //remove jokers from the hashmap
        cardValues.remove("J");

        //get hashmap values and put them in an array
        List<Integer> values = new ArrayList<Integer>();
        for (String key : cardValues.keySet()){
            values.add(cardValues.get(key));
        }

        if (values.size() == 0){
            return "FIVE";
        }

        //sort the array ascending
        values.sort(null);
        values = values.reversed();

        if (jokers == 0){
            

        if (values.get(0) == 5){
            return "FIVE";
        }

        if (values.get(0) == 4){
            return "FOUR";
        }

        if (values.get(0) == 3 && values.get(1) == 2){
            return "FULL";
        }

        if (values.get(0) == 3){
            return "THREE";
        }

        if (values.get(0) == 2 && values.get(1) == 2){
            return "TWOPAIRS";
        }

        if (values.get(0) == 2){
            return "PAIR";
        }

        return "HIGHCARD";
    } else {

        if (values.get(0) + jokers == 5){
            return "FIVE";
        }

        if (values.get(0) + jokers == 4){
            return "FOUR";
        }

        

        if (values.get(0) + jokers == 3 && values.get(1) == 2){
            return "FULL";
        }

        if (values.get(0) + jokers == 3){
            return "THREE";
        }


        if (values.get(0) + jokers == 2 ){
            return "PAIR";
        }

        return "HIGHCARD";

    }
    }
    
}
