#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <ctime>
#include <set>
#include <utility>
#include <algorithm>
#include <map>

using namespace std;

bool getNewPatternMap(map<char, string> &m, map<char, string> &res, char c, string &s) {
  if (m.find(c) != m.end()) {
    if (m[c] != s) {
      return false;
    }
  } else {
    for (auto it : m) {
      if (it.second == s && it.first != c) {
        return false;
      }
    }
  }
  res = m;
  res[c] = s;
  return true;
}

bool isPatternMatched(string& str, string& pattern) {
  if (pattern.size() < 1) {
    return true;
  }
  vector<vector<map<char, string> > > res1(str.size(), vector<map<char, string> >()), res2(str.size(), vector<map<char, string> >());
  for (int i = 0; i < res1.size(); i++) {
    map<char, string> m;
    m[pattern[0]] = str.substr(0, i + 1);
    res1[i].push_back(m);
  }

  for (int i = 1; i < pattern.size(); i++) {
    for (int j = 0; j < str.size(); j++) {
      res2[j].clear();
      for (int k = 1; k <= j; k++) {
        string lastWord = str.substr(k, j - k + 1);
        for (map<char, string> m : res1[k - 1]) {
          map<char, string> tmp;
          if (getNewPatternMap(m, tmp, pattern[i], lastWord)) {
            res2[j].push_back(tmp);
          }
        }
      }
    }
    swap(res1, res2);
  }
  if (res1[str.size() - 1].size() > 0) {
    for (map<char, string> m : res1[str.size() - 1]) {
      for (auto p : m) {
        cout << p.first << ":" << p.second << endl;
      }
      cout << endl;
    }
  }
  return res1[str.size() - 1].size() > 0;
}

int main(void) {
  string str = "asdasdasdasd", pattern = "AAAA";
  cout << isPatternMatched(str, pattern) << endl;
  str = "bigboyboybig";
  pattern = "ABBA";
  cout << isPatternMatched(str, pattern) << endl;
  str = "bigbigbigbig";
  cout << isPatternMatched(str, pattern) << endl;
}
