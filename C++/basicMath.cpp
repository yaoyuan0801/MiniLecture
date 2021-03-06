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
  
  
  void print() const {
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
  bigInt add(const bigInt &a, const bigInt &b) {
    if (a.sign == 0) {
      return b;
    }
    if (b.sign == 0) {
      return a;
    }
    bigInt aa(a), bb(b);
    if (compareAbs(aa, bb)) {
      swap(aa, bb);
    }
    if (aa.sign == bb.sign) {
      bigInt res = addAbs(aa, bb);
      res.sign = aa.sign;
      return res;
    }
    bigInt res = subtractAbs(aa, bb);
    if (aa.sign == -1) {
      res.sign = -1;
    }
    return res;
  }
  
  bigInt subtract(const bigInt &a, const bigInt &b) {
    bigInt aa(a), bb(b);
    bb.sign = -bb.sign;
    return add(aa, bb);
  }
  
  bigInt multiply(const bigInt &a, const bigInt &b) {
    if (a.sign == 0 || b.sign == 0) {
      return bigInt(0, vector<int>());
    }
     bigInt aa(a), bb(b);
    if (compareAbs(a, b)) {
      swap(aa, bb);
    }
    bigInt res = multiplyAbs(aa, bb);
    res.sign = aa.sign * bb.sign;
    return res;
  }
  
  bigInt divide(const bigInt &a,  const bigInt &b) {
    if (b.sign == 0) {
      cout<<"Bad input"<<endl;
      return b;
    }
    if (compareAbs(a, b)) {
      return bigInt(0, vector<int>());
    }
    bigInt aa(a), bb(b);
    bigInt res = divideAbs(aa, bb);
    res.sign = a.sign * b.sign;
    return res;
  }
  
private:
   bool compareAbs(const bigInt &a, const bigInt &b) {
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
  
  bigInt addAbs(bigInt &a, bigInt &b) {
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
  
  bigInt subtractAbs(bigInt &a, bigInt &b) {
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
  
  bigInt divideAbs(bigInt &a, bigInt &b) {
    bigInt partialRes(1, vector<int>{1}), res(0, vector<int>());
    int count = 0;
    while (!compareAbs(a, b)) {
      b.number.push_back(0);
      partialRes.number.push_back(0);
      count++;
    }
    b.number.pop_back();
    partialRes.number.pop_back();
    count--;
    while (count >= 0) {
      if (!compareAbs(a, b)) {
        a = subtractAbs(a, b);
        res = add(res, partialRes);
      } else {
        b.number.pop_back();
        partialRes.number.pop_back();
        count--;
      }
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
  cout<<endl;
  
  x.print();
  y.print();
  oper.subtract(x, y).print();
  cout<<endl;
  
  x.print();
  y.print();
  oper.multiply(x, y).print();
  cout<<endl;

  x.print();
  y.print();
  oper.divide(x, y).print();
  cout<<endl;
  
  x.print();
  y.print();
  oper.divide(y, x).print();

  return 0;
}