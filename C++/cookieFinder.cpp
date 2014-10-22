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
#include <set>

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

void printVectorOfVector(vector<vector<int> > &v) {
  for (auto tmp : v) {
    printVector(tmp);
  }
  cout<<endl;
}

struct Point {
  int x;
  int y;
  Point() : x(0), y(0) {}
  Point(int xx, int yy) : x(xx), y(yy) {}
  void print() {
    cout << "(" <<x <<" "<<y << ")" << endl;
  }
};

bool operator<(const Point &a, const Point &b) {
  if (a.x < b.x) {
    return true;
  } else if (a.x == b.x) {
    return a.y < b.y;
  }
  return false;
}

vector<Point> getNeighborPoints(Point curr, int m, int n, vector<vector<bool> > &isVisited, set<Point> &obstacleSet) {
  int dx[4] = {-1, 0, 1, 0}, dy[4] = {0, -1, 0, 1};
  vector<Point> result;
  for (int i = 0; i < 4; i++) {
    int xx = curr.x + dx[i], yy = curr.y + dy[i];
    if (xx < 0 || xx >= m || yy < 0 || yy >= n || isVisited[xx][yy]) {
      continue;
    }
    Point next(xx, yy);
    if (obstacleSet.find(next) == obstacleSet.end()) {
      result.push_back(next);
    }
  }
  return result;
}

void findDistance(vector<vector<int> > &totalDistance, Point p, set<Point> &obstacleSet) {
  queue<Point> q1, q2;
  int m = totalDistance.size(), n = totalDistance[0].size();
  vector<vector<bool> > isVisited(m, vector<bool>(n));
  int distance = 0;
  q1.push(p);
  while (!q1.empty() || !q2.empty()) {
    Point curr = q1.front();
    q1.pop();
    if (totalDistance[curr.x][curr.y] == INT_MAX) {
      totalDistance[curr.x][curr.y] = 0;
    }
    totalDistance[curr.x][curr.y] += distance;
    isVisited[curr.x][curr.y] = true;
    vector<Point> nextPoints = getNeighborPoints(curr, m, n, isVisited, obstacleSet);
    for (Point next : nextPoints) {
      q2.push(next);
    }
    if (q1.empty()) {
      swap(q1, q2);
      distance ++;
    }
  }
}

Point findMinPoint(vector<vector<int> > &totalDistance) {
  int min = INT_MAX;
  Point minPoint;
  for (int i = 0; i < totalDistance.size(); i++) {
    int j = min_element(totalDistance[i].begin(), totalDistance[i].end()) - totalDistance[i].begin();
    if (totalDistance[i][j] < min) {
      min = totalDistance[i][j];
      minPoint = Point(i, j);
    }
  }
  cout << min << endl;
  return minPoint;
}

Point cookieFinder(int m, int n, vector<Point> &cookies, vector<Point> &obstacles) {
  vector<vector<int> > totalDistance(m, vector<int>(n, INT_MAX));
  set<Point> obstacleSet(obstacles.begin(), obstacles.end());
  for (auto p : cookies) {
    findDistance(totalDistance, p, obstacleSet);
  }
  printVectorOfVector(totalDistance);
  return findMinPoint(totalDistance);
}

int main(void) {
  vector<Point> cookies{Point(1, 1), Point(0, 3)};
  
  vector<Point> obstacles{Point(0, 1), Point(1, 2), Point(2,2)};
  
  Point res = cookieFinder(4, 4, cookies, obstacles);
  res.print();
  return 0;
}