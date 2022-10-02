//
//  Solution.cpp
//  1615-max-network-rank
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
    int max(int a, int b) {
        int res = 0;
        
        if(a > b) res = a;
        else res = b;
        
        return res;
    }
    
public:
    int maximalNetworkRank(int n, vector<vector<int>> & roads) {
        
        unordered_map<int, unordered_map<int, bool>> adjMap;
        vector<int> degrees(n, 0);
        
        for(auto v : roads) {
            int i = v[0];
            int j = v[1];
            degrees[i]++;
            degrees[j]++;
            adjMap[i][j] = true;
            adjMap[j][i] = true;
        }
        
        int maxDeg = 0;
        
        for(int i = 0; i < n; i++) {
            for(int j = 0; j < n; j++) {
                if(adjMap[i][j] && i != j) {
                    maxDeg = max(maxDeg, degrees[i] + degrees[j] - 1);
                }
                if(!adjMap[i][j] && i != j) {
                    maxDeg = max(maxDeg, degrees[i] + degrees[j]);
                }
            }
        }
        
        return maxDeg;
    }
};
