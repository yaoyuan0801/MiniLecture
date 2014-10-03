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

int main(void) {
  vector<vector<int> > res;
  SquareRing ring;
  res = ring.squareRing(35);
  printVectorOfVector(res);
  return 0;
}