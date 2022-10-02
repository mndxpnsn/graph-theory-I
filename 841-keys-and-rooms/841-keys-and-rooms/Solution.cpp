//
//  Solution.cpp
//  841-keys-and-rooms
//
//  Created by Derek Harrison on 01/10/2022.
//

#include <stdio.h>
#include <queue>
#include <vector>

using namespace std;

class Solution {
public:
    bool canVisitAllRooms(vector<vector<int>> & rooms) {
        
        vector<bool> visited(rooms.size(), false);
        
        queue<int> queue;
        
        queue.push(0);
        
        while(!queue.empty()) {
            int size = (int) queue.size();
            
            for(int k = 0; k < size; k++) {
                int node = queue.front();
                
                queue.pop();
                
                if(visited[node])
                    continue;
                
                visited[node] = true;
                
                for(auto e : rooms[node]) {
                    queue.push(e);
                }
            }
        }
        
        for(auto e : visited) {
            if(!e)
                return false;
        }
        
        return true;
    }
};
