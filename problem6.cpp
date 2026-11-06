#include <bits/stdc++.h>
using namespace std;

const long long MOD = 1000000007LL;
const int MAX_LEN = 100;
const int MAX_SUM = 25 * MAX_LEN;

long long ways[MAX_LEN + 1][MAX_SUM + 1];

int main() {
    ways[0][0] = 1;
    for (int len = 1; len <= MAX_LEN; len++) {
        for (int s = 0; s <= 25 * len; s++) {
            long long total = 0;
            for (int c = 0; c <= 25 && c <= s; c++) total += ways[len - 1][s - c];
            ways[len][s] = total % MOD;
        }
    }

    int t;
    scanf("%d", &t);
    char word[128];
    while (t--) {
        scanf("%s", word);
        int len = strlen(word);
        int sum = 0;
        for (int i = 0; i < len; i++) sum += word[i] - 'a';
        printf("%lld\n", (ways[len][sum] - 1 + MOD) % MOD);
    }
    return 0;
}
