//
//  Solution.cpp
//  997-find-judge
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
public:
    int findJudge(int n, vector<vector<int>> & trust) {
        
        unordered_map<int, bool> stash;
        unordered_map<int, unordered_map<int, bool>> adjMap;
        
        for(auto v : trust) {
            int i = v[0];
            int j = v[1];
            stash[i] = true;
            adjMap[i][j] = true;
        }
        
        if(trust.size() == 0 && n > 1) {
            return -1;
        }
        
        int candidate = 1;
        
        for(int i = 1; i <= n; i++) {
            if(stash[i] == false) {
                candidate = i;
            }
        }
        
        for(auto v : trust) {
            int person = v[0];
            if(!adjMap[person][candidate]) {
                return -1;
            }
        }
        
        return candidate;
    }
};
