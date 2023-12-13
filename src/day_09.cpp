#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>
#include <numeric>

using namespace std;
using ll = unsigned long long;

int countRes( vector<ll>& vec, bool part2 ) {
    bool z = true;
    for ( auto& n : vec ) {
        if ( n != 0 ) {
            z = false;
            break;
        }
    }
    if ( z ) return 0;

    vector<ll> diffs;
    for ( int i = 1; i < vec.size(); i++ ) {
        diffs.emplace_back(vec[i]-vec[i-1]);
    }

    if ( !part2 ) {
        return vec.back() + countRes(diffs, false);
    }
    else {
        return vec[0] - countRes(diffs, true);
    }
}

int main ( ) {
    string line;
    ll res1 = 0, 
        res2 = 0;
    ll tmp;

    while( getline(cin, line) ) {
        if ( line.empty() ) break;

        istringstream ss(line);
        vector<ll> nums;
        while( ss >> tmp ) {
            nums.push_back(tmp);
        }
        res1 += countRes(nums, false);
        res2 += countRes(nums, true);
    }

    cout << "Res1: " << res1 << endl;
    cout << "Res2: " << res2 << endl;
}