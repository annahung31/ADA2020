// REFERENCE:
// https://www.geeksforgeeks.org/kruskals-minimum-spanning-tree-using-stl-in-c/ 
// https://www.geeksforgeeks.org/dijkstras-shortest-path-algorithm-using-priority_queue-stl/

#include <bits/stdc++.h> 
using namespace std; 
typedef pair<long long, long long> iPair; 
# define INF LLONG_MAX

////////// codes for dijkstra /////////////////
// A directed graph using adjacency list representation  
class GraphD { 
	long long V; // No. of vertices 
	// store vertex and weight pair for every edge
	list< pair<long long, long long> > *adj; 

public: 
	GraphD(long long V); // Constructor 
	void addEdge(long long u, long long v, long long w); 
	long long shortestPath(long long s, long long t); 
}; 

// Allocates memory for adjacency list 
GraphD::GraphD(long long V){ 
	this->V = V; 
	adj = new list<iPair> [V]; 
} 

void GraphD::addEdge(long long u, long long v, long long w){ 
	adj[u].push_back(make_pair(v, w)); 
	adj[v].push_back(make_pair(u, w)); 
} 

// Prints shortest paths from src to all other vertices 
long long GraphD::shortestPath(long long src, long long dst){ 
	priority_queue< iPair, vector <iPair> , greater<iPair> > pq; 
	vector<long long> dist(V, INF); 
	pq.push(make_pair(0, src)); 
	dist[src] = 0; 

	while (!pq.empty()){ 
		long long u = pq.top().second; 
		pq.pop(); 

		// Get all adjacent vertices of a vertex 
		list< pair<long long, long long> >::iterator i; 
		for (i = adj[u].begin(); i != adj[u].end(); ++i) {  
			long long v = (*i).first; 
			long long weight = (*i).second;

            // relax
			if (dist[v] > dist[u] + weight){ 

				dist[v] = dist[u] + weight; 
				pq.push(make_pair(dist[v], v)); 
			} 
		} 
	} 

    return dist[dst];
} 


// Graph for kruskal 
struct Graph{ 
	long long V, E; 
	vector< pair<long long, iPair> > edges; 

	// Constructor 
	Graph(long long V, long long E){ 
		this->V = V; 
		this->E = E; 
	} 

	// Utility function to add an edge 
	void addEdge(long long u, long long v, long long w){ 
		edges.push_back({w, {u, v}}); 
	} 

	long long solve(long long S, long long T); 
}; 

struct DisjointSets{ 
    long long *parent, *rnk; 
    long long n; 
  
    DisjointSets(long long n) { 
        // Allocate memory 
        this->n = n; 
        parent = new long long[n+1]; 
        rnk = new long long[n+1]; 
  
        // Initially, all vertices are in different sets and have rank 0. 
        for (long long i = 0; i <= n; i++){ 
            rnk[i] = 0; 
            parent[i] = i; //every element is parent of itself 
        } 
    } 
  
    long long find(long long u){ 
        /* Make the parent of the nodes in the path 
           from u--> parent[u] point to parent[u] */
        if (u != parent[u]) 
            parent[u] = find(parent[u]); 
        return parent[u]; 
    } 
  
    // Union by rank 
    void merge(long long x, long long y) { 
        x = find(x), y = find(y); 
  
        //  Make tree with smaller height a subtree of the other tree
        if (rnk[x] > rnk[y]) 
            parent[y] = x; 
        else
            parent[x] = y; 
  
        if (rnk[x] == rnk[y]) 
            rnk[y]++; 
    } 
}; 

long long Graph::solve(long long S, long long T){ 
    // Sort edges in increasing order on basis of cost 
    sort(edges.begin(), edges.end()); 
  
    DisjointSets ds(V);  // disjoint sets 
    GraphD g(V);         // dijkstra Graph
  
    // Iterate through all sorted edges 
    vector< pair<long long, iPair> >::iterator it; 
    for (it=edges.begin(); it!=edges.end(); it++){ 
        long long u = it->second.first; 
        long long v = it->second.second; 
  
        long long set_u = ds.find(u); 
        long long set_v = ds.find(v); 
  
        // check cycle
        if (set_u != set_v){ 
            ds.merge(set_u, set_v); 

            // Add edge into dijkstra graph
            g.addEdge(u-1, v-1, it->first); 
            g.addEdge(v-1, u-1, it->first); 
        } 
    } 

	// dijkstra
    long long ans = g.shortestPath(S-1, T-1); 
	
    return ans; 
} 
  
int main(){ 
	int V, E, S, T, u, v, w, i;
    cin >> V >> E >> S >> T; 
	Graph g(V, E); 

    for (i = 0; i < E; i++){
        cin >> u >> v >> w;
        g.addEdge(u, v, w); 
    }

    long long ans = g.solve(S, T); 
    cout << ans << "\n";
	return 0; 
} 
