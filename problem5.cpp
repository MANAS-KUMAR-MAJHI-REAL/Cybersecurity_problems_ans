#include <bits/stdc++.h>
using namespace std;

static int trie[1000002][26];
static int wordAt[1000002];

int main() {
    int n;
    scanf("%d", &n);
    static char text[10005];
    scanf("%s", text);
    int m;
    scanf("%d", &m);

    vector<string> words(m + 1);
    int nodeCount = 1;
    char buf[1005];
    for (int w = 1; w <= m; w++) {
        scanf("%s", buf);
        words[w] = buf;
        int len = words[w].size();
        int cur = 0;
        for (int i = len - 1; i >= 0; i--) {
            int c = tolower(words[w][i]) - 'a';
            if (!trie[cur][c]) trie[cur][c] = nodeCount++;
            cur = trie[cur][c];
        }
        wordAt[cur] = w;
    }

    vector<char> reach(n + 1, 0);
    vector<int> usedWord(n + 1, 0);
    reach[0] = 1;
    for (int i = 0; i < n; i++) {
        if (!reach[i]) continue;
        int cur = 0;
        for (int j = i; j < n; j++) {
            cur = trie[cur][text[j] - 'a'];
            if (!cur) break;
            if (wordAt[cur] && !reach[j + 1]) {
                reach[j + 1] = 1;
                usedWord[j + 1] = wordAt[cur];
            }
        }
    }

    vector<int> chosen;
    int pos = n;
    while (pos > 0) {
        int w = usedWord[pos];
        chosen.push_back(w);
        pos -= (int)words[w].size();
    }
    reverse(chosen.begin(), chosen.end());

    for (size_t i = 0; i < chosen.size(); i++) {
        if (i) putchar(' ');
        fputs(words[chosen[i]].c_str(), stdout);
    }
    putchar('\n');
    return 0;
}
