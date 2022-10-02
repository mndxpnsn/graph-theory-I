//
//  Solution.cpp
//  802-find-safe-states
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>
#include <vector>
#include <unordered_map>

using namespace std;

class Solution {
    
    bool dfs(vector<vector<int>> & graph, int node, vector<bool> & visited, unordered_map<int, bool> & store) {
        
        bool res = true;
        
        if(store[node] || graph[node].size() == 0)
            return true;
        
        if(visited[node])
            return false;
            
        visited[node] = true;
        for(auto e : graph[node])
            res = res && dfs(graph, e, visited, store);
        visited[node] = false;
        
        store[node] = res;
        
        return res;
    }
    
public:
    vector<int> eventualSafeNodes(vector<vector<int>> & graph) {
                
        int n = (int) graph.size();
        vector<bool> visited(n, false);
        unordered_map<int, bool> store;
        
        vector<int> res;
        for(int i = 0; i < n; i++) {
            if(dfs(graph, i, visited, store)) {
                res.push_back(i);
            }
        }
        
        return res;
    }
};
