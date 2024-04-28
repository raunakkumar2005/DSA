#include <iostream>
#include <vector>
#include <queue>
// #include <climits> // For INT_MAX
using namespace std;

int spanningTree(int V, vector<pair<int, int>> adj[]) {
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
    // Visited Array
    bool visited[V] = {false};
    // Pushing the start Node
    pq.push({0, 0});
    int sum = 0;
    while (!pq.empty()) {
        auto it = pq.top();
        pq.pop();

        int node = it.second;
        int wt = it.first;

        if (visited[node]) continue;
        visited[node] = true;
        sum += wt;

        for (auto it : adj[node]) {
            int adjNode = it.first;
            int edgW = it.second;
            if (!visited[adjNode]) {
                pq.push({edgW, adjNode});
            }
        }
    }
    return sum;
}

int main() {
    int V;
    cout << "Enter the number of vertices: ";
    cin >> V;

    vector<pair<int, int>> adj[V];

    int E;
    cout << "Enter the number of edges: ";
    cin >> E;

    cout << "Enter the edges in the format 'u v weight':" << endl;
    for (int i = 0; i < E; ++i) {
        int u, v, weight;
        cin >> u >> v >> weight;

        adj[u].push_back({v, weight});
        adj[v].push_back({u, weight});
    }

    int mst_sum = spanningTree(V, adj);
    cout << "The sum of weights in the minimum spanning tree is: " << mst_sum << endl;

    return 0;
}
