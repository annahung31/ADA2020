// C++ program to find the longest 
// path in the DAG 
// Reference: https://www.geeksforgeeks.org/longest-path-in-a-directed-acyclic-graph-dynamic-programming/

#include <bits/stdc++.h> 
using namespace std; 

long long S[1000000];
// Function to traverse the DAG 
// and apply Dynamic Programming 
// to find the longest path 
void dfs(long long node, vector<vector<long long>> adj[], long long dp[], bool vis[]) 
{ 
	// Mark as visited 
	vis[node] = true; 

	// Traverse for all its children 
	for (long long i = 0; i < adj[node].size(); i++) { 
		
		// If not visited 
		if (!vis[adj[node][i][1]]) 
			dfs(adj[node][i][1], adj, dp, vis); 

		// Store the max of the paths 
		dp[node] = max(dp[node], S[node]+ adj[node][i][2] + dp[adj[node][i][1]]); 
		
	} 
} 

// Function to add an edge 
void addEdge(vector<vector<long long>> adj[], long long u, long long v, long long w) 
{ 
	adj[u].push_back({u,v, w}); 
	
} 

// Function that returns the longest path 
long long findLongestPath(vector<vector<long long>> adj[], long long n) 
{ 
	// Dp array 
	long long dp[n + 1]; 
	memset(dp, 0, sizeof dp); 
	for (long long i = 1; i <=n; i++){
		dp[i] = S[i];
	}

	// Visited array to know if the node 
	// has been visited previously or not 
	bool vis[n + 1]; 
	memset(vis, false, sizeof vis); 

	// Call DFS for every unvisited vertex 
	for (long long i = 1; i <= n; i++) { 
		
		if (!vis[i]) 
			dfs(i, adj, dp, vis); 
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


	for (i = 1; i <= N; i++){
		cin >> s_i;
		S[i] = s_i;
	}
    
    for (j = 0; j < M; j++){
        cin >> u >> v >> w_j;
        addEdge(adj, u, v, w_j); 
      
    }
    cout << findLongestPath(adj, N); 

    return 0;
}