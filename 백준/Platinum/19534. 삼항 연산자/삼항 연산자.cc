//#include <bits/stdc++.h>
#include <iostream>
#include <vector>
#include <stack>

#define for1(i, n) for(int i = 0; i < n; i++)
#define for2(i, from, to) for(int i = from; i < to; i++)
using namespace std;

int ans = 0;
int N;
string str;

struct node {
    bool isleaf;
    bool flag;
    int left, right;
    int leaf;

    node* next_node_ok = nullptr;
    node* next_node_not_ok = nullptr;
};

node* root;
node leaves[28];

int getindex(char ch)
{
    if (ch >= 'a' && ch <= 'z') return ch - 'a';
    if (ch == '0') return 26;
    else return 27;
}

void makeGraph()
{
    stack<char> op;
    stack<node*> v, v_cache;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '=' || str[i] == ':' || str[i] == '?') op.push(str[i]);
        else v.push(&leaves[getindex(str[i])]);
    }

    while (!op.empty() || !v.empty())
    {
        if(!v.empty())
        {
            node* v_tmp = v.top();
            v_cache.push(v_tmp);
            root = v_tmp;
            v.pop();
        }
        
        char op_tmp = ' ';
        if(!op.empty())
        {
            op_tmp = op.top();
            op.pop();
        }

        if (op_tmp == '=')
        {
            node* v_another_tmp = v.top();
            v_cache.push(v_another_tmp);
            v.pop();

            node* node_not_leaf = new node;

            node_not_leaf->isleaf = false;
            node_not_leaf->left = v_cache.top()->leaf;
            v_cache.pop();
            node_not_leaf->right = v_cache.top()->leaf;
            v_cache.pop();
            node_not_leaf->next_node_ok = v_cache.top();
            v_cache.pop();
            node_not_leaf->next_node_not_ok = v_cache.top();
            v_cache.pop();

            root = node_not_leaf;
            v.push(node_not_leaf);
        }
    }
}

void dfs(int x, vector<bool>& visited, vector<vector<int> >& graph)
{
    visited[x] = true;
    
    for(int i = 0; i < 28; i++)
    {
        if(graph[x][i] && !visited[i])
        {
            dfs(i, visited, graph);
        }
    }
}

int getcasecnt(vector<vector<vector<int> > >& conditions)
{
    vector<vector<int> > graph;
    graph.resize(28, vector<int> (28, 0));
    for(int i = 0; i < 28; i++)
    {
        for(int j = 0; j < 2; j++)
        {
            for(int k = 0; k < 28; k++)
            {
                if(conditions[i][j][k])
                {
                    graph[i][k] = 1;
                    graph[k][i] = 1;
                }
            }
        }
    }
    
    int ret = 1;
    vector<bool> visited(28, false);

    dfs(26, visited, graph);
    dfs(27, visited, graph);
    
    for (int i = 0; i < N; i++)
    {
        if (!visited[i])
        {
            dfs(i, visited, graph);
            ret *= 2;
        }
    }
    return ret;
}

void promising_dfs(int flag,
                   int cand,
                   int x,
                   vector<bool>& visited,
                   vector<vector<vector<int> > >& conditions,
                   bool* ret)
{
    visited[x] = true;
    if(conditions[x][flag == 0 ? 1 : 0][cand]) *ret = false;
    if(!*ret) return;
    
    for(int y = 0; y < 28; y++)
    {
        if(!visited[y] &&
           conditions[x][0][y])
        {
            promising_dfs(flag == 0 ? 1 : 0, cand, y, visited, conditions, ret);
        }
        if(!visited[y] &&
           conditions[x][1][y])
        {
            promising_dfs(flag == 1 ? 1 : 0, cand, y, visited, conditions, ret);
        }
        
    }
}

bool chk_if_promising(int falg, int left, int right, vector<vector<vector<int> > >& conditions)
{
    bool ret = true;
    vector<bool> visited(28, false);
    promising_dfs(falg, left, right, visited, conditions, &ret);
    return ret;
}

