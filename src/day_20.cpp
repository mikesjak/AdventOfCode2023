#include <iostream>
#include <vector>
#include <cmath>
#include <numeric>
#include <algorithm>
#include <set>
#include <unordered_set>
#include <cstring>
#include <unordered_map>
#include <iomanip>
#include <queue>
#include <numeric>
#include <map>
#include <sstream>
#include <cassert>

using ll = long long;
using ld = double;

#define int ll

using namespace std;

// Needs to be stored without first letter due to implementation of loadNode
const string start = "roadcaster";
const string lastNode = "jz";

/**
 * Struct to store single node
 */
struct Node {
    string m_Name;
    char m_Type{};
    bool m_IsOn = false;
    vector<string> m_Adj;
    map<string, bool> m_Input;
};

map<string, Node*> m;

/**
 * Function traversing through graph using BFS
 * @param target node where to stop
 * @return found, low, high
 */
vector<int> bfs( const string& target ) {
    queue<pair<bool, pair<string, string>>> q;
    q.emplace(1, make_pair(start, ""));

    int cntLow = 0, cntHigh = 0;

    while ( !q.empty() ) {
        string currName, prevName;
        bool low;
        low = q.front().first;
        currName = q.front().second.first;
        prevName = q.front().second.second;
        q.pop();

        if ( low ) cntLow++;
        else cntHigh++;
        if ( currName == lastNode && prevName == target && !low ) {
            return {1, 0, 0};
        }

        if ( m.count(currName) == 0 )
            continue;
        Node *currNode = m[currName];

        if ( currNode->m_Type == 'b' ) {
            for (string &n: currNode->m_Adj) {
                q.emplace(low, make_pair(n, currName));
            }
        }
        else if ( currNode->m_Type == '%' ) {
            if ( low ) {
                currNode->m_IsOn = !currNode->m_IsOn;
                for (string &n: currNode->m_Adj) {
                    q.emplace(!currNode->m_IsOn, make_pair(n, currName));
                }
            }
        }
        else {
            currNode->m_Input[prevName] = !low;
            bool allHigh = true;
            for ( auto& n : currNode->m_Input ) {
                if ( !n.second ) {
                    allHigh = false;
                    break;
                }
            }
            for ( string &n: currNode->m_Adj ) {
                q.emplace(allHigh, make_pair(n, currName));
            }
        }
    }
    return {0, cntLow, cntHigh};
}

/**
 * Load single node
 * @param line string to be parsed
 */
void readNode( string &line ) {
    istringstream ss(line);
    Node* node = new Node();

    ss >> node->m_Name;
    node->m_Type = node->m_Name[0];
    node->m_Name = node->m_Name.substr(1,node->m_Name.length()-1);

    string n;
    ss >> n;
    while ( ss >> n ) {
        if ( n.back() == ',' )
            n.pop_back();
        node->m_Adj.emplace_back(n);
    }
    m[node->m_Name] = node;
}

/**
 * Initialize graph before BFS
 * @param name
 * @param v
 */
void initGraph( const string &name, set<string> &v ) {
    v.insert(name);

    auto node = m[name];
    if ( node->m_Type == '%' )
        node->m_IsOn = false;

    for (auto &n: node->m_Adj) {
        if ( !m.count(n) )
            continue;
        if ( m[n]->m_Type == '&' ) {
            m[n]->m_Input[name] = false;
        }
        if ( !v.count(n) )
            initGraph(n, v);
    }
}

/**
 * Wrapper function to solve part 1
 * @return solution to part 1
 */
ll solvePart1() {
    set<string> v;
    int low, high;
    ll sumLow = 0, sumHigh = 0;

    initGraph(start, v);

    for (int i = 1; i <= 1000; ++i) {
        vector<int> res = bfs("?");
        low = res[1];
        high = res[2];
        sumLow += low;
        sumHigh += high;
    }

    return sumLow * sumHigh;
}

/**
 * Wrapper function to solve part 2
 * Very slow
 * @return solution to part 2
 */
ll solvePart2() {
    ll res = 1;
    for (auto &name: {"dh", "mk", "rn", "vf"}) {
        set<string> visited;
        int cnt = 0;

        initGraph(start, visited);

        while ( true ){
            vector<int> tmp = bfs(name);
            if ( tmp[0] == 1 ) break;
            cnt++;
        }
        res *= cnt + 1;
    }
    return res;
}

signed main() {
    string line;
    freopen("in.txt", "r", stdin);

    int res1 = 0,
        res2 = 0;

    while ( getline(cin, line) ) {
        readNode(line);
    }

    res1 = solvePart1();
    cout << "Part1: " << res1 << endl;
    res2 = solvePart2();
    cout << "Part2: " << res2 << endl;
}