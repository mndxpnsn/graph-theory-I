//
//  Solution.cpp
//  pacific-atlantic
//
//  Created by Derek Harrison on 01/10/2022.
//

#include <vector>
#include <stdio.h>

using namespace std;

class Solution {
    
    void dfs(vector<vector<int>> & heights, int i, int j, vector<vector<bool>> & visited) {
        
        int r = (int) heights.size();
        int c = (int) heights[0].size();
        
        int n = i > 0 ? i - 1 : 0;
        int s = i < r - 1 ? i + 1 : r - 1;
        int w = j > 0 ? j - 1 : 0;
        int e = j < c - 1 ? j + 1 : c - 1;
        
        bool canN = heights[n][j] >= heights[i][j];
        bool canS = heights[s][j] >= heights[i][j];
        bool canW = heights[i][w] >= heights[i][j];
        bool canE = heights[i][e] >= heights[i][j];
        
        if(visited[i][j]) {
            return;
        }
        
        visited[i][j] = true;
        if(canN) dfs(heights, n, j, visited);
        if(canS) dfs(heights, s, j, visited);
        if(canW) dfs(heights, i, w, visited);
        if(canE) dfs(heights, i, e, visited);
    }
    
public:
    vector<vector<int>> pacificAtlantic(vector<vector<int>> & heights) {
        
        int m = (int) heights.size();
        int n = (int) heights[0].size();
        
        vector<vector<int>> res;
        
        vector<vector<bool>> visitedAtl;
        vector<vector<bool>> visitedPac;
        
        for(auto v : heights) {
            vector<bool> visVec;
            for(auto e : v) {
                visVec.push_back(false);
            }
            visitedAtl.push_back(visVec);
            visitedPac.push_back(visVec);
        }
        
        for(int i = 0; i < m; ++i) {
            dfs(heights, i, n - 1, visitedAtl);
            dfs(heights, i, 0, visitedPac);
        }
        
        for(int j = 0; j < n; ++j) {
            dfs(heights, m - 1, j, visitedAtl);
            dfs(heights, 0, j, visitedPac);
        }
        
        for(int i = 0; i < m; ++i) {
            for(int j = 0; j < n; ++j) {
                if(visitedAtl[i][j] && visitedPac[i][j]) {
                    res.push_back({i, j});
                }
            }
        }
        
        return res;
    }
};
