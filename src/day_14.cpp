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

#define CYCLES 1000000000

using namespace std;
using ll = unsigned long long;

vector<vector<char>> m;

// Storing transition to find cycle
map< vector< vector<char> >, pair<int, vector<vector<char>> > > dp;

ll res1 = 0;
ll res2 = 0;

// Count load of current matrix
ll countLoad() {
    ll load = 0;

    for ( int i = 0; i < m.size(); i++ ) {
        for ( int j = 0; j < m[i].size(); j++ ) {
            if ( m[i][j] == 'O' )
                load += m.size()-i;
        }
    }

    return load;
}

// Falling functions to all sites
void fallNorth() {
    for ( int i = 0; i < m.size(); i++ ) {
        for ( int j = 0; j < m[i].size(); j++ ) {
            if ( m[i][j] != 'O' ) continue;

            bool moved = false;
            int k = i-1;

            if ( i > 0 ) {
                while ( k >= 0 && m[k][j] == '.' ) {
                    k--;
                    moved = true;
                }
            }

            if ( moved ) {
                m[k+1][j] = 'O';
                m[i][j] = '.';
            }
        }
    }
}

void fallSouth() {
    for ( int i = m.size()-1; i >= 0; i-- ) {
        for ( int j = 0; j < m[i].size(); j++ ) {
            if ( m[i][j] != 'O' ) continue;

            bool moved = false;
            int k = i+1;

            if ( i < m.size()-1 ) {
                while ( k <= m.size()-1 && m[k][j] == '.' ) {
                    k++;
                    moved = true;
                }
            }

            if ( moved ) {
                m[k-1][j] = 'O';
                m[i][j] = '.';
            }
        }
    }
}

void fallEast() {
    for ( int j = m[0].size(); j >= 0; j-- ) {
        for ( int i = 0; i < m.size(); i++ ) {
            if ( m[i][j] != 'O' ) continue;

            bool moved = false;
            int k = j+1;

            if ( j < m[0].size()-1 ) {
                while ( k <= m[0].size() && m[i][k] == '.' ) {
                    k++;
                    moved = true;
                }
            }

            if ( moved ) {
                m[i][k-1] = 'O';
                m[i][j] = '.';
            }
        }
    }
}

void fallWest() {
    for ( int j = 0; j <= m[0].size()-1; j++ ) {
        for ( int i = 0; i < m.size(); i++ ) {
            if ( m[i][j] != 'O' ) continue;

            bool moved = false;
            int k = j-1;

            if ( j > 0 ) {
                while ( k >= 0 && m[i][k] == '.' ) {
                    k--;
                    moved = true;
                }
            }

            if ( moved ) {
                m[i][k+1] = 'O';
                m[i][j] = '.';
            }
        }
    }
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        char c;
        vector<char> tmp;

        istringstream ss(line);
        while ( ss >> c ) {
            tmp.push_back(c);
        }
        m.push_back(tmp);
    }
    vector<vector<char>> mCycles, m_start = m;

    bool fC = false;
    ll cycle = 0;
    for ( int i = 0; i < CYCLES; i++ ) {
        if ( dp[m].second.size() != 0 && !fC ) {
            fC = true;
            cycle = (i-dp[m].first);
            m = dp[m].second;
            while ( i+cycle < CYCLES )
                i += cycle;
        }
        else {
            vector<vector<char>> mOld = m;

            fallNorth();
            if (i == 0)
                res1 = countLoad();
            fallWest();
            fallSouth();
            fallEast();

            if ( dp[mOld].second.size() == 0 )
                dp[mOld] = {i, m};
        }
    }
    res2 = countLoad();

    cout << "Part1: " << res1 << endl;
    cout << "Part2: " << res2 << endl;
}