void traversal(node* curNode, vector<vector<vector<int> > > conditions)
{
    if (curNode->isleaf)
    {
//        cout << "leaf : " << curNode->leaf << '\n';
        if (curNode->leaf != 27)
        {
            if(curNode->leaf == 26)
            {
                ans += getcasecnt(conditions);
                return;
            }
            
            if(!conditions[curNode->leaf][1][27] &&
               chk_if_promising(1, curNode->leaf, 26, conditions))
            {
                //a==b?b==1?a:b:b에서 a==b -> b==1 -> a==0에서 모순이 발생하는데 이를 고려 못함
                conditions[26][1][curNode->leaf] = 1;
                conditions[curNode->leaf][1][26] = 1;
                ans += getcasecnt(conditions);
                return;
            }
        }
        return;
    }

    if (curNode->left >= 26 && curNode->right >= 26)
    {
        if (curNode->left == curNode->right) traversal(curNode->next_node_ok, conditions);
        else traversal(curNode->next_node_not_ok, conditions);
    }
    
    else
    {
        if (chk_if_promising(1, curNode->left, curNode->right, conditions))
        {
            vector<vector<vector<int> > > next_conditions = conditions;
            next_conditions[curNode->left][1][curNode->right] = 1;
            next_conditions[curNode->right][1][curNode->left] = 1;
            if(curNode->left == 26)
            {
                next_conditions[curNode->right][0][27] = 1;
                next_conditions[27][0][curNode->right] = 1;
            }
            if(curNode->right == 26)
            {
                next_conditions[curNode->left][0][27] = 1;
                next_conditions[27][0][curNode->left] = 1;
            }
            if(curNode->left == 27)
            {
                next_conditions[curNode->right][0][26] = 1;
                next_conditions[26][0][curNode->right] = 1;
            }
            if(curNode->right == 27)
            {
                next_conditions[curNode->left][0][26] = 1;
                next_conditions[26][0][curNode->left] = 1;
            }
            traversal(curNode->next_node_ok, next_conditions);

        }

        if (curNode->left != curNode->right &&
            chk_if_promising(0, curNode->left, curNode->right, conditions))
        {
            vector<vector<vector<int> > > next_conditions = conditions;
            next_conditions[curNode->left][0][curNode->right] = 1;
            next_conditions[curNode->right][0][curNode->left] = 1;
            if(curNode->left == 26)
            {
                next_conditions[curNode->right][1][27] = 1;
                next_conditions[27][1][curNode->right] = 1;
            }
            if(curNode->right == 26)
            {
                next_conditions[curNode->left][1][27] = 1;
                next_conditions[27][1][curNode->left] = 1;
            }
            if(curNode->left == 27)
            {
                next_conditions[curNode->right][1][26] = 1;
                next_conditions[26][1][curNode->right] = 1;
            }
            if(curNode->right == 27)
            {
                next_conditions[curNode->left][1][26] = 1;
                next_conditions[26][1][curNode->left] = 1;
            }
            traversal(curNode->next_node_not_ok, next_conditions);
        }
    }
}

int main()
{
    cin >> N;
    cin >> str;

    for (int i = 0; i < str.size(); i++)
    {
        if (str[i] == '=')
        {
            str.erase(str.begin() + i);
            i++;
        }
    }

    for (int i = 0; i < 26; i++)
    {
        leaves[i].isleaf = true;
        leaves[i].leaf = getindex('a' + i);
    }

    leaves[26].isleaf = true;
    leaves[26].leaf = getindex('0');
    leaves[27].isleaf = true;
    leaves[27].leaf = getindex('1');

    makeGraph();

    vector<vector<vector<int> > > conditions;
    conditions.resize(28, vector<vector<int> > (2, vector<int> (28, 0)));
    traversal(root, conditions);

    cout << ans;
}
