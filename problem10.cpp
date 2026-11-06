#include <bits/stdc++.h>
using namespace std;

int ask(int c, int r) {
    printf("? %d %d\n", c, r);
    fflush(stdout);
    int h;
    if (scanf("%d", &h) != 1) exit(0);
    return h;
}

int main() {
    int n;
    scanf("%d", &n);

    int block = 1;
    while (block * block < n) block++;

    int y = ask(n, 1);

    unordered_map<int, int> seen;
    seen.reserve(block * 2 + 10);
    seen[y] = 0;

    int cycleLen = -1;
    int cur = y;
    for (int i = 1; i < block; i++) {
        cur = ask(1, cur);
        if (cur == y) {
            cycleLen = i;
            break;
        }
        seen[cur] = i;
    }

    if (cycleLen < 0) {
        int z = y;
        for (int j = 1;; j++) {
            z = ask(block, z);
            auto it = seen.find(z);
            if (it != seen.end()) {
                cycleLen = block * j - it->second;
                break;
            }
        }
    }

    int shift = (cycleLen - y % cycleLen) % cycleLen;
    int r = shift == 0 ? y : ask(shift, y);

    printf("! %d %d\n", y, r);
    fflush(stdout);
    return 0;
}
