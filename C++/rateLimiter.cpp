#include <iostream>
#include <time.h>
#include <unordered_map>
#include <algorithm>
#include <stdlib.h>
#include <unistd.h>
using namespace std;

class RateLimiter {
  private:
    double rate;
    double tokens;
    double limit;
    time_t lastHitTime;
  public:
    RateLimiter(double r, double l) : rate(r), tokens(0.0), limit(l) {
      lastHitTime = time(NULL);
    }
    bool pass() {
      time_t currTime = time(NULL);
      tokens += (currTime - lastHitTime) * rate;
      tokens = min(tokens, limit);
      lastHitTime = currTime;
      if (tokens >= 1.0) {
        tokens -= 1.0;
        return true;
      }
      return false;
    }
};

int main(void) {
  RateLimiter limiter(1.0, 3.0);
  sleep(3);
  for (int i = 0; i < 5; i++) {
    cout << i <<" : " << limiter.pass() << endl;  
  }
  sleep(2);
  for (int i = 5; i < 10; i++) {
    cout << i <<" : " << limiter.pass() << endl;  
  }
}
