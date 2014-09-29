#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <limits.h>
#include <time.h>

using namespace std;

class Subset {
public:
  vector<vector<int> > subsets(vector<int> &S) {
    sort(S.begin(), S.end());
    vector<vector<int> > res;
    getSubsets(S, 0, vector<int>(), res);
    return res;
  }
  
  void getSubsets(vector<int> &S, int idx, vector<int> curr, vector<vector<int> > &res) {
    if (idx == S.size()) {
      res.push_back(curr);
      return;
    }
    getSubsets(S, idx + 1, curr, res);
    curr.push_back(S[idx]);
    getSubsets(S, idx + 1, curr, res);
  }
  
};



void PrintVector(vector<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}

vector<int> getRandomVector(int size, int rangeStart, int rangeEnd) {
  assert(size > 0);
  assert(rangeStart < rangeEnd);
  default_random_engine generator((unsigned int)time(0));
  uniform_int_distribution<int> distribution(rangeStart, rangeEnd);
  vector<int> res;
  for (int i = 0; i < size; i++) {
    int s = distribution(generator);
    res.push_back(s);
  }
  return res;
}


int main(void) {
  int n = 5;
  Subset test;
  vector<int> input = getRandomVector(n, 0, 100);
  PrintVector(input);
  cout<<endl;
  vector<vector<int> > subsets = test.subsets(input);
  for (auto v : subsets) {
    PrintVector(v);
  }
  cout<<endl;
}