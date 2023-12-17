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
using matrix = vector<vector<int>>;
using node = pair<int,int>;

vector<vector<int>> m;

/**
 * Struct to store state
 */
struct state {
    node coords;
    int steps{};
    char dir{};
    int heatLoss{};
};

/**
 * Function to store state in 32 b
 * @param s state to store
 * @return returned in
 */
int storeState ( const state& s ) {
    uint32_t hash = 0;
    hash |= s.coords.first;
    hash |= s.coords.second << 8;
    hash |= s.steps << 16;
    hash |= s.dir << 24;
    return hash;
}

/**
 * Function to find all possible neighbours from given node
 * @param n node to search neighbours
 * @param dir current direction
 * @return vector of all neighbours
 */
vector<pair<node, char>> findNeighbours( const node& n, char dir ) {
    vector<pair<node, char>> res;
    // Up
    if ( n.first-1 >= 0 && dir != 'D' )
        res.emplace_back(make_pair(n.first-1, n.second), 'U');
    // Right
    if ( n.second+1 < m[0].size() && dir != 'L' )
        res.emplace_back(make_pair(n.first, n.second+1), 'R');
    // Down
    if ( n.first+1 < m.size() && dir != 'U' )
        res.emplace_back(make_pair(n.first+1, n.second), 'D');
    // Left
    if ( n.second-1 >= 0 && dir != 'R' )
        res.emplace_back(make_pair(n.first, n.second-1), 'L');
    return res;
}

/**
 * Dijkstra algorithm to find path with lowest heat loss
 * @param start starting node
 * @param end ending node
 * @param minSteps minimal steps in one direction
 * @param maxSteps maximal steps in one direction
 * @return amount of heat loss on the found path
 */
int findPath( node start, node end, int minSteps, int maxSteps ) {
    auto cmp = [](const auto& a, const auto& b) {
        return a.heatLoss > b.heatLoss;
    };

    // Priority queue
    std::priority_queue < state, vector<state>, decltype(cmp)> pq;

    // Mark visited states
    unordered_map<uint32_t, int> v;

    // Mark prev
    map<node, node> p;

    for ( const auto& n : findNeighbours(start, ' ' ) ) {
        p[n.first] = start;
        state ns;
        ns.coords = n.first;
        ns.steps = 1;
        ns.dir = n.second;
        ns.heatLoss = m[n.first.first][n.first.second];
        pq.push(ns);
    }

    int res = 0;

    while ( !pq.empty() ) {
        state currS = pq.top();
        pq.pop();

        if ( currS.coords.first == end.first && currS.coords.second == end.second && currS.steps >= minSteps ) {
            res = currS.heatLoss;
            break;
        }

        auto neighs = findNeighbours( currS.coords, currS.dir );
        for ( const auto& nn : neighs ) {
            state nextState;
            nextState.coords = nn.first;
            nextState.dir = nn.second;
            nextState.heatLoss = currS.heatLoss + m[nn.first.first][nn.first.second];
            if ( nn.second == currS.dir ) {
                nextState.steps = currS.steps + 1;
            }
            else {
                nextState.steps = 1;
            }

            if ( currS.steps > maxSteps ) continue;
            if ( nextState.dir != currS.dir && currS.steps < minSteps ) continue;

            uint32_t hashedState = storeState(nextState);
            auto it = v.find(hashedState);
            if ( it != v.end() ) {
                if ( it->second > nextState.heatLoss ) {
                    it->second = nextState.heatLoss;
                    pq.push(nextState);
                    p[nextState.coords] = currS.coords;
                }
            }
            else {
                v[hashedState] = nextState.heatLoss;
                pq.push(nextState);
                p[nextState.coords] = currS.coords;
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

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        vector<int> tmp;
        for ( char& c : line )
            tmp.emplace_back((int)(c-'0'));
        m.emplace_back(tmp);
    }

    res1 = findPath({0,0}, {m.size()-1, m[0].size()-1}, 1, 3);
    cout << "Part1: " << res1 << endl;
    res2 = findPath({0,0}, {m.size()-1, m[0].size()-1}, 4, 10);
    cout << "Part2: " << res2 << endl;
}
