#include <bits/stdc++.h>
using namespace std;

unordered_map< int, vector<pair<int, int>> > adj;

void BFS(int start) {
    set<int> visited;          // To track visited nodes
    queue<int> q;

    visited.insert(start);
    q.push(start);

    cout << "BFS traversal: ";

    while (!q.empty()) {
        int node = q.front();
        q.pop();
        cout << node << " ";

        for (auto neighbor : adj[node]) {
            int next = neighbor.first;
            if (visited.find(next) == visited.end()) {
                visited.insert(next);
                q.push(next);
            }
        }
    }

    cout << "\n";
}

void DFS_Helper(int node, set<int> &visited) {
    visited.insert(node);
    cout << node << " ";

    for (auto neighbor : adj[node]) {
        int next = neighbor.first;
        if (visited.find(next) == visited.end()) {
            DFS_Helper(next, visited);
        }
    }
}

void DFS(int start) {
    set<int> visited;
    cout << "DFS traversal: ";
    DFS_Helper(start, visited);
    cout << "\n";
}


void Dijkstra(int start) {
    unordered_map<int, int> dist;

    // Initialize all distances to infinity
    for (auto &node : adj) {
        dist[node.first] = INT_MAX;
    }

    // Min-heap: (distance, node)
    priority_queue<pair<int, int>, vector<pair<int, int>>, greater<>> pq;

    dist[start] = 0;
    pq.push({0, start});

    while (!pq.empty()) {
        pair<int, int> top = pq.top();
        pq.pop();

        int d = top.first;
        int u = top.second;

        if (d > dist[u]) continue;

        for (auto &neighbor : adj[u]) {
            int v = neighbor.first;
            int weight = neighbor.second;

            if (dist[u] + weight < dist[v]) {
                dist[v] = dist[u] + weight;
                pq.push({dist[v], v});
            }
        }
    }

    // Print the shortest distances
    cout << "Shortest distances from node " << start << ":\n";
    for (auto &p : dist) {
        if (p.second == INT_MAX)
            cout << p.first << " -> INF\n";
        else
            cout << p.first << " -> " << p.second << "\n";
    }
}


int main() {
    int choice;

    while (true) {
        cout << "\n==== Graph Visualizer ====\n";
        cout << "1. Add Edge\n";
        cout << "2. Display Adjacency List\n";
        cout << "3. Run BFS\n";
        cout << "4. Run DFS\n";
        cout << "5. Run Dijkstra\n";
        cout << "6. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1: {
                int u, v, w;
                cout << "Enter source node: ";
                cin >> u;
                cout << "Enter destination node: ";
                cin >> v;
                cout << "Enter weight: ";
                cin >> w;

                // For undirected graph
                adj[u].push_back({v, w});
                adj[v].push_back({u, w});
                
                cout << "Edge added successfully.\n";

                break;
            }    
            case 2: {

                cout << "Adjacency List:\n";
                for (auto &node : adj) {
                    cout << node.first << " -> ";
                    for (auto &neighbor : node.second) {
                        cout << "(" << neighbor.first << ", weight=" << neighbor.second << ") ";
                    }
                    cout << "\n";
                }
                break;
            }
            case 3: {
                int start;
                cout << "Enter starting node for BFS: ";
                cin >> start;

                    if (adj.find(start) == adj.end()) {
                        cout << "Start node doesn't exist in graph.\n";
                    } else {
                        BFS(start);
                    }

                break;
            }
            case 4:{
                int start;
                cout << "Enter starting node for DFS: ";
                cin >> start;

                if (adj.find(start) == adj.end()) {
                    cout << "Start node doesn't exist in graph.\n";
                } else {
                    DFS(start);
                }

                break;
            }
            case 5:{
                int start;
                cout << "Enter starting node for Dijkstra: ";
                cin >> start;

                if (adj.find(start) == adj.end()) {
                    cout << "Start node doesn't exist in graph.\n";
                } else {
                    Dijkstra(start);
                }

                break;
            }    
            case 6:
                cout << "Exiting program.\n";
                return 0;
            default:
                cout << "Invalid choice. Try again.\n";
        }
    }

    return 0;
}
