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

void printVectorOfVector(vector<vector<int> > &v) {
  for (auto &x : v) {
    printVector(x);
  }
  cout << endl;
}

vector<int> spiralOrder(vector<vector<int> > &matrix) {
  vector<int> res;
  if (matrix.size() < 1) {
      return res;
  }
  int m = matrix.size(), n = matrix[0].size();
  int k = min(m / 2, n / 2);
  
  for (int i = 0; i < k; i++) {
    for (int j = i; j < n - 1 - i; j++) {
      res.push_back(matrix[i][j]);
    }
    for (int j = i; j < m - 1 - i; j++) {
      res.push_back(matrix[j][n - 1 - i]);
    }
    for (int j = i; j < n  - 1 - i; j++) {
      res.push_back(matrix[m - 1 - i][n - 1 -j]);
    }
    for (int j = i; j < m - 1 - i; j++) {
      res.push_back(matrix[m - 1 - j][i]);
    }
  }
  if (m >= n && n % 2 == 1) {
    for (int i = k; i <  m - k; i++) {
      res.push_back(matrix[i][n / 2]);
    }
  }
  if (m < n && m % 2 == 1) {
    for (int i = k; i <  n - k; i++) {
      res.push_back(matrix[m / 2][i]);
    }
  }
  return res;
}



int main(void) {
  vector<vector<int> > v{{1,2,3}, {4,5,6}, {7,8,9}, {10, 11, 12}};
  vector<int> res = spiralOrder(v);
  printVectorOfVector(v);
  printVector(res);
  return 0;
}
