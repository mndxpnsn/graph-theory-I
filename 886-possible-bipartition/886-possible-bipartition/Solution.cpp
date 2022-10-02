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

typedef struct Node {
    int node;
    int list;
} nd;

class Solution {
    
public:
      
    bool possibleBipartition(int n, vector<vector<int>> & dislikes) {
        
        vector<vector<int>> adjList;
        vector<bool> visited;
        vector<int> group;
        
        for(int i = 0; i < n + 1; i++) {
            vector<int> listLoc;
            adjList.push_back(listLoc);
            visited.push_back(false);
            group.push_back(-1);
        }
        
        visited[0] = true;
        
        for(auto v : dislikes) {
            int i = v[0];
            int j = v[1];
            adjList[i].push_back(j);
            adjList[j].push_back(i);
        }
        
        // DFS
        stack<nd> stash;
        stash.push({1, 1});
        group[1] = 1;
        bool allFound = false;
        while(!stash.empty()) {
            nd node = stash.top();
            stash.pop();
            visited[node.node] = true;
            allFound = true;
            for(auto e : visited)
                if(!e)
                    allFound = false;
            for(auto e : adjList[node.node]) {
                if(group[e] == group[node.node])
                    return false;
                if(visited[e])
                    continue;
                if(node.list == 1) {
                    group[e] = 2;
                    stash.push({e, 2});
                }
                if(node.list == 2) {
                    group[e] = 1;
                    stash.push({e, 1});
                }
            }
            
            if(stash.empty() && !allFound) {
                int count = 1;
                while(count < n && visited[count]) {
                    count++;
                }
                stash.push({count, 1});
                group[count] = 1;
            }
        }
        
        return true;
    }
};
