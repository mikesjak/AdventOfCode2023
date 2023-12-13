#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>

using namespace std;

static vector<int> lineNums;
static vector<string> words = {"one", "two", "three", "four", "five", "six", "seven", "eight", "nine"};

bool isANumber( char n ) {
    return n >= 48 && n <= 57;
}

void handleLine( string& line ) {
    vector<int> nums;

    for ( int i = 0; i < line.length(); i++ ) {
        if ( isANumber(line[i]) ) {
            int tmp = (int)line[i]-48;
            nums.push_back(tmp);    
        } 
        else {
            for ( int s = 0; s < words.size(); s++ ) {
                for ( int l = 3; l <= 5; l++ ) {
                    if ( line.substr(i, l) == words[s] ) {
                        nums.push_back(s+1);
                    }
                }
            }
        }
    }

    int lineNum = 10*nums[0] + nums[nums.size()-1];
    lineNums.push_back(lineNum);
}

int main ( ) { 

    string line;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        cout << line << endl;
        handleLine(line);
    }

    int res = 0;
    for ( auto& n : lineNums ) res += n;
    cout << "Result: " << res << endl;
}
