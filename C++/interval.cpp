#include <iostream>
#include <string>
#include <sstream>
#include <random>
#include <algorithm>
#include <assert.h>
#include <vector>
#include <limits.h>
#include <time.h>

using namespace std;

string intToString(int x) {
    stringstream ss;
    ss << x;
    string res;
    ss >> res;
    return res;
}

struct Interval {
    int start;
    int end;
    Interval(int s, int t) : start(s), end(t) {}
    string toString() {
        return "[ " + intToString(start) + " , " + intToString(end) + " ]";
    }
};

struct EndPoint {
    int pos;
    bool type;
    EndPoint(int p, bool t) : pos(p), type(t) {}
};

bool operator<(const EndPoint &p1, const EndPoint &p2) {
    if (p1.pos == p2.pos) {
        return p1.type;
    }
    return p1.pos < p2.pos;
}

vector<Interval> getRandomInterval(int size, int rangeStart, int rangeEnd) {
    assert(size > 0);
    assert(rangeStart < rangeEnd);
    default_random_engine generator((unsigned int)time(0));
    uniform_int_distribution<int> distribution(rangeStart, rangeEnd);
    vector<Interval> res;
    for (int i = 0; i < size; i++) {
        int s = distribution(generator);
        int t = distribution(generator);
        while (s == t) {
            t = distribution(generator);
        }
        if (s > t) {
            swap(s, t);
        }
        Interval intv(s, t); 
        res.push_back(intv);
    }
    return res;
}

void printIntervals(vector<Interval> &intervals) {
    for (auto interval : intervals) {
        cout<< interval.toString() <<endl;
    }
}

vector<Interval> mergeIntervals(vector<Interval> &intervals) {
    vector<EndPoint> endpoints;
    for (auto interval : intervals) {
        endpoints.push_back(EndPoint(interval.start, true));
        endpoints.push_back(EndPoint(interval.end, false));
    }
    sort(endpoints.begin(), endpoints.end());
    int count = 0, startpos = INT_MIN, endpos = INT_MIN;
    vector<Interval> res;
    for (auto endpoint : endpoints) {
        if (endpoint.type) { 
            count ++;
            if (count == 1) {
                startpos = endpoint.pos;
            } 
        } else {
            count--;
            if (count == 0) {
                endpos = endpoint.pos;
                res.push_back(Interval(startpos, endpos));
            }
        }
    }
    return res;
}

int pointOfMostIntersection(vector<Interval> &intervals) {
    vector<EndPoint> endpoints;
    for (auto interval : intervals) {
        endpoints.push_back(EndPoint(interval.start, true));
        endpoints.push_back(EndPoint(interval.end, false));
    }
    sort(endpoints.begin(), endpoints.end());
    int count = 0, pos = INT_MIN, currCount = 0;
    for (auto endpoint : endpoints) {
        if (endpoint.type) { 
            count ++;
            if (count > currCount) {
                pos = endpoint.pos;
                currCount = count;
            } 
        } else {
            count--;
        }
    }
    return pos;
}

int main(void) {
    int n = 5, rstart = 0, rend = 100;
    //vector<interval> v = getrandominterval(n, rstart, rend);
    vector<Interval> v;
    v.push_back(Interval(1, 3));
    v.push_back(Interval(3, 5));
    v.push_back(Interval(5, 6));
    v.push_back(Interval(5, 8));
    v.push_back(Interval(7, 10));
    v.push_back(Interval(13, 16));

    printIntervals(v);
    cout<< intToString(n)<<endl;
    vector<Interval> res = mergeIntervals(v);
    printIntervals(res);
    cout<<"Point of most intersection : " << pointOfMostIntersection(v)<<endl;
    return 0;
}
