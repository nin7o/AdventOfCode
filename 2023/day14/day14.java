import java.io.File;
import java.lang.reflect.Array;
import java.util.ArrayList;
import java.util.HashMap;
import java.util.List;
import java.util.Scanner;

public class day14 {

    public static ArrayList<ArrayList<Character>> map = new ArrayList<ArrayList<Character>>();
    public static ArrayList<ArrayList<Character>> oldMap = new ArrayList<ArrayList<Character>>();

    public static ArrayList<String> mapsInCache = new ArrayList<String>();

    public static HashMap<String, String> cache = new HashMap<String, String>();
    public static long currentCycle = 0L;
    public static final long numOfCycles = 1000000000L;

    public static void main(String[] args) {
        try {
            File file = new File("input");
            Scanner sc = new Scanner(file);

            while (sc.hasNextLine()) {
                String line = sc.nextLine();
                ArrayList<Character> row = new ArrayList<Character>();
                for (char c : line.toCharArray()) {
                    row.add(c);
                }
                map.add(row);
            }

            map = makeCycles(map);

            for(long i = 0; i < numOfCycles; i++){
                //map = make1cycle(map);
            }
            

            //for each row count the number of O
            int flag = 0;
            int count = 0;
            int rowIndex = 0;
            for (ArrayList<Character> row : map) {
                for (char c : row) {
                    if (c == 'O') {
                        count++;
                    }
                }
                //System.out.println("Row " + rowIndex + " has " + count + " O that have the value " + (row.size() - rowIndex) + "each");
                flag += count * (row.size() - rowIndex);
                rowIndex++;
                count = 0;
            }

            System.out.println("Flag: " + flag);
            sc.close();
        } catch (Exception e) {
            e.printStackTrace();
        }
    }

    public static ArrayList<ArrayList<Character>> tiltingSide(String side, ArrayList<ArrayList<Character>> mapOld){
        ArrayList<ArrayList<Character>> newMap = new ArrayList<ArrayList<Character>>();
        ArrayList<ArrayList<Character>> result = new ArrayList<ArrayList<Character>>();
        ArrayList<ArrayList<Character>> returnmap = new ArrayList<ArrayList<Character>>();
        int rowIndex = 0;
        int charIndex = 0;

        switch (side) {
            case "left":
                newMap = mirror(mapOld);
                result = tiltingSide("up", newMap);
                returnmap = mirror(result);
                return returnmap;
        
            case "right":
                newMap = mirror(mapOld);
                result = tiltingSide("down", newMap);
                returnmap = mirror(result);
                return returnmap;
        }

        for (int i = 0; i < mapOld.size(); i++) {

            switch (side){

                case "up":
                    rowIndex = 0;
                    charIndex = 0;
                    for (ArrayList<Character> row : mapOld) {
                        for (char c : row) {
                            if (c == '.' && rowIndex < mapOld.size() - 1) {
                                //get next row 
                                ArrayList<Character> nextRow = mapOld.get(rowIndex + 1);
                                //get next char
                                char nextChar = nextRow.get(charIndex);
                                if (nextChar == 'O') {
                                   row.set(charIndex, 'O');
                                   nextRow.set(charIndex, '.');

                                } 


                            } 
                            charIndex++;
                        }
                        charIndex = 0;
                        rowIndex++;
                    }
                    break;

                case "down":
                    rowIndex = mapOld.size() - 1;
                    charIndex = 0;
                    for (int rowNum = mapOld.size() - 1; rowNum >= 0; rowNum--) {
                        ArrayList<Character> row = mapOld.get(rowNum);
                        rowIndex = rowNum;
                        for (char c : row) {
                            if (c == '.' && rowIndex >0) {
                                //get next row 
                                ArrayList<Character> nextRow = mapOld.get(rowIndex - 1);
                                //get next char
                                char nextChar = nextRow.get(charIndex);
                                if (nextChar == 'O') {
                                   row.set(charIndex, 'O');
                                   nextRow.set(charIndex, '.');

                                } 


                            } 
                            charIndex++;
                        }
                        charIndex = 0;
                        rowIndex++;
                    }
                    break;

            }

            return mapOld;

        }

        return null;

    }

