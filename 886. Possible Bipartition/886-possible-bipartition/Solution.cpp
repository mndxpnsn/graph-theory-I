//
//  Solution.cpp
//  886-possible-bipartition
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
    bool possibleBipartition(int n, vector<vector<int>> & dislikes) {
        
        vector<vector<int>> graph(n + 1);
        
        for(auto v : dislikes) {
            graph[v[0]].push_back(v[1]);
            graph[v[1]].push_back(v[0]);
        }
        
        vector<bool> visited(n + 1, false);
        
        // Perform breadth-first search starting from each node
        for(int p = 1; p <= n; p++) {
            
            vector<cl> colors(n + 1, DEF);
            
            nd start = {p, BLUE};
            
            queue<nd> queue;
            queue.push(start);
            
            while(!queue.empty()) {
                nd node = queue.front();
                queue.pop();

                int id = node.id;
                cl color = node.color;

                visited[id] = true;
                colors[id] = color;

                for(auto e : graph[id]) {
                    // Graph is not bipartite
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
        
        // Graph is bipartite
        return true;
        
    }
};
