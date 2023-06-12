#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <queue>
#include <fstream>

using namespace std;

struct dungeon {
    bool available[4] = {false, false, false, false};
    int availablecnt = 0;
};

struct coord {
    int r, c;
};

struct node {
    int direction;
    coord subtreeRoot;
    int depth;
};

int dir[4][2] = { {1, 0}, {-1, 0}, {0, 1}, {0, -1} };
int ans = 0;
int h, w;
vector<vector<bool>> visited;
vector<vector<bool>> route;
vector<vector<node>> subtreeRootandDepth;
vector<vector<dungeon>> castle;

bool can_construct(int r, int c, int firstr, int firstc) {
    node firstnode = subtreeRootandDepth[firstr][firstc];
    int tmpr = r;
    int tmpc = c;
    // direction이 일정한 것이 아니다.
    // 내려가면서 갱신될 때만 갱신해줘야 한다.
    while (firstnode.depth < subtreeRootandDepth[tmpr][tmpc].depth) {
        coord tmpnode = subtreeRootandDepth[tmpr][tmpc].subtreeRoot;
        if(subtreeRootandDepth[tmpr][tmpc].direction == firstnode.direction &&
           subtreeRootandDepth[tmpr][tmpc].subtreeRoot.r == firstnode.subtreeRoot.r &&
           subtreeRootandDepth[tmpr][tmpc].subtreeRoot.c == firstnode.subtreeRoot.c &&
           firstnode.depth < subtreeRootandDepth[tmpr][tmpc].depth) return false;
        tmpr = subtreeRootandDepth[tmpnode.r][tmpnode.c].subtreeRoot.r;
        tmpc = subtreeRootandDepth[tmpnode.r][tmpnode.c].subtreeRoot.c;
    }
    
    while (subtreeRootandDepth[r][c].depth > 1) {
        coord tmpsubtree = subtreeRootandDepth[r][c].subtreeRoot;
        if(route[tmpsubtree.r][tmpsubtree.c] || route[r][c]) return false;
        
        r = subtreeRootandDepth[tmpsubtree.r][tmpsubtree.c].subtreeRoot.r;
        c = subtreeRootandDepth[tmpsubtree.r][tmpsubtree.c].subtreeRoot.c;
    }
    
    return true;
}

void make_tree(int r, int c, int height, coord subtreeRoot, int direction, bool isroot)
{
    subtreeRootandDepth[r][c].subtreeRoot = subtreeRoot;
    subtreeRootandDepth[r][c].direction = direction;
    
    bool flag = false;
    if (castle[r][c].availablecnt > 2 || isroot)
    {
        subtreeRoot.r = r;
        subtreeRoot.c = c;
        flag = true;
    }

    subtreeRootandDepth[r][c].depth = height;

    for (int k = 0; k < 4; ++k)
    {
        int nr = r + dir[k][0];
        int nc = c + dir[k][1];

        if (nr < 1 || nr > h || nc < 1 || nc > w) continue;
        if (subtreeRootandDepth[nr][nc].depth > 0) continue;

        if (castle[r][c].available[k])
        {
            if(flag) make_tree(nr, nc, height + 1, subtreeRoot, k, false);
            else make_tree(nr, nc, height + 1, subtreeRoot, direction, false);
        }
    }
}

void traverse_tree(int r, int c, int height)
{
    if (r == h && c == w) return;
    visited[r][c] = true;
    route[r][c] = true;

    for (int k = 0; k < 4; ++k) {
        int nr = r + dir[k][0];
        int nc = c + dir[k][1];

        if (nr < 1 || nr > h || nc < 1 || nc > w) continue;

        if (castle[r][c].available[k])
        {
            if (visited[nr][nc]) continue;
            traverse_tree(nr, nc, height + 1);
        }
        else {
            if (route[nr][nc]) continue;
            if (height + subtreeRootandDepth[nr][nc].depth <= ans) continue;
            if (!can_construct(nr, nc, r, c)) continue;
            
            ans = height + subtreeRootandDepth[nr][nc].depth;
        }
    }

    route[r][c] = false;
}

void solve()
{
    subtreeRootandDepth.resize(h + 1, vector<node>(w + 1, node{ 0, coord{0, 0}, 0 }));

    make_tree(h, w, 1, coord{ h, w }, -1, true);

    ans = subtreeRootandDepth[1][1].depth;

    visited.resize(h + 1, vector<bool>(w + 1, false));
    route.resize(h + 1, vector<bool>(w + 1, false));

    traverse_tree(1, 1, 1);
}

int main() {
    //freopen("/Users/ijuheon/Desktop/cpp/ps/ps/input.txt", "r", stdin);
    cin >> h >> w;

    castle.resize(h + 1, vector<dungeon>(w + 1));

    vector<string> castleInfo(2 * h + 1, string(2 * w + 1, ' '));
    for (int i = 0; i < 2 * h + 1; ++i)
        for (int j = 0; j < 2 * w + 1; ++j)
            cin >> castleInfo[i][j];

    for (int i = 1; i < 2 * h; i += 2) {
        for (int j = 1; j < 2 * w; j += 2) {

            for (int k = 0; k < 4; ++k) {
                int ni = i / 2 + 1;
                int nj = j / 2 + 1;

                int nr = i + dir[k][0];
                int nc = j + dir[k][1];

                if (nr >= 2 * h || nr < 1 || nc >= 2 * w || nc < 1) continue;

                if (castleInfo[nr][nc] == '.')
                {
                    castle[ni][nj].available[k] = true;
                    ++castle[ni][nj].availablecnt;
                }
            }
        }
    }

    solve();
    cout << ans;

    return 0;
}
