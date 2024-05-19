#include <vector>
#include <iostream>

using namespace std;

bool dfs(int node, int color, vector<vector<int>> &graph, vector<int> &visited) {
  visited[node] = color;
  for (int i = 0; i < graph[node].size(); i++) {
    int newNode = graph[node][i];
    if (visited[newNode] == color) return false;
    if (visited[newNode] == -color) continue; 
    if (!dfs(newNode, -color, graph, visited)) return false;
  }
  return true;
}

bool isBipartite(vector<vector<int>>& graph) {
    size_t n = graph.size();
    vector<int> visited = vector<int>(n, 0);
    for (int i = 0; i < n; i++) {
      if (visited[i] == 0) {
        if (!dfs(i, 1, graph, visited)) return false;
      }
    }
    return true;
}

int main() {
  vector<vector<int>> a = {{2,3,5,6,7,8,9},{2,3,4,5,6,7,8,9},{0,1,3,4,5,6,7,8,9},{0,1,2,4,5,6,7,8,9},{1,2,3,6,9},{0,1,2,3,7,8,9},{0,1,2,3,4,7,8,9},{0,1,2,3,5,6,8,9},{0,1,2,3,5,6,7},{0,1,2,3,4,5,6,7}};
  cout << isBipartite(a) << "\n";
}
