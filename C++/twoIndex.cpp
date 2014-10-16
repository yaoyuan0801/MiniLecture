#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <limits.h>
#include <time.h>
#include <map>
#include <unordered_map>

using namespace std;

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

void printVector(vector<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}


int distanceOfClosestNumber(int a, int b, const vector<int> &v) {
  int idxA = -1, idxB = -1;
  int d = INT_MAX;
  for (int i = 0; i < v.size(); i++) {
    if (v[i] == a) {
      if (idxB != -1) {
        d = min(i - idxB, d);
      }
      idxA = i;
    }
    if (v[i] == b) {
      if (idxA != -1) {
        d = min(i - idxA, d);
      }
      idxB = i;
    }
  }
  return d == INT_MAX ? -1 : d;
}

string minWindow(string S, string T) {
  unordered_map<char, int> mS, mT;
  for (char c : T) {
    mS[c] = 0;
    mT[c]++;
  }
  int d = INT_MAX;
  int idx = 0, total = 0;
  string res;
  for (int i = 0; i < S.size(); i++) {
    if (mS.find(S[i]) == mS.end()) {
      continue;
    }
    if (mS[S[i]] <mT[S[i]]) {
      total++;
    }
    mS[S[i]]++;
    while ((mS.find(S[idx]) == mS.end() || mS[S[idx]] > mT[S[idx]])) {
      if (mS.find(S[idx]) != mS.end()) {
        mS[S[idx]]--;
      }
      idx++;
    }
    if (total == T.size() && i - idx + 1 < d) {
      d = i - idx + 1;
      res = S.substr(idx, d);
    }
  }
  return res;
}

int main(void) {
  int n = 10;
  vector<int> input = getRandomVector(n, 0, 5);
  printVector(input);
  cout<<endl;
  cout << distanceOfClosestNumber(1, 1, input) << endl;
  cout << minWindow("ADOBECODEBANC", "ABC") <<endl;
  return 0;
}