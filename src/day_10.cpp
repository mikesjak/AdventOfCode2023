#include<stdio.h>
#include<iostream>
#include<queue>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include <numeric>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <numeric>
#include <map>
#include <sstream>
#include <cassert>

using namespace std;
using ll = unsigned long long;

map<pair<int, int>, set<pair<int, int>>> sn;
vector<vector<char>> v;
vector<vector<int>> d;
pair<int, int> start;

vector<pair<int, int>> findNeighbours( int x, int y ) {
    char c = v[x][y];
    switch(c) {
        case '|':
            return {{x+1, y},{x-1, y}};
        case '-':
            return {{x, y-1},{x, y+1}};
        case 'L':
            return {{x-1, y},{x, y+1}};
        case 'J':
            return {{x-1, y},{x, y-1}};
        case 'F':
            return {{x+1, y},{x, y+1}};
        case '7':
            return {{x+1, y},{x, y-1}};
        default:
            return {{-1, -1}, {-1, -1}};
    }
}

bool isPipe(int x, int y) {
    return x >= 0 && x < v.size() && y >= 0 && y < v[0].size() && v[x][y] != '.';
}

void handleStartNeighbour( int x, int y ) {
    if ( x > 0 || x >= v.size() || y < 0 || y >= v[x].size() ) return;
    auto r = findNeighbours(x, y);
    // cout << "N: " << x << " " << y << endl;
    if ( !isPipe(r[0].first, r[0].second) || !isPipe(r[1].first, r[1].second) ) return;
    // cout << "Nb: " << r.first.first << " " << r.first.second <<  " " << v[r.first.first][r.first.second] << endl;
    // cout << "Nb: " << r.second.first << " " << r.second.second <<  " " << v[r.second.first][r.second.second] << endl;
    if ( v[r[0].first][r[0].second] == 'S' || v[r[1].first][r[1].second] == 'S' ){
        sn[{x,y}].insert(r[0]);
        sn[{x,y}].insert(r[1]);
        sn[r[0]].insert({x,y});
        sn[r[1]].insert({x,y});
        cout << "INSERTING!" << endl;
    }
}

void handleStart() {
    handleStartNeighbour(start.first-1, start.second-1);
    handleStartNeighbour(start.first-1, start.second);
    handleStartNeighbour(start.first-1, start.second+1);
    handleStartNeighbour(start.first,   start.second+1);
    handleStartNeighbour(start.first+1, start.second+1);
    handleStartNeighbour(start.first+1, start.second);
    handleStartNeighbour(start.first+1, start.second-1);
    handleStartNeighbour(start.first,   start.second-1);
}

int findPath() {
    queue<pair<pair<int, int>, int>> q;
    set<pair<int, int>> v;
    int res = 0;

    d[start.first][start.second] = 0;
    v.insert(start);
    for ( auto& n : sn[start] ) {
        q.emplace(n, 1);
        v.insert(n);
    }
    while( !q.empty() ) {
        pair<int, int> currN = q.front().first;
        int currD = q.front().second;
        cout << "N: " << currN.first << "," << currN.second << " " << currD << endl;
        q.pop();
        d[currN.first][currN.second] = currD;
        res = max(res, currD);

        for ( auto& nb : findNeighbours(currN.first, currN.second) ) {
            if ( v.count(nb) == 0 && isPipe(nb.first, nb.second) ) {
                q.emplace(nb, currD+1);
                v.insert(nb);
            }
        }
    }
    cout << "Res: " << res << endl;
}

void clearMaze() {
    cout << "Clearing!" << endl;

    for ( int i = 0; i < v.size(); i++ ) {
        for ( int j = 0; j < v[i].size(); j++ ) {
            if ( d[i][j] == -1 )
                v[i][j] = '.';
        }
    }
}

void printMaze() {
    for ( int i = 0; i < v.size(); i++ ) {
        for ( int j = 0; j < v[i].size(); j++ ) {
            cout << v[i][j] << " ";
        }
        cout << endl;
    }
}

int countInside() {
    int res = 0;

    for ( int i = 0; i < v.size()-1; i++ ) {
        int vc = 0;
        for ( int j = 0; j < v[i].size()-1; j++ ) {
            if ( v[i][j] == '.' && vc % 2 == 1 ) {
                res++;
                v[i][j] = 'X';
            }
            else if (  v[i][j] == '|' || v[i][j] == 'F' || v[i][j] == '7' )
                vc++;
        }
    }
    return res;
}

int main ( ) {
    string line;
    freopen("../in.txt", "r", stdin);

    while( getline(cin, line) ) {
        if ( line.empty() ) break;
        vector<char> tmp;
        vector<int> tmpD;
        char c;
        istringstream ss(line);

        while ( ss >> c ) {
            tmp.push_back(c);
            tmpD.emplace_back(-1);
            if ( c == 'S' ) {
                start = {v.size(), tmp.size()-1};
            }
        }
        v.push_back(tmp);
        d.push_back(tmpD);
    }

    cout << "Start: " << start.first << " " << start.second << endl;

    handleStart();
    for ( auto& p : sn ) {
        cout << "N: " << p.first.first << " " << p.first.second << endl;
        for ( auto& nb : p.second ) cout << nb.first << " " << nb.second << endl;
    }

    findPath();

    printMaze();
    clearMaze();
    cout << "Res2: " << countInside() << endl;
    printMaze();
}