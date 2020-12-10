
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/ 

#include <bits/stdc++.h> 
using namespace std; 
typedef pair<int, int> iPair; 
# define INF 0x3f3f3f3f 
// codes for dijkstra

// This class represents a directed graph using 
// adjacency list representation 
class GraphD 
{ 
	int V; // No. of vertices 

	// In a weighted graph, we need to store vertex 
	// and weight pair for every edge 
	list< pair<int, int> > *adj; 

public: 
	GraphD(int V); // Constructor 

	// function to add an edge to graph 
	void addEdge(int u, int v, int w); 

	// prints shortest path from s 
	int shortestPath(int s, int t); 
}; 

// Allocates memory for adjacency list 
GraphD::GraphD(int V) 
{ 
	this->V = V; 
	adj = new list<iPair> [V]; 
} 

void GraphD::addEdge(int u, int v, int w) 
{ 
	adj[u].push_back(make_pair(v, w)); 
	adj[v].push_back(make_pair(u, w)); 
} 

// Prints shortest paths from src to all other vertices 
int GraphD::shortestPath(int src, int dst){ 

	priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 

	vector<int> dist(V, INF); 

	pq.push(make_pair(0, src)); 
	dist[src] = 0; 

	while (!pq.empty()) 
	{ 
		
		int u = pq.top().second; 
		pq.pop(); 

		// 'i' is used to get all adjacent vertices of a vertex 
		list< pair<int, int> >::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) { 
            
			// Get vertex label and weight of current adjacent 
			// of u. 
			int v = (*i).first; 
			int weight = (*i).second; 
            
			// If there is shorted path to v through u. 
			if (dist[v] > dist[u] + weight) 
			{ 
				// Updating distance of v 
				dist[v] = dist[u] + weight; 
				pq.push(make_pair(dist[v], v)); 
			} 
		} 
	} 

    return dist[dst];
} 



// Structure to represent a graph 
struct Graph 
{ 
	int V, E; 
	vector< pair<int, iPair> > edges; 

	// Constructor 
	Graph(int V, int E) 
	{ 
		this->V = V; 
		this->E = E; 
	} 

	// Utility function to add an edge 
	void addEdge(int u, int v, int w) 
	{ 
		edges.push_back({w, {u, v}}); 
	} 

	int solve(int S, int T); 
	
}; 



// To represent Disjoint Sets 
struct DisjointSets 
{ 
    int *parent, *rnk; 
    int n; 
  
    // Constructor. 
    DisjointSets(int n) 
    { 
        // Allocate memory 
        this->n = n; 
        parent = new int[n+1]; 
        rnk = new int[n+1]; 
  
        // Initially, all vertices are in 
        // different sets and have rank 0. 
        for (int i = 0; i <= n; i++) 
        { 
            rnk[i] = 0; 
  
            //every element is parent of itself 
            parent[i] = i; 
        } 
    } 
  
    // Find the parent of a node 'u' 
    // Path Compression 
    int find(int u) 
    { 
        /* Make the parent of the nodes in the path 
           from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(int x, int y) 
    { 
        x = find(x), y = find(y); 
  
        /* Make tree with smaller height 
           a subtree of the other tree  */
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else // If rnk[x] <= rnk[y] 
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 

int Graph::solve(int S, int T) 
{ 
    int mst_wt = 0; // Initialize result 
  
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end()); 
  
    // Create disjoint sets 
    DisjointSets ds(V); 

    // create dijkstra Graph
    GraphD g(V); 
  
    // Iterate through all sorted edges 
    vector< pair<int, iPair> >::iterator it; 
    for (it=edges.begin(); it!=edges.end(); it++) 
    { 
        int u = it->second.first; 
        int v = it->second.second; 
  
        int set_u = ds.find(u); 
        int set_v = ds.find(v); 
  
        // Check if the selected edge is creating 
        // a cycle or not (Cycle is created if u 
        // and v belong to same set) 
        if (set_u != set_v) 
        { 
            // Current edge will be in the MST 
            // so print it 
  
            // Update MST weight 
            mst_wt += it->first; 
  
            // Merge two sets 
            ds.merge(set_u, set_v); 

            // Add edge into dijkstra graph
            g.addEdge(u-1, v-1, it->first); 
        } 
    } 


	// dijkstra
    int ans = g.shortestPath(S-1, T-1); 
	
    return ans; 
} 
  


// Driver program to test above functions 
int main() 
{ 
	/* Let us create above shown weighted 
	and unidrected graph */
	int V, E, S, T, u, v, w, i;
    cin >> V >> E >> S >> T; 
	Graph g(V, E); 

    for (i = 0; i < E; i++){
        cin >> u >> v >> w;
        g.addEdge(u, v, w); 
    }

    int ans = g.solve(S, T); 
	return 0; 
} 
