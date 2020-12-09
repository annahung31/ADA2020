// C++ program to find the longest 
// path in the DAG 

#include <bits/stdc++.h> 
using namespace std; 


long long child[1000000];
long long MAX;
long long dp[1000000];
vector<long long> backup;



// Function to add an edge 
void addEdge(vector<vector<long long> > adj[], long long u, long long v, long long w) 
{ 
	adj[u].push_back({ u, v, w}); 
	
} 


void dfs(long long node, vector<vector<long long > > adj[], long long dis[], bool vis[], long long& max_node) 
{ 
	// Mark as visited 
	vis[node] = true; 
	// cout << "visit " << node << "\n";
	

	// Traverse for all its children 
	for (long long i = 0; i < adj[node].size(); i++) { 
		// cout << adj[node][i][0] <<  " adj:" << adj[node][i][1] << "\n";

		if (!vis[adj[node][i][1]]){
			dis[adj[node][i][1]] = adj[node][i][2] + dis[node]; 
			// cout << adj[node][i][1] << " dis:" << dis[adj[node][i][1]] << "\n";
			
			if (MAX < dis[adj[node][i][1]]){
				MAX = dis[adj[node][i][1]];
				max_node = adj[node][i][1];
			}
			dfs(adj[node][i][1], adj, dis, vis, max_node);
		}
		else{
			// cout << adj[node][i][1] << "visited" << "\n";
			continue;
		}	

	} 
} 


// Function that returns the longest path 
long long findLongestPath(vector<vector<long long> > adj[], long long n, long long start) 
{ 

	long long dis[n+1];
	memset(dis, 0, sizeof dis); 

	bool vis[n + 1]; 
	memset(vis, false, sizeof vis); 
	
	memset(child, -1, sizeof child); 

	long long max_node;
	max_node = 0;

	// Call first DFS for every unvisited vertex 
	for (long long i = start; i <= n; i++) { 
		
		if (!vis[i]) 
			dfs(i, adj, dis, vis, max_node); 
	} 

	return max_node;


} 



void dfsDp(long long node, vector<vector<long long > > adj[], long long dis[], int vis[]) 
{ 
	
	// Mark as visited 
	vis[node] = 1; 
	// cout << "visit " << node << "\n";
	long long tempDp=0;
	// Traverse for all its children 
	for (long long i = 0; i < adj[node].size(); i++) { 
		// cout << adj[node][i][0] <<  " adj:" << adj[node][i][1] << "\n";

		if (vis[adj[node][i][1]] == 0){
			dis[adj[node][i][1]] = adj[node][i][2] + dis[node]; 
			// cout << adj[node][i][1] << " dis:" << dis[adj[node][i][1]] << "\n";
			
			
			MAX = max(MAX, dis[adj[node][i][1]]);
			
			dfsDp(adj[node][i][1], adj, dis, vis);
			// cout << "tempDp: " << adj[node][i][1] << ":" << dp[adj[node][i][1]] << "," << adj[node][i][2] << "\n";
			if (tempDp < dp[adj[node][i][1]] + adj[node][i][2]){
				backup.push_back(tempDp);
				tempDp = dp[adj[node][i][1]] + adj[node][i][2];
				// cout << "tempDP is " << tempDp << "\n";
				child[node] = adj[node][i][1];
				
			}
			else{
				// cout << "backup" << "\n";
				backup.push_back(dp[adj[node][i][1]] + adj[node][i][2]);
			}
			
		}
		else{
			// cout << adj[node][i][1] << "visited" << "\n";
			continue;
		}
	} 

	vis[node] = 2;
	
	dp[node] = max(dp[node], tempDp);
	// cout << node << "finished" << ", dp: " << dp[node] << "\n";
	
	
} 




void findWholeGraph(vector<vector<long long> > adj[], long long n, long long start)
{ 
	
	long long dis[n+1];
	memset(dis, 0, sizeof dis); 

	int vis[n + 1]; 
	memset(vis, 0, sizeof vis); 
	
	memset(child, -1, sizeof child); 


	// queue<int> Queue; 

	for (long long i = start; i <= n; i++) { 
		
		if (!vis[i]) 
			dfsDp(i, adj, dis, vis); 
	} 



	// for (long long i = 1; i <= n; i++){
	// 	cout << child[i] << " ";
	// }
	// cout << "\n";

	

} 



int main(){ 
    long long N, i, j, s_i, u, v, w_j; 

	MAX = 0;
    cin >> N;
    vector<vector<long long > > adj[N + 1]; 

    
    for (j = 0; j < N-1; j++){
        cin >> u >> v >> w_j;
        addEdge(adj, u, v, w_j); 
		addEdge(adj, v, u, w_j); 
		// cout << u << "," << v << ": " << v << "," << u << "\n";
    }


	for (i = 0; i <= N+1; i++){
		dp[i] = 0;
	}

	// for (i = 1; i <= N; i++){
	// 	cout << "===== start from " << i << "\n";
	// 	findLongestPath(adj, N, i);
	// 	cout << "===== finished from " << i << "\n";
	// }
	
	long long max_node = findLongestPath(adj, N, 1);
	findWholeGraph(adj, N, max_node);

	
	// for (i = 0; i <= N+1; i++){
	// 	cout << dp[i] << " ";
	// }
	// cout << "\n";
	
	sort(backup.begin(), backup.end()); 

	// cout << backup.back() << " ccc \n"; 

	for (i = 0; i < N; i++){
		if (i == 0)
			cout << 0 << " ";
		else if (i == 1)
			cout << MAX << " ";
		else{
			if (!backup.empty()){
				MAX += backup.back();
				cout << MAX  << " ";
				backup.pop_back();
			}
			else{
				cout << MAX << " ";
			}
		}
	}
    
	cout << "\n";

    return 0;
}