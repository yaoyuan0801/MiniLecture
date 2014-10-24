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

void printVector(vector<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}


int binarySearch(const vector<int> &aux, const vector<int> &v, int i) {
  int start = 0, end = aux.size() - 1;
  while (start <= end) {
    int mid = (end - start) / 2 + start;
    if (v[aux[mid]] == v[i]) {
      return mid;
    }
    if (v[aux[mid]] > v[i]) {
      end = mid - 1;
    } else {
      start = mid + 1;
    }
  }
  return start;
}

vector<int> longestIncSubSeq(const vector<int> &v) {
  vector<int> aux, prev(v.size());
  aux.push_back(-1);
  prev.push_back(-1);
  for (int i = 0; i < v.size(); i++) {
    int idx = binarySearch(aux, v, i);
    if (idx >= aux.size()) {
      prev[i] = aux[aux.size() - 1];
      aux.push_back(i);
    } else if (v[aux[idx]] > v[i]) {
      aux[idx] = i;
      prev[i] = aux[idx - 1];
    }
  }
  vector<int> res(aux.size() - 1);
  int k = aux[aux.size() - 1];
  for (int i = aux.size() - 1; i > 0; i--) {
    res[i - 1] = v[k];
    k = prev[k];
  }
  printVector(res);
  return res;
}

int main(void) {
  vector<int> a{3, 5, 4, 2, 6, 10, 1, 4, 7};
  vector<int> res = longestIncSubSeq(a);
  return 0;
}