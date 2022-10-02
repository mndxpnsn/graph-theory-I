import java.util.LinkedList;
import java.util.Queue;

public class Solution {

    class Cell {
        public int i;
        public int j;
        Cell(int i, int j) {
            this.i = i;
            this.j = j;
        }
    }

    public int nearestExit(char[][] maze, int[] entrance) {

        int r = maze.length;
        int c = maze[0].length;

        Cell start = new Cell(entrance[0], entrance[1]);

        Queue<Cell> queue = new LinkedList<>();
        queue.add(start);

        boolean[][] visited = new boolean[r][c];

        int path = 0;

        // Perform BFS
        while(!queue.isEmpty()) {
            int size = queue.size();

            for(int k = 0; k < size; ++k) {
                Cell cell = queue.poll();

                int i = cell.i;
                int j = cell.j;

                if(visited[i][j]) {
                    continue;
                }

                visited[i][j] = true;

                int n = cell.i - 1;
                int w = cell.j - 1;
                int s = cell.i + 1;
                int e = cell.j + 1;

                // Search north
                if(n >= 0 && maze[n][j] == '.') {
                    Cell cellLoc = new Cell(n, j);
                    queue.add(cellLoc);
                }
                // Search south
                if(s < r && maze[s][j] == '.') {
                    Cell cellLoc = new Cell(s, j);
                    queue.add(cellLoc);
                }
                // Search west
                if(w >= 0 && maze[i][w] == '.') {
                    Cell cellLoc = new Cell(i, w);
                    queue.add(cellLoc);
                }
                // Search east
                if(e < c && maze[i][e] == '.') {
                    Cell cellLoc = new Cell(i, e);
                    queue.add(cellLoc);
                }
                // Exit reached
                if(i == 0 || i == r - 1 || j == 0 || j == c - 1) {
                    if(i != entrance[0] || j != entrance[1]) {
                        return path;
                    }
                }
            }

            path++;
        }

        return -1;
    }
}