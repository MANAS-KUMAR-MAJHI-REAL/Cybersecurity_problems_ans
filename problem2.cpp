#include <bits/stdc++.h>
using namespace std;

const int BITS = 30;
const int FULL = (1 << BITS) - 1;

int main() {
    mt19937 rng(chrono::steady_clock::now().time_since_epoch().count());
    int t;
    if (scanf("%d", &t) != 1) return 0;

    vector<int> order(BITS);
    iota(order.begin(), order.end(), 0);

    while (t--) {
        shuffle(order.begin(), order.end(), rng);
        int x = 0;
        for (int i = 0; i < BITS / 2; i++) x |= 1 << order[i];

        printf("%d\n", x);
        fflush(stdout);

        int o;
        if (scanf("%d", &o) != 1 || o == -1) return 0;

        int outside = FULL & ~x;
        int d;
        if (o == x) {
            d = (int)(rng() & FULL);
            if (!(d & x)) d |= 1 << order[rng() % (BITS / 2)];
            if (!(d & outside)) d |= 1 << order[BITS / 2 + rng() % (BITS / 2)];
        } else if ((o & ~x) == 0) {
            d = x & -x;
        } else {
            d = outside & -outside;
        }

        printf("0 %d\n", d);
        fflush(stdout);

        int r;
        if (scanf("%d", &r) != 1 || r == -1) return 0;

        bool fitsZero = ((r & x) == o) || ((r | x) == o);
        printf("%d\n", fitsZero ? 0 : 1);
        fflush(stdout);
    }
    return 0;
}
