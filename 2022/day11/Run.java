import java.util.Arrays;

public class Run {

    public static long worry_level = 0;

    public static int modulo = 2*13*3*17*19*7*11*5;

    public static void main(String[] args) {
        monkey monkey0 = new monkey(0, new long[]{89L,95L,92L,64L,87L,68L}, "mult", 11, 2, 7, 4);
        monkey monkey1 = new monkey(1, new long[]{87L, 67L}, "sum", 1, 13, 3, 6);
        monkey monkey2 = new monkey(2, new long[]{95L, 79L, 92L, 82L, 60L}, "sum", 6, 3, 1, 6);
        monkey monkey3 = new monkey(3, new long[]{67L, 97L, 56L}, "square", 0, 17, 7, 0);
        monkey monkey4 = new monkey(4, new long[]{80L, 68L, 87L, 94L, 61L, 59L, 50L, 68L}, "mult", 7, 19, 5, 2);
        monkey monkey5 = new monkey(5, new long[]{73L, 51L, 76L, 59L}, "sum", 8, 7, 2, 1);
        monkey monkey6 = new monkey(6, new long[]{92L}, "sum", 5, 11, 3, 0);
        monkey monkey7 = new monkey(7, new long[]{99L, 76L, 78L, 76L, 79L, 90L, 89L}, "sum", 7, 5, 4, 5);


        monkey[] monkeys = new monkey[]{monkey0, monkey1, monkey2, monkey3, monkey4, monkey5, monkey6, monkey7};

        

        //circle through each monkey of the monkeys list 20 times
        for (int i = 1; i < 10001; i++) {
            for (monkey monkey : monkeys) {
                while (monkey.getListLength() > 0) {
                    monkey.changeWorryLevel();
                    int itemSentTo = monkey.itemSentTo();
                    monkeys[itemSentTo].addToList(worry_level);
                    monkey.removeFromList();
                }
            }

            System.out.println("== After round " + i + " ==");
            for (monkey monkey : monkeys) {
              System.out.println("  Monkey " + monkey.id + " inspected items " + monkey.number_of_inspections + " times.");
            }
        }

        long max_number_of_inspections = 0;
        long second_max_number_of_inspections = 0;

        //print out the final list of each monkey
        for (monkey monkey : monkeys) {
            System.out.println("Monkey " + monkey.id + " has a list of " + monkey.getListLength() + " items and inspected " + monkey.number_of_inspections + " items");
            System.out.println("  " + Arrays.toString(monkey.list));
            if (monkey.number_of_inspections > max_number_of_inspections) {
                second_max_number_of_inspections = max_number_of_inspections;
                max_number_of_inspections = monkey.number_of_inspections;
            } else if (monkey.number_of_inspections > second_max_number_of_inspections) {
                second_max_number_of_inspections = monkey.number_of_inspections;
            }
        }

        System.out.println("The monkey with the most inspections inspected " + max_number_of_inspections + " items");
        System.out.println("The monkey with the second most inspections inspected " + second_max_number_of_inspections + " items");

        System.out.println("The level of monkey business is " + (max_number_of_inspections * second_max_number_of_inspections) + "");
        

    }

}
