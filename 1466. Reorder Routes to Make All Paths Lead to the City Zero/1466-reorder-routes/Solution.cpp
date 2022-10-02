//
//  Solution.cpp
//  1466-reorder-routes
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stack>
#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
public:
    int minReorder(int n, vector<vector<int>> & connections) {
        
        vector<vector<int>> adjList;
        vector<vector<int>> adjListDir;
        vector<bool> visited;
        
        for(int i = 0; i < n; i++) {
            vector<int> listLoc;
            adjList.push_back(listLoc);
            adjListDir.push_back(listLoc);
            visited.push_back(false);
        }
        
        for(auto v : connections) {
            int i = v[0];
            int j = v[1];
            adjList[i].push_back(j);
            adjList[j].push_back(i);
            adjListDir[i].push_back(j);
        }
        
        stack<int> stash;
        
        stash.push(0);
        
        int ops = 0;
        
        while(!stash.empty()) {
            int node = stash.top();
            
            stash.pop();
            
            visited[node] = true;
            
            for(auto e : adjList[node]) {
                if(!visited[e]) {
                    stash.push(e);
                    for(auto c : adjListDir[node])
                        if(c == e)
                            ops++;
                }
            }
        }
        
        return ops;
    }
};
