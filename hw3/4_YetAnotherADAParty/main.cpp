#include <bits/stdc++.h>
using namespace std;

long long ans[1000000];  
long long output[1000000];
long long changeTime[1000000];
typedef pair<long long, long long> iPair; 



struct Group {  
    string s;  
    long long c;
	long long t;
	long long k;
};


void solve(Group groups[], long long N, long long Q){
    deque < iPair > line;

    long long i, j, idx, group_type, group_size, added_num, delta, ans_temp;
    for (i=1; i <= Q; i++){
        // cout << "======" << "\n";
        /*
        groups[i].s = [front/back]
        groups[i].c = number of new people
        groups[i].t = type
        groups[i].k = number to persuade
        */
        ans_temp = ans[groups[i].t];
        added_num = 0;
        if (groups[i].s == "back"){
            if (!line.empty()){
                idx = line.size() - 1;
                while (groups[i].k > 0 && idx >= 0){

                    group_size = line[idx].first;
                    group_type = line[idx].second; 
                    // cout << "check" << idx << " :(" << group_size << "," <<  group_type << ")" << "\n";

                    // look back to the neighors
                    if (group_type != groups[i].t){  // if not the same type,  

                        // update output
                        delta = i - changeTime[group_type];
                        output[group_type] += delta * ans[group_type];
                        // cout << "output update for " <<  group_type <<  "when change " << delta << " * " << ans[group_type] << "\n";
                        changeTime[group_type] = i;

                        if (group_size <=  groups[i].k){  
                            // cout << "eat them all ";

                            // change type num
                            ans[group_type] -= group_size;
                            // cout << group_type << ": " << ans[group_type] << "\n";
                            // update line & k
                            line.pop_back();
                            groups[i].k -= group_size;
                            added_num += group_size;
                            idx--;
                            // cout << ", still need " << groups[i].k << "\n";
                            
                        }
                        else{
                            // cout << "eat partial " << "\n";
                            line[idx].first -= groups[i].k;
                            ans[group_type] -= groups[i].k;
                            // cout << group_type << ": " << ans[group_type] << "\n";
                            // cout << "type " << group_type << "left " << line[idx].first << "\n";
                            added_num += groups[i].k;
                            groups[i].k = 0;
                            break;
                        }
                    

                    
                    }
                    else{
                        // cout << "same type" << "\n";                        
                        added_num += group_size;
                        line.pop_back();
                        ans[groups[i].t] -= group_size;   //ans 在這邊被扣掉了，有什麼辦法補回來嗎
                        groups[i].k -= group_size;
                        idx--;
                    }                
                }


                // cout << "add final " << "\n";
                // update output
                delta = i - changeTime[groups[i].t];
                output[groups[i].t] += delta * ans_temp;
                // cout << "output update for " <<  groups[i].t <<  " when add final  " << delta << " * " << ans_temp << "\n";
                changeTime[groups[i].t] = i;

                // record status and update ans
                line.push_back({groups[i].c + added_num, groups[i].t});   
                ans[groups[i].t] = ans[groups[i].t] + groups[i].c + added_num;



                // cout << groups[i].t << ": " << ans[groups[i].t] << "\n";
            }

            else{
                // cout << "begin:" << "\n";
                line.push_back({groups[i].c, groups[i].t}); 
                ans[groups[i].t] += groups[i].c;
                changeTime[groups[i].t] = i;
                // cout << groups[i].t << ": " << ans[groups[i].t] << "\n";
            }
                      
       }


        else{
            if (!line.empty()){
                idx = 0;
                while (groups[i].k > 0 && idx < line.size()){

                    group_size = line[idx].first;
                    group_type = line[idx].second; 
                    // cout << "check" << idx << " :(" << group_size << "," <<  group_type << ")" << "\n";

                    // look back to the neighors
                    if (group_type != groups[i].t){  // if not the same type,  
                        

                        // update output
                        delta = i - changeTime[group_type];
                        output[group_type] += delta * ans[group_type];
                        // cout << "output update for " <<  group_type <<  "when change " << delta << " * " << ans[group_type] << "\n";
                        changeTime[group_type] = i;


                        if (group_size <=  groups[i].k){  
                            // cout << "eat them all ";

                            // change type num
                            ans[group_type] -= group_size;
                            // cout << group_type << ": " << ans[group_type] << "\n";
                            // update line & k
                            line.pop_front();
                            groups[i].k -= group_size;
                            added_num += group_size;
                            // cout << ", still need " << groups[i].k << "\n";
                            
                        }
                        else{
                            // cout << "eat partial " << "\n";
                            line[idx].first -= groups[i].k;
                            ans[group_type] -= groups[i].k;
                            // cout << group_type << ": " << ans[group_type] << "\n";
                            // cout << "type " << group_type << "left " << line[idx].first << "\n";
                            added_num += groups[i].k;
                            groups[i].k = 0;
                            break;
                        }
                    }
                    else{
                        // cout << "same type" << "\n";                        
                        added_num += group_size;
                        line.pop_front();
                        ans[groups[i].t] -= group_size;
                        groups[i].k -= group_size;
                    }                
                }

                // cout << "add final " << "\n";
                // update output
                delta = i - changeTime[groups[i].t];
                output[groups[i].t] += delta * ans_temp;
                // cout << "output update for " <<  groups[i].t <<  " when add final  " << delta << " * " << ans_temp << "\n";
                changeTime[groups[i].t] = i;


                line.push_front({groups[i].c + added_num, groups[i].t});   
                ans[groups[i].t] = ans[groups[i].t] + groups[i].c + added_num;
                
                // cout << groups[i].t << ": " << ans[groups[i].t] << "\n";
            }

            else{
                // cout << "begin:" << "\n";
                line.push_front({groups[i].c, groups[i].t}); 
                ans[groups[i].t] += groups[i].c;
                changeTime[groups[i].t] = i;
                // cout << groups[i].t << ": " << ans[groups[i].t] << "\n";
            }
                 
        }




        // cout << i << ": ";
        // for (j = 0; j< line.size(); j++){
        //     cout << "( " << line[j].first << "," << line[j].second << " )";
        // }
        // cout << "\n";

        // for (j = 1; j <= N; j++){
            
        //     cout << ans[j] << " ";
            
        // }
        // cout << "\nchangetime:";

        // for (j = 1; j <= N; j++){
            
        //     cout << changeTime[j] << " ";
            
        // }
        // cout << "\noutput: ";


        // for (j = 1; j <= N; j++){
            
        //     cout << output[j] << " ";
            
        // }
        // cout << "\n";



    }

    // cout << "last check:" << " ";
    for (j = 1; j <= N; j++){
        delta = i - changeTime[j];
        output[j] += delta * ans[j];

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

	for (i = 0; i <= N+2; i++){
			ans[i] = 0;
            output[i] = 0;
            changeTime[i] = 0;
	}

	solve(groups, N, Q);

    for (i = 1; i <= N; i++){
        cout << output[i] << " ";
    }
    cout << "\n";

    return 0; 
} 



