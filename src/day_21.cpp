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
using matrix = vector<vector<char>>;
using node = pair<int, int>;

#define int ll
#define REFLECTIONS 202300

matrix m, m2;

/**
 * Finds neighbours for current node
 * @param n to find neighbours to
 * @return vector of neighbours
 */
vector<node> findNeighbours( const node& n ) {
    vector<node> res;

    // Down
    if ( n.first > 0 && m[n.first-1][n.second] == '.' )
        res.emplace_back(n.first-1, n.second);

    // Up
    if ( n.first < m.size()-1 && m[n.first+1][n.second] == '.' )
        res.emplace_back(n.first+1, n.second);


    // left
    if ( n.second > 0 && m[n.first][n.second-1] == '.' )
        res.emplace_back(n.first, n.second-1);

    // Up
    if ( n.second < m.size()-1 && m[n.first][n.second+1] == '.' )
        res.emplace_back(n.first, n.second+1);

    return res;
}

/**
 * BFS function to solve AOC 2023 Day 21
 * @param start starting node
 * @param finalDist steps to be done
 * @return number of garden plots reachable with finalDist steps
 */
int bfs( const node& start, int finalDist ) {
    int res = 0;
    queue<pair<node, int>> q;
    set<node> v;

    q.emplace(start, 0);
    v.emplace(start);

    while ( !q.empty() ) {
        node currNode = q.front().first;
        int currDist = q.front().second;
        q.pop();

        if ( currDist > finalDist )
            break;

        if ( currDist % 2 == finalDist % 2 ) {
            res++;
        }

        for ( auto& n : findNeighbours(currNode) ) {
            if ( v.count(n) == 0 ) {
                v.insert(n);
                q.emplace(n, currDist+1);
            }
        }
    }
    return res;
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    int res1 = 0,
        res2 = 0;
    node start{};

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;

        istringstream ss(line);
        vector<char> tmp;
        char c;

        while ( ss >> c ) {
            if ( c == 'S' ) {
                start = {m.size(), tmp.size()};
                tmp.push_back('.');
            }
            else {
                tmp.push_back(c);
            }
        }
        m.push_back(tmp);
        int lineSize = tmp.size();

        for ( int i = 0; i < (REFLECTIONS*2); i++ ) {
            for ( int j = 0; j < lineSize; j++ ) {
                if ( tmp[j] != 'S' ) {
                    tmp.push_back(tmp[j]);
                }
                else {
                    tmp.push_back('.');
                }
            }
        }
        m2.push_back(tmp);
    }
    for ( int i = 0; i < REFLECTIONS*2; i++ ) {
        for ( int j = 0; j < m.size(); j++ ) {
            m2.push_back(m2[j]);
        }
    }

    node newStart = {start.first+(m.size()*REFLECTIONS+1)-1, start.second+(m[0].size()*REFLECTIONS+1)-1 };
    m2[newStart.first][newStart.second] = 'S';

    cout << newStart.first << " " << newStart.second << endl;
    res1 = bfs(start, 64);
    cout << "Part1: " << res1 << endl;

    m = m2;
    res2 = bfs(newStart, 26501365);
    cout << "Part2: " << res2 << endl;
}