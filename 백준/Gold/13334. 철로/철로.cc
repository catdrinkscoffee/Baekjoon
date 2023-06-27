#include <iostream>
#include <queue>
#include <algorithm>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

int N;

struct rail
{
    int st, en;
    
    bool operator<(const rail& a) const
    {
        return st > a.st;
    }
};

bool comparebyst(const rail& a, const rail& b)
{
    return a.st < b.st;
}

bool comparebyen(const rail& a, const rail& b)
{
    return a.en < b.en;
}

vector<rail> coord;

int main()
{
    int railLength;
    cin >> N;
    for1(i, N)
    {
        int a, b;
        cin >> a >> b;
        if(a > b) swap(a, b);
        coord.push_back(rail{a, b});
    }
    cin >> railLength;
    
    sort(coord.begin(), coord.end(), comparebyst);
    vector<int> stinfo;
    for1(i, coord.size())
    {
        int j = i + 1;
        while (j < coord.size() && coord[j].st == coord[i].st) j++;
        stinfo.push_back(coord[i].st);
        i = j - 1;
    }
    
    sort(coord.begin(), coord.end(), comparebyen);
    
    priority_queue<rail> pq;
    
    int enidx = 0;
    int ans = 0;
    for1(i, stinfo.size())
    {
        int railst = stinfo[i];
        int railen = stinfo[i] + railLength;
        while (enidx < coord.size() && coord[enidx].en <= railen)
        {
            if(coord[enidx].st >= railst) pq.push(coord[enidx]);
            enidx++;
            if(enidx >= coord.size()) break;
        }
        ans = max(ans, (int)pq.size());
        
        while (!pq.empty() && pq.top().st <= railst) pq.pop();
    }
    
    cout << ans;
    return 0;
}
