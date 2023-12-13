#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>

using namespace std;
using ll = unsigned long long;

static vector<ll> seeds;

bool isNumber( char n ) {
    return n >= 48 && n <= 57;
}

void loadSeeds( string& line ) {
    istringstream ss(line);
    string seed, range;
    ss >> seed;

    cout << "Seeds: ";
    while( ss >> seed >> range ) {
        for ( int i = 0; i < stoll(range); i++ )
            seeds.push_back(stoll(seed)+1);
        cout << seeds[seeds.size()-1] << " ";
    }
    cout << endl;
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

ll mapSeed( set<tuple<ll, ll, ll>>& m, ll seed ) {
    auto it = m.upper_bound({seed+1, -1, -1});
    ll src, dest, range;

    if ( it == m.begin() ) return seed;
    it--;

    tie(src, dest, range) = *it;
    if ( seed < src + range ) return seed + dest - src;
    return seed;
}

int main ( ) {
    string line;
    getline(cin, line);
    loadSeeds(line);

    getline(cin, line);

    for ( int i = 0; i < 7; i++ ) {
        getline(cin, line);
        auto m = loadPairs();
        
        for ( auto& s : seeds ) {
            s = mapSeed(m, s);
        } 
    }

    ll result = UINT64_MAX;
    for ( auto&s : seeds )
        result = min(s, result);

    cout << "Res: " << result << endl;

    return 0;
}
