#include <iostream>
#include <vector>
#include <map>
#include <limits>
#include <algorithm>  

using namespace std;

//g_link: store graph structure
//key: node-id, value: node-ids list and corresponding edge weights linked to the key,
std::map<int, vector<pair<int,int>>> g_link;
std::map<int, map<int,bool>> visted_node;
int src_node, target_node, target_me;

//set true if print running infomation
bool verbose = true;
//if direct graph, switch first-node & second-node of input & push to graph
bool is_direct = true;



bool dfs(int parent, int current_node, int score){
  //args: 
  //current_node: 
  //cout<<"Now in node: "<<i<<", "<<a[i]<<" , sum= "<<sum<<endl;
  visted_node[parent][current_node] = true;
  if(current_node == target_node) {
    cout<<"Arrive in the destination: "<<current_node<<", current minimal edge weight = "<<score<<endl; 
    if(score < target_me) {
      target_me = score; 
    }
    return true;
  }
  //move to next child
  //cout<<"move no ****"<<i<<", no, sum= "<<sum<<endl;
  for(vector<pair<int,int>>::iterator it = g_link[current_node].begin(); it != g_link[current_node].end(); it++) {
    //cout<<"Now in node: "<<*it<<", score = "<<score<<endl; 
    int sc = min(it->second, score);
    if(verbose)
      cout<<"Now in node: "<<it->first<<", score = "<<sc<<endl;

    if(!visted_node[current_node][it->first])
      if(dfs(current_node, it->first, sc)) {
      cout<<"Now in node: "<<it->first<<", score = "<<sc<<endl; 
        //return true;
    }
  }

  return false;
}
void solve(){
  if(dfs(0, src_node, target_me)) 
    cout<<"minimal weight: "<<target_me;
  else 
    cout<<"All path searched for answe"<<endl;
}

int main(int argc, char** argv) {
  /*test data
  5 5
  1 3 3
  1 2 2
  2 4 2
  2 5 1
  3 5 10  

  1 5 minimal 1
  3 5 not find
  */;
  
  //read in node-size & edge number
  int node_size, edge_size;
  cout<<"Input: node number, edge number"<<endl;
  cin>>node_size>>edge_size;
  //Read-in link info into g_link a line-by-line
  for(int k = 0; k < edge_size; k++) {
    int first_node, next_node,weight;
    cin>>first_node>>next_node>>weight;
    if(g_link.find(first_node) == g_link.end()) {
      //if first_node not in graph, i.e. first time insert it, create a empty vector to save target node list
      g_link[first_node] = vector<pair<int,int>>();
      visted_node[first_node] = map<int,bool>();
    }
    g_link[first_node].push_back(pair<int,int>(next_node, weight));
    visted_node[first_node][next_node] = false;

    //
    if(is_direct) {
      if(g_link.find(next_node) == g_link.end()) {
        //if first_node not in graph, i.e. first time insert it, create a empty vector to save target node list
        g_link[next_node] = vector<pair<int,int>>();
        visted_node[next_node] = map<int,bool>();
      }
      g_link[next_node].push_back(pair<int,int>(first_node, weight)); 
      visted_node[next_node][first_node] = false;
    }
  }

  if(verbose) {
    for(map<int,vector<pair<int,int>>>::iterator it=g_link.begin(); it!=g_link.end(); it++) {
      //cout<<it->first<<" ";
      for(vector<pair<int,int>>::iterator it2=it->second.begin(); it2 != it->second.end(); it2++) {
        cout<<it->first<<" "<<it2->first<<" "<<it2->second<<endl;
      }
    }
  }
  //

  cout<<"Input source node and targte node"<<endl;
  cin>>src_node>>target_node;


  int mx_limit = std::numeric_limits<int>::max();
  target_me = mx_limit;
  solve();
  if(target_me < mx_limit) {
    cout<< "minimal weight: "<< target_me<<endl;
  }
  else {
    cout<<"Not find because no path"<<endl;
  }
  return 0;
}
