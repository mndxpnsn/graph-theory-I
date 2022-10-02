public class Solution {

    void isSub(int[][] grid1, int[][] grid2, int i, int j, boolean[][] visited, boolean[] is) {

        int r = grid1.length;
        int c = grid1[0].length;

        int n = i > 0 ? i - 1 : 0;
        int s = i < r - 1 ? i + 1 : r - 1;
        int w = j > 0 ? j - 1 : 0;
        int e = j < c - 1 ? j + 1 : c - 1;

        if(grid2[i][j] == 1 && grid1[i][j] == 0) {
            is[0] = false;
        }

        if(grid2[i][j] == 0 || visited[i][j]) {
            return;
        }

        visited[i][j] = true;

        isSub(grid1, grid2, n, j, visited, is);
        isSub(grid1, grid2, s, j, visited, is);
        isSub(grid1, grid2, i, w, visited, is);
        isSub(grid1, grid2, i, e, visited, is);
    }

    public int countSubIslands(int[][] grid1, int[][] grid2) {

        int m = grid1.length;
        int n = grid2[0].length;

        boolean[][] visited = new boolean[m][n];
        boolean[] is = new boolean[1];

        int res = 0;

        for(int i = 0; i < m; i++) {
            for(int j = 0; j < n; j++) {
                if(grid2[i][j] == 1 && !visited[i][j]) {
                    is[0] = true;
                    isSub(grid1, grid2, i, j, visited, is);
                    if(is[0]) {
                        res++;
                    }
                }
            }
        }

        return res;
    }
}