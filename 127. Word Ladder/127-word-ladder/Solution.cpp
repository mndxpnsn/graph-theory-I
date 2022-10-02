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

const int QUEUE_SIZE = 10000;
const int inf = 3e8;

int path = inf;

enum ass_flags {
    ASSED = true,
    UNASSED = false
};

enum color_codes {
    WHITE = 0,
    BLACK = 2
};

typedef struct Node {
    color_codes color = WHITE;
    int d = inf;
    Node * pi = NULL;
    string str;
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

    void Check_overflow();
    void Check_underflow();
public:
    Queue();
    void Enqueue(node);
    node Dequeue();
    void Print_queue();
    int Get_head();
    int Get_tail();
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

void Queue::Check_overflow() {
    if((this->tail == this->head) && (this->array[this->tail].assed == ASSED)) {
        throw "stack overflow";
    }
    else {};
}

void Queue::Check_underflow() {
    if(this->tail == this->head && this->array[this->head].assed == UNASSED) {
        throw "stack underflow";
    }
    else {};
}

void Queue::Enqueue(node element) {
    Queue::Check_overflow();
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

node Queue::Dequeue() {
    Queue::Check_underflow();
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

void Queue::Print_queue() {
    for(int n = 0; n < this->size; ++n) {
        printf("%i: %i\tassed: %i\n", n, this->array[n].value, this->array[n].assed);
    }
}

int Queue::Get_head() {
    return this->head;
}

int Queue::Get_tail() {
    return this->tail;
}

int bfs(int n, vector<vector<int>> edges, string endWord, vector<string> & wordList, int s) {

    int num_vertices = (int) wordList.size();
    int num_edges = (int) edges.size();

    //Create edges
    vector<vector<int>> edges_reordered;
    for(int i = 0; i < num_edges; ++i) {
        int start_index = edges[i][0];
        int end_index = edges[i][1];
        edges_reordered.push_back({start_index, end_index});
    }

    //Initialize graph
    node * graph = new node[num_vertices];
    for(int i = 0; i < num_vertices; ++i) {
        graph[i].color = WHITE;
        graph[i].d = inf;
        graph[i].str = wordList[i];
        graph[i].index = i;
        graph[i].pi = NULL;
    }

    graph[0].color = BLACK;
    graph[0].d = 0;
    graph[0].pi = NULL;

    for(int i = 0; i < num_edges; ++i) {
        int start_index = edges_reordered[i][0];
        int end_index = edges_reordered[i][1];
        graph[start_index].adj_nodes.push_back(end_index);
        graph[end_index].adj_nodes.push_back(start_index);
    }

    //Perform bfs algorithm
    Queue Q;
    node node_elem = graph[0];
    Q.Enqueue(node_elem);

    path = inf;
    
    int head = Q.Get_head();
    int tail = Q.Get_tail();
    int size_queue = tail - head;
    while(size_queue > 0) {
        node_elem = Q.Dequeue();
        node * curr_node = &graph[node_elem.index];

        int num_adj_nodes = (int) node_elem.adj_nodes.size();
        for(int i = 0; i < num_adj_nodes; ++i) {
            int adj_node_index = node_elem.adj_nodes[i];
            node * adj_node = &graph[adj_node_index];

            if(curr_node->str == endWord) {
                path = curr_node->d + 1;
            }
            
            if(adj_node->color == WHITE) {
                adj_node->color = BLACK;
                adj_node->d = curr_node->d + 1;
                adj_node->pi = curr_node;
                Q.Enqueue(* adj_node);
            }
        }

        head = Q.Get_head();
        tail = Q.Get_tail();
        size_queue = tail - head;
    }

    return path;
}

class Solution {
    
    int diff(string & a, string & b) {
        int diff = (int) a.length();
        
        for(int i = 0; i < a.length(); ++i) {
            if(a[i] != b[i]) {
                diff--;
            }
        }
        
        return diff;
    }
    
    vector<vector<int>> makeGraph(vector<string> & words) {
        vector<vector<int>> res;
        
        int n = (int) words.size();
        int w = (int) words[0].length();
        
        for(int i = 0; i < n; ++i) {
            for(int j = i + 1; j < n; ++j)  {
                int d = diff(words[i], words[j]);
                if(d == w - 1) {
                    res.push_back({i, j});
                }
            }
        }
        
        return res;
    }
    
public:
    int ladderLength(string beginWord, string endWord, vector<string> & wordList) {
       
        int n = (int) wordList.size();
        
        wordList.insert(wordList.begin(), beginWord);
        
        vector<vector<int>> edges = makeGraph(wordList);
        
        bfs(n, edges, endWord, wordList, 0);
    
        return path == inf ? 0 : path;
    }
};
