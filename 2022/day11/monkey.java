import java.util.*;
import java.io.*;

public class monkey {

    public int id;
    // int list
    public int[] list;

    public String operation;
    public int operation_int;

    public int divisible;

    public int throw_true;
    public int throw_false;

    public int number_of_inspections = 0;

    public monkey(int id, int[] list, String operation, int operation_int, int divisible, int throw_true, int throw_false) {
        this.id = id;
        this.list = list;
        this.operation = operation;
        this.divisible = divisible;
        this.throw_true = throw_true;
        this.throw_false = throw_false;
        this.operation_int = operation_int;
    }

    void changeWorryLevel() {
        Run.worry_level = 0;
        System.out.println("  Monkey inspects an item with a worry level of " + list[0]);
        this.number_of_inspections++;
        switch (operation) {
            case "sum": {
                Run.worry_level = (list[0] + operation_int);
                System.out.println("    Worry level increseases by " + operation_int + " to " + Run.worry_level);
                Run.worry_level = Run.worry_level/3;
                System.out.println("    Monkey gets bored with item. Worry level is divided by 3 to " + Run.worry_level);
                break;
            }
            case "mult": {
                Run.worry_level = (list[0] * operation_int);
                System.out.println("    Worry level is multiplied by " + operation_int + " to " + Run.worry_level);
                Run.worry_level = Run.worry_level/3;
                System.out.println("    Monkey gets bored with item. Worry level is divided by 3 to " + Run.worry_level);
                break;
            }
            case "square": {
                Run.worry_level = (list[0] * list[0]);
                System.out.println("    Worry level is squared to " + Run.worry_level);
                Run.worry_level = Run.worry_level/3;
                System.out.println("    Monkey gets bored with item. Worry level is divided by 3 to " + Run.worry_level);
                break;
            }
        }
    }

    int itemSentTo(){
        int itemSentTo = 0;
        if (Run.worry_level % divisible == 0) {
            itemSentTo = throw_true;
            System.out.println("    Current worry level is divisible by " + divisible );
            System.out.println("    Monkey throws item with worry level of " + Run.worry_level + "to monkey " + throw_true);
        } else {
            itemSentTo = throw_false;
            System.out.println("    Current worry level is not divisible by " + divisible );
            System.out.println("    Monkey throws item with worry level of " + Run.worry_level + "to monkey " + throw_false);
        }
        return itemSentTo;
    }

    int getListLength() {
        return list.length;
    }

    void addToList(int item) {
        int[] newList = new int[list.length + 1];
        for (int i = 0; i < list.length; i++) {
            newList[i] = list[i];
        }
        newList[list.length] = item;
        list = newList;
    }

    void removeFromList(){
        //remove the first element of the list
        int[] newList = new int[list.length - 1];
        for (int i = 0; i < list.length - 1; i++) {
            newList[i] = list[i + 1];
        }
        list = newList;
    }

}