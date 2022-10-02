//
//  solution.cpp
//  1091-shortest-path
//
//  Created by Derek Harrison on 10/09/2022.
//

#include "solution.hpp"

#include <iostream>
#include <vector>

using namespace std;

int inf = 2e9;
int QUEUE_SIZE = 10001;

enum ass_flags {
    ASSED = true,
    UNASSED = false
};

enum color_codes {
    WHITE = 0,
    GRAY = 1,
    BLACK = 2
};

typedef struct Node {
    color_codes color = WHITE;
    int d = inf;
    Node* pi = NULL;
    int parent_index = 0;
    int index = 0;
    vector<int> adj_nodes;
} node;

typedef struct Queue_array {
    ass_flags assed;
    int value;
    node elem;
} queue_array;

class Queue {
private:
    int tail;
    int head;
    int size;
    queue_array * array;

    void check_overflow();
    void check_underflow();
public:
    Queue();
    void enqueue(node);
    node dequeue();
    int get_head();
    int get_tail();
};

Queue::Queue() {
    this->tail = 0;
    this->head = 0;
    this->size = QUEUE_SIZE;

    this->array = new queue_array[QUEUE_SIZE];

    for(int n = 0; n < QUEUE_SIZE; ++n) {
        this->array[n] = {UNASSED, };
    }
}

void Queue::check_overflow() {
    if((this->tail == this->head) && (this->array[this->tail].assed == ASSED)) {
        throw "stack overflow";
    }
    else {};
}

void Queue::check_underflow() {
    if(this->tail == this->head && this->array[this->head].assed == UNASSED) {
        throw "stack underflow";
    }
    else {};
}

void Queue::enqueue(node element) {
    Queue::check_overflow();
    if(this->tail == this->size - 1) {
        this->array[this->tail].elem = element;
        this->array[this->tail].assed = ASSED;
        this->tail = 0;
    }
    else {
        this->array[this->tail].elem = element;
        this->array[this->tail].assed = ASSED;
        this->tail = this->tail + 1;
    }
}

node Queue::dequeue() {
    Queue::check_underflow();
    node element = this->array[this->head].elem;
    if(this->head == this->size - 1) {
        this->array[this->head].assed = UNASSED;
        this->head = 0;
    }
    else {
        this->array[this->head].assed = UNASSED;
        this->head = this->head + 1;
    }

    return element;
}

int Queue::get_head() {
    return this->head;
}

int Queue::get_tail() {
    return this->tail;
}

class Solution {

    vector<int> bfs(int n, int m, vector<vector<int>> & edges, int s) {

        int num_vertices = n;
        int num_edges = m;
        int size_edge = 1; //Weight of an edge

        //Create edges
        vector<vector<int>> edges_reordered;
        for(int i = 0; i < m; ++i) {
            int start_index = edges[i][0];
            int end_index = edges[i][1];
            edges_reordered.push_back({start_index, end_index});
        }

        //Initialize graph
        node * graph = new node[num_vertices + 1];
        for(int i = 0; i < num_vertices + 1; ++i) {
            graph[i].color = WHITE;
            graph[i].d = inf;
            graph[i].parent_index = 0;
            graph[i].index = i;
            graph[i].pi = NULL;
        }

        graph[1].color = GRAY;
        graph[1].d = 0;
        graph[1].pi = NULL;

        for(int i = 0; i < num_edges; ++i) {
            int start_index = edges_reordered[i][0];
            int end_index = edges_reordered[i][1];
            graph[start_index].adj_nodes.push_back(end_index);
            graph[end_index].adj_nodes.push_back(start_index);
        }

        //Perform bfs algorithm
        Queue Q;
        node node_elem = graph[1];
        try { Q.enqueue(node_elem); }
        catch(string s) { cout << s << endl; }

        int head = Q.get_head();
        int tail = Q.get_tail();
        int size_queue = tail - head;
        while(size_queue > 0) {

            try { node_elem = Q.dequeue(); }
            catch(string s) { cout << s << std::endl; }

            node* curr_node = &graph[node_elem.index];

            int num_adj_nodes = (int) node_elem.adj_nodes.size();
            for(int i = 0; i < num_adj_nodes; ++i) {
                int adj_node_index = node_elem.adj_nodes[i];
                node* adj_node = &graph[adj_node_index];

                if(adj_node->color == WHITE) {
                    adj_node->color = GRAY;
                    adj_node->d = curr_node->d + 1;
                    adj_node->pi = curr_node;

                    try { Q.enqueue(*adj_node); }
                    catch(string s) { cout << s << endl; }
                }
            }

            curr_node->color = BLACK;
            head = Q.get_head();
            tail = Q.get_tail();
            size_queue = tail - head;
        }

        //Compute result graph
        for(int i = 1; i < num_vertices + 1; ++i) {
            if(graph[i].d == inf) { graph[i].d = -1; }
            else { graph[i].d = size_edge * graph[i].d; }
        }

        //Reorder results
        vector<int> results;
        for(int i = 1; i < num_vertices + 1; ++i) {
            results.push_back(graph[i].d);
        }

        return results;
    }

public:
    int shortestPathBinaryMatrix(vector<vector<int>> & grid) {
        
        int n = (int) grid.size();
        
        if(grid[0][0] == 1 || grid[n - 1][n - 1] == 1) {
            return -1;
        }
        
        vector<vector<int>> edges;
        
        vector<vector<int>> nums;
        
        for(int i = 0; i < n; ++i) {
            vector<int> numsLoc;
            for(int j = 0; j < n; ++j) {
                numsLoc.push_back(0);
            }
            nums.push_back(numsLoc);
        }
        
        int numV = 0;
        
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                if(grid[i][j] == 0) {
                    numV++;
                    nums[i][j] = numV;
                }
            }
        }
        
        
        for(int i = 0; i < n; ++i) {
            for(int j = 0; j < n; ++j) {
                for(int r = i - 1; r <= i + 1; ++r) {
                    for(int c = j - 1; c <= j + 1; ++c) {

                        if(c >= n || c < 0 || r >= n || r < 0) {
                            continue;
                        }
                        int nn = nums[i][j];
                        int mm = nums[r][c];
                        
                        if(nn != mm && grid[r][c] == 0 && grid[i][j] == 0) {
                            edges.push_back({nn, mm});
                        }
                    }
                }
            }
        }
        
        int numEdges = (int) edges.size();
        
        vector<int> results = bfs(numV, numEdges, edges, 1);
        
        return results.back() == -1 ? -1 : results.back() + 1;
    }
};
