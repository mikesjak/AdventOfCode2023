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
using node = pair<int, int>;

vector<int> x = {-1, 0, 1,  0};
vector<int> y = { 0, 1, 0, -1};

vector<vector<char>> matrix;
vector<vector<bool>> visited;
node start = {0, 1};
int res1, res2;

/**
 * Recursive function solving both parts
 * @param curr Current node
 * @param part1 true if solving part 1
 * @return result for solved part
 */
int solve( node curr, bool part1) {
    int i = curr.first;
    int j = curr.second;
    if ( i == matrix.size() - 1) {
        return 0;
    }

    visited[i][j] = true;
    int res = INT32_MIN;
    char currC = matrix[i][j];
    if ( part1 && currC != '.' ) {
        if (currC == '^' && !visited[i - 1][j])
            res = solve({i - 1, j}, part1) + 1;
        else if (currC == 'v' && !visited[i + 1][j])
            res = solve({i + 1, j}, part1) + 1;
        else if (currC == '<' && !visited[i][j - 1])
            res = solve({i, j - 1}, part1) + 1;
        else if (currC == '>' && !visited[i][j + 1])
            res = solve({i, j + 1}, part1) + 1;
    }
    else {
        for (int k = 0; k < 4; ++k) {
            int iNew = i + x[k];
            int jNew = j + y[k];
            if ( iNew >= 0 && matrix[iNew][jNew] != '#' && !visited[iNew][jNew] ) {
                res = max(res, solve({iNew, jNew}, part1) + 1);
            }
        }
    }

    visited[i][j] = false;
    return res;
}

int main() {
    string line;
    freopen("../in.txt", "r", stdin);

    while (getline(cin, line)) {
        istringstream ss(line);
        vector<char> tmp;
        char c;
        while ( ss >> c ) {
            tmp.push_back(c);
        }
        matrix.emplace_back(tmp);
    }

    visited.resize(300);
    for ( auto& tmp : visited ) {
        tmp.resize(300);
    }

    res1 = solve(start, true);
    res2 = solve(start, false);
    cout << "Part1: " << res1 << endl;
    cout << "Part2: " << res2 << endl;
}