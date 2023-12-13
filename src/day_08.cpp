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
static string guide;

map<string, pair<string, string>> m;

int countSteps() {
    int i = 0,
        res = 0;
    string curr = "AAA";
    while ( curr != "ZZZ" ) {
        char nextStep = guide[i];

        if ( nextStep == 'L' ) curr = m[curr].first;
        else curr = m[curr].second;

        res++;
        i = (i+1)%guide.size();
    }
    return res;
}

int countSteps2( string& start ) {
    int i = 0,
        res = 0;
    string curr = start;
    while ( curr.back() != 'Z' ) {
        char nextStep = guide[i];

        if ( nextStep == 'L' ) curr = m[curr].first;
        else curr = m[curr].second;

        res++;
        i = (i+1)%guide.size();
    }
    return res;
}

int main ( ) {
    vector<string> v;
    string line, word;
    getline(cin, line);
    guide = line;
    getline(cin, line);

    while( getline(cin, line) ) {
        if ( line.empty() ) break;
        string src = line.substr(0, 3), 
             destL = line.substr(7, 3),
             destR = line.substr(12,3);

        m[src] = {destL, destR};
        if ( src.back() == 'A' ) v .push_back(src); 
        cout << src << " " << destL << " " << destR << endl;
    }

    ll res2 = 0;
    for ( auto& n : v ) {
        ll tmp = countSteps2(n);
        if ( res2 == 0 ) {
            res2 = tmp;
        }
        else {
            res2 = lcm(tmp, res2);
        }
    }

    cout << "Res: " << countSteps() << endl;
    cout << "Res2: " << res2 << endl;
}