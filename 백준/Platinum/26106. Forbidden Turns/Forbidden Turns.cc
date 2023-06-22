#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
#include <fstream>
#include <set>
#include <limits>

using namespace std;
const int limit = numeric_limits<int>::max();

int edge_cnt, vertex_cnt, forbidden_turns_cnt;
int source, destination;
int ans = limit;

struct mynode {
    int to;
    int cost;
};

struct abc {
    int a, b, c;
    bool operator<(const abc& rhs) const {
        if(a == rhs.a && b == rhs.b) return c < rhs.c;
        if(a == rhs.a) return b < rhs.b;
        return a < rhs.a;
    }
};

struct djnode {
    int cost;
    abc subroutine;
};
struct compare{
    bool operator()(const djnode& lhs, const djnode& rhs) {
        return lhs.cost > rhs.cost;
    }
};

set<abc> forbidden_turns;
set<abc> used_turns;

vector<vector<mynode> > graph;
vector<int> min_cost;

void solve()
{
    priority_queue<djnode, vector<djnode>, compare> pq;
    pq.push(djnode{0, abc{-1, -1, source}});
    min_cost[source] = 0;
    while (!pq.empty()) {
        djnode front = pq.top();
        pq.pop();
        
        abc abc = front.subroutine;
//        cout << " cost : " << front.cost;
//        cout << " abc : " << abc.a << " " << abc.b << " " << abc.c << endl;
    
        int tmpc = abc.c;
        
        abc.a = abc.b;
        abc.b = abc.c;
        
        for(int i = 0; i < graph[tmpc].size(); ++i)
        {
            mynode to = graph[tmpc][i];
            abc.c = to.to;
            if(forbidden_turns.find(abc) != forbidden_turns.end()) continue;
            
            int herecost = to.cost + front.cost;
            if(used_turns.find(abc) == used_turns.end())
            {
                used_turns.insert(abc);
                pq.push(djnode{herecost, abc});
            }
            if(min_cost[to.to] > herecost)
            {
                min_cost[to.to] = herecost;
//                pq.push(djnode{herecost, abc});
            }
           
        }
    }
    
    if(min_cost[destination] == limit) cout << -1;
    else cout << min_cost[destination];
}

int main()
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    //freopen("/Users/ijuheon/Desktop/cpp/ps/ps/input.txt", "r", stdin);
    
    cin >> edge_cnt >> vertex_cnt >> forbidden_turns_cnt;
    cin >> source >> destination;
    
    graph.resize(vertex_cnt);
    min_cost.resize(vertex_cnt, limit);
    
    int from, to, cost;
    for(int i = 0; i < edge_cnt; ++i)
    {
        cin >> from >> to >> cost;
        graph[from].push_back(mynode{to, cost});
    }
    
    int a, b, c;
    for(int i = 0; i < forbidden_turns_cnt; ++i)
    {
        cin >> a >> b >> c;
        forbidden_turns.insert(abc{a, b, c});
    }
    
    solve();
    cout << endl;
    return 0;
}
