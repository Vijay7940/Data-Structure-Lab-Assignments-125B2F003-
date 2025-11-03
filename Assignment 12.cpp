#include <iostream>
using namespace std;

#define MAX 100       // Max no of houses (vertices)
#define INF 999999    // Represents infinity (very large value for comparison)

// CLASS 1: PRIM'S ALGORITHM
class PipelineNetwork {
private:
    int vertices;               // No of houses
    int graph[MAX][MAX];        // Adjacency matrix to store connection costs
   
    // Method: Find vertex with minm key value not yet included in MST
    int findMinKey(int key[], bool mstSet[]) {
        int min = INF;
        int minIndex = -1;
       
        for (int v = 0; v < vertices; v++) {
            if (!mstSet[v] && key[v] < min) {
                min = key[v];
                minIndex = v;
            }
        }
        return minIndex;
    }
   
    // Method: Print the final Minimum Spanning Tree
    void printMST(int parent[], int graph[MAX][MAX]) {
        cout << "\n=== Water Pipeline Network Layout ===" << endl;
        cout << "Connection\t\tCost (in thousands)" << endl;
        int totalCost = 0;
       
        for (int i = 1; i < vertices; i++) {
            cout << "House " << parent[i] << " - House " << i 
                 << "\t\t" << graph[i][parent[i]] << endl;
            totalCost += graph[i][parent[i]];
        }
       
        cout << "\nTotal Cost: " << totalCost << " thousands" << endl;
        cout << "Total Houses Connected: " << vertices << endl;
    }
   
public:
    // Constructor: Initialize graph with 0 cost (no connection)
    PipelineNetwork(int v) {
        vertices = v;
        for (int i = 0; i < MAX; i++) {
            for (int j = 0; j < MAX; j++) {
                graph[i][j] = 0;
            }
        }
    }
   
    // Method: Add connection between two houses
    void addConnection(int house1, int house2, int cost) {
        graph[house1][house2] = cost;
        graph[house2][house1] = cost; // Undirected connection
    }
   
    // Method: Apply Prim's Algorithm to find MST
    void primMST() {
        int parent[MAX];     // Stores constructed MST
        int key[MAX];        // Minimum cost to connect a house
        bool mstSet[MAX];    // Tracks houses included in MST
       
        // Initialize all keys as infinite and mstSet as false
        for (int i = 0; i < vertices; i++) {
            key[i] = INF;
            mstSet[i] = false;
        }
       
        // Start from the first house (vertex 0)
        key[0] = 0;
        parent[0] = -1; // Root node has no parent
       
        // Constructing MST with (vertices - 1) edges
        for (int count = 0; count < vertices - 1; count++) {
            // Pick minimum key vertex not yet included in MST
            int u = findMinKey(key, mstSet);
            mstSet[u] = true;
           
            // Update key values of adjacent vertices
            for (int v = 0; v < vertices; v++) {
                if (graph[u][v] && !mstSet[v] && graph[u][v] < key[v]) {
                    parent[v] = u;
                    key[v] = graph[u][v];
                }
            }
        }
       
        // Print the constructed MST
        printMST(parent, graph);
    }
   
    // Method: Display available pipeline connections (input data)
    void displayGraph() {
        cout << "\n=== Available Pipeline Connections ===" << endl;
        cout << "House1\tHouse2\tCost" << endl;
        for (int i = 0; i < vertices; i++) {
            for (int j = i + 1; j < vertices; j++) {
                if (graph[i][j] != 0) {
                    cout << i << "\t" << j << "\t" << graph[i][j] << endl;
                }
            }
        }
    }
};

// CLASS 2: KRUSKAL'S ALGORITHM
class KruskalPipelineNetwork {
private:
    // Structure to represent a pipeline connection
    struct Edge {
        int src;
        int dest;
        int cost;
    };
   
    int vertices;        // Number of houses
    Edge edges[MAX];     // Array of all connections
    int edgeCount;       // Total number of edges added
    int parent[MAX];     // For Disjoint Set (Union-Find)
   
