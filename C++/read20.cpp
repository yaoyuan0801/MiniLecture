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
#include <fstream>

using namespace std;

bool read20(string& buffer) {
  static ifstream fin("./read20.cpp");
  for (int i = 0; i < 20; i++) {
    char c;
    if (fin >> c) {
      buffer.push_back(c);
    } else {
      return false;
    }
  }
  return true;
}

bool readk(string& res, int k) {
  static string buffer;
  static int offset = 0;
  static bool eof = false;
  while (offset + k >= buffer.size() && !eof) {
    res += buffer.substr(offset);
    k -= buffer.size() - offset;
    offset = 0;
    buffer.clear();
    if (!read20(buffer)) {
      eof = true;
    }
  }
  res += buffer.substr(offset, k);
  offset += k;
  return offset < buffer.size();
}


int main(void) {
  string res;
  readk(res, 10);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 50);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 50);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 50);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 500);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 451);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 50);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  return 0;
}