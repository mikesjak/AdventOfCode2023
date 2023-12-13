#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>

using namespace std;
using ll = unsigned long long;

static set<pair<ll, ll>> seeds;

void loadSeeds( string& line ) {
    ll start, range;

    istringstream ss(line);
    string tmp;
    ss >> tmp;

    while( ss >> start >> range ) {
        seeds.emplace(start, start + range -1);
    }
}

set<tuple<ll, ll, ll>> loadPairs() {
    set<tuple<ll, ll, ll>> res;
    ll dest, src, range;
    string word;

    while ( getline(cin, word) && word != "" ) {
        stringstream ss(word);
        ss >> dest >> src >> range;
        res.emplace(src, dest, range);
    }
    return res;
}

void mapSeed( ll &u, ll v, ll src, ll dest, ll range, set<pair<ll, ll>> &newSeeds ) {
    ll u2 = max(u, src);
    ll v2 = min(v, src + range - 1);
    if (u2 > u) {
        newSeeds.emplace(u, src - 1);
    }
    if (u2 <= v2) {
        newSeeds.emplace(u2 + dest - src, v2 + dest - src);
    }
    
    u = v2 + 1;
}

void mapAllSeeds( ll u, ll v, set<tuple<ll, ll, ll>> &mapping, set<pair<ll, ll>> &newSeeds ) {
    auto it = mapping.upper_bound({u + 1, -1, -1});
    if (it != mapping.begin()) {
        it--;
    }

    while (it != mapping.end()) {
        ll source, dest, range;
        tie(source, dest, range) = *it;
        if (source > v) break;

        mapSeed(u, v, source, dest, range, newSeeds);
        ++it;
    }

    if (u < v) {
        newSeeds.emplace(u + 1, v);
    }
}

int main ( ) {
    string line;
    getline(cin, line);
    loadSeeds(line);

    getline(cin, line);

    for ( int i = 0; i < 7; i++ ) {
        getline(cin, line);
        auto m = loadPairs();
        set<pair<ll, ll>> newSeeds;

        for (auto &p: seeds) {
            mapAllSeeds(p.first, p.second, m, newSeeds);
        }
        seeds = newSeeds;
    }

    ll result = UINT64_MAX;
    for ( auto&s : seeds )
        result = min(s.first, result);

    cout << "Res: " << result << endl;

    return 0;
}