    // Method: Find the parent of a node (with path compression)
    int find(int i) {
        if (parent[i] == i) {
            return i;
        }
        return find(parent[i]);
    }
   
    // Method: Union of two sets (connect components)
    void unionSets(int x, int y) {
        int xroot = find(x);
        int yroot = find(y);
        parent[xroot] = yroot;
    }
   
    // Method: Sort edges in ascending order of cost (Bubble Sort)
    void sortEdges() {
        for (int i = 0; i < edgeCount - 1; i++) {
            for (int j = 0; j < edgeCount - i - 1; j++) {
                if (edges[j].cost > edges[j + 1].cost) {
                    Edge temp = edges[j];
                    edges[j] = edges[j + 1];
                    edges[j + 1] = temp;
                }
            }
        }
    }
   
public:
    // Constructor: Initialize vertices and parent array
    KruskalPipelineNetwork(int v) {
        vertices = v;
        edgeCount = 0;
        for (int i = 0; i < vertices; i++) {
            parent[i] = i;
        }
    }
   
    // Method: Add an edge (connection) between two houses
    void addEdge(int src, int dest, int cost) {
        edges[edgeCount].src = src;
        edges[edgeCount].dest = dest;
        edges[edgeCount].cost = cost;
        edgeCount++;
    }
   
    // Method: Apply Kruskal's Algorithm to find MST
    void kruskalMST() {
        // Step 1: Sort all edges by cost
        sortEdges();
       
        cout << "\n=== Water Pipeline Network Layout (Kruskal) ===" << endl;
        cout << "Connection\t\tCost (in thousands)" << endl;
       
        int totalCost = 0;
        int edgesSelected = 0;
       
        // Step 2: Pick smallest edge one by one
        for (int i = 0; i < edgeCount && edgesSelected < vertices - 1; i++) {
            int x = find(edges[i].src);
            int y = find(edges[i].dest);
           
            // If including this edge doesn’t form a cycle
            if (x != y) {
                cout << "House " << edges[i].src << " - House " << edges[i].dest 
                     << "\t\t" << edges[i].cost << endl;
                totalCost += edges[i].cost;
                unionSets(x, y);
                edgesSelected++;
            }
        }
       
        // Display total MST cost
        cout << "\nTotal Cost: " << totalCost << " thousands" << endl;
        cout << "Total Houses Connected: " << vertices << endl;
    }
};

// MAIN FUNCTION 
int main() {
    int numHouses;
   
    cout << "=== Pimpri Chinchwad Municipal Corporation ===" << endl;
    cout << "=== Water Pipeline Network Planning ===" << endl;
   
    // Input number of houses
    cout << "\nEnter number of houses: ";
    cin >> numHouses;
   
    PipelineNetwork network(numHouses);  // Create Prim's network object
   
    // Input number of connections
    int numConnections;
    cout << "Enter number of possible pipeline connections: ";
    cin >> numConnections;
   
    // Input connections (house1 house2 cost)
    cout << "\nEnter connections (house1 house2 cost):" << endl;
    for (int i = 0; i < numConnections; i++) {
        int h1, h2, cost;
        cin >> h1 >> h2 >> cost;
        network.addConnection(h1, h2, cost);
    }
   
    // Displaying input graph
    network.displayGraph();
   
    // Apply Prim's Algorithm
    cout << "\n=== Using Prim's Algorithm ===" << endl;
    network.primMST();
   
    // Create Kruskal network object
    KruskalPipelineNetwork kruskalNetwork(numHouses);
   
    // Input same connections for Kruskal
    cout << "\nEnter same connections for Kruskal's algorithm:" << endl;
    for (int i = 0; i < numConnections; i++) {
        int h1, h2, cost;
        cin >> h1 >> h2 >> cost;
        kruskalNetwork.addEdge(h1, h2, cost);
    }
   
    // Apply Kruskal's Algorithm
    cout << "\n=== Using Kruskal's Algorithm ===" << endl;
    kruskalNetwork.kruskalMST();
   
    return 0;
}

