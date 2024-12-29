#include <iostream>
#include <vector>
using namespace std;

const int max = 1000;  
const int INF = 100000;

typedef struct {
    int f;
    int r;
    int A[max];
} que;

int isfull(que* q) {
    return q->r == max - 1;
}

int isempty(que* q) {
    return q->r == q->f;
}

void enqueue(que* q, int data) {
    if (isfull(q)) {
        cout << "queue overflow\n";
    } else {
        q->r++;
        q->A[q->r] = data;
    }
}

int dequeue(que* q) {
    int x = -1;
    if (isempty(q)) {
        cout << "queue underflow\n";
    } else {
        x = q->A[q->f];
        q->f++;
    }
    return x;
}

void display(que* q) {
    if (isempty(q)) {
        cout << "queue is empty\n";
    } else {
        for (int i = q->f + 1; i <= q->r; i++)
            cout << q->A[i] << "\t";
        cout << endl;
    }
}

struct Edge {
    int src, dest, weight;
};

class Graph {
    int V;
    vector<pair<int, int>>* adjList; // Adjacency list
public:
    Graph(int V) {
        this->V = V;
        adjList = new vector<pair<int, int>>[V];
    }

    void addEdge(int u, int v, int weight) {
        adjList[u].push_back({v, weight});
        adjList[v].push_back({u, weight}); 
    }

    void dijkstra(int src) {
        vector<int> dist(V, INF); 
        vector<int> parent(V, -1);
        que q;
        q.r = q.f = -1;

        for (int i = 0; i < V; i++) {
            dist[i] = INF;
            parent[i] = -1;
            enqueue(&q, i);
        }

        dist[src] = 0;

        while (!isempty(&q)) {
            int u = dequeue(&q);

            for (auto& neighbor : adjList[u]) {
                int v = neighbor.first;
                int weight = neighbor.second;

                if (dist[u] + weight < dist[v]) {
                    dist[v] = dist[u] + weight;
                    parent[v] = u;
                    if (dist[v] == INF) {
                        enqueue(&q, v);
                    }
                }
            }
        }

      
        cout << "Vertex   Distance from Source   Parent\n";
        for (int i = 0; i < V; i++) {
            cout << i << " \t\t " << dist[i] << " \t\t " << parent[i] << endl;
        }
    }
};

int main() {
    int V = 6; 
    Graph g(V);

   
    vector<Edge> edges = {
        {0, 1, 201}, // A-B
        {0, 2, 302}, // A-C
        {1, 3, 153}, // B-D
        {1, 4, 252}, // B-E
        {2, 3, 101}, // C-D
        {2, 5, 402}, // C-F
        {3, 5, 301}  // D-F
    };

    for (const Edge& edge : edges) {
        g.addEdge(edge.src, edge.dest, edge.weight);
    }

    // Starting node is 'A', which is node 0
    g.dijkstra(0);

    return 0;
}
