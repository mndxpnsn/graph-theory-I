//
//  Solution.cpp
//  1376-time-to-inform
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
    
    int dfs(vector<vector<int>> & adjList, int node, vector<int> & itime) {
        
        int res = 0;
        
        for(auto e : adjList[node])
            res = max(res, itime[node] + dfs(adjList, e, itime));
        
        return res;
    }
    
public:
    int numOfMinutes(int n, int headID, vector<int> & manager, vector<int> & informTime) {
        
        vector<vector<int>> adjList(n, vector<int>(0, 0));
        
        for(int i = 0; i < n; i++) {
            if(manager[i] != -1)
                adjList[manager[i]].push_back(i);
        }
        
        return dfs(adjList, headID, informTime);
    }
};
