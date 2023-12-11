#include <unordered_map>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <cassert>
#include <cstdio>
#include <queue>
#include <vector>
#include <numeric>
#include <iomanip>
#include <string>
#include <cmath>
#include <queue>
#include <set>
#include <map>


using namespace std;
using ll = long long;

#define int ll

vector<vector<char>> space;
vector<pair<ll, ll>> gs, gsOld;

void printGalaxies() {
    cout << "Printing!!!!" << endl;
    for ( auto& g: gs ) {
        cout << g.first << " " << g.second << endl;
    }
}

void expandSpace( bool part2 ) {
    bool empty;
    gsOld = gs;

    // Rows
    for ( ll i = 0; i < space.size(); i++ ) {
        empty = true;
        for (ll j = 0; j < space[i].size(); j++) {
            if ( space[i][j] != '.' ) {
                empty = false;
            }
        }
        if ( empty ) {
            cout << "Row [" << i << "] is being expanded!" << endl;
            for ( int k = 0; k <= gs.size(); k++ ) {
                if ( gsOld[k].first > i ) {
                    gs[k].first += 999999;
                }
            }
        }
    }

    printGalaxies();

    // Columns
    for ( int j = 0; j < space[0].size(); j++ ) {
        empty = true;
        for (int i = 0; i < space.size(); i++) {
            if ( space[i][j] != '.' ) {
                empty = false;
            }
        }
        if ( empty ) {
            cout << "Col [" << j << "] is being expanded!" << endl;
            for ( int k = 0; k <= gs.size(); k++ ) {
                if ( gsOld[k].second > j ) {
                    gs[k].second += 999999;
                }
            }
        }
    }
}

ll countDistances() {
    ll res = 0;
    for ( auto& g1 : gs ) {
        for ( auto& g2 : gs ) {
            if ( g1 == g2 ) continue;

            res += llabs(g1.first-g2.first)+llabs(g1.second-g2.second);
        }
    }
    return res/2;
}

signed main ( ) {
    string line;
    freopen("../in.txt", "r", stdin);

    while( getline(cin, line) ) {
        if ( line.empty() ) break;
        istringstream ss(line);
        char c;
        vector<char> tmp;

        while ( ss >> c ) {
            if ( c == '#' )
                gs.emplace_back(space.size(),tmp.size());
            tmp.push_back(c);
        }

        space.push_back(tmp);
    }
    printGalaxies();
    expandSpace(false);
    printGalaxies();

    ll res = countDistances();
    cout << "Res: " << res << endl;
}