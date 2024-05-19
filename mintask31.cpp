#include <algorithm>
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <cassert>
#include <fstream>

using namespace std;

map<int, string> intToFunc;
map<string, int> funcToInt;
map<int, vector<int>> graph;
map<int, vector<int>> reverseGraph;

void getTimes(int node, vector<bool> &visited, vector<int> &graphTime, int &index) {
  visited[node] = true;
  for (auto &&newNode : reverseGraph[node]) {
    if (visited[newNode]) continue;
    getTimes(newNode, visited, graphTime, index);
  }
  graphTime[index--] = node;
}

bool isCycle(int node, vector<int> &visited, vector<int> &ans) {
  visited[node] = 1;
  bool cycle = false;
  for (auto newNode : graph[node]) {
    if (visited[newNode] == 1) {
        cycle = true;
    }
    if (visited[newNode]) continue;
     cycle = isCycle(newNode, visited, ans) || cycle;
    }
  ans.push_back(node);
  visited[node] = 2;
  return cycle;
}

vector<pair<vector<int>, bool>> kosaraju() {
  int n = funcToInt.size();
  vector<bool> visitedTime(n, false);
  vector<int> graphTime(n);
  int index = n - 1;
  for (int i = 0; i < n; i++) {
    if (!visitedTime[i]) getTimes(i, visitedTime, graphTime, index);
  }
  vector<int> visited(n, 0);
  vector<pair<vector<int>, bool>> ans;
  for (size_t i = 0; i < n; i++) {
    if (!visited[graphTime[i]]){
      ans.push_back({});
      ans.back().second = isCycle(graphTime[i], visited, ans.back().first);
    }
  }
  return ans;
}

void saveFunc(int &c, string func) {
  if (funcToInt.find(func) == funcToInt.end()) {
      intToFunc[c] = func;
      funcToInt[func] = c++;
    }
}

void getGraphs(int n, ifstream &cin) {
  int c = 0;
  for (size_t i = 0; i < n; i++) {
    string from;
    cin >> from;
    cout << from << " ";
    from.pop_back();
    saveFunc(c, from);
    int nFrom = funcToInt[from];
    string func;
    cin >> func;
    cout << func << " ";
    while (func.back() == ',') {
      func.pop_back();
      saveFunc(c, func);
      graph[nFrom].push_back(funcToInt[func]);
      reverseGraph[funcToInt[func]].push_back(nFrom);
      cin >> func;
      cout << func << " ";
    }
    cout << "\n";
    saveFunc(c, func);
    graph[nFrom].push_back(funcToInt[func]);
    reverseGraph[funcToInt[func]].push_back(nFrom);
  }
}

void solve(ifstream &cin) {
  int n;
  assert(n > 0);
  cin >> n;
  getGraphs(n, cin);
  auto ans = kosaraju();
  int maxIndex = -1;
  for (size_t i = 0; i < ans.size(); i++) {
    vector<int> &group = ans[i].first;
    bool cycle = ans[i].second;
    if (cycle && (ans[maxIndex].first.size() < group.size() || maxIndex == -1)) maxIndex = i;
    for (auto &&func : group) {
      cout << "Recursion in function " << intToFunc[func] << ": " << cycle << "\n";
    }
  }
  if (maxIndex == -1) {
    cout << "No recursion components\n";
    return;
  }
  cout << "Maximum recursion component: ";
  vector<int> &maxRC = ans[maxIndex].first;
  for (int i = 0; i < maxRC.size() - 1; i++) {
    cout << intToFunc[maxRC[i]] << ", ";
  }
  cout << intToFunc[maxRC[maxRC.size() - 1]] << "\n";

}
int main() {
  ifstream cin;
  cin.open("tests.txt");
  int m;
  cin >> m;
  for (int i = 0; i < m; i++) {
    intToFunc = map<int, string>();
    funcToInt = map<string, int>();
    graph = map<int, vector<int>>();
    reverseGraph = map<int, vector<int>>();
    solve(cin);
    cout << "\n";
  }
}
