public class Solution {

    int flood(int[][] grid, int t, int i, int j, boolean[][] visited) {

        int area = 0;

        int m = grid.length;
        int n = grid[0].length;

        int N = i > 0 ? i - 1 : 0;
        int S = i + 1 < m ? i + 1 : m - 1;
        int W = j > 0 ? j - 1 : 0;
        int E = j + 1 < n ? j + 1 : n - 1;

        if(visited[i][j] || grid[i][j] != t)
            return 0;

        visited[i][j] = true;

        area = 1;

        area += flood(grid, t, N, j, visited);
        area += flood(grid, t, S, j, visited);
        area += flood(grid, t, i, W, visited);
        area += flood(grid, t, i, E, visited);

        return area;
    }

    public int maxAreaOfIsland(int[][] grid) {

        int m = grid.length;
        int n = grid[0].length;

        boolean[][] visited = new boolean[m][n];

        int area = 0;

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                area = Math.max(area, flood(grid, 1, i, j, visited));
            }
        }

        return area;
    }
}