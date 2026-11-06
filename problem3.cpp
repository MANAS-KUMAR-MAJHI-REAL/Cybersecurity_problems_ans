#include <bits/stdc++.h>
using namespace std;

const string ALPHABET = "0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

int charId(char c) {
    return (int)ALPHABET.find(c);
}

int main() {
    int n;
    scanf("%d", &n);
    const int B = 62;
    int nodes = B * B;
    vector<vector<int>> adj(nodes);
    vector<int> in(nodes, 0), out(nodes, 0);

    char buf[8];
    int firstSource = -1;
    for (int i = 0; i < n; i++) {
        scanf("%s", buf);
        int a = charId(buf[0]), b = charId(buf[1]), c = charId(buf[2]);
        int from = a * B + b;
        int to = b * B + c;
        adj[from].push_back(to);
        out[from]++;
        in[to]++;
        if (firstSource < 0) firstSource = from;
    }

    int start = firstSource;
    int starts = 0, ends = 0;
    bool valid = true;
    for (int v = 0; v < nodes; v++) {
        int diff = out[v] - in[v];
        if (diff == 1) {
            starts++;
            start = v;
        } else if (diff == -1) {
            ends++;
        } else if (diff != 0) {
            valid = false;
        }
    }
    if (!valid || starts > 1 || ends > 1 || starts != ends) {
        puts("NO");
        return 0;
    }

    vector<int> stk = {start};
    vector<int> path;
    while (!stk.empty()) {
        int v = stk.back();
        if (!adj[v].empty()) {
            int to = adj[v].back();
            adj[v].pop_back();
            stk.push_back(to);
        } else {
            path.push_back(v);
            stk.pop_back();
        }
    }
    reverse(path.begin(), path.end());

    if ((int)path.size() != n + 1) {
        puts("NO");
        return 0;
    }

    string password;
    password += ALPHABET[path[0] / B];
    password += ALPHABET[path[0] % B];
    for (size_t i = 1; i < path.size(); i++) password += ALPHABET[path[i] % B];

    puts("YES");
    puts(password.c_str());
    return 0;
}
