//
//  Solution.cpp
//  1319-num-ops-network
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stack>
#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
    
    void dfs(vector<vector<int>> & adjList, int i, vector<bool> & visited) {
 
        stack<int> stash;
        stash.push(i);
        while(!stash.empty()) {
            int node = stash.top();
            
            stash.pop();

            if(visited[node]) {
                continue;
            }
            
            visited[node] = true;

            for(auto e : adjList[node]) {
                stash.push(e);
            }
        }
    }
    
public:
    int makeConnected(int n, vector<vector<int>> & connections) {
        
        vector<vector<int>> adjList;
        vector<bool> visited;
        
        if(connections.size() < n - 1) {
            return -1;
        }
        
        for(int i = 0; i < n; i++) {
            vector<int> list;
            adjList.push_back(list);
            visited.push_back(false);
        }
        
        for(auto v : connections) {
            int node = v[0];
            int adj = v[1];
            adjList[node].push_back(adj);
            adjList[adj].push_back(node);
        }

        int count = 0;
        
        for(int i = 0; i < n; i++) {
            if(!visited[i]) {
                dfs(adjList, i, visited);
                count++;
            }
        }
        
        return count - 1;
    }
};
