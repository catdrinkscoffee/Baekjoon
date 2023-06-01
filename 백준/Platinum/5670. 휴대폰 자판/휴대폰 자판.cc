#include <bits/stdc++.h>

using namespace std;
const int ALPHABET = 28;
class trie {
public:
    bool endWithThisAlphabet[ALPHABET]{ false };
    trie* next_node[ALPHABET];
    int cnt;
    int terminated;

    trie() : cnt(0), terminated(0) {
        memset(next_node, 0, sizeof(next_node));
    }
    ~trie() {
        for (int i = 0; i < ALPHABET; ++i) {
            if (next_node[i])
                delete next_node[i];
        }
    }
    void insert(trie* cur_node, string& s)
    {
        int idx = s.back() - 'a';
        if (next_node[idx]) {
            s.pop_back();
            if (s.size() == 0) {
                endWithThisAlphabet[idx] = true;
                ++terminated;
                return;
            }
            next_node[idx]->insert(next_node[idx], s);
        }
        else {
            ++cnt;
            s.pop_back();
            trie* new_node = new trie;
            next_node[idx] = new_node;

            if (s.size() == 0) {
                endWithThisAlphabet[idx] = true;
                ++terminated;
                return;
            }
            next_node[idx]->insert(next_node[idx], s);
        }
    }

    void traverse(trie* cur_node, int type_cnt, float* t, bool flag) {
        if (!flag && (cnt > 1)) ++type_cnt;
        if (cur_node->terminated > 0)
        {
            //            cout << type_cnt * terminated << '\n';
            *t += type_cnt * terminated;
        }
        for (int i = 0; i < ALPHABET; ++i) {
            if (next_node[i])
            {
                //                cout << char('a' + i) << '\n';
                if (endWithThisAlphabet[i])
                    next_node[i]->traverse(next_node[i], type_cnt + 1, t, true);
                else next_node[i]->traverse(next_node[i], type_cnt, t, false);
            }
        }
    }

};

int main() {
    int N;

    while (cin >> N) {
        trie* root = new trie;

        for (int i = 0; i < N; ++i) {
            string s;
            cin >> s;
            reverse(s.begin(), s.end());
            root->insert(root, s);
        }

        float t = 0;
        root->traverse(root, 1, &t, true);
        float ans = round(t / N * 100) / 100;
        cout << fixed;
        cout.precision(2);
        cout << ans << '\n';

        delete root;
    }
}
