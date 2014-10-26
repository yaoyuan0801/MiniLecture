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

class LRUCache{
private:
  unordered_map<int, list<pair<int, int> >::iterator> m;
  list<pair<int, int> > l;
  int cap;
  void update(int key, int value) {
    list<pair<int, int>>::iterator it = m[key];
    l.erase(it);
    l.insert(l.end(), pair<int, int>(key, value));
    m[key] = l.end();
    m[key]--;
  }
public:
  LRUCache(int capacity) : cap(capacity) { }
  
  int get(int key) {
    if (m.find(key) == m.end()) {
      return -1;
    }
    update(key, m[key]->second);
    return m[key]->second;
  }
  
  void set(int key, int value) {
    if (m.find(key) != m.end()) {
      update(key, value);
      return;
    }
    l.insert(l.end(), pair<int, int>(key, value));
    m[key] = l.end();
    m[key]--;
    if (l.size() > cap) {
      int toKick = l.begin()->first;
      m.erase(toKick);
      l.erase(l.begin());
    }
  }
};

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
  int n = 20;
  vector<int> input1 = getRandomVector(n, 0, 5), input2 = getRandomVector(n, 0, 5);
  printVector(input1);
  printVector(input2);
  cout<<endl;
  LRUCache cache(3);
  for (int i = 0; i < n; i ++) {
    cache.put(input1[i], input2[i]);
    cout<< cache.get(input2[i]) << " ";
  }
  cout << endl;
  return 0;
}