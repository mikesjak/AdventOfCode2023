#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include <sstream>

using namespace std;

static map<int, map<string, int>> games;

static int res = 0;
static int res2 = 0;

void handleGames( string& game ) {
    istringstream ss(game);
    string word;

    ss >> word >> word;
    int id = stoi(word);

    int amount;

    while ( ss >> amount >> word ) {
        if ( word.back() == ',' || word.back() == ';' ) word = word.substr(0, word.length() - 1);
        games[id][word] = max(games[id][word], amount);
    }

    if ( games[id]["red"] <= 12 && games[id]["green"] <= 13 && games[id]["blue"] <= 14 ) {
            res += id;
    }
    res2 += games[id]["red"] * games[id]["green"] * games[id]["blue"];
}

int main ( ) {

    string line;

    while ( getline(cin, line) ) {
        if ( line.empty() ) break;
        handleGames(line);
        cout << res << " - " << res2 << endl;
    }

    cout << "Games possible: " << res << endl;
    cout << "Power of games: " << res2 << endl;
} 