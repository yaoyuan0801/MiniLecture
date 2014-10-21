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

template <class T>

void printVector(vector<T> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}

bool isCharMatch(char a, char b) {
  if (b == '?') {
    return true;
  }
  if (a == b) {
    return true;
  }
  return false;
}

int countRegularChar(const char* s) {
  int count = 0, i = 0;
  while (s[i]) {
    count += (s[i] != '*');
    i++;
  }
  return count;
}
class WildCard{
  
public:
  bool isMatch(const char *s, const char *p) {
    int l1 = strlen(s), l2 = strlen(p);
    if (countRegularChar(p) > countRegularChar(s)) {
      return false;
    }
    vector<bool> res1(l2 + 1), res2(l2 + 1);
    res1[0] = true;
    for (int i = 0; i < l2; i++) {
      if (p[i] == '*') {
        res1[i + 1] = true;
      } else {
        break;
      }
    }    
    for (int i = 0; i < l1; i++) {
      res2[0] = false;
      for (int j = 0; j < l2; j++) {
        if (p[j] != '*') {
          res2[j + 1] = res1[j] && isCharMatch(s[i], p[j]);
        } else {
          res2[j + 1] = res1[j] || res1[j + 1] || res2[j];
        }
      }
      swap(res1, res2);
    }
    return res1[l2];
  }
};
class Regex {
public:
  bool isCharMatch(char a, char b) {
    if (b == '.') {
      return true;
    }
    if (a == b) {
      return true;
    }
    return false;
  }
  
  int countRegularChar(const char* s) {
    int count = 0, i = 0;
    while (s[i]) {
      count += (s[i] != '*');
      i++;
    }
    return count;
  }
  
  bool isMatch(const char *s, const char *p) {
    int l1 = strlen(s), l2 = strlen(p);
    vector<bool> res1(l2 + 1), res2(l2 + 1);
    res1[0] = true;
    for (int i = 1; i < l2; i += 2) {
      if (p[i] == '*' && p[i - 1] != '*' && res1[i - 1]) {
        res1[i + 1] = true;
      } else {
        break;
      }
    }
    for (int i = 0; i < l1; i++) {
      res2[0] = false;
      for (int j = 0; j < l2; j++) {
        if (p[j] != '*') {
          res2[j + 1] = res1[j] && isCharMatch(s[i], p[j]);
        } else {
          if (j > 0) {
            res2[j + 1] = res2[j - 1];
            res2[j + 1] = res2[j + 1] || (res2[j] && isCharMatch(s[i], p[j - 1]));
            res2[j + 1] = res2[j + 1] || (res1[j + 1] && isCharMatch(s[i], p[j - 1]));
          }
        }
      }
      swap(res1, res2);
    }
    return res1[l2];
  }
};

int main(void) {
  char* s = "bbbaab", *p = "a**?***";
  WildCard wildCard;
  cout<< wildCard.isMatch(s, p) <<endl;
  Regex regex;
  s = "aaba";
  p = "ab*a*c*a";
  cout << regex.isMatch(s, p) << endl;
}