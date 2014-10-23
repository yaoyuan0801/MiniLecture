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

struct bigInt {
  int sign; // -1, 0, 1
  vector<int> number;
  bigInt(int s, vector<int> num) : sign(s), number(num) {}
  
  void print() {
    if (sign == 0) {
      cout<< 0 <<endl;
      return;
    }
    cout << ((sign == 1) ? '+' : '-');
    for (auto i : number) {
      cout<<i;
    }
    cout<<endl;
  }
};

class bigIntOperator {
public:
  bigInt add(bigInt& a, bigInt& b) {
    if (a.sign == 0) {
      return b;
    }
    if (b.sign == 0) {
      return a;
    }
    if (compareAbs(a, b)) {
      swap(a, b);
    }
    if (a.sign == b.sign) {
      bigInt res = addAbs(a, b);
      res.sign = a.sign;
      return res;
    }
    bigInt res = subtractAbs(a, b);
    if (a.sign == -1) {
      res.sign = -1;
    }
    return res;
  }
  
  bigInt subtract(bigInt& a, bigInt& b) {
    bigInt bb(b);
    bb.sign = -bb.sign;
    return add(a, bb);
  }
  
  bigInt multiply(bigInt& a, bigInt& b) {
    if (a.sign == 0 || b.sign == 0) {
      return bigInt(0, vector<int>());
    }
    if (compareAbs(a, b)) {
      swap(a, b);
    }
    bigInt res = multiplyAbs(a, b);
    res.sign = a.sign * b.sign;
    return res;
  }
  
private:
   bool compareAbs(bigInt& a, bigInt& b) {
    if (a.number.size() != b.number.size()) {
      return a.number.size() < b.number.size();
    }
   
    for (int i = 0; i < a.number.size(); i++) {
      if (a.number[i] != b.number[i]) {
        return a.number[i] < b.number[i];
      }
    }
    return false;
  }
  
  bigInt addAbs(bigInt& a, bigInt &b) {
    vector<int> res;
    int i = a.number.size() - 1, j = b.number.size() - 1, c = 0;
    while (i >= 0 || j >= 0) {
      int bb = (j >= 0) ? b.number[j] : 0;
      int tmp = a.number[i] + bb + c;
      res.push_back(tmp % 10);
      c = tmp / 10;
      i--;
      j--;
    }
    if (c) {
      res.push_back(c);
    }
    reverse(res);
    bigInt out(1, res);
    return out;
  }
  
  bigInt subtractAbs(bigInt& a, bigInt &b) {
    vector<int> res;
    int i = a.number.size() - 1, j = b.number.size() - 1, c = 0;
    while (i >= 0 || j >= 0) {
      int bb = (j >= 0) ? b.number[j] : 0;
      int tmp = a.number[i] - bb - c;
      c = tmp < 0;
      tmp += c * 10;
      res.push_back(tmp);
      i--;
      j--;
    }
    while (!res.empty() && res[res.size() - 1] == 0) {
      res.pop_back();
    }
    reverse(res);
    return bigInt(res.size() > 0, res);
  }
  
  bigInt multiplyAbs(bigInt &a, bigInt &b) {
    bigInt res(0, vector<int>());
    for (int i = b.number.size() - 1; i >= 0; i--) {
      vector<int> v;
      int c = 0;
      for (int j = a.number.size() - 1; j >= 0; j--) {
        int tmp  = a.number[j] * b.number[i] + c;
        v.push_back(tmp % 10);
        c = tmp / 10;
      }
      if (c) {
        v.push_back(c);
      }
      reverse(v);
      for (int k = b.number.size() - 1; k > i; k--) {
        v.push_back(0);
      }
      bigInt sum(1, v);
      res = add(res, sum);
    }
    return res;
  }
  
  void reverse(vector<int> &v) {
    int i = 0, j = v.size() - 1;
    while (i < j) {
      swap(v[i++], v[j--]);
    }
  }
  
};

int main(void) {
  vector<int> a{1,3}, b{1, 2, 5};
  bigInt x(1, a), y(-1, b);
  bigIntOperator oper;
  x.print();
  y.print();
  oper.add(x, y).print();
  oper.subtract(x, y).print();
  oper.multiply(x, y).print();
  return 0;
}