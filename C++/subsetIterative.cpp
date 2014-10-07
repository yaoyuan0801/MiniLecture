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

using namespace std;



map<int, int> getCount(const vector<int> &input) {
  map<int, int> count;
  for (int num : input) {
    count[num]++;
  }
  return count;
}

vector<int> getSubsetFromCount(const vector<int>& subsetCount, const map<int, int> & elementCount) {
  int i = 0;
  vector<int> res;
  for (auto& it : elementCount) {
    for (int j = 0; j < subsetCount[i]; j++) {
      res.push_back(it.first);
    }
    i++;
  }
  return res;
}

bool incrementCount(vector<int>& subsetCount, const map<int, int> & elementCount) {
  int carry = 1, i = 0;
  for (auto& it : elementCount) {
    int tmp = subsetCount[i] + carry;
    subsetCount[i] = tmp % (it.second + 1);
    carry = tmp / (it.second + 1);
    i++;
  }
  // carry > 0 means overflow
  return carry;
}

vector<vector<int> > allSubset(const vector<int> &input) {
  map<int, int> elementCount = getCount(input);
  vector<int> subsetCount(elementCount.size(), 0);
  vector<vector<int> > res;
  while (true) {
    res.push_back(getSubsetFromCount(subsetCount, elementCount));
    if (incrementCount(subsetCount, elementCount)) {
      // all subsets found
      return res;
    }
  }
}

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
  vector<int> input = getRandomVector(n, 0, 10);
  printVector(input);
  cout<<endl;
  vector<vector<int> > res = allSubset(input);
  printVectorOfVector(res);
  return 0;
}