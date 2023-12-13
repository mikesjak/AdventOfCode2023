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
using matrix = vector<vector<char>>;


#define int ll

// Compare two matrix
int compareMatrix( matrix& a, matrix& b ) {
    int diffs = 0;

    for ( int i = 0; i < a.size(); i++ ) {
        for ( int j = 0; j < a[i].size(); j++ ) {
            if ( a[i][j] != b[i][j] ) diffs++;
        }
    }

    return diffs;
}

// Find single reflection point
int findReflection( matrix& m, bool part2 ) {
    for ( int i = 0; i < m.size()-1; i++ ) {
        uint8_t mSize = min(i+1, m.size()-(i+1));
        matrix a(mSize), b(mSize);

        for ( int j = 0; j < mSize; j++ ) {
            a[j] = m[i-j];
            b[j] = m[i+j+1];
        }

        if ( compareMatrix(a,b) == 0 && !part2) {
            return i+1;
        }
        else if (compareMatrix(a, b) == 1 && part2 ){
            return i+1;
        }
    }
    return m.size() + 1;
}

// Transpose matrix
matrix transposeMatrix( const matrix& m ) {
    matrix mT(m[0].size(), vector<char>(m.size()));

    for ( int i = 0; i < m.size(); i++ ) {
        for ( int j = 0; j < m[i].size(); j++ ) {
            mT[j][i] = m[i][j];
        }
    }

    return mT;
}

// Tries to find both reflection points
int findReflections( matrix& m, bool part2 ) {
    int res = 0;
    matrix mT = transposeMatrix(m);

    int tmpR = findReflection(m, part2);
    if ( tmpR > m.size() ) tmpR = 0;
    res += (100*tmpR);

    int tmpC = findReflection(mT, part2);
    if ( tmpC > mT.size() ) tmpC = 0;
    res += tmpC;

    return res;
}

signed main() {
    vector<vector<char>> m;
    string line;
    freopen("../in.txt", "r", stdin);

    int res1 = 0,
        res2 = 0;

    while ( getline(cin, line) ) {

        // Handle matrix nd
        if ( line.empty()  ) {
            res1 += findReflections( m, false);
            res2 += findReflections(m, true);
            m = {};
            getline(cin, line);
        }
        vector<char> tmp;

        for ( auto& c : line )
            tmp.push_back(c);

        m.push_back(tmp);
    }

    // Handle last matrix
    res1 += findReflections(m, false);
    res2 += findReflections(m, true);

    cout << "Res1: " << res1 << endl;
    cout << "Res2: " << res2 << endl;
}