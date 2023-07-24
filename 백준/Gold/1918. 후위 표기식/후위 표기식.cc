#include <iostream>
#include <queue>
#include <stack>
#include <vector>
#include <string>
#include <math.h>

using namespace std;

int priority(char ch)
{
    if (ch == '(') return -1;
    if (ch == '+' || ch == '-') return 0;
    if (ch == '*' || ch == '/') return 1;
    return 2;
}

void merge_fomular(stack<string>& f, stack<char>& op)
{
    string A = f.top(); f.pop();
    string B = f.top(); f.pop();

    B += A;
    B += op.top();
    op.pop();
    f.push(B);
}

int main() {
    string s; cin >> s;
    stack<string> fom;
    stack<char> ops;
    for (int i = 0; i < s.size(); ++i)
    {
        if (s[i] >= 'A' && s[i] <= 'Z')
        {
            string tmp = "";
            tmp += s[i];
            fom.push(tmp);
            continue;
        }

        if (s[i] == '(') ops.push(s[i]);
        else if (!ops.empty() && ops.top() != '(' && priority(s[i]) <= priority(ops.top()))
        {
            // 이 때도 나보다 먼저 계산되어야 하는 것들을 쭉 계산해야함.
            while (!ops.empty() && priority(s[i]) <= priority(ops.top())) {
                merge_fomular(fom, ops);
            }
            ops.push(s[i]);
        }
        else if (s[i] == ')')
        {
            while (ops.top() != '(') {
                merge_fomular(fom, ops);
            }
            ops.pop();
        }
        else ops.push(s[i]);
    }

    while (!ops.empty()) {
        merge_fomular(fom, ops);
    }
    cout << fom.top();
}
