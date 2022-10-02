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

    void genStrings(int[] ins, List<String> strings) {

        int[] ibk = new int[ins.length];

        for(int i = 0; i < ins.length; i++) {
            ibk[i] = ins[i];
        }

        for(int i = 0; i < ins.length; i++) {
            ibk[i] = ins[i] + 1 < 10 ? ins[i] + 1 : 0;
            String str = toStr(ibk);
            strings.add(str);
            ibk[i] = ins[i] - 1 > -1 ? ins[i] - 1 : 9;
            str = toStr(ibk);
            strings.add(str);
            ibk[i] = ins[i];
        }
    }

    boolean isDead(String[] deadends, String str) {

        for(var s : deadends) {
            if(s.equals(str)) {
                return true;
            }
        }

        return false;
    }

    public int openLock(String[] deadends, String target) {

        Set<String> set = new HashSet<>();

        Queue<String> queue = new LinkedList<>();

        String strInit = "0000";

        if(isDead(deadends, strInit)) {
            return -1;
        }

        queue.add(strInit);

        int path = 0;

        while(!queue.isEmpty()) {

            int size = queue.size();

            for(int i = 0; i < size; i++) {

                String str = queue.poll();

                if(str.equals(target)) {
                    return path;
                }

                char[] chr = str.toCharArray();

                int[] ins = new int[chr.length];

                for(int j = 0; j < chr.length; j++) {
                    ins[j] = Character.getNumericValue(chr[j]);
                }
                List<String> strings = new ArrayList<>();
                List<Integer> ints = new ArrayList<>();

                genStrings(ins, strings);

                for(var s : strings) {

                    if(set.contains(s)) {
                        continue;
                    }

                    set.add(s);

                    if(!s.equals(str) && !isDead(deadends, s)) {
                        queue.add(s);
                    }
                }
            }

            path++;
        }

        return -1;
    }
}