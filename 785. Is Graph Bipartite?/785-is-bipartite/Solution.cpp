//
//  Solution.cpp
//  785-is-bipartite
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stack>
#include <stdio.h>
#include <vector>

using namespace std;

typedef enum Color {
    BLUE = 2,
    RED = 1,
    DEF = 0,
} cl;

typedef struct Node {
    int id;
    cl color;
} nd;

class Solution {
public:
    bool isBipartite(vector<vector<int>> & graph) {
        
        int n = graph.size();
        
        vector<bool> visited(n, false);
        
        for(int p = 0; p < n; p++) {
            
            vector<cl> colors(n, DEF);
            
            nd start = {p, BLUE};

            queue<nd> queue;

            queue.push(start);

            while(!queue.empty()) {

                int size = queue.size();

                for(int k = 0; k < size; k++) {
                    nd node = queue.front();
                    queue.pop();

                    int id = node.id;
                    cl color = node.color;

                    visited[id] = true;
                    colors[id] = color;

                    for(auto e : graph[id]) {
                        if(visited[e] && colors[id] == colors[e])
                            return false;
                        if(!visited[e] && color == BLUE) {
                            nd nodeLoc = {e, RED};
                            queue.push(nodeLoc);
                        }
                        if(!visited[e] && color == RED) {
                            nd nodeLoc = {e, BLUE};
                            queue.push(nodeLoc);
                        }
                    }
                }
            }
        }
        
        return true;
    }
};
