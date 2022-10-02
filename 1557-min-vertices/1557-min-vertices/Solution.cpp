//
//  Solution.cpp
//  1557-min-vertices
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    vector<int> findSmallestSetOfVertices(int n, vector<vector<int>> & edges) {
        
        unordered_map<int, bool> store;
        
        for(auto v : edges)
            store[v[1]] = true;
        
        vector<int> res;
        
        for(int i = 0; i < n; i++)
            if(store[i] == false)
                res.push_back(i);
        
        return res;
    }
};
