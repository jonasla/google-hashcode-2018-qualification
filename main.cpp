#include <bits/stdc++.h>

using namespace std;

typedef long long tint;
typedef pair<tint, tint> ii;
typedef vector<ii> vii;

#define forn(i,n) for(tint i=0; i<(tint)(n); i++)

tint R, C, F, N, B, T;

tint manh(tint a, tint b, tint x, tint y) {
  return abs(a-x) + abs(b-y);
}

struct Point { 
  tint x, y;
  Point(tint xx, tint yy) : x(xx), y(yy) {}
  Point() {
    x = 0, y = 0;
  }
};

tint manh(const Point& p1, const Point& p2) {
  return manh(p1.x, p1.y, p2.x, p2.y);
}

struct Ride { 
  Point ini, end;
  tint s, f;
  
  Ride(tint a, tint b, tint x, tint y, tint ss, tint ff) { 
    ini = Point(a, b);
    end = Point(x, y);
    s = ss;
    f = ff;
  }
  
  tint dist() const {
    return manh(ini, end);
  }
};

// <profit, time>
ii profit_time(tint time, tint xpos, tint ypos, const Ride& ride) {
  tint dist_to_ride = manh(Point(xpos, ypos), ride.ini);
  tint arrival_time = time + dist_to_ride;
  arrival_time = max(arrival_time, ride.s);
  
  if (arrival_time <= ride.s) {
    return {ride.dist() + B, arrival_time + ride.dist()};
  } else if (arrival_time <= ride.f - ride.dist()) {
    return {ride.dist(), arrival_time + ride.dist()}; 
  } else {
    return {0, 0};
  }
}

int main() {
  cin >> R >> C >> F >> N >> B >> T;
  tint a, b, x, y, s, f;
  
  vector<Ride> rides;  
  multimap<tint, tint> ends_to_rides;
  
  rides.emplace_back(0, 0, 0, 0, 0, 0);
  forn(i,N) {
    cin >> a >> b >> x >> y >> s >> f;
    
    ends_to_rides.insert({f, rides.size()});
    rides.emplace_back(a, b, x, y, s, f);
  }
    
  /// GREEDY
  
  tint TOTAL_PROFIT = 0;
  
  // <time, x, y>
  unordered_set<tint> used_rides;
  used_rides.insert(0);
  
  priority_queue<tuple<tint, tint, tint>, vector<tuple<tint, tint, tint>>, less<tuple<tint, tint, tint>>> Q;
  forn (i, F) {
    Q.push({0, 0, 0});
  }
  
  while (!Q.empty()) {
    tint time, xpos, ypos;
    tie(time, xpos, ypos) = Q.top();
    Q.pop();
    
    tint max_profit = 0;
    tint selected_end_time = 0;
    tint selected_ride = -1;
    
    auto it = ends_to_rides.lower_bound(time);
    while (it != ends_to_rides.end()) {
      tint next_ride = it->second;
      
      if (used_rides.find(next_ride) == used_rides.end()) {      
        tint profit, end_time;
        tie(profit, end_time) = profit_time(time, xpos, ypos, rides[next_ride]);
        
        if (profit > max_profit || (profit == max_profit && end_time < selected_end_time)) {
          max_profit = profit;
          selected_ride = next_ride;
          selected_end_time = end_time;
        }
      }
      ++it;
    }
    
    if (selected_ride != -1) {
      used_rides.insert(selected_ride);
      Q.push({selected_end_time, 
        rides[selected_ride].end.x, rides[selected_ride].end.y});
      TOTAL_PROFIT += max_profit;
    }
    
  }
  
  cout << TOTAL_PROFIT << endl;
  return 0;
}
