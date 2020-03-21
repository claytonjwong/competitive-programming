#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

int main() {
    int N; cin >> N;
    VVI A(N, VI(N));
    for (auto i{ 0 }; i < N; ++i)
        for (auto j{ 0 }; j < N; ++j)
            cin >> A[i][j];
    auto INF = 1e9 + 7, best = INF;
    VI cur(N), ans;
    iota(cur.begin(), cur.end(), 0);
    auto calcCost = [&](int i = 0, int j = 0, int cost = 0) {
        for (auto k{ 0 }; k + 1 < N; ++k)
            i = cur[k],
            j = cur[k + 1],
            cost += A[i][j];
        return cost;
    };
    do {
        auto cost = calcCost();
        if (best > cost)
            best = cost,
            ans = cur;
    } while (next_permutation(cur.begin(), cur.end()));
    transform(ans.begin(), ans.end(), ans.begin(), [](auto x) { return x + 1; }); // 0-based to 1-based indexing
    copy(ans.begin(), ans.end(), ostream_iterator<int>(cout, " ")), cout << endl;
    return 0;
}
