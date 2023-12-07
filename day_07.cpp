#include<stdio.h>
#include<iostream>
#include<vector>
#include<set>
#include<map>
#include<string>
#include<sstream>
#include<algorithm>

using namespace std;
using ll = unsigned long long;
vector<pair<string, int>> cards;
/*
0 - High card 
1 - One pair
2 - Two pair
3 - One triple
4 - Fullhouse
5 - Quadra
6 - Penta
*/
static string ranking1 = "23456789TJQKA";
static string ranking2 = "J23456789TQKA";

bool cmpCards( string& card1, string& card2, string& ranking ) {
    for (int i = 0; i < 5; ++i) {
        if (card1[i] != card2[i]) {
            return ranking.find(card1[i]) < ranking.find(card2[i]);
        }
    }
    return 0;
}

int countRank1( string& card ) {
    map<char, int> uc;
    for ( char c: card ) {
        uc[c]++;
    }
    if ( uc.size() == 1 ) return 6;
    if ( uc.size() == 2 ) {
        if ( uc[card[0]] == 4 || uc[card[1]] == 4 ) return 5;
        return 4;
    }
    if ( uc.size() == 3 ) {
        if ( uc[card[0]] == 3 || uc[card[1]] == 3 || uc[card[2]] == 3 ) return 3;
        return 2;
    }
    if ( uc.size() == 4 ) return 1;
    return 0;
}

int countRank2( string& card, int recIndex ) {
    if ( recIndex == 5 ) return countRank1(card);
    if ( card[recIndex] != 'J') return countRank2(card, recIndex + 1);

    int res = -1;
    for ( int i = 1; i < ranking2.length(); i++) {
        card[recIndex] = ranking2[i];
        res = max(res, countRank2(card, recIndex + 1));
    }
    card[recIndex] = 'J';
    return res;
}

bool cmp1( pair<string, int>& card1, pair<string,int>& card2 ) {
    int rank1 = countRank1(card1.first);
    int rank2 = countRank1(card2.first);

    if (rank1 == rank2) {
        return cmpCards(card1.first, card2.first, ranking1);
    }
    return rank1 < rank2;
}

bool cmp2( pair<string, int>& card1, pair<string,int>& card2 ) {
    int rank1 = countRank2(card1.first, 0);
    int rank2 = countRank2(card2.first, 0);

    if (rank1 == rank2) {
        return cmpCards(card1.first, card2.first, ranking2);
    }
    return rank1 < rank2;
}

int main ( void ) {
    string line, card;
    int bet;

    while( getline(cin, line) ) {
        if ( line.empty() ) break;

        istringstream ss(line);
        ss >> card >> bet;
        cards.emplace_back(card, bet);
    }

    int res = 0;
    sort(cards.begin(), cards.end(), cmp1);
    for ( int i = cards.size()-1; i >= 0; i-- ) {
        //cout << cards[i].first << " " << cards[i].second << endl;
        res += ((i+1)*cards[i].second);
    }
    cout << "Res1: " << res << endl;
    res = 0;

    sort(cards.begin(), cards.end(), cmp2);
    for ( int i = cards.size()-1; i >= 0; i-- ) {
        //cout << cards[i].first << " " << cards[i].second << endl;
        res += ((i+1)*cards[i].second);
    }
    cout << "Res2: " << res << endl;
}