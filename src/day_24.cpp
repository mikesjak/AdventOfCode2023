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
using ld = long double;
using line = pair<ll,ll>;

#define int ll

const ll minR = 200000000000000ll;
const ll maxR = 400000000000000ll;
const ld eps = 1e-9;

struct Stone {
    ll x, y, z;
    ll vx, vy, vz;
};

vector<Stone> v;

/**
 * Function controlling if 2 stones intersect
 * @param s1
 * @param s2
 * @return true if intersect
 */
bool intersect(const Stone &s1, const Stone &s2) {
    ll A1 = s1.vx;
    ll B1 = -s2.vx;
    ll C1 = s2.x - s1.x;

    ll A2 = s1.vy;
    ll B2 = -s2.vy;
    ll C2 = s2.y - s1.y;

    ll D = A1 * B2 - A2 * B1;
    ll Dx = C1 * B2 - B1 * C2;
    ll Dy = A1 * C2 - A2 * C1;

    if (D != 0) {
        ld t1 = (ld) Dx / D, t2 =(ld) Dy / D;
        if (t1 < -eps || t2 < -eps) {
            return false;
        }

        ld x = (ld)s1.x + (ld)s1.vx * t1;
        ld y = (ld)s1.y + (ld)s1.vy * t1;

        return x > minR - eps &&
               x < maxR + eps &&
               y > minR - eps &&
               y < maxR + eps;
    }
    return false;
}

/**
 * Parse input and create new stone
 * @param line string to be parsed
 * @return new stone
 */
Stone createStone( const string& line ) {
    Stone res{};
    istringstream ss(line);
    string tmp;
    char c;
    ss >> tmp;
    res.x = stoll(tmp.substr(0, tmp.size()-1));
    ss >> tmp;
    res.y = stoll(tmp.substr(0, tmp.size()-1));
    ss >> tmp;
    res.z = stoll(tmp);

    ss >> c;

    ss >> tmp;
    res.vx = stoll(tmp.substr(0, tmp.size()-1));
    ss >> tmp;
    res.vy = stoll(tmp.substr(0, tmp.size()-1));
    ss >> tmp;
    res.vz = stoll(tmp);

    return res;
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    while ( getline(cin, line) ) {
        Stone tmp = createStone(line);
        v.emplace_back(tmp);
    }

    int res = 0;
    for ( int i = 0; i + 1 < v.size(); i++ ) {
        for ( int j = i + 1; j < v.size(); j++ ) {
            if ( intersect(v[i], v[j]) ) res++;
        }
    }
    cout << "Part1: " << res << "\n";

}