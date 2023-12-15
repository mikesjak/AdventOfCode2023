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

vector<string> ins;
map<string, bool> ltb;

using box = vector<pair<string, int>>;

/**
 * Hash function (part1)
 * @param s string to hash
 * @return value 0-256, represents hashed string
 */
int hashString( string& s ) {
    int res = 0;
    for ( char c : s ) {
        int aV = c + res;
        //cout << c << " " << aV << " ";
        aV *= 17;
        //cout << aV << " ";
        aV %= 256;
        //cout << aV << endl;
        res = aV;
    }
    return res;
}

/**
 * Parses input
 * @param s to parse
 * @return <hash, focal length, label>
 * */
tuple<uint16_t, uint8_t, string> parseInput( string& s ) {
    int pos = s.find('-');
    string label, fl;
    if ( pos != string::npos ) {
        label = s.substr(0, pos);
        uint16_t hash = hashString(label);
        //cout << "Label: " << label << endl;
        return {hash, 10, label};
    }
    else {
        pos = s.find('=');
        label = s.substr(0, pos);
        uint16_t hash = hashString(label);
        fl = s.substr(pos+1, 1);
        //cout << "Label: " << label << " " << stoi(fl) << " " << hash << endl;

        return {hash, stoi(fl), label};
    }
}

signed main() {
    string line;
    freopen("../in.txt", "r", stdin);

    ll res1 = 0,
        res2 = 0;

    // Load input and count part1;
    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        istringstream ss(line);
        string s;
        while ( getline(ss,s, ',' ) ) {
            res1 += hashString(s);
            ins.push_back(s);
        }
    }

    vector<box> boxes(256);

    // Part2
    for ( string& s : ins ) {
        auto t = parseInput(s);
        const auto [hash, fl, label] = t;

        // -
        if ( fl == 10 ) {
            if ( ltb[label] ) {
                ltb[label] = false;
                auto it = boxes[hash].begin();
                for ( it; it != boxes[hash].end(); it++ ) {
                    if ( it->first == label ) break;
                }
                boxes[hash].erase(it);
            }

        }
        // =
        else {
            // Replacing
            if ( ltb[label] ) {
                auto it = boxes[hash].begin();
                for ( it; it != boxes[hash].end(); it++ ) {
                    if ( it->first == label ) break;
                }
                it->second = fl;
            } // Adding new element
            else {
                ltb[label] = true;
                boxes[hash].emplace_back(label,fl);
            }
        }
    }

    // Count part 2
    for ( int j = 0; j < boxes.size(); j++ ) {
        for ( int i = 0; i < boxes[j].size(); i++ ) {
            int rl = (j+1)*(i+1)*boxes[j][i].second;
            res2 += rl;
        }
    }

    cout << "Res1: " << res1 << endl;
    cout << "Res2: " << res2 << endl;
}