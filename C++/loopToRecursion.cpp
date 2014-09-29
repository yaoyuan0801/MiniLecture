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

class CombinationSum1 {
public:
  vector<vector<int> > combinationSum(vector<int> &candidates, int target) {
    sort(candidates.begin(), candidates.end());
    vector<vector<int> > res;
    getCombinationSum(candidates, 0, vector<int>(), res, target);
    return res;
  }
  
  void getCombinationSum(vector<int> &values, int idx, vector<int> curr, vector<vector<int> > &res, int target) {
    if (target == 0) {
      res.push_back(curr);
      return;
    }
    if (idx >= values.size() || target < values[idx]) {
      return;
    }
    for (int i = 0; i <= target / values[idx]; i++) {
      getCombinationSum(values, idx + 1, curr, res, target - i * values[idx]);
      curr.push_back(values[idx]);
    }
  }
};

void PrintVector(vector<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}

void PrintVectorOfVector(vector<vector<int> > &v) {
  for (auto tmp : v) {
    PrintVector(tmp);
  }
  cout<<endl;
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
  PrintVectorOfVector(subsets);
  
  vector<int> v {1, 2, 3, 4, 5};
  CombinationSum1 combSum1;
  vector<vector<int> > combs = combSum1.combinationSum(v, 5);
  PrintVectorOfVector(combs);
}