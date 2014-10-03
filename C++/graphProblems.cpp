#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <limits.h>
#include <time.h>
#include <unordered_map>
#include <map>
#include <math.h>
#include <set>

using namespace std;

void printVector(vector<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}

void printSet(set<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}


void printVectorOfVector(vector<vector<int> > &v) {
  for (auto tmp : v) {
    printVector(tmp);
  }
  cout<<endl;
}


class SquareRing {
public:
  void getSquareRings(int idx, unordered_map<int, set<int> > &adjList, vector<int> curr, set<int> numbers, vector<vector<int> > &res, int n) {
    if (idx == n) {
      // printVector(curr);
      int root = (int)sqrt(curr[0] + curr[n - 1]);
      if (root * root == curr[0] + curr[n - 1]) {
        res.push_back(curr);
      }
      return;
    }
    if (idx == 0) {
      for (int i = 1; i <= n; i++) {
        curr.push_back(i);
        numbers.erase(i);
        getSquareRings(1, adjList, curr, numbers, res, n);
        numbers.insert(i);
        curr.pop_back();
      }
    } else {
      for (int i : adjList[curr[idx - 1]]) {
        if (numbers.find(i) == numbers.end()) {
          continue;
        }
        curr.push_back(i);
        numbers.erase(i);
        getSquareRings(idx + 1, adjList, curr, numbers, res, n);
        numbers.insert(i);
        curr.pop_back();
      }
    }
  }
  
  vector<vector<int> > squareRing(int n) {
    unordered_map<int, set<int> > adjList;
    for (int i = 1; i <= n; i++) {
      adjList[i] = set<int> ();
      for (int j = 1; j * j <= n + i; j++) {
        if (j * j - i > 0) {
          adjList[i].insert(j * j - i);
        }
      }
    }
    
    vector<vector<int> > res;
    set<int> numbers;
    for (int i = 1; i <= n; i++) {
      numbers.insert(i);
    }
    getSquareRings(0,adjList, vector<int> (), numbers, res, n);
    return res;
  }
};

void reverseVector(vector<int> &v) {
  int i = 0, j = v.size() - 1;
  while(i < j) {
    swap(v[i++], v[j--]);
  }
  
}

typedef int JobID;

class TopoSort {
public:
  bool visit(JobID id, map<JobID, int> &mark, map<JobID, set<JobID> > &adjMap, vector<JobID> &result) {
    if (mark.find(id) != mark.end() && mark[id] == 1) {
      return false;
    }
    if (mark.find(id) != mark.end() && mark[id] == 0) {
      mark[id] = 1;
      if (adjMap.find(id) != adjMap.end()) {
        for (JobID nextId : adjMap[id]) {
          if (!visit(nextId, mark, adjMap, result)) {
            return false;
          }
        }
      }
      mark.erase(id);
      result.push_back(id);
    }
    return true;
  }
  
  bool jobSchedule(const map<JobID, vector<JobID> > &deps, int n, vector<JobID> &result) {
    map<JobID, set<JobID> > adjMap;
    map<JobID, int> mark;
    for (auto& it : deps) {
      for (JobID idx : it.second) {
        if (adjMap.find(idx) == adjMap.end()) {
          adjMap[idx] = set<JobID>();
        }
        adjMap[idx].insert(it.first);
      }
    }
    for (JobID i = 1; i <= n; i++) {
      mark[i] = 0;
    }
    while (!mark.empty()) {
      if (!visit(mark.begin()->first,  mark, adjMap, result)) {
        return false;
      }
    }
    reverseVector(result);
    return true;
  }
};

int main(void) {
  vector<vector<int> > res;
  
  SquareRing ring;
  res = ring.squareRing(35);
  printVectorOfVector(res);
  
  TopoSort topoSort;
  vector<JobID> topoSortRes;
  cout<<topoSort.jobSchedule(map<JobID, vector<JobID>>(), 2, topoSortRes) <<endl;
  printVector(topoSortRes);
  return 0;
}