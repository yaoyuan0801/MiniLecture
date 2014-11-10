#include <iostream>
#include <unordered_map>
#include <vector>
#include <unordered_set>
#include <algorithm>
#include <map>
#include <set>

using namespace std;

void printVector(vector<int> &v) {
  for (int x : v) {
    cout << x <<" ";
  }
  cout << endl;
}

vector<int> topoSort(map<int, vector<int> > &adjList) {
  map<int, int> reverseAdjList;
  set<int> candidates;
  vector<int> res;
  for (auto &node: adjList) {
    candidates.insert(node.first);
  }
  // construct reverseAdjList
  for (auto &node: adjList) {
    for (int toNode : node.second) {
      if (reverseAdjList.find(toNode) == reverseAdjList.end()) {
        reverseAdjList[toNode] = 0;
        candidates.erase(toNode);
      }
      reverseAdjList[toNode]++;
    }
  }
  while (!candidates.empty()) {
    int node = *candidates.begin();
    res.push_back(node);
    candidates.erase(node);
    for (int toNode : adjList[node]) {
      reverseAdjList[toNode]--;
      if (reverseAdjList[toNode] == 0) {
        candidates.insert(toNode);
      }
    }
  }
  if (res.size() < adjList.size()) {
    cout << "Circle!" << endl;
  }
  return res;
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
