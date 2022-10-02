//
//  Solution.cpp
//  847-shortest-path
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

typedef struct Node {
    int index;
    int mask;
} nd;

const int MAX = 300000000;

class Solution {
public:
    int shortestPathLength(vector<vector<int>> & graph) {
        
        int n = (int) graph.size();
        
        // All bitmask
        int all = (1 << n) - 1;
        
        vector<vector<bool>> visited(n + 2, vector<bool>(all + 2, false));
        
        // Initialize queue
        queue<nd> queue;
        
        for(int i = 0; i < n; i++) {
            queue.push({i, 1 << i});
        }
        
        // BFS
        int path = 0;

        while(!queue.empty()) {
            int size = (int) queue.size();

            path++;
            
            for(int k = 0; k < size; k++) {
                nd node = queue.front();

                queue.pop();

                int index = node.index;
                int mask = node.mask;

                visited[index][mask] = true;

                for(auto e : graph[index]) {
                    int newMask = mask | 1 << e;
                    
                    // State already reached
                    if(visited[e][newMask]) {
                        continue;
                    }
                    
                    visited[e][newMask] = true;
                    
                    // All nodes visited
                    if(newMask == all) {
                        return path;
                    }
                    
                    queue.push({e, newMask});
                }
            }
        }
        
        return 0;
    }
};
