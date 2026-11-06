#include <bits/stdc++.h>
using namespace std;

int main() {
    int n, k, l;
    scanf("%d %d %d", &n, &k, &l);
    vector<int> lit(n + 2, 0);
    for (int i = 0; i < k; i++) {
        int x;
        scanf("%d", &x);
        lit[x] = 1;
    }
    vector<int> lens(l);
    for (int &a : lens) scanf("%d", &a);
    sort(lens.begin(), lens.end());
    lens.erase(unique(lens.begin(), lens.end()), lens.end());

    vector<int> marks;
    for (int i = 1; i <= n + 1; i++) {
        if (lit[i] != lit[i - 1]) marks.push_back(i);
    }

    int m = marks.size();
    const int INF = 1000000000;
    vector<vector<int>> cost(m, vector<int>(m, INF));

    for (int s = 0; s < m; s++) {
        vector<int> dist(n + 2, -1);
        queue<int> q;
        dist[marks[s]] = 0;
        q.push(marks[s]);
        while (!q.empty()) {
            int u = q.front();
            q.pop();
            for (int a : lens) {
                int next[2] = {u - a, u + a};
                for (int w : next) {
                    if (w >= 1 && w <= n + 1 && dist[w] < 0) {
                        dist[w] = dist[u] + 1;
                        q.push(w);
                    }
                }
            }
        }
        for (int t = 0; t < m; t++) {
            if (dist[marks[t]] >= 0) cost[s][t] = dist[marks[t]];
        }
    }

    int full = (1 << m) - 1;
    vector<int> best(1 << m, INF);
    best[0] = 0;
    for (int mask = 0; mask < full; mask++) {
        if (best[mask] >= INF) continue;
        int i = 0;
        while (mask >> i & 1) i++;
        for (int j = i + 1; j < m; j++) {
            if (mask >> j & 1 || cost[i][j] >= INF) continue;
            int nm = mask | (1 << i) | (1 << j);
            best[nm] = min(best[nm], best[mask] + cost[i][j]);
        }
    }
    printf("%d\n", best[full] >= INF ? -1 : best[full]);
    return 0;
}
