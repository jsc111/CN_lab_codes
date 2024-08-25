#include <iostream>
#include <vector>
#include <climits> // For INT_MAX

using namespace std;

const int INF = INT_MAX; // Infinity

// Function to print the distance vector
void printDistanceVector(vector<vector<int>>& dist) {
    int n = dist.size();
    for (int i = 0; i < n; i++) {
        cout << "Distance vector for node " << i << ": ";
        for (int j = 0; j < n; j++) {
            if (dist[i][j] == INF)
                cout << "INF ";
            else
                cout << dist[i][j] << " ";
        }
        cout << "\n";
    }
}

// Distance Vector Routing Algorithm
void distanceVectorRouting(vector<vector<int>>& graph) {
    int n = graph.size();
    vector<vector<int>> dist = graph;
    vector<bool> updated(n, false); // Flag to track if distance vector was updated

    // Distance vector algorithm
    bool anyUpdate;
    do {
        anyUpdate = false;
        for (int i = 0; i < n; i++) { // For each node
            for (int j = 0; j < n; j++) { // For each destination
                for (int k = 0; k < n; k++) { // For each intermediate node
                    if (dist[i][k] != INF && dist[k][j] != INF) {
                        if (dist[i][j] > dist[i][k] + dist[k][j]) {
                            dist[i][j] = dist[i][k] + dist[k][j];
                            updated[i] = true; // Marks if for node i was updated
                            anyUpdate = true; // Set anyUpdate flag to true
                        }
                    }
                }
            }
        }

        // Send updated distance vectors to neighbors
        for (int i = 0; i < n; i++) {
            if (updated[i]) { // If distance vector for node i was updated
                cout << "Node " << i << " updated its distance vector.\n";
        // Send updated distance vector to neighbors (not implemented in this example)
                updated[i] = false; // Reset updated flag for node i
            }
        }
    } while (anyUpdate); // Repeat until no updates

    printDistanceVector(dist);
}

int main() {
    int n;
    cout << "Enter the number of nodes: ";
    cin >> n;

    vector<vector<int>> graph(n, vector<int>(n, INF));

    cout << "Enter the adjacency matrix representing costs between nodes:\n";
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cin >> graph[i][j];
        }
    }

    distanceVectorRouting(graph);

    return 0;
}
