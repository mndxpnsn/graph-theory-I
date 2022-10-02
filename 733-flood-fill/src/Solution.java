public class Solution {

    void flood(int[][] image, int t, int color, int i, int j, boolean[][] visited) {

        int m = image.length;
        int n = image[0].length;

        int N = i > 0 ? i - 1 : 0;
        int S = i + 1 < m ? i + 1 : m - 1;
        int W = j > 0 ? j - 1 : 0;
        int E = j + 1 < n ? j + 1 : n - 1;

        if(visited[i][j] || image[i][j] != t)
            return;

        visited[i][j] = true;

        image[i][j] = color;

        flood(image, t, color, N, j, visited);
        flood(image, t, color, S, j, visited);
        flood(image, t, color, i, W, visited);
        flood(image, t, color, i, E, visited);
    }

    public int[][] floodFill(int[][] image, int sr, int sc, int color) {

        int m = image.length;
        int n = image[0].length;

        boolean[][] visited = new boolean[m][n];

        int pixColor = image[sr][sc];

        flood(image, pixColor, color, sr, sc, visited);

        return image;
    }
}