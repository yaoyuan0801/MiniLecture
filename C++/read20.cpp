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

ifstream fin("./read20.cpp");

bool read20(string& buffer) {
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

bool readKOptimized(string& res, int k) {
  static string buffer;
  static int offset = 0;
  static bool eof = false;
  if (offset + k >= buffer.size()) {
    res += buffer.substr(offset);
    k -= res.size();
    offset = 0;
    buffer.clear();
  }
  
  if (!eof) {
    for (int i = 0; i < k / 20; i++) {
      if (!read20(res)) {
        eof = true;
        return false;
      }
    }
  }
  
  k = k % 20;
  eof = !read20(buffer);
  string tmp =  buffer.substr(0, k);
  offset = tmp.size();
  res += tmp;
  return res.size() < k;
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
  readk(res, 500);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 900);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readk(res, 900);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  fin.close();
  
  fin.open("./read20.cpp");
  cout<<endl;
  readKOptimized(res, 10);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readKOptimized(res, 50);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readKOptimized(res, 50);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readKOptimized(res, 500);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readKOptimized(res, 900);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  readKOptimized(res, 900);
  cout<<res<<" "<<res.size()<<endl;
  res.clear();
  fin.close();

  return 0;
}