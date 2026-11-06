#include <bits/stdc++.h>
using namespace std;

struct Query {
    int type, a, b;
};

struct RollbackDsu {
    vector<int> parent, size, history;

    RollbackDsu(int n) : parent(n + 1), size(n + 1, 1) {
        iota(parent.begin(), parent.end(), 0);
    }

    int find(int x) {
        while (parent[x] != x) x = parent[x];
        return x;
    }

    void join(int a, int b) {
        a = find(a);
        b = find(b);
        if (a == b) return;
        if (size[a] > size[b]) swap(a, b);
        parent[a] = b;
        size[b] += size[a];
        history.push_back(a);
    }

    void rollback(size_t mark) {
        while (history.size() > mark) {
            int r = history.back();
            history.pop_back();
            size[parent[r]] -= size[r];
            parent[r] = r;
        }
    }
};

vector<vector<int>> tree;
vector<pair<int, int>> contacts;
vector<int> askedPerson;
vector<int> result;

void addContact(int node, int l, int r, int ql, int qr, int id) {
    if (ql > r || qr < l) return;
    if (ql <= l && r <= qr) {
        tree[node].push_back(id);
        return;
    }
    int mid = (l + r) / 2;
    addContact(node * 2, l, mid, ql, qr, id);
    addContact(node * 2 + 1, mid + 1, r, ql, qr, id);
}

void walk(int node, int l, int r, RollbackDsu &dsu) {
    size_t mark = dsu.history.size();
    for (int id : tree[node]) dsu.join(contacts[id].first, contacts[id].second);
    if (l == r) {
        result[l] = dsu.size[dsu.find(askedPerson[l])];
    } else {
        int mid = (l + r) / 2;
        walk(node * 2, l, mid, dsu);
        walk(node * 2 + 1, mid + 1, r, dsu);
    }
    dsu.rollback(mark);
}

int main() {
    int n, q, k;
    scanf("%d %d %d", &n, &q, &k);
    vector<Query> qs(q);
    vector<int> dayEnds;
    vector<int> askedBefore(q + 1, 0);
    for (int i = 0; i < q; i++) {
        scanf("%d", &qs[i].type);
        if (qs[i].type == 1) {
            scanf("%d %d", &qs[i].a, &qs[i].b);
        } else if (qs[i].type == 2) {
            scanf("%d", &qs[i].a);
        } else {
            dayEnds.push_back(i);
        }
        askedBefore[i + 1] = askedBefore[i] + (qs[i].type == 2);
    }

    int asks = askedBefore[q];
    if (asks == 0) return 0;

    tree.assign(4 * asks + 4, {});
    result.assign(asks, 0);
    for (int i = 0; i < q; i++) {
        if (qs[i].type == 2) askedPerson.push_back(qs[i].a);
    }

    int day = 0;
    for (int i = 0; i < q; i++) {
        if (qs[i].type == 3) {
            day++;
        } else if (qs[i].type == 1) {
            long long lastIdx = (long long)day + k - 1;
            int expiry = lastIdx < (long long)dayEnds.size() ? dayEnds[lastIdx] : q;
            int lo = askedBefore[i];
            int hi = askedBefore[expiry] - 1;
            if (lo <= hi) {
                contacts.push_back({qs[i].a, qs[i].b});
                addContact(1, 0, asks - 1, lo, hi, (int)contacts.size() - 1);
            }
        }
    }

    RollbackDsu dsu(n);
    walk(1, 0, asks - 1, dsu);

    for (int i = 0; i < asks; i++) printf("%d\n", result[i]);
    return 0;
}
