import java.util.HashSet;
import java.util.LinkedList;
import java.util.Queue;
import java.util.Set;

public class Solution {

    boolean validMutation(String str1, String str2) {

        char[] chars1 = str1.toCharArray();
        char[] chars2 = str2.toCharArray();

        int n = chars1.length;

        int diff = 0;
        for(int i = 0; i < n; ++i) {
            if(chars1[i] != chars2[i]) {
                diff++;
            }
        }

        return diff == 1;
    }

    public int minMutation(String start, String end, String[] bank) {

        Set<String> set = new HashSet<>();

        Queue<String> queue = new LinkedList<>();

        queue.add(start);

        int path = 0;
        while(!queue.isEmpty()) {

            int size = queue.size();

            for(int i = 0; i < size; i++) {
                String str = queue.poll();

                // Continue if node is explored
                if(set.contains(str)) {
                    continue;
                }

                // Final mutation reached
                if(str.equals(end)) {
                    return path;
                }

                // Add node to visited set
                set.add(str);

                // Search for valid mutations in bank
                for(int k = 0; k < bank.length; ++k) {
                    if(validMutation(str, bank[k])) {
                        queue.add(bank[k]);
                    }
                }
            }

            path++;
        }

        return -1;
    }
}