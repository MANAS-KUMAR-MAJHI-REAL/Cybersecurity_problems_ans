#include <bits/stdc++.h>
using namespace std;

int n;
vector<vector<int>> adj;
vector<int> parentOf, subSize;
vector<long long> memo;

long long solve(int u, int v) {
    if (u == v) return 0;
    long long &res = memo[(size_t)u * n + v];
    if (res >= 0) return res;
    int stepU = parentOf[(size_t)v * n + u];
    int stepV = parentOf[(size_t)u * n + v];
    long long gain = (long long)subSize[(size_t)v * n + u] * subSize[(size_t)u * n + v];
    res = gain + max(solve(stepU, v), solve(u, stepV));
    return res;
}

int main() {
    scanf("%d", &n);
    adj.assign(n, {});
    for (int i = 0; i < n - 1; i++) {
        int a, b;
        scanf("%d %d", &a, &b);
        a--;
        b--;
        adj[a].push_back(b);
        adj[b].push_back(a);
    }

    parentOf.assign((size_t)n * n, -1);
    subSize.assign((size_t)n * n, 1);
    memo.assign((size_t)n * n, -1);

    vector<int> order;
    order.reserve(n);
    for (int root = 0; root < n; root++) {
        order.clear();
        order.push_back(root);
        parentOf[(size_t)root * n + root] = -1;
        for (size_t i = 0; i < order.size(); i++) {
            int u = order[i];
            for (int w : adj[u]) {
                if (w == parentOf[(size_t)root * n + u]) continue;
                parentOf[(size_t)root * n + w] = u;
                order.push_back(w);
            }
        }
        for (int i = n - 1; i > 0; i--) {
            int u = order[i];
            subSize[(size_t)root * n + parentOf[(size_t)root * n + u]] += subSize[(size_t)root * n + u];
        }
    }

    long long best = 0;
    for (int u = 0; u < n; u++) {
        for (int v = u + 1; v < n; v++) best = max(best, solve(u, v));
    }
    printf("%lld\n", best);
    return 0;
}
