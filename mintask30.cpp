#include <vector>
#include <iostream>

using namespace std;

bool dfs(int node, vector<vector<int>> &graph, vector<int> &visited, int &c, vector<int> &ans) {
  visited[node] = 1;
  bool correct = 1;
  for (auto newNode : graph[node]) {
    if (visited[newNode] == 1) return false;
    if (visited[newNode] == 2) continue;
     correct = dfs(newNode, graph, visited, c, ans);
    }
  ans[node] = c--;
  visited[node] = 2;
  return correct;
}

bool topSort(vector<vector<int>> &graph, vector<int> &ans) {
  int n = graph.size();
  vector<int> visited = vector<int>(n, 0);
  vector<int> reverseAns = vector<int>(n, 0);
  int c = n - 1;
  for (int i = 0; i < n; i++) {
    if (!visited[i]) {
      if (!dfs(i, graph, visited, c, reverseAns)) return false;
    }
  }
  for (int i = 0; i < n; i++) ans[reverseAns[i]] = i;
  return true;
}

vector<int> sortItems(int n, int m, vector<int>& group, vector<vector<int>>& beforeItems) {
    int g = m;
    for (int i = 0; i < n; i++) {
        if (group[i] == -1) {
            group[i] = g++;
        }
    }
    vector<vector<int>> graphItems = vector<vector<int>>(n);
    vector<vector<int>> graphGroups = vector<vector<int>>(g);
    for (int i = 0; i < n; i++) {
      for (auto &&item : beforeItems[i]) {
        graphItems[item].push_back(i);
        if (group[item] != group[i])
          graphGroups[group[item]].push_back(group[i]);
      }
    }
    vector<int> sortedItems = vector<int>(n);
    vector<int> sortedGroups = vector<int>(g);
    if (!topSort(graphItems, sortedItems) || !topSort(graphGroups, sortedGroups))
        return {};
for (auto&& i : sortedGroups) {
    cout << i << " ";
  }
cout << "\n";
    vector<vector<int>> ansDict = vector<vector<int>>(g);
    for (auto &&item : sortedItems) {
      ansDict[group[item]].push_back(item);
    }
    vector<int> ans = vector<int>(n);
    int c = 0;
    for (auto &&i : sortedGroups) {
      for (auto &&item : ansDict[i]) {
        ans[c++] = item;
      }
    }
    return ans;
}

int main() {
  int n = 8;
  int m = 2;
  vector<int> group = {-1,-1,1,0,0,1,0,-1};
  vector<vector<int>> beforeItems = {{}, {6}, {5}, {6}, {3, 6}, {}, {}, {}};
  vector<int> ans = sortItems(n, m, group, beforeItems);
  //cout << ans << "\n";
  for (auto&& i : ans) {
    cout << i << " ";
  }
  cout << "\n";
}
