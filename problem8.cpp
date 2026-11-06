#include <bits/stdc++.h>
using namespace std;

struct ParityDsu {
    vector<int> parent, size, parity, history;

    ParityDsu(int n) : parent(n + 1), size(n + 1, 1), parity(n + 1, 0) {
        iota(parent.begin(), parent.end(), 0);
    }

    pair<int, int> find(int x) {
        int p = 0;
        while (parent[x] != x) {
            p ^= parity[x];
            x = parent[x];
        }
        return {x, p};
    }

    bool join(int a, int b) {
        auto [ra, pa] = find(a);
        auto [rb, pb] = find(b);
        if (ra == rb) return pa != pb;
        if (size[ra] > size[rb]) swap(ra, rb);
        parent[ra] = rb;
        parity[ra] = pa ^ pb ^ 1;
        size[rb] += size[ra];
        history.push_back(ra);
        return true;
    }

    void rollback(size_t mark) {
        while (history.size() > mark) {
            int r = history.back();
            history.pop_back();
            size[parent[r]] -= size[r];
            parent[r] = r;
            parity[r] = 0;
        }
    }
};

int n, q;
vector<vector<pair<int, int>>> tree;
vector<char> answer;

void addEdge(int node, int l, int r, int ql, int qr, pair<int, int> e) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node].push_back(e);
        return;
    }
    int mid = (l + r) / 2;
    addEdge(node * 2, l, mid, ql, qr, e);
    addEdge(node * 2 + 1, mid + 1, r, ql, qr, e);
}

void walk(int node, int l, int r, ParityDsu &dsu) {
    size_t mark = dsu.history.size();
    bool ok = true;
    for (auto &e : tree[node]) {
        if (!dsu.join(e.first, e.second)) {
            ok = false;
            break;
        }
    }
    if (!ok) {
        for (int i = l; i <= r; i++) answer[i] = 0;
    } else if (l == r) {
        answer[l] = 1;
    } else {
        int mid = (l + r) / 2;
        walk(node * 2, l, mid, dsu);
        walk(node * 2 + 1, mid + 1, r, dsu);
    }
    dsu.rollback(mark);
}

int main() {
    scanf("%d %d", &n, &q);
    tree.assign(4 * q + 4, {});
    answer.assign(q, 1);

    unordered_map<long long, int> since;
    since.reserve(q * 2);
    for (int i = 0; i < q; i++) {
        int x, y;
        scanf("%d %d", &x, &y);
        long long key = (long long)x * (n + 1) + y;
        auto it = since.find(key);
        if (it == since.end()) {
            since[key] = i;
        } else {
            addEdge(1, 0, q - 1, it->second, i - 1, {x, y});
            since.erase(it);
        }
    }
    for (auto &kv : since) {
        int x = kv.first / (n + 1);
        int y = kv.first % (n + 1);
        addEdge(1, 0, q - 1, kv.second, q - 1, {x, y});
    }

    ParityDsu dsu(n);
    walk(1, 0, q - 1, dsu);

    for (int i = 0; i < q; i++) puts(answer[i] ? "YES" : "NO");
    return 0;
}
