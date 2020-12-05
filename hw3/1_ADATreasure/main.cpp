// C++ program to find the longest 
// path in the DAG 
// Reference: https://www.geeksforgeeks.org/longest-path-in-a-directed-acyclic-graph-dynamic-programming/

#include <bits/stdc++.h> 
using namespace std; 

long long S[1000000];
long long S_DAG[1000000];
long long discover[1000000];
long long finish[1000000];
long long predecessor[1000000];
long long parent[1000000];

// Function to traverse the DAG 
// and apply Dynamic Programming 
// to find the longest path 
void dfs(long long node, vector<vector<long long>> adj[], int vis[], long long& time, stack<int> &Stack) 
{ 
	// Mark as visited 
	vis[node] = 1; 
	discover[node] = time++;  

	// Traverse for all its children 
	for (long long i = 0; i < adj[node].size(); i++) { 
		
		// If not visited 
		if (!vis[adj[node][i][1]]) 

			dfs(adj[node][i][1], adj, vis, time, Stack); 

		
	} 

	// Mark as finished
	vis[node] = 2; 
	finish[node] = time++;  
	Stack.push(node);
	

} 

void sec_dfs(long long node, vector<vector<long long>> adj_T[], int vis[], long long component_id, vector<vector<long long>> components[]){
	vis[node] = 2;
	
	// cout << node << " ";
	// Traverse for all its children 
	for (long long i = 0; i < adj_T[node].size(); i++) { 
		
		// If not visited 
		if (!vis[adj_T[node][i][1]]) 
			sec_dfs(adj_T[node][i][1], adj_T, vis, component_id, components); 
	} 


	// cout << "C[" << component_id << "] append [" << node << "]\n";
	components[component_id].push_back({node});
	S_DAG[component_id] = S_DAG[component_id] + S[node];
	parent[node] = component_id;
}


void third_dfs(long long node, vector<vector<long long>> adj_DAG[], long long dp[], int vis[]) 
{ 
	// Mark as visited 
	vis[node] = 1; 

	// Traverse for all its children 
	for (long long i = 0; i < adj_DAG[node].size(); i++) { 
		
		// If not visited 
		if (!vis[adj_DAG[node][i][1]]) 

			third_dfs(adj_DAG[node][i][1], adj_DAG, dp, vis); 

		// Store the max of the paths 
		dp[node] = max(dp[node], S_DAG[node]+ adj_DAG[node][i][2] + dp[adj_DAG[node][i][1]]); 
		
	} 

	// Mark as finished
	vis[node] = 2; 	

} 

void condense_graph_dfs(long long node, vector<vector<long long>> adj[], vector<vector<long long>> adj_DAG[], int vis[]) 
{ 
    vis[node]=2; 
    for (long long i = 0; i < adj[node].size(); i++) 
    { 
        long long p_start=parent[node];             // node belongs to which component
        long long p_vertex=parent[adj[node][i][1]]; // adjency of node belongs to which component
        // cout << node << "belong to " << p_start << " , and " << adj[node][i][1] << " belong to"  << p_vertex << "\n";
		
		if(p_start==p_vertex)                       // in the same component
        { 
			S_DAG[p_start] += adj[node][i][2];
            continue; 
        } 
        else 
        { 
            adj_DAG[p_start].push_back({p_start, p_vertex, adj[node][i][2]}); 
			// cout << "edge in DAG: " << p_start << " -> " << p_vertex << ", " <<adj[node][i][2] << "\n";
			
        } 
        if(!vis[adj[node][i][1]]) 
            condense_graph_dfs(adj[node][i][1], adj, adj_DAG, vis); 
    } 
}







// Function to add an edge 
void addEdge(vector<vector<long long>> adj[], long long u, long long v, long long w) 
{ 
	adj[u].push_back({u, v, w}); 
	
} 




// Function that returns the longest path 
long long findLongestPath(vector<vector<long long>> adj[], vector<vector<long long>> adj_T[],  long long n) 
{ 

	// Visited array to know if the node 
	// has been visited previously or not 
	int vis[n + 1]; 
	memset(vis, 0, sizeof vis); 


	// Set stack to store finishing time order
	stack<int> Stack; 
	

	long long time = 0; 

	// Call DFS for every unvisited vertex 
	for (long long i = 1; i <= n; i++) { 
		
		if (!vis[i]) 
			dfs(i, adj, vis, time, Stack); 
	} 



    // Mark all the vertices as not visited (For second DFS) 
    for (long long i = 1; i <= n; i++) 
        vis[i] = 0; 


	long long component_id = 0;
	vector<vector<long long>> components[n + 1]; 
    while (Stack.empty() == false) 
    { 
        // Pop a vertex from stack 
        long long i = Stack.top(); 
        Stack.pop(); 
  
        // Print Strongly connected component of the popped vertex 
		
        if (!vis[i]) 
        {
			// cout << i << endl;  
			component_id++;
			S_DAG[component_id] = 0;
            sec_dfs(i, adj_T, vis, component_id, components); 
            
        } 
		
		
    }



    for (long long i = 1; i <= n; i++) 
        vis[i] = 0; 

	vector<vector<long long>> adj_DAG[n + 1]; 
	for (long long i = 1; i <= n; i++) { 
		if (!vis[i]) 
			condense_graph_dfs(i, adj, adj_DAG, vis);
	} 

	// Dp array 
	long long dp[n + 1]; 
	memset(dp, 0, sizeof dp); 
	for (long long i = 1; i <=component_id; i++){
		dp[i] = S_DAG[i];
	}
    for (long long i = 1; i <= n; i++) 
        vis[i] = 0; 

	// Third dfs for DAG
	for (long long i = 1; i <= n; i++) { 
		
		if (!vis[i]) 
			third_dfs(i, adj_DAG, dp, vis); 
	} 



	long long ans = 0; 

	// Traverse and find the maximum of all dp[i] 
	for (long long i = 1; i <= n; i++) { 
		ans = max(ans, dp[i]); 
	} 



	return ans; 
} 





int main(){ 
    long long N, M, i, j, s_i, u, v, w_j;

    cin >> N >> M;
    vector<vector<long long>> adj[N + 1]; 
	vector<vector<long long>> adj_T[N + 1]; 


	for (i = 1; i <= N; i++){
		cin >> s_i;
		S[i] = s_i;
		discover[i] = 0;
		finish[i] = 0;
		predecessor[i] = -1;	
	}
    
    for (j = 0; j < M; j++){
        cin >> u >> v >> w_j;
        addEdge(adj, u, v, w_j);
		addEdge(adj_T, v, u, w_j);  
    }
    cout << findLongestPath(adj, adj_T, N) << "\n"; 


    return 0;
}

