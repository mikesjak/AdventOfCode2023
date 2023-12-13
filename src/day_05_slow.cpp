#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>

using namespace std;

map<unsigned long long, map<unsigned long long, unsigned long long>> pairs;
map<unsigned long long, map<unsigned long long, bool>> marked;
vector<unsigned long long> seeds;

static pair<string, string> last;
static unsigned long long ind = 0;

bool isNumber( char n ) {
    return n >= 48 && n <= 57;
}

void loadSeeds( string& line ) {
    istringstream ss(line);
    string word;
    ss >> word;

    cout << "Seeds: ";
    while( ss >> word ) {
        cout << word;
        seeds.push_back(stoll(word));
    }
    cout << endl;
}

void handleLine( string& line ) { 
    // Handle num
    if ( isNumber(line[0]) ) {
        istringstream ss(line);
        string word;
        unsigned  drs, srs, r;

        ss >> word;
        drs = stoll(word);
        ss >> word;
        srs = stoll(word);
        ss >> word;
        r = stoll(word);

        for ( int i = 0; i < r; i++ ) {
            pairs[ind][srs+i] = drs+i;
            marked[ind][srs+i] = true;
        }
        
    } // Handle string
    else {
        string tmp, src, dest;
        for ( int i = 0; i < line.length()-1; i++ ) { 
            if ( line[i] == '-' ) {
                src = tmp;
                tmp = "";
                i += 4;
            }
            if ( line[i] == ' ' ) break;
            tmp.append(line, i, 1);
        }
        dest = tmp;

        last = {dest, src};
        if ( src != "seed" ) ind++;
    }
}

int handleSeeds() {
    unsigned long long lowest = UINT_FAST64_MAX;
    for ( auto& s : seeds ) {
        int n = s;

        for ( int i = 0; i <= ind; i++ ) {
            cout << n << ", ";
            if ( !marked[i][n] )
                n = n;
            else
                n = pairs[i][n]; 
        }
        cout << n << endl;
        if ( n < lowest ) lowest = n;
    }
    return lowest;
}

int main ( ) {
    string line;
    getline(cin, line);
    loadSeeds(line);

    while ( getline(cin, line) ) {
        if ( line.empty() ) {
            getline(cin,line);
            if ( line.empty() ) break;             
        }
        handleLine(line);
    }

    cout << "Part1: " << handleSeeds() << endl;;

    return 0;
}
