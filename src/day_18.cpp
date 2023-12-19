#include <unordered_map>
#include <string_view>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <numeric>
#include <iomanip>
#include <cstdio>
#include <string>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <chrono>
#include <format>

using namespace std;
using ll = long long;

map<char, pair<int, int>> dirs = {
        {'0', {0,1} },
        {'1', {1,0} },
        {'2', {0,-1} },
        {'3', {-1,0} },
        {'R', {0,1} },
        {'L', {0,-1} },
        {'U', {-1,0} },
        {'D', {1,0} },
};

ll res1 = 0,
   res2 = 0;

/**
 * Count area using Shoelace formula
 * @param v vector of edges
 * @return counted area
 */
ll countArea( vector<pair<ll, ll>>& v ) {
    ll area = 0;
    for ( int i = 1; i < v.size(); i++ ) {
        auto p1 = v[i-1];
        auto p2 = v[i];
        area += ( p1.first + p2.first ) * ( p2.second - p1.second );
    }
    return abs(area/2);
}

/**
 * Finds solution of day 18 AOC 2023
 * @param v vector of edges
 * @param perimeter
 * @return area with deepened inside
 */
ll solve( vector<pair<ll, ll>>& v, ll perimeter ) {
    ll area = countArea(v);
    return ( ( area - (perimeter / 2 ) + 1 ) + perimeter);
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    vector<pair<ll, ll>> v1, v2;

    ll x1, x2, y1, y2, per, per2;
    x1 = x2 = y1 = y2 = per = per2 = 0;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        char dir;
        ll steps;
        string h;

        istringstream ss(line);
        ss >> dir >> steps >> h;

        // Part 1
        auto d = dirs[dir];
        x1 += steps*d.first;
        y1 += steps*d.second;
        per += steps;
        v1.emplace_back(x1,y1);

        // Part 2
        dir = h[7];
        h = h.substr(2,5);
        sscanf(h.c_str(), "%x", &steps);
        d = dirs[dir];
        x2 += steps * d.first;
        y2 += steps * d.second;
        v2.emplace_back(x2, y2);
        per2 += steps;
    }

    res1 = solve(v1, per);
    cout << "Part1: " << res1 << endl;
    res2 = solve(v2, per2);
    cout << "Part2: " << res2 << endl;
}