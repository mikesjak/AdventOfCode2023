#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>

using namespace std;

static long long res = 0;
static map<int, int> copies;

int handleCard( string& card ) {
    vector<string> wn;

    int worth = 0,
        matches = 0;
    
    istringstream ss(card);
    string word;

    ss >> word >> word;
    int id = stoi(word);
    copies[id] ++;

    //cout << "ID: " << id << ", copies: " << copies[id] << endl;

    // Load winning numbers
    while ( ss >> word ) {
        if ( word == "|" ) break;
        wn.push_back(word);
    }

    // Handle chosen numbers
    while ( ss >> word ) {
        for ( auto& n : wn ) {
            if ( n == word ) {
                if ( worth == 0 ) worth++;
                else worth *= 2;
                matches++;
                break;
            }
        }
    }

    // Handle copies
    for ( int i = 1; i <= matches; i++ ) {
        copies[id+i] += copies[id];
        //cout << "Adding " << copies[id] << " copies to " << id+i << endl;
    }

    return worth;
}

int main ( void ) {
    string line;
    int res2 = 0;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        res += handleCard(line);
    }

    for ( auto& c : copies )
        res2 += c.second;

    cout << "Res: " << res << endl;
    cout << "Copies: " << res2 << endl;

    return 0;
}
