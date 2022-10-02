public class Solution {

    void flood(int[][] grid, int t, int i, int j, boolean[][] visited) {

        int m = grid.length;
        int n = grid[0].length;

        int N = i > 0 ? i - 1 : 0;
        int S = i + 1 < m ? i + 1 : m - 1;
        int W = j > 0 ? j - 1 : 0;
        int E = j + 1 < n ? j + 1 : n - 1;

        if(visited[i][j] || grid[i][j] != t)
            return;

        visited[i][j] = true;

        flood(grid, t, N, j, visited);
        flood(grid, t, S, j, visited);
        flood(grid, t, i, W, visited);
        flood(grid, t, i, E, visited);
    }

    public int closedIsland(int[][] grid) {
        int m = grid.length;
        int n = grid[0].length;

        boolean[][] visited = new boolean[m][n];

        for(int j = 0; j < n; ++j) {
            flood(grid, 0, 0, j, visited);
            flood(grid, 0, m - 1, j, visited);
        }

        for(int i = 0; i < m; ++i) {
            flood(grid, 0, i, 0, visited);
            flood(grid, 0, i, n - 1, visited);
        }

        int numIslands = 0;

        for(int i = 1; i < m - 1; ++i) {
            for(int j = 1; j < n - 1; ++j) {
                if(grid[i][j] == 0 && !visited[i][j]) {
                    flood(grid, 0, i, j, visited);
                    numIslands++;
                }
            }
        }

        return numIslands;
    }
}