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
using ll = unsigned long long;

#define int ll

/**
 * Struct to hold single part
 */
struct Part {
    int x = 0;
    int m = 0;
    int a = 0;
    int s = 0;
};

/**
 * Struct to hold single rule
 */
struct Rule {
    bool greater = false;
    char var{};
    int val = 0;
    string dest{};

    /**
     * Checks if part matches the rule
     * @param p part to be checked
     * @return true of matches
     */
    bool matchRule( const Part& p ) const {
        if ( var == 'E' ) return true;
        if ( greater ) {
            if ( var == 'x' )
                return p.x > val;
            if ( var == 'm' )
                return p.m > val;
            if ( var == 'a' )
                return p.a > val;
            if ( var == 's' )
                return p.s > val;
        }
        else {
            if ( var == 'x' )
                return p.x < val;
            if ( var == 'm' )
                return p.m < val;
            if ( var == 'a' )
                return p.a < val;
            if ( var == 's' )
                return p.s < val;
        }
        return false;
    }
};

/**
 * Parses string and separates single rules
 * Last rule is marked with var 'E'
 * @param line string to be parsed
 * @return vector of rules
 */
vector<Rule> parseRules( string line ) {
    vector<Rule> res;

    int i = 0;
    while ( !line.empty() ) {
        Rule r;

        r.var = line[0];
        r.greater = line[1] == '>';
        int pos = line.find(':');

        if ( pos == std::string::npos ) {
            pos = line.find('}');
            r.dest = line.substr(0,pos);
            r.var = 'E';
            res.push_back(r);
            return res;
        }
        else {
            r.val = stoi(line.substr(2, pos-2));
            int pos2 = line.find(',');
            r.dest = line.substr(pos+1, pos2-pos-1);
            res.push_back(r);
            line = line.substr(pos2+1, line.length()-pos);
        }
    }
    return res;
}

/**
 * Parses string and separates single parts
 * @param line string to be parsed
 * @return created part
 */
Part parsePart( string line ) {
    Part res;

    int pos = line.find(',');
    res.x = stoi(line.substr(2, pos-2));
    line = line.substr(pos+1, line.length()-pos);

    pos = line.find(',');
    res.m = stoi(line.substr(2, pos-2));
    line = line.substr(pos+1, line.length()-pos);

    pos = line.find(',');
    res.a = stoi(line.substr(2, pos-2));
    line = line.substr(pos+1, line.length()-pos);

    res.s = stoi(line.substr(2, line.length()-3));
    return res;
}

/**
 * Checks upper bounds
 * @param bounds bounds to be checked
 * @param r current rule
 * @return true if bounds can be updated
 */
bool updateUpBounds( map<char, pair<ll, ll>> &bounds, Rule &r ) {
    if (r.var == 'E')
        return true;

    if ( r.greater ) {
        if ( bounds[r.var].second <= r.val)
            return false;
        bounds[r.var].first = max(bounds[r.var].first, r.val + 1);
        return true;
    }
    else {
        if (bounds[r.var].first >= r.val)
            return false;
        bounds[r.var].second = min(bounds[r.var].second, r.val - 1);
        return true;
    }
}

/**
 * Checks lower bounds
 * @param bounds bounds to be checked
 * @param r current rule
 * @return true if bounds can be updated
 */
bool updateLowBounds( map<char, pair<ll, ll>> &bounds, Rule &r ) {
    if (r.var == 'E')
        return false;

    if ( r.greater ) {
        if ( bounds[r.var].first > r.val)
            return false;
        bounds[r.var].second = min(bounds[r.var].second, r.val);
        return true;
    }
    else {
        if (bounds[r.var].second < r.val)
            return false;
        bounds[r.var].first = max(bounds[r.var].first, r.val);
        return true;
    }
}

/**
 * DFS algorithm to travel through graph to count needed bounds
 * @param curr current workflow
 * @param b map of bounds
 * @param g graph
 * @return returns all possible combinations of part values matching the workflows
 */
ll dfs( const string& curr,  map<char,pair<ll, ll>>& b, map<string, vector<Rule>>& g ) {
    ll res = 0;

    if ( curr == "R" ) return 0;
    if ( curr == "A" ) {
        res = 1;
        for ( auto &p: b ) {
            res *= ( p.second.second - p.second.first + 1 );
        }
        return res;
    }

    for (auto &r: g[curr]) {
        auto nB = b;
        if ( updateUpBounds(nB, r) ) res += dfs(r.dest, nB, g);
        if ( !updateLowBounds(b, r) ) break;
    }
    return res;
}

/**
 * Checking if part match any workflow
 * @param p part to be checked
 * @param g graph
 * @return true if part matches any workflow
 */
bool solvePart1( const Part& p, map<string, vector<Rule>>& g ) {
    string curr = "in";

    while ( true ) {
        if ( curr == "A" ) return true;
        if ( curr == "R" ) return false;
        for ( Rule r : g[curr] ) {
            if ( r.matchRule(p) ) {
                curr = r.dest;
                break;
            }
        }
    }
}

/**
 * Solves part 2 using DFS algorithm
 * @param g
 * @return
 */
ll solvePart2( map<string, vector<Rule>>& g ) {
    map<char, pair<ll, ll>> bounds;
    for (char c: string("xmas")) {
        bounds[c] = {1, 4000};
    }
    return dfs("in", bounds, g);
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    map<string, vector<Rule>> g;

    ll res1 = 0,
       res2 = 0;

    // Load rules
    while ( getline(cin, line) ) {
        if ( line.empty()  ) break;

        vector<Rule> r;
        string n{};
        for (int i = 0; i < line.size(); i++) {
            if (line[i] == '{') {
                n = line.substr(0, i);
                r = parseRules( line.substr(i+1, line.length()-i-1) );
            }
        }
        g[n] = r;
    }

    // Load parts
    while ( getline(cin, line) ) {
        if ( line.empty()  ) break;
        cout << line << endl;
        Part p = parsePart(line.substr(1, line.length()-1));
        if ( solvePart1(p,g) ) {
            res1 += p.a + p.m + p.x + p.s;
        }
    }

    res2 = solvePart2(g);
    cout << "Part 1: " << res1 << endl;
    cout << "Part 2: " << res2 << endl;
}