//
//  Solution.cpp
//  127-word-ladder
//
//  Created by Derek Harrison on 02/10/2022.
//

#include <stdio.h>
#include <string>
#include <vector>

using namespace std;

class Solution {
    
    int bfsSub(vector<unordered_set<int>> & adjList, queue<int> & queue, vector<bool> & visited, vector<bool> & visitedRef, int & pathLen) {
        int size = queue.size();

        pathLen++;

        for(int k = 0; k < size; k++) {

            int node = queue.front();
            queue.pop();

            if(visited[node])
                continue;

            visited[node] = true;
            
            // Search complete
            if(visited[node] && visitedRef[node])
                return pathLen - 1;

            for(auto e : adjList[node]) {
                if(visited[e])
                    continue;

                queue.push(e);
            }
        }
        
        return 0;
    }
    
public:
    int ladderLength(string beginWord, string endWord, vector<string> & wordList) {
        
        // Make adjacency list
        wordList.insert(wordList.begin(), beginWord);
        
        int n = wordList.size();
        int w = beginWord.length();
        
        unordered_map<string, set<int>> adjMap;
        vector<unordered_set<int>> adjList(n);
        
        int end = -1;
        for(int i = 0; i < n; i++) {
            if(endWord == wordList[i])
                end = i;
            for(int c = 0; c < w; c++) {
                string strLoc = wordList[i];
                strLoc[c] = '?';
                adjMap[strLoc].insert(i);
                for(auto e : adjMap[strLoc]) {
                    adjList[i].insert(e);
                    adjList[e].insert(i);
                }
            }
        }

        // Target word not in wordList
        if(end == -1)
            return 0;
        
        // Perform bidirectional breadth-first search
        vector<bool> visitedA(n, false);
        vector<bool> visitedB(n, false);
        
        queue<int> queueA;
        queueA.push(0);
        queue<int> queueB;
        queueB.push(end);
        
        int pathLen = 0;
    
        while(!queueA.empty() && !queueB.empty()) {
            
            int dist = -1;
            
            // Search starting from beginWord
            dist = bfsSub(adjList, queueA, visitedA, visitedB, pathLen);
            
            if(dist != 0)
                return dist;
            
            // Search starting from endWord
            dist = bfsSub(adjList, queueB, visitedB, visitedA, pathLen);
                
            if(dist != 0)
                return dist;
        }
        
        // Target word cannot be reached
        return 0;
    }
};
