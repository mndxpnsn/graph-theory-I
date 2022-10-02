import java.util.ArrayList;
import java.util.List;

public class Solution {

    int LARGE = 300000000;

    int min(int a, int b) {
        int res = 0;

        if(a < b) res = a;
        else res = b;

        return res;
    }

    void flood(int[][] grid, int i, int j, boolean[][] visited) {

        int d = grid.length;

        int n = i > 0 ? i - 1 : 0;
        int s = i < d - 1 ? i + 1 : d - 1;
        int w = j > 0 ? j - 1 : 0;
        int e = j < d - 1 ? j + 1 : d - 1;

        if(visited[i][j] || grid[i][j] == 0 || grid[i][j] == 2) {
            return;
        }

        visited[i][j] = true;

        grid[i][j] = 2;

        flood(grid, n, j, visited);
        flood(grid, s, j, visited);
        flood(grid, i, w, visited);
        flood(grid, i, e, visited);

        visited[i][j] = false;
    }

    public int shortestBridge(int[][] grid) {

        int n = grid.length;

        int res = LARGE;

        boolean[][] visited = new boolean[n][n];

        // Flood one island
        boolean flooded = false;
        for(int i = 0; i < n && !flooded; ++i) {
            for(int j = 0; j < n && !flooded; ++j) {
                if(grid[i][j] == 1) {
                    flood(grid, i, j, visited);
                    flooded = true;
                }
            }
        }

        List<List<Integer>> island1 = new ArrayList<>();
        List<List<Integer>> island2 = new ArrayList<>();

        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 1) {
                    List<Integer> vecLoc = new ArrayList<>();
                    vecLoc.add(i);
                    vecLoc.add(j);
                    island1.add(vecLoc);
                }
                if(grid[i][j] == 2) {
                    List<Integer> vecLoc = new ArrayList<>();
                    vecLoc.add(i);
                    vecLoc.add(j);
                    island2.add(vecLoc);
                }
            }
        }

        for(var v1 : island1) {
            for(var v2 : island2) {
                res = min(res, Math.abs(v1.get(0) - v2.get(0)) + Math.abs(v1.get(1) - v2.get(1)));
            }
        }

        return res - 1;
    }
}