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
#include <stack>

using namespace std;

vector<string> parseInfix(string &ex) {
  vector<string> res;
  res.push_back("(");
  string num("");
  for (int i = 0; i < ex.size(); i++) {
    if (ex[i] >= '0' && ex[i] <= '9') {
      num += ex[i];
    }
    else {
      if (num.size() > 0) {
        res.push_back(num);
      }
      num.clear();
      res.push_back(string(1, ex[i]));
    }
  }
  res.push_back(num);
  res.push_back(")");
  return res;
}

bool isOperator(string &token) {
  return token == "+" || token == "-" || token == "*" || token == "/";
}

int getPriority(string &token) {
  if (token == "(" || token == ")") {
    return 3;
  }
  if (token == "*" || token == "/") {
    return 2;
  }
  return  1;
}

bool isHigherPriority(string &token1, string &token2) {
  return getPriority(token1) > getPriority(token2);
}

bool isNumber(string &token) {
  return token[0] >= '0' && token[0] <= '9';
}

int getNumber(string &token) {
  stringstream ss(token);
  int res;
  ss >> res;
  return res;
}

void eval(stack<string> &operatorStack, stack<int> &numberStack) {
  int a = numberStack.top();
  numberStack.pop();
  int b = numberStack.top();
  numberStack.pop();
  string op = operatorStack.top();
  operatorStack.pop();
  int res = 0;
  if (op == "+") {
    res = a + b;
  }
  if (op == "-") {
    res = b - a;
  }
  if (op == "*") {
    res = a * b;
  }
  if (op == "/") {
    res = b / a;
  }
  numberStack.push(res);
}

int evalInfix(string &ex) {
  vector<string> tokens = parseInfix(ex);
  stack<string> operatorStack;
  stack<int> numberStack;
  for (string str : tokens) {
    if (str == "(") {
      operatorStack.push(str);
      continue;
    }
    if (str == ")")  {
      while (operatorStack.top() != "(") {
        eval(operatorStack, numberStack);
      }
      operatorStack.pop();
      continue;
    } 
    if (isNumber(str)) {
      numberStack.push(getNumber(str));
      continue;
    }
    while (operatorStack.top() != "(" && !isHigherPriority(str, operatorStack.top())) {
      eval(operatorStack, numberStack);
    }
    operatorStack.push(str);
  }  
  return numberStack.top();
}

int main(void) {
  string ex = "74/2+1-(97+3)*2";
  cout << ex <<" = " << evalInfix(ex) << endl;
  return 0;
}
