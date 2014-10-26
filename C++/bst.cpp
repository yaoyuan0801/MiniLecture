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

void printVector(vector<int> &v) {
  cout<<"[ ";
  for (int x : v) {
    cout<< " " << x;
  }
  cout<< " ]"<<endl;
}

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode(int v) : val(v), left(NULL), right(NULL) {}
};

class Tree {
private:
  TreeNode* _root;
  
  void inOrderRecursive(TreeNode* root) {
    if (!root) {
      return;
    }
    inOrderRecursive(root->left);
    cout << " " << root->val << " ";
    inOrderRecursive(root->right);
  }
  
  void preOrderRecursive(TreeNode* root) {
    if (!root) {
      return;
    }
    cout << " " << root->val << " ";
    preOrderRecursive(root->left);
    preOrderRecursive(root->right);
  }
  
  void destroy(TreeNode* t) {
    if (!t) {
      return;
    }
    destroy(t->left);
    destroy(t->right);
    delete t;
   }
  
public:
  Tree() : _root(NULL) {}
  Tree(TreeNode* r) : _root(r) {}
  ~Tree() {
    destroy(_root);
  }
  
  void inOrder() {
    inOrderRecursive(_root);
    cout<<endl;
  }
  
  void preOrder() {
    preOrderRecursive(_root);
    cout<<endl;
  }
  
  void inOrderIterative() {
    stack<TreeNode*> s;
    TreeNode* curr = _root;
    while (!s.empty() || curr) {
      if (curr) {
        s.push(curr);
        curr = curr->left;
      } else {
        curr = s.top();
        s.pop();
        cout << curr->val << " ";
        curr = curr->right;
      }
    }
    cout << endl;
  }
  
  void preOrderIterative() {
    stack<TreeNode*> s;
    TreeNode* curr = _root;
    while (curr || !s.empty()) {
      cout << curr->val << " ";
      if (curr->right) {
        s.push(curr->right);
      }
      if (curr->left) {
        curr = curr->left;
      } else if (!s.empty()) {
          curr = s.top();
          s.pop();
      } else {
        break;
      }
    }
    cout << endl;
  }
  
  TreeNode* getRoot() {
    return _root;
  }
  
  void insert(int x) {
    TreeNode* prev = NULL, *curr = _root;
    while (curr) {
      if (curr->val == x) {
        return;
      }
      prev = curr;
      if (curr->val > x) {
        curr = curr->left;
      } else {
        curr = curr->right;
      }
    }
    TreeNode* tmp = new TreeNode(x);
    if (!prev) {
      _root = tmp;
      return;
    }
    if (prev->val > x) {
      prev->left = tmp;
    } else {
      prev->right = tmp;
    }
  }
};

class BstIterator {
private:
  TreeNode* _root;
  TreeNode* curr;
  stack<TreeNode*> s;

public:
  BstIterator(TreeNode* root) : _root(root), curr(root) {}
  TreeNode* next() {
    if (!hasNext()) {
      return NULL;
    }
    while (curr) {
      s.push(curr);
      curr = curr->left;
    }
    curr = s.top();
    s.pop();
    TreeNode* res = curr;
    curr = curr->right;
    return res;
  }
  
  bool hasNext() {
    return curr || !s.empty();
  }
};


int main(void) {
  int n = 10;
  vector<int> input = getRandomVector(n, 0, 30);
  Tree t;
  printVector(input);
  for (int x : input) {
    t.insert(x);
  }
  t.inOrder();
  t.inOrderIterative();
  BstIterator it(t.getRoot());
  while (it.hasNext()) {
    cout << it.next()->val << " ";
  }
  cout << endl;
  cout << endl;

  t.preOrder();
  t.preOrderIterative();
  return 0;

}