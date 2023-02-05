//Note: I was not able to figure out a way to properly ask for user input
//and allow the input to depict the algorithm, so the only way to change
//the algorithm is to change the number in the graph at the bottom of the
//code.

#include <iostream>
#include <limits>
using namespace std;

#define MAX 1000

class Node1{
    public:
        int key;
        int wgt;
        Node1 *next;
        Node1(int, int);
};

Node1::Node1(int key, int wgt){
    this->key = key;
    this->wgt = wgt;
    this->next = NULL;
}

class graph{
    bool direct;
    public:
        Node1 *edge[MAX + 1];
        graph(bool);
        ~graph();
        void insert_edge(int, int, int, bool);
        void print();
};

graph::graph(bool direct){
    this->direct = direct;
    for(int a = 1; a < (MAX + 1); a ++){
        this->edge[a] = NULL;
    }
}

graph::~graph(){
}

void graph::insert_edge(int i, int j, int wgt, bool direct){
    if(i > 0 && i < (MAX + 1) && j > 0 && j < (MAX + 1)){
        Node1 *edge = new Node1(j, wgt);
        edge->next = this->edge[i];
        this->edge[i] = edge;
        if(!direct){
            insert_edge(j, i, wgt, true);
        }
    }
}

void graph::print(){
    for(int v = 1; v < (MAX + 1); v ++){
        if(this->edge[v] != NULL){
            cout << "Vertex " << v << " has neighbors: " << endl;
            Node1 *current = this->edge[v];
            while(current != NULL){
                cout << current->key << endl;
                current = current->next;
            }
        }
    }
}

void init_vars(bool discover[], int dist[], int parent[]){
    for(int b = 1; b < (MAX + 1); b ++){
        discover[b] = false;
        dist[b] = std::numeric_limits<int>::max();
        parent[b] = -1;
    }
}

void shortest_path(graph *g, int parent[], int dist[], int start){

    bool discover[MAX + 1];
    Node1 *current;
    int v_current;
    int v_neighbor;
    int wgt;
    int small_dist;

    init_vars(discover, dist, parent);

    dist[start] = 0;
    v_current = start;

    while(discover[v_current] == false){

        discover[v_current] = true;
        current = g->edge[v_current];

        while(current != NULL){

            v_neighbor = current->key;
            wgt = current->wgt;

            if((dist[v_current] + wgt) < dist[v_neighbor]){
                dist[v_neighbor] = dist[v_current] + wgt;
                parent[v_neighbor] = v_current;
            }
            current = current->next;
        }

        small_dist = std::numeric_limits<int>::max();
        for(int c = 1; c < (MAX + 1); c ++){
            if(!discover[c] && (dist[c] < small_dist)){
                v_current = c;
                small_dist = dist[c];
            }
        }
    }
}

void print_path(int pr, int parent[]){
    if(pr > 0 && pr < (MAX + 1) && parent[pr] != -1){
        cout << parent[pr] << " ";
        print_path(parent[pr], parent);
    }
}

void print_dist(int start, int dist[]){
    for(int d = 1; d < (MAX + 1); d ++){
        if(dist[d] != std::numeric_limits<int>::max()){
            cout << "Shortest distance from " << start << " to " << d << " is: " << dist[d] << endl;
        }
    }
}

int main(){

    graph *g = new graph(false);
    int parent[MAX + 1];
    int dist[MAX + 1];
    int start = 1;

    g->insert_edge(1, 3, 5, false);
    g->insert_edge(1, 4, 1, false);
    g->insert_edge(2, 5, 1, false);
    g->insert_edge(3, 4, 5, false);
    g->insert_edge(3, 2, 4, false);
    g->insert_edge(5, 1, 2, false);
    g->insert_edge(4, 5, 2, false);

    shortest_path(g, parent, dist, start);

    print_path(5, parent);
    print_dist(start, dist);

    delete g;
    return 0;
}
