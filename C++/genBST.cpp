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
#include <queue>

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

void destroyTree(TreeNode* root) {
  if (!root) {
    return;
  }
  destroyTree(root->left);
  destroyTree(root->right);
  delete root;
}

TreeNode* getBSTRecursive(vector<int> &v, int s, int t) {
  if (s > t) {
    return NULL;
  }
  if (s == t) {
    return new TreeNode(v[s]);
  }
  int m = (t - s) / 2 + s;
  TreeNode* root = new TreeNode(v[m]);
  root->left = getBSTRecursive(v, s, m - 1);
  root->right = getBSTRecursive(v, m + 1, t);
  return root;
}

TreeNode* getBST(vector<int> &v) {
  return getBSTRecursive(v, 0, v.size() - 1);
}

void printTreeByLevel(TreeNode* root) {
  if (!root) {
    return;
  }
  queue<TreeNode*> q1, q2;
  int count1 = 1, count2 = 0;
  q1.push(root);
  while (count1) {
    TreeNode* curr = q1.front();
    q1.pop();
    if (curr) {
      cout << curr->val << " ";
      count1--;
      q2.push(curr->left);
      q2.push(curr->right);
      count2 += (curr->left != NULL) + (curr->right != NULL);
    } else {
      cout << "# ";
      q2.push(NULL);
      q2.push(NULL);
    }
    if (q1.empty()) {
      cout << endl;
      swap(q1, q2);
      swap(count1, count2);
    }
  }
}

int main(void) {
  int n = 15;
  vector<int> input = getRandomVector(n, 0, 50);
  sort(input.begin(), input.end());
  printVector(input);
  TreeNode* root = getBST(input);
  printTreeByLevel(root);
  destroyTree(root);
  cout<<endl;
  
  return 0;
}
