#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
#include <stack>
#include <set>

using namespace std;

void topoSortHelper(int node, set<int> &visited, map<int, vector<int> > &adjList, stack<int> &res) {
  visited.insert(node);
  for (int nextNode : adjList[node]) {
    if (visited.find(nextNode) == visited.end()) {
      topoSortHelper(nextNode, visited, adjList, res);
    }
  }
  res.push(node);
}

vector<int> topoSort(map<int, vector<int> > &adjList) {
  stack<int> res;
  set<int> visited;
  for (auto x : adjList) {
    cout << x.first << endl;
    if (visited.find(x.first) == visited.end()) {
      topoSortHelper(x.first, visited, adjList, res);
    }
  }
  vector<int> v(res.size());
  for (int i = 0; i < v.size(); i++) {
    v[i] = res.top();
    res.pop();
  }
  return v;
}

void printVector(vector<int> &v) {
  for (int x : v) {
    cout << x <<" ";
  }
  cout << endl;
}

int main(void) {
  map<int, vector<int> > adjList;
  adjList[0] = vector<int> {1, 5, 6};
  adjList[1] = vector<int>();
  adjList[2] = vector<int> {0, 3};
  adjList[3] = vector<int> {5};
  adjList[4] = vector<int> ();
  adjList[5] = vector<int> {4};
  adjList[6] = vector<int> {4, 9};
  adjList[7] = vector<int> {6};
  adjList[8] = vector<int> ();
  adjList[9] = vector<int> {10, 11, 12};
  adjList[10] = vector<int>();
  adjList[11] = vector<int> {12};
  adjList[12] = vector<int>();
  vector<int> res = topoSort(adjList);
  printVector(res); 
}
