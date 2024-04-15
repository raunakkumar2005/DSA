#include <iostream>
#include <vector>
#include <queue>
#include <climits>
using namespace std;

#define INF INT_MAX

// Structure to represent an edge in the graph
struct Edge {
    int to;
    int weight;
};

// Function to find the minimum spanning tree using Prim's algorithm
void primMST(const vector<vector<Edge>>& graph, int startVertex) {
    int V = graph.size();
    vector<int> parent(V, -1); // To store the parent of each vertex in the MST
    vector<int> key(V, INF);   // To store the key (minimum weight) of each vertex
    vector<bool> inMST(V, false); // To keep track of vertices included in MST

    // Priority queue to store vertices with their key values
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;

    // Initialize the start vertex with key 0
    key[startVertex] = 0;
    pq.push({0, startVertex});

    // Prim's algorithm
    while (!pq.empty()) {
        int u = pq.top().second;
        pq.pop();

        // Include vertex u in MST
        inMST[u] = true;

        // Update key value and parent index of adjacent vertices
        for (const Edge& edge : graph[u]) {
            int v = edge.to;
            int weight = edge.weight;
            if (!inMST[v] && weight < key[v]) {
                parent[v] = u;
                key[v] = weight;
                pq.push({key[v], v});
            }
        }
    }

    // Print the MST
    cout << "Minimum Spanning Tree:" << endl;
    for (int i = 1; i < V; ++i) {
        cout << "Edge: " << parent[i] << " - " << i << " Weight: " << key[i] << endl;
    }
}

int main() {
    // Example graph
    int V = 5; // Number of vertices
    vector<vector<Edge>> graph(V);

    // Add edges
    graph[0].push_back({1, 2});
    graph[0].push_back({3, 6});
    graph[1].push_back({0, 2});
    graph[1].push_back({2, 3});
    graph[1].push_back({3, 8});
    graph[1].push_back({4, 5});
    graph[2].push_back({1, 3});
    graph[2].push_back({4, 7});
    graph[3].push_back({0, 6});
    graph[3].push_back({1, 8});
    graph[3].push_back({4, 9});
    graph[4].push_back({1, 5});
    graph[4].push_back({2, 7});
    graph[4].push_back({3, 9});

    // Start vertex for Prim's algorithm
    int startVertex = 0;

    // Find and print the minimum spanning tree
    primMST(graph, startVertex);

    return 0;
}