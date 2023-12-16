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
#include <utility>
#include <vector>
#include <cmath>
#include <queue>
#include <set>
#include <map>
#include <chrono>
#include <format>

using namespace std;
using ll = unsigned long long;
using node = pair<int, int>;
using state = string;

#define int ll

/**
 * Matrix to store input
 */
vector<vector<char>> m;

/**
 * Matrix to store walked path
 */
vector<vector<char>> m_path;

/**
 * Checks if node coords are valid
 * @param n node to check
 * @return true if node valid
 */
bool isValidNode( node n ) {
    return n.first >= 0 && n.first < m.size() && n.second >= 0 && n.second < m[0].size();
}

/**
 * Compares 2 matrix
 * @param a matrix A
 * @param b matrix B
 * @return return true if equal
 */
bool cmpMatrix( vector<vector<char>>& a, vector<vector<char>>&b ) {
    for ( int i = 0; i < a.size(); i++ ) {
        for ( int j = 0; j < a[0].size(); j++ ) {
            if ( a[i][j] != b [i][j] ) return false;
        }
    }
    return true;
}

/**
 * Print matrix
 * @param matrix Matrix to print
 */
void printMatrix( vector<vector<char>>& matrix ) {
    for ( auto& r : matrix ) {
        for ( auto& c : r ) {
            cout << c << " ";
        }
        cout << endl;
    }
    cout << endl;
}

/**
 * returns set of directions from given node
 * @param n node to get available directions
 * @param s current direction
 * @return next direction(s)
 */
vector<string> getDirection( node n, const state& s ) {
    char c = m[n.first][n.second];
    if ( c == '.' ) return {s};
    else if ( c == '|' ) {
        if ( s == "left" || s == "right" ) return {"up","down"};
        else return {s};
    }
    else if ( c == '-' ) {
        if ( s == "up" || s == "down" ) return {"left","right"};
        else return {s};
    }
    else if ( c == '/' ) {
        if ( s == "left" ) return {"down"};
        if ( s == "right" ) return {"up"};
        if ( s == "up") return {"right"};
        else return {"left"};
    }
    else {
        if ( s == "right") return {"down"};
        if ( s == "up") return {"left"};
        if ( s == "left" ) return {"up"};
        else return {"right"};
    }
}

/**
 * Move light from node in given direction
 * @param n source node
 * @param s current direction
 * @return returns new position of light
 */
node moveInDir( node n, const state& s ) {
    int node_f = n.first;
    int node_s = n.second;
    if ( s == "left" ) node_s--;
    if ( s == "right" ) node_s++;
    if ( s == "up" ) node_f--;
    if ( s == "down" ) node_f++;
    return {node_f, node_s};
}

/**
 * Count energized nodes
 * @param start starting node
 * @param dir starting direction
 * @return
 */
int energize( node start, const state& dir ) {
    queue<pair<node, state>> q;
    vector<vector<char>> mPrev;
    set<pair<node, state>> vs;
    set<node> v;

    v.insert(start);
    node curr = start;
    state currDir = dir;

    m_path = m;
    m_path[0][0] = '#';
    mPrev = m_path;

    int notChanged = 0;

    q.emplace(curr, currDir);
    while ( !q.empty() ) {
        curr = q.front().first;
        currDir = q.front().second;
        q.pop();
        mPrev = m_path;

        m_path[curr.first][curr.second] = '#';

        for ( auto& d : getDirection(curr, currDir) ) {
            node n = moveInDir(curr, d);
            if ( isValidNode(n) && vs.count({n, d}) == 0 ) {
                q.emplace(n, d);
                v.insert(n);
                vs.insert({n, d});
            }
        }

        if (cmpMatrix(mPrev, m_path) ) notChanged++;
        else notChanged = 0;
    }

    return v.size();
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    int res2 = 0;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;

        vector<char> tmp;
        char c;

        istringstream ss(line);
        while ( ss >> c ) {
            tmp.push_back(c);
        }
        m.push_back(tmp);
    }

    cout << "Part1: " << energize({0,0}, "right") << endl;

    // Upper edge
    for ( int i = 0; i < m[0].size(); i++ ) {
        vector<state> dirs = {"down"};
        if ( i != 0 ) dirs.emplace_back("left");
        if ( i != m[0].size()-1 ) dirs.emplace_back("right");
        for ( auto& d : dirs ) {
            res2 = max(res2, energize({0, i}, d));
        }
    }

    // Down edge
    for ( int i = 0; i < m[0].size(); i++ ) {
        vector<state> dirs = {"up"};
        if ( i != 0 ) dirs.emplace_back("left");
        if ( i != m[0].size()-1 ) dirs.emplace_back("right");
        for ( auto& d : dirs ) {
            res2 = max(res2, energize({m.size()-1, i}, d));
        }
    }

    // Left edge
    for ( int i = 0; i < m.size(); i++ ) {
        vector<state> dirs = {"right"};
        if ( i != 0 ) dirs.emplace_back("up");
        if ( i != m.size()-1 ) dirs.emplace_back("down");
        for ( auto& d : dirs ) {
            res2 = max(res2, energize({i, 0}, d));
        }
    }

    // Right edge
    for ( int i = 0; i < m.size(); i++ ) {
        vector<state> dirs = {"left"};
        if ( i != 0 ) dirs.emplace_back("up");
        if ( i != m.size()-1 ) dirs.emplace_back("down");
        for ( auto& d : dirs ) {
            res2 = max(res2, energize({i, m[0].size()-1}, d));
        }
    }

    cout << "Part2: " << res2 << endl;
}