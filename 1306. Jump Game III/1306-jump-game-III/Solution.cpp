//
//  Solution.cpp
//  1306-jump-game-III
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <queue>
#include <stdio.h>
#include <vector>

using namespace std;

class Solution {
public:
    bool canReach(vector<int> & arr, int start) {
        
        queue<int> queue;
        queue.push(start);
        vector<bool> visited(arr.size(), false);
    
        while(!queue.empty()) {
            
            int size = (int) queue.size();
            
            for(int k = 0; k < size; k++) {
                
                int node = queue.front();
                queue.pop();
                
                if(arr[node] == 0) {
                    return true;
                }
                
                if(visited[node]) {
                    continue;
                }
                
                visited[node] = true;
                
                if(node + arr[node] < arr.size()) {
                    queue.push(node + arr[node]);
                }
                if(node - arr[node] >= 0) {
                    queue.push(node - arr[node]);
                }
            }
        }
        
        return false;
    }
};
