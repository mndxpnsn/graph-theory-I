//
//  solution.cpp
//  797-all-paths
//
//  Created by mndx on 10/09/2022.
//

#include <vector>

using namespace std;

class Solution {
    
    void getPaths(vector<vector<int>> & graph, int node, vector<int> & path, vector<vector<int>> & list) {
        
        int m = (int) graph.size();
        int n = (int) graph[node].size();
        
        // Final node reached
        if(node == m - 1) {
            list.push_back(path);
        }
        
        for(int j = 0; j < n; ++j) {
            path.push_back(graph[node][j]);
            getPaths(graph, graph[node][j], path, list);
            path.pop_back();
        }
        
    }
    
public:
    vector<vector<int>> allPathsSourceTarget(vector<vector<int>> & graph) {
        
        vector<int> path = {0};
        vector<vector<int>> listPaths;
        
        getPaths(graph, 0, path, listPaths);
        
        return listPaths;
    }
};
