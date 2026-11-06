#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;

struct Link {
    long long key;
    int a, b;
};

vector<int> boss;

int findBoss(int x) {
    while (boss[x] != x) {
        boss[x] = boss[boss[x]];
        x = boss[x];
    }
    return x;
}

int main() {
    int n, m;
    int k;
    scanf("%d %d %d", &n, &m, &k);
    vector<long long> keys(n + 1);
    for (int i = 1; i <= n; i++) scanf("%lld", &keys[i]);

    vector<Link> links(m);
    for (auto &e : links) {
        scanf("%d %d", &e.a, &e.b);
        e.key = keys[e.a] ^ keys[e.b];
    }
    sort(links.begin(), links.end(), [](const Link &x, const Link &y) { return x.key < y.key; });

    vector<long long> pow2(n + 1);
    pow2[0] = 1;
    for (int i = 1; i <= n; i++) pow2[i] = pow2[i - 1] * 2 % MOD;

    long long totalKeys = 1;
    for (int i = 0; i < k; i++) totalKeys = totalKeys * 2 % MOD;

    boss.resize(n + 1);
    for (int i = 1; i <= n; i++) boss[i] = i;

    long long answer = 0;
    long long groups = 0;
    int i = 0;
    while (i < m) {
        int j = i;
        int merged = 0;
        while (j < m && links[j].key == links[i].key) {
            int ra = findBoss(links[j].a);
            int rb = findBoss(links[j].b);
            if (ra != rb) {
                boss[ra] = rb;
                merged++;
            }
            j++;
        }
        answer = (answer + pow2[n - merged]) % MOD;
        groups++;
        for (int t = i; t < j; t++) {
            boss[links[t].a] = links[t].a;
            boss[links[t].b] = links[t].b;
        }
        i = j;
    }

    long long untouched = ((totalKeys - groups) % MOD + MOD) % MOD;
    answer = (answer + untouched * pow2[n]) % MOD;
    printf("%lld\n", answer);
    return 0;
}