    public static ArrayList<ArrayList<Character>> mirror(ArrayList<ArrayList<Character>> map){
        ArrayList<ArrayList<Character>> newMap = new ArrayList<ArrayList<Character>>();
        // each character of each row of map is concatenated to a new row in newMap
        // so that the first row of map becomes the first column of newMap
        // and the last row of map becomes the last column of newMap
        for (int i = 0; i < map.size(); i++) {
            ArrayList<Character> newRow = new ArrayList<Character>();
            for (int j = 0; j < map.size(); j++) {
                newRow.add(map.get(j).get(i));
            }
            newMap.add(newRow);
        }
        
        return newMap;

    }

    public static ArrayList<ArrayList<Character>> make1cycle(ArrayList<ArrayList<Character>> mapp){

        String mapString = map2string(mapp);
        boolean inCache = cache.containsKey(mapString);

        if (inCache) {
            System.out.println("cache hit!");
            return string2map(cache.get(mapString));
        } else {
            System.out.println("cache miss!");
        }
        ArrayList<ArrayList<Character>> newMap = new ArrayList<ArrayList<Character>>();
        newMap = mapp;
        for (int i = 0; i < mapp.size(); i++) {
            newMap = tiltingSide("up", newMap);
        }
        for (int i = 0; i < mapp.size(); i++) {
            newMap = tiltingSide("left", newMap);
        }
        for (int i = 0; i < mapp.size(); i++) {
            newMap = tiltingSide("down", newMap);
        }
        for (int i = 0; i < mapp.size(); i++) {
            newMap = tiltingSide("right", newMap);
        }

        cache.put(mapString, map2string(newMap));
        mapsInCache.add(mapString);
        
        return newMap;

    }

    public static String map2string(ArrayList<ArrayList<Character>> map){
        StringBuilder sb = new StringBuilder();
        for (ArrayList<Character> row : map) {
            for (char c : row) {
                sb.append(c);
            }
            sb.append("\n");
        }
        return sb.toString();
    }

    public static ArrayList<ArrayList<Character>> string2map(String mapString){
        ArrayList<ArrayList<Character>> map = new ArrayList<ArrayList<Character>>();
        for (String row : mapString.split("\n")) {
            ArrayList<Character> newRow = new ArrayList<Character>();
            for (char c : row.toCharArray()) {
                newRow.add(c);
            }
            map.add(newRow);
        }
        return map;
    }

    public static ArrayList<ArrayList<Character>> makeCycles(ArrayList<ArrayList<Character>> mappa){
        ArrayList<ArrayList<Character>> workingMap = new ArrayList<ArrayList<Character>>();
        workingMap = mappa;
        long oldCacheSize = cache.size();
        long newCacheSize = cache.size();
        System.out.println("Determining loop size");
        ArrayList<ArrayList<Character>> oldMap = new ArrayList<ArrayList<Character>>();
        do {
            oldMap = workingMap;
            workingMap = make1cycle(workingMap);
            currentCycle++;
            oldCacheSize = newCacheSize;
            newCacheSize = cache.size();
        } while (oldCacheSize != newCacheSize);

        System.out.println("Looking for when the loop starts");
        long loopStart = 0;
        for (int i = 0; i < mapsInCache.size(); i++) {
            if (mapsInCache.get(i).equals(map2string(oldMap))) {
                loopStart = i;
                break;
            }
        }
        System.out.println("Loop starts at: " + loopStart);
        int loopSize = mapsInCache.size() - (int) loopStart;
        System.out.println("Loop size: " + loopSize);

        // loopsize plus tard, working map revient à la même chose
        workingMap = oldMap;
        long cyclesLeft = numOfCycles - currentCycle + 1;

        long cyclesToMake = cyclesLeft % loopSize;
        System.out.println("Cycles left: " + cyclesLeft);
        System.out.println("Cycles to make: " + cyclesToMake);

        for (int i = 0; i < cyclesToMake; i++) {
            workingMap = make1cycle(workingMap);
        }


        return workingMap;
        
    }


        
}

/*
.....#....
....#...O#
.....##...
..O#......
......OO#.
.O#...O#.#
....O#....
......OOOO
#...O###.O
#.OOO#..OO

.....#....
....#...O#
.....##...
..O#......
.....OOO#.
.O#...O#.#
....O#...O
.......OOO
#...O###.O
#..OO#..OO
 */