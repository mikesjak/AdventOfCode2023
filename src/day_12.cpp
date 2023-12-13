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

#define int ll

struct springCond {
    string spring;
    vector<int> groups;
};

vector<springCond> conds;

// Recursion idea found on reddit
// Recursion function solving part one
int countArrangements( springCond& c, int rowPos, int groupPos, int groupLen ) {
    int arr = 0;

    if ( rowPos == c.spring.length() ) {
        // End of the row and all groups found
        if ( groupPos == c.groups.size() && groupLen == 0 ) {
            return 1;
        }
        // Counting last group and checking if finished
        if ( groupPos == c.groups.size()-1 && groupLen == c.groups[groupPos] ) {
            return 1;
        }

        // Groups can't be matched with any arrangements
        return 0;
    }

    if ( c.spring[rowPos] == '.' || c.spring[rowPos] == '?' ) {
        // Currently not counting group, no new group started => continue
        if ( groupLen == 0 ) {
            arr += countArrangements(c, rowPos + 1, groupPos, 0);
        }
        // if ending group, continue to next group
        else if ( groupLen > 0 && groupPos < c.groups.size() && c.groups[groupPos] == groupLen ) {
            arr += countArrangements(c, rowPos + 1, groupPos + 1, 0);
        }
    }

    if ( c.spring[rowPos] == '#' || c.spring[rowPos] == '?' ) {
        // Start or continue counting current group -> advance row
        arr += countArrangements(c, rowPos + 1, groupPos, groupLen + 1);
    }

    return arr;
}

// Recursion using memoization
int countArrangements2( springCond& record, map<tuple<int,int,int>, int>& visited, const tuple<int,int,int> state ) {
    if (auto const entry = visited.find(state); entry != visited.end())
    {
        auto const& [_, arrangements] = *entry;
        return arrangements;
    }

    auto const [rp, gp, gl] = state;
    if (rp == record.spring.length())
    {
        // reached end of row, check if all groups were found and no additional group is currently counting
        if (gp == record.groups.size() && gl == 0)
        {
            return 1;
        }

        // if we are currently counting the last group check if it was completed on the last character
        if (gp == record.groups.size() - 1 && gl == record.groups[gp])
        {
            return 1;
        }

        // group arrangements could not be matched to the row input in this branch
        return 0;
    }

    auto arrangements = 0ULL;
    if ( record.spring[rp] == '.' || record.spring[rp] == '?' )
    {
        if (gl == 0)
        {
            // no counting group, no new group, advance row
            arrangements += countArrangements2(record, visited, std::make_tuple(rp + 1, gp, 0));
        }
        else if (gl > 0 && gp < record.groups.size() && record.groups[gp] == gl)
        {
            // group closed. Check if current group matches counted group. If so, advance row and inspect next group.
            arrangements += countArrangements2(record, visited, std::make_tuple(rp + 1, gp + 1, 0));
        }
    }

    if (record.spring[rp] == '#' || record.spring[rp] == '?')
    {
        // start or continue counting current group, advance row
        arrangements += countArrangements2(record, visited, std::make_tuple(rp + 1, gp, gl + 1));
    }

    visited[state] = arrangements;
    return arrangements;
}


signed main( ) {
    string line;
    freopen("../in.txt", "r", stdin);

    int res1 = 0,
        res2 = 0;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        springCond sc;
        string s;

        istringstream ss(line);
        ss >> sc.spring;
        while ( getline(ss,s,',') ) {
            sc.groups.emplace_back(stoi(s));
        }

        int r1 = countArrangements(sc, 0, 0, 0);
        res1 += r1;

        springCond p2 = sc;
        for ( int i = 0; i < 4; i++ ) {
            string tmpc = "?";
            p2.spring.append(tmpc);
            p2.spring.append(sc.spring);
            for ( auto& n : sc.groups )
                p2.groups.push_back(n);
        }

        tuple<int, int, int> state = {};
        map<tuple<int, int, int>, int> v;
        int r2 = countArrangements2(p2, v, state);
        res2 += r2;

        conds.push_back(p2);
    }

    cout << "Part1: " << res1 << endl;
    cout << "Part2: " << res2 << endl;

    // Comparing both solutions
    res2 = 0;
    const auto start2 = std::chrono::high_resolution_clock::now();
    for ( auto& c : conds ) {
        tuple<int, int, int> state = {};
        map<tuple<int, int, int>, int> v;
        res2 += countArrangements2(c, v, state);
    }
    const auto end2 = std::chrono::high_resolution_clock::now();
    auto ms2 = std::chrono::duration_cast<std::chrono::milliseconds>(end2 - start2).count();
    cout << "Memoization:" << endl;
    cout << "Res: " << res2 << ", Time: " << ms2 << "ms" << endl;
    res1 = 0;
    const auto start1 = std::chrono::high_resolution_clock::now();
    for ( auto& c : conds ) {
        res1 += countArrangements(c, 0, 0, 0);
    }
    const auto end1 = std::chrono::high_resolution_clock::now();
    auto ms = std::chrono::duration_cast<std::chrono::milliseconds>(end1 - start1).count();
    cout << "Simple recursion:" << endl;
    cout << "Res: " << res1 << ", Time: " << ms << "ms" << endl;
}