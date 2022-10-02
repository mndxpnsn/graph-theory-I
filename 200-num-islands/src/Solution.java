public class Solution {

    void search(char[][] grid, boolean[][] visited, int i, int j) {

        int r = grid.length;
        int c = grid[0].length;

        // If visited or is water
        if(visited[i][j] || grid[i][j] == '0') {
            return;
        }

        visited[i][j] = true;

        int n = i > 0 ? i - 1 : 0;
        int s = i < r - 1 ? i + 1 : r - 1;
        int w = j > 0 ? j - 1 : 0;
        int e = j < c - 1 ? j + 1 : c - 1;

        search(grid, visited, n, j);
        search(grid, visited, i, w);
        search(grid, visited, s, j);
        search(grid, visited, i, e);

    }

    public int numIslands(char[][] grid) {

        int num = 0;

        int m = grid.length;
        int n = grid[0].length;

        boolean[][] visited = new boolean[m][n];

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == '1' && visited[i][j] == false) {
                    search(grid, visited, i, j);
                    num++;
                }
            }
        }

        return num;
    }
}