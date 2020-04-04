#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

#define MEMORY_EFFICIENT

int main() {
    int INF = 1e9 + 7;
    int N; cin >> N;
    VI A; copy_n(istream_iterator<int>(cin), N, back_inserter(A));
    auto max = *max_element(A.begin(), A.end());
#ifndef MEMORY_EFFICIENT
    VVI T(N + 1, VI(max + 1));
    for (auto i{ 1 }; i <= N; ++i) {
        auto best{ INF };
        for (auto j{ 0 }; j <= max; ++j) {
            best = min(best, T[i - 1][j]); // previous best
            T[i][j] = best + abs(A[i - 1] - j); // current best = previous best + cost to change i-th element of A to value j
        }
    }
    cout << *min_element(T[N].begin(), T[N].end()) << endl;
#else // MEMORY_EFFICIENT
    VI pre(max + 1),
       cur(max + 1);
    for (auto i{ 1 }; i <= N; ++i) {
        auto best{ INF };
        for (auto j{ 0 }; j <= max; ++j) {
            best = min(best, pre[j]); // previous best
            cur[j] = best + abs(A[i - 1] - j); // current best = previous best + cost to change i-th element of A to value j
        }
        swap(pre, cur);
    }
    cout << *min_element(pre.begin(), pre.end()) << endl;
#endif
    return 0;
}
