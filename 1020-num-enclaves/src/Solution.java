public class Solution {

    void flood(int[][] grid, int i, int j, boolean[][] visited) {

        int r = grid.length;
        int c = grid[0].length;

        if(visited[i][j] || grid[i][j] == 0) {
            return;
        }

        visited[i][j] = true;

        grid[i][j] = 0;

        int n = i > 0 ? i - 1 : 0;
        int s = i < r - 1 ? i + 1 : r - 1;
        int w = j > 0 ? j - 1 : 0;
        int e = j < c - 1 ? j + 1 : c - 1;

        flood(grid, n, j, visited);
        flood(grid, s, j, visited);
        flood(grid, i, w, visited);
        flood(grid, i, e, visited);
    }

    public int numEnclaves(int[][] grid) {

        int m = grid.length;
        int n = grid[0].length;

        boolean[][] visited = new boolean[m][n];

        int res = 0;

        for(int i = 0; i < m; i++) {
            flood(grid, i, 0, visited);
            flood(grid, i, n - 1, visited);
        }

        for(int j = 0; j < n; j++) {
            flood(grid, 0, j, visited);
            flood(grid, m - 1, j, visited);
        }

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                res = res + grid[i][j];
            }
        }

        return res;
    }
}