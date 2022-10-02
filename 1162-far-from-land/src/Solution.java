public class Solution {

    int LARGE = 300000000;

    int min(int a, int b) {
        int res = 0;

        if(a < b) res = a;
        else res = b;

        return res;
    }

    int max(int a, int b) {
        int res = 0;

        if(a > b) res = a;
        else res = b;

        return res;
    }

    int minDistTL(int[][] mat, int i, int j, boolean[][] visited, int[][] dp) {

        int res = LARGE;

        int m = mat.length;
        int n = mat[0].length;

        int N = i > 0 ? i - 1 : 0;
        int W = j > 0 ? j - 1 : 0;

        if(dp[i][j] != 0) {
            return dp[i][j];
        }

        if(visited[i][j]) {
            return LARGE;
        }

        if(mat[i][j] == 1) {
            return 0;
        }

        visited[i][j] = true;
        int val1 = 1 + minDistTL(mat, N, j, visited, dp);
        int val3 = 1 + minDistTL(mat, i, W, visited, dp);
        visited[i][j] = false;

        res = min(res, val1);
        res = min(res, val3);

        dp[i][j] = res;

        return res;
    }

    int minDistBR(int[][] mat, int i, int j, boolean[][] visited, int[][] dpTL, int[][] dpBR) {

        int res = LARGE;

        int m = mat.length;
        int n = mat[0].length;

        int S = i < m - 1 ? i + 1 : m - 1;
        int E = j < n - 1 ? j + 1 : n - 1;

        if(dpBR[i][j] != 0) {
            return dpBR[i][j];
        }

        if(visited[i][j]) {
            return LARGE;
        }

        if(mat[i][j] == 1) {
            return 0;
        }

        visited[i][j] = true;
        int val2 = 1 + minDistBR(mat, S, j, visited, dpTL, dpBR);
        int val4 = 1 + minDistBR(mat, i, E, visited, dpTL, dpBR);
        visited[i][j] = false;

        res = min(res, val2);
        res = min(res, val4);
        res = min(res, dpTL[i][j]);

        dpBR[i][j] = res;

        return res;
    }

    int updateMatrix(int[][] mat) {

        int m = mat.length;
        int n = mat[0].length;

        int res = 0;

        boolean[][] visited = new boolean[m][n];

        int[][] mat_store = new int[m][n];

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                mat_store[i][j] = mat[i][j];
            }
        }

        int[][] dpTL = new int[m][n];
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                mat[i][j] = minDistTL(mat_store, i, j, visited, dpTL);
            }
        }

        int[][] dpBR = new int[m][n];
        for(int i = m - 1; i >= 0; --i) {
            for(int j = n - 1; j >= 0; --j) {
                int val = minDistBR(mat_store, i, j, visited, dpTL, dpBR);
                mat[i][j] = min(mat[i][j], val);
            }
        }

        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                res = max(res, mat[i][j]);
            }
        }

        return res;
    }

    boolean allLand(int[][] grid) {

        for(var v : grid) {
            for(var e : v) {
                if(e != 1) {
                    return false;
                }
            }
        }

        return true;
    }

    boolean allWater(int[][] grid) {
        for(var v : grid) {
            for(var e : v) {
                if(e != 0) {
                    return false;
                }
            }
        }

        return true;
    }

    public int maxDistance(int[][] grid) {

        if(allLand(grid) || allWater(grid)) {
            return -1;
        }

        return updateMatrix(grid);
    }
}