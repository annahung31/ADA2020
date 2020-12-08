// C++ program to find the longest 
// path in the DAG 

#include <bits/stdc++.h>
using namespace std;


long long ans[1000000][1000000];   // ans[type][group]

struct Group {  
    string s;  
    long long c;
	long long t;
	long long k;
};



void printGroup(struct Group g) {
    printf("g(%d, %d, %d)\n", g.c, g.t, g.k);
	if (g.s == "back")
		cout << "back" << "\n";
}


void solve(Group groups[], long long N, long long Q){
	
	for (long long i=1; i <= Q; i++){
		printGroup(groups[i]);
		// cout << i << "," << groups[i].t << "," << groups[i].c << "\n";
		ans[groups[i].t][i] = ans[groups[i].t][i-1] + groups[i].c;
		
	}
}


int main() { 
	cin.tie(nullptr), cout.sync_with_stdio(0);

	long long N, Q, i, j, c_i, t_i, k_i;
	string s_i;
	cin >> N >> Q;

    struct Group g;	
	Group groups[Q+1];

	for (i = 1; i <= Q; i++){
		cin >> s_i >> c_i >> t_i >> k_i;
		g.s = s_i;
		g.c = c_i;
		g.t = t_i;
		g.k = k_i;
		groups[i] = g;
	}

	for (i = 0; i <= N; i++){
		for (j = 0; j <= Q; j++){
			ans[i][j] = 0;
		}
	}

	solve(groups, N, Q);

	// count output
	for (i=1; i<=N; i++){
		long long popularity =0;
		for (j = 1; j <= Q; j++){
			popularity += ans[i][j];
		}
		cout << popularity << " ";
	}

	cout << "\n";


    return 0; 
} 



