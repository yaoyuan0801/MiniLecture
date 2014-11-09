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

int c1 = 0, c2 = 0;

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

void qSort1(vector<int> &v, int start, int end) {
  int m = (end - start) / 2 + start;
  swap(v[m], v[end]);
  c1++;
  int j = start;
  for (int i = start; i < end; i++) {
    if (v[i] < v[end] && i != j) {
      swap(v[i], v[j++]);
      c1++;
    }
  }
  swap(v[j], v[end]);
  if (start < j - 1) {
    qSort1(v, start, j - 1);
  }
  if (j + 1 < end) {
    qSort1(v, j + 1, end);
  }
}

void qSort2(vector<int> &v, int start, int end) {
  int pivot = v[(end - start) / 2 + start];
  int i = start, j = end;
  while (i <= j) {
    while (v[i] < pivot) {
      i++;
    }
    while (v[j] > pivot) {
      j--;
    }
    if (i <= j) {
      swap(v[i], v[j]);
      c2++;
      i++;
      j--;
    }
  }
  if (start < j) {
    qSort2(v, start, j);
  }
  if (end > i) {
    qSort2(v, i, end);
  }
}

int main(void) {
  int n = 100;
  double t1 = 0, t2 = 0;
  for (int i = 0; i < 1000000; i++) {
    if (i % 10000 == 0) {
      cout << i << " ";
      cout.flush();
    }
    vector<int> input1 = getRandomVector(n, -5000000, 5000000), input2(input1);
    clock_t c1 = clock();
    qSort2(input2, 0, n - 1);
    clock_t c2 = clock();
    t2 += (c2 - c1)  ;
    c1 = clock();
    qSort1(input1, 0, n - 1);
    c2 = clock();
    t1 += (c2 - c1)  ;
  }
  cout << endl << endl;
  cout << "q1 run time = " << t1 << endl;
  cout << "q1 swap = " << c1 << endl;
  cout << "q2 run time = " << t2 << endl;
  cout << "q2 swap = " << c2 << endl;
  return 0;
}
