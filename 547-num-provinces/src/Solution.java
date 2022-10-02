class Solution {

    void dfs(boolean[] used, int[][] isConnected, int row) {

        int n = isConnected.length;

        for(int col = 0; col < n; ++col) {
            if(col != row && !used[col] && isConnected[row][col] == 1 ) {
                used[row] = true;
                used[col] = true;
                dfs(used, isConnected, col);
            }
        }
    }

    public int findCircleNum(int[][] isConnected) {

        int n = isConnected.length;

        int res = 0;

        boolean[] used = new boolean[n];

        for(int row = 0; row < n; ++row) {
            if(!used[row]) {
                dfs(used, isConnected, row);
                res++;
            }
        }

        return res;
    }
}