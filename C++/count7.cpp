#include <iostream>
#include <string>
#include <sstream>
#include <vector>
#include <map>

using namespace std;

int count7(int n) {
  map<int, int> m;
  m[1] = 0;
  int k = 10;
  while (k < n) {
    m[k] = m[k / 10] * 10 + k / 10;
    k *= 10;
  } 
  
  int res = 0;
  k /= 10;
  while (n) {
    int firstDigit = n / k;
    int currCount = firstDigit * m[k];
    if (firstDigit > 7) {
      currCount += k;
    }
    if (firstDigit == 7) {
      currCount += n - k * 7 + 1;
    }
    res += currCount;
    n = n - firstDigit * k;
    k = k / 10;
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
    if (count7Linear(n) != count7(n)) {
      cout << n << " " << count7Linear(n) << " " << count7(n) << endl;
    } 
  } 
  return 0;
}
