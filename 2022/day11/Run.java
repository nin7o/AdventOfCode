import java.util.Arrays;

public class Run {

    public static int worry_level = 0;

    public static void main(String[] args) {
        monkey monkey0 = new monkey(0, new int[]{89,95,92,64,87,68}, "mult", 11, 2, 7, 4);
        monkey monkey1 = new monkey(1, new int[]{87, 67}, "sum", 1, 13, 3, 6);
        monkey monkey2 = new monkey(2, new int[]{95, 79, 92, 82, 60}, "sum", 6, 3, 1, 6);
        monkey monkey3 = new monkey(3, new int[]{67, 97, 56}, "square", 0, 17, 7, 0);
        monkey monkey4 = new monkey(4, new int[]{80, 68, 87, 94, 61, 59, 50, 68}, "mult", 7, 19, 5, 2);
        monkey monkey5 = new monkey(5, new int[]{73, 51, 76, 59}, "sum", 8, 7, 2, 1);
        monkey monkey6 = new monkey(6, new int[]{92}, "sum", 5, 11, 3, 0);
        monkey monkey7 = new monkey(7, new int[]{99, 76, 78, 76, 79, 90, 89}, "sum", 7, 5, 4, 5);


        monkey[] monkeys = new monkey[]{monkey0, monkey1, monkey2, monkey3, monkey4, monkey5, monkey6, monkey7};

        //circle through each monkey of the monkeys list 20 times
        for (int i = 0; i < 20; i++) {
            for (monkey monkey : monkeys) {
                while (monkey.getListLength() > 0) {
                    monkey.changeWorryLevel();
                    int itemSentTo = monkey.itemSentTo();
                    monkeys[itemSentTo].addToList(worry_level);
                    monkey.removeFromList();
                }
            }
        }

        //print out the final list of each monkey
        for (monkey monkey : monkeys) {
            System.out.println("Monkey " + monkey.id + " has a list of " + monkey.getListLength() + " items and inspected " + monkey.number_of_inspections + " items");
            System.out.println("  " + Arrays.toString(monkey.list));
        }
        

    }

}