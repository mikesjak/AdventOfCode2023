#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>

using namespace std;
using ll = unsigned long long;
vector<ll> times, distances;

int findWaysToWin( int time, int distToReach ) {
    float c = pow((pow(time, 2) - (4*distToReach)), 0.5);
    cout << "C: " << c << endl;
    float xMin = (time-c)/2;
    float xMax = (time+c)/2;
    cout << "Min: " << xMin << ", Max: " << xMax << endl;;

    return floor(xMax) - ceil(xMin) - 1;
}

vector<ll> handleLine( string& line ) {
    istringstream ss(line);
    vector<ll> vec;
    string tmp;
    ll val;

    ss >> tmp;
    while( ss >> val ) {
        vec.push_back(val);
    }
    return vec;
}

int main ( ) {
    string line;
    // Time
    getline(cin, line);
    times = handleLine(line);
    // Distances
    getline(cin, line);
    distances = handleLine(line);

    ll res = 0;
    vector<ll> ways;
    for ( int i = 0; i < times.size()-1; i++ ) {
        res = findWaysToWin(times[i], distances[i]);
        ways.push_back(res);
    }

    res = 0;
    for ( auto&w : ways ) {
        if ( res == 0 ) res = w;
        else res *= w;
    }

    cout << "Res: " << endl;
}