#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <numeric>
#include <map>
#include <sstream>
#include <cassert>

using namespace std;

int res1 = 0;
int res2 = 0;

/**
 * Struct representing single brick
 */
struct Rectangle {
    int id, x1, y1, z1, x2, y2, z2;
};

vector<Rectangle> v;
vector<set<int>> above, below;

/**
 * Compare function for rectangles
 * @param a 
 * @param b 
 * @return true if b is above a
 */
bool cmp( Rectangle& a, Rectangle& b ) {
    return a.z1 < b.z1;
}

/**
 * Marks used coordinates
 * @param r current rectangle
 * @param used container of used coords
 */
void mark( Rectangle &r, vector<vector<vector<int>>>& used ) {
    for ( int i = r.x1; i <= r.x2; i++ ) {
        for ( int j = r.y1; j <= r.y2; j++ ) {
            for ( int k = r.z1; k <= r.z2; k++ ) {
                used[i][j][k] = r.id;
            }
        }
    }
}

/**
 * Simulate falling of one rectangle
 * @param r rectangle to fall
 * @param used container of used coords
 */
void fall( Rectangle &r, vector<vector<vector<int>>>& used ) {
    int step = r.z1 - 1;
    for ( int i = r.x1; i <= r.x2; i++ ) {
        for ( int j = r.y1; j <= r.y2; j++ ) {

            int k = 0;
            while (r.z1 - k >= 2 && used[i][j][r.z1 - k - 1] == -1) {
                k++;
            }
            step = min(step, k);

        }
    }

    for ( int i = r.x1; i <= r.x2; i++ ) {
        for ( int j = r.y1; j <= r.y2; j++ ) {
            for ( int k = 1; k <= step; k++ ) {
                used[i][j][r.z1 - k] = r.id;
                used[i][j][r.z2 + 1 - k] = -1;
            }
        }
    }

    r.z1 -= step;
    r.z2 -= step;
}

/**
 * Find bricks above r
 * @param r curr brick
 * @param used container of used coords
 */
void findAbove( Rectangle &r, const vector<vector<vector<int>>>& used ) {
    for ( int i = r.x1; i <= r.x2; ++i ) {
        for ( int j = r.y1; j <= r.y2; ++j ) {
            if ( used[i][j][r.z2 + 1] != -1 ) {
                above[r.id].insert(used[i][j][r.z2 + 1]);
                below[used[i][j][r.z2 + 1]].insert(r.id);
            }
        }
    }
}

/**
 * BFS function to simulate falling
 * @param start 
 * @return 
 */
int BFS( int start ) {
    vector<int> belowCnt(v.size());
    queue<int> q;

    for ( int i = 0; i < v.size(); i++ ) {
        belowCnt[i] = below[i].size();
    }

    q.emplace(start);
    int res = 0;

    while ( !q.empty() ) {
        int i = q.front();
        q.pop();
        for ( auto j: above[i] ) {
            belowCnt[j] -= 1;
            if ( belowCnt[j] == 0) {
                res++;
                q.emplace(j);
            }
        }
    }
    return res;
}

/**
 * Function parsing input and creating new rectangle
 * @param line string to parse
 * @return created rectangle
 */
Rectangle createRec(string& line ) {
    istringstream ss(line);
    Rectangle res{};

    res.id = v.size();

    size_t pos = line.find(',');
    res.x1 = stoi(line.substr(0, pos));
    line = line.substr(pos+1);

    pos = line.find(',');
    res.y1 = stoi(line.substr(0, pos));
    line = line.substr(pos+1);

    pos = line.find('~');
    res.z1 = stoi(line.substr(0, pos));
    line = line.substr(pos+1);

    pos = line.find(',');
    res.x2 = stoi(line.substr(0, pos));
    line = line.substr(pos+1);

    pos = line.find(',');
    res.y2 = stoi(line.substr(0, pos));
    line = line.substr(pos+1);

    res.z2 = stoi(line.substr(0));

    return res;
}

int main() {
    vector<vector<vector<int>>> used(20, vector<vector<int>>(20, vector<int>(400, -1)));

    string line;
    freopen("../in.txt", "r", stdin);

    while ( getline(cin, line) ) {
        Rectangle tmp = createRec(line);
        v.emplace_back(tmp);
        mark(tmp, used);
    }

    sort(v.begin(), v.end(), cmp);

    for ( Rectangle &r: v ) {
        fall(r, used);
    }

    above.resize(v.size());
    below.resize(v.size());

    for (Rectangle &r: v) {
        findAbove(r, used);
    }

    for (Rectangle &r: v) {
        int tmp = BFS(r.id);
        res1 += (tmp == 0);
        res2 += tmp;
    }
    cout << "Part1: " << res1 << endl;
    cout << "Part2: " << res2 << endl;

}