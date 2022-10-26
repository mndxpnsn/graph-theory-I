//
//  Solution.cpp
//  1129-shortest-alternating-path
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

const int LARGE = 3e8;

typedef enum Color{
    RED = 1,
    BLUE = 2,
    GREEN = 3,
    DEF = 0
} cl;

typedef struct Node {
    int index;
    int dist;
    cl color;
} nd;

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>> & blueEdges) {
        
        vector<vector<cl>> colorMat(n, vector<cl>(n, DEF));
        vector<vector<int>> adjList(n, vector<int>(0, 0));
        
        // Make adjacency list and color matrix
        for(auto v : redEdges) {
            int i = v[0];
            int j = v[1];
            colorMat[i][j] = RED;
            adjList[i].push_back(j);
        }
        
        for(auto v : blueEdges) {
            int i = v[0];
            int j = v[1];
            if(colorMat[i][j] == RED) {
                colorMat[i][j] = GREEN;
            }
            if(colorMat[i][j] == DEF) {
                colorMat[i][j] = BLUE;
                adjList[i].push_back(j);
            }
        }
                
        // Perform breadth-first search
        vector<int> res(n, LARGE);
                
        vector<vector<bool>> visited(n, vector<bool>(4, false));
        
        queue<nd> queue;
        
        queue.push({0, 0, BLUE});
        queue.push({0, 0, RED});
        
        while(!queue.empty()) {
            int size = queue.size();
            
            nd node = queue.front();
            queue.pop();

            int dist = node.dist;
            int index = node.index;
            cl color = node.color;

            if(visited[index][color])
                continue;

            visited[index][color] = true;

            // Compute distance from node 0 to index
            res[index] = min(res[index], dist);

            // Explore neighbors
            for(auto e : adjList[index]) {
                cl col = colorMat[index][e];

                if(visited[e][col])
                    continue;

                // Add neighbors to queue
                if(color == RED && (col == GREEN || col == BLUE))
                    queue.push({e, dist + 1, BLUE});
                if(color == BLUE && (col == GREEN || col == RED))
                    queue.push({e, dist + 1, RED});
            }
        }
        
        // Set unreachable nodes to -1
        for(int i = 0; i < n; i++) {
            if(res[i] == LARGE) {
                res[i] = -1;
            }
        }
        
        return res;
    }
};
