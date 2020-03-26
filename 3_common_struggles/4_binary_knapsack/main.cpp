#include <iostream>
#include <vector>

using namespace std;
using VI = vector<int>;
using LL = long long;

// Failed case #11/43: time limit exceeded (Time used: 3.99/2.00, memory used: 9420800/536870912.)
void go(LL& max, VI& W, VI& V, int cap, LL val = 0, int i = 0) {
    int N = W.size();
    if (i == N) {
        max = std::max(max, val);
        return;
    }
    for (auto j{ 0 }; j < N; ++j) {
        if (cap >= W[i])
            go(max, W, V, cap - W[i], val + V[i], i + 1); // with ✅
        go(max, W, V, cap, val, i + 1);                             // without ❌
    }
}

int main() {
    LL N, cap; cin >> N >> cap;
    VI W(N), V(N); for (auto i{ 0 }; i < N; cin >> W[i] >> V[i], ++i); // (W)eight, (V)alue
    auto max{ 0LL };
    go(max, W, V, cap);
    cout << max << endl;
    return 0;
}
