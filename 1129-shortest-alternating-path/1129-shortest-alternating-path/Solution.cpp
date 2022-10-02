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

typedef struct Node {
    int index;
    int dist;
    int list;
} nd;

const int LARGE = 3e8;

class Solution {
public:
    vector<int> shortestAlternatingPaths(int n, vector<vector<int>>& redEdges, vector<vector<int>> & blueEdges) {
        
        vector<vector<int>> colorMat(n, vector<int>(n, -n));
        vector<vector<int>> adjList(n, vector<int>(0, 0));
        
        // Make adjacency list and color matrix
        for(auto v : redEdges) {
            int i = v[0];
            int j = v[1];
            colorMat[i][j] = 1;
            adjList[i].push_back(j);
        }
        
        for(auto v : blueEdges) {
            int i = v[0];
            int j = v[1];
            if(colorMat[i][j] == 1) {
                colorMat[i][j] = 0;
            }
            else {
                colorMat[i][j] = -1;
                adjList[i].push_back(j);
            }
        }
                
        vector<vector<bool>> visited(n, vector<bool>(3, false));
        vector<int> res(n, LARGE);
        
        queue<nd> queue;
        
        queue.push({0, 0, 1});
        queue.push({0, 0, -1});
        
        // BFS
        while(!queue.empty()) {
            int size = (int) queue.size();
            
            for(int k = 0; k < size; k++) {
                nd node = queue.front();
                queue.pop();
                
                int dist = node.dist;
                int index = node.index;
                int list = node.list;
                
                if(visited[index][list + 1])
                    continue;
                
                visited[index][list + 1] = true;
                
                // Compute distance from node 0 to index
                res[index] = min(res[index], dist);
                
                // Explore neighbors
                for(auto e : adjList[index]) {
                    int col = colorMat[index][e];
                    if(visited[e][col + 1]) continue;
                    // Add neighbors to queue
                    if(-list == col || col == 0) {
                        queue.push({e, dist + 1, -list});
                    }
                }
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
