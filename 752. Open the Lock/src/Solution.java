import java.util.*;

public class Solution {

    String toStr(int[] ints) {
        String str = "";
        for(var e : ints) {
            String strLoc = String.valueOf(e);
            str = str + strLoc;
        }
        return str;
    }

    boolean isDead(String[] deadends, String str) {

        for(var s : deadends) {
            if(s.equals(str))
                return true;
        }

        return false;
    }

    int[] strToIntArray(String str) {
        char[] chr = str.toCharArray();

        int[] ins = new int[chr.length];

        for(int j = 0; j < chr.length; j++)
            ins[j] = Character.getNumericValue(chr[j]);

        return ins;
    }

    List<String> genStrings(int[] ints) {

        List<String> strings = new ArrayList<>();

        int[] res = new int[ints.length];

        for(int i = 0; i < ints.length; i++)
            res[i] = ints[i];

        for(int i = 0; i < ints.length; i++) {
            res[i] = ints[i] + 1 < 10 ? ints[i] + 1 : 0;
            strings.add(toStr(res));

            res[i] = ints[i] - 1 > -1 ? ints[i] - 1 : 9;
            strings.add(toStr(res));

            res[i] = ints[i];
        }

        return strings;
    }

    List<String> computeAdj(String str) {
        int[] intArray = strToIntArray(str);

        return genStrings(intArray);
    }

    int popAndPush(Queue<String> queue, Set<String> set, Set<String> setRef, int path, int pathRef, String[] deadends, String target) {
        int size = queue.size();

        for(int i = 0; i < size; i++) {

            // Pop element from queue
            String str = queue.poll();

            // Search complete
            if(set.contains(str) && setRef.contains(str))
                return path + pathRef;

            // One-directional search found target early
            if(str.equals(target))
                return path;

            // Compute adjacent sequences and add them to queue
            List<String> strings = computeAdj(str);

            for(var s : strings) {

                // Check if sequence has been tried
                if(set.contains(s))
                    continue;

                set.add(s);

                // Add sequence to queue
                if(!isDead(deadends, s)) {
                    queue.add(s);
                }
            }
        }

        return -1;
    }

    public int openLock(String[] deadends, String target) {

        Set<String> setA = new HashSet<>();
        Set<String> setB = new HashSet<>();

        Queue<String> queueA = new LinkedList<>();
        Queue<String> queueB = new LinkedList<>();

        String strInit = "0000";

        // Initial sequence is a deadend
        if(isDead(deadends, strInit)) {
            return -1;
        }

        // Perform bidirectional breadth-first search
        queueA.add(strInit);
        queueB.add(target);

        int pathA = 0;
        int pathB = 0;

        while(!queueA.isEmpty() && !queueB.isEmpty()) {

            int val = -1;

            // Search graph starting from strInit
            val = popAndPush(queueA, setA, setB, pathA, pathB, deadends, target);

            pathA++;

            if(val != -1)
                return val;

            // Search graph starting from target
            val = popAndPush(queueB, setB, setA, pathB, pathA, deadends, strInit);

            pathB++;

            if(val != -1)
                return val;

        }

        return -1;
    }
}