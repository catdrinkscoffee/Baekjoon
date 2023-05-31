#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

class trie {
public:
    vector< pair<string, trie*> > trie_container;
    
    void insert(trie* curNode, vector<string> string_container) {
        if(string_container.size() == 0) return;
        
        int idx = -1;
        
        for(int i = 0; i < trie_container.size(); ++i) {
            if(trie_container[i].first == string_container.back()) {
                idx = i;
                break;
            }
        }
        
        if(idx >= 0)
        {
            string_container.pop_back();
            trie_container[idx].second->insert(trie_container[idx].second, string_container);
        }
        else
        {
            trie* new_trie = new trie;
            trie_container.push_back(make_pair(string_container.back(), new_trie));
            string_container.pop_back();
            trie_container[trie_container.size() - 1].second->insert(trie_container[trie_container.size() - 1].second, string_container);
        }
    }
    
    void traverse(int curdepth, trie* curNode) {
        sort(trie_container.begin(), trie_container.end());
        for(auto& tri : trie_container) {
            for(int i = 0; i < curdepth * 2; ++i) {
                cout << '-';
            }
            cout << tri.first << '\n';
            tri.second->traverse(curdepth + 1, tri.second);
        }
    }
    
};


int main () {
    int N;
    cin >> N;
    trie* root = new trie;
    for(int i = 0; i < N; ++i){
        int M;
        cin >> M;
        vector<string> container;
        for(int j = 0; j < M; ++j) {
            string s;
            cin >> s;
            container.push_back(s);
        }
        reverse(container.begin(), container.end());
        root->insert(root, container);
    }
    root->traverse(0, root);
}
