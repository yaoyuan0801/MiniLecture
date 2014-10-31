#include <iostream>
#include <string>
#include <sstream>
#include <vector>

using namespace std;

vector<int> c;

int tenPowerN(int n) {
  int res = 1;
  for (int i = 0; i < n; i++) {
    res *= 10;
  }
  return res;
}

void count7Helper(int l) {
  c.resize(l + 1);
  c[0] = 0;
  c[1] = 1;
  for (int i = 2; i <= l; i++) {
    c[i] = c[i-1] * 10 + tenPowerN(i-1);
  }
  cout << endl;
}

int toNumber(string s) {
  if (s.size() == 0) {
    return 0;
  }
  stringstream ss(s);
  int res;
  ss >> res;
  return res;
}

int count7(string n) {
  if (c.size() < n.size()) {
    count7Helper(n.size());
  }  
  if (n.size() == 0) {
    return 0;
  }
  int res = 0;
  res += (n[0] - '0') * c[n.size() - 1] + count7(n.substr(1));
  if (n[0] > '7') {
    res += tenPowerN(n.size() - 1);
  }
  if (n[0] == '7') {
    res += toNumber(n.substr(1)) + 1;
  }
  return res;
}


int count7Linear(int n) {
  int res = 0;
  for (int i = 1; i <= n; i++) {
    string s = to_string(i);
    for (char c : s) {
      res += (c == '7');
    }
  }
  return res;
}

int main(void) {
  for (int n = 1; n < 1000; n++) {
    if (count7Linear(n) != count7(to_string(n))) {
      cout << n << endl;
    } 
  } 
  return 0;
}
