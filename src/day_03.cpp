#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>

using namespace std;

bool isANumber( char n ) {
    return n >= 48 && n <= 57;
}

static vector<char> notSymbols = { '0', '1', '2', '3', '4', '5', '6', '7', '8', '9', '.' };

static vector< vector<char>> m;
static map< pair<int,int>, set<int> > mp;

void loadMatrix () {
    string line;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        vector<char> tmp;
        for ( auto& c : line ) tmp.push_back(c);
        
        m.push_back(tmp);
    }
}

bool isSymbol( char c ) {
    for ( auto& ns : notSymbols ) {
        if ( c == ns ) {
            return false;
        }
    }
    return true;
}

set<pair<int, int>> handleNeighbours( int r, int c ) {
    set<pair<int, int>> res;
    cout << "Testing:" << r << " " << c << endl;
    // Up
    if ( r != 0 && isSymbol(m[r-1][c]) ) res.insert({r-1, c});
    // Down
    if ( r != m.size()-1 && isSymbol(m[r+1][c]) ) res.insert({r+1, c});
    // Left
    if ( c != 0 && isSymbol(m[r][c-1]) ) res.insert({r, c-1});
    // Right
    if ( c != m[r].size()-1 && isSymbol(m[r][c+1]) ) res.insert({r, c+1});
    // Up Left
    if ( c != 0 && r != 0 && isSymbol(m[r-1][c-1]) ) res.insert({r-1,c-1});
    // Up Right
    if ( c != m[r].size()-1 && r != 0 && isSymbol(m[r-1][c+1]) ) res.insert({r-1,c+1});
    // Down Left
    if ( c != 0 && r != m.size()-1 && isSymbol(m[r+1][c-1]) ) res.insert({r+1,c-1});
    // Down Right
    if ( c != m[r].size()-1 && r != m.size()-1 && isSymbol(m[r+1][c+1]) ) res.insert({r+1,c+1});

    if ( !res.empty() ) cout << "Found symbol!" << endl;

    return res;
}

int main ( ) {
    loadMatrix();

    long long r1 = 0;
    long long r2 = 0;

    for ( int r = 0; r < m.size(); r++ ) {
        set<pair<int, int>> metSymbolsCoords; 
        for ( int c = 0; c < m[r].size(); c++ ) {
            metSymbolsCoords.clear();

            while ( c < m[r].size() && !isANumber(m[r][c]) ) {
                c++;
            }
            if ( c >= m[r].size() ) break;

            int s = c;
            int e = c;
            bool metSymbol = false;


            // Handling one number
            while ( c <= m[r].size()-1 && isANumber(m[r][c]) ) {
                set<pair<int, int>> tmp = handleNeighbours(r, c);
                for ( auto& p : tmp ){
                    metSymbolsCoords.insert(p);
                }
                if ( !metSymbolsCoords.empty() ) metSymbol = true;
                e++;
                c++;
            }
            e--;

            if ( metSymbol ) {
                int num = 0;
                int p = 0;
                for ( int i = e; i >= s; i-- ) {
                    num += pow(10, p)*(stoi(to_string(m[r][i]))-48);
                    p++;
                }

                cout << "Adding: " << num << endl;
                r1 += num;

                for ( auto& smb : metSymbolsCoords ) {
                    if ( m[smb.first][smb.second] == '*' ) mp[smb].insert(num);
                }
            }
        }
    }

    for ( auto& s : mp ) {
        cout << s.first.first << " " << s.first.second << " " << s.second.size() << endl;;
        if ( s.second.size() == 2 ) {
            int tmp = 0;
            for ( auto& n : s.second )
                if ( tmp == 0 ) tmp = n;
                else tmp *= n; 
            r2 += tmp;
        }
    }

    cout << "Part1: " << r1 << endl;
    cout << "Part2: " << r2 << endl;
}