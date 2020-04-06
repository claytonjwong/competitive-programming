#include <iostream>
#include <vector>
#include <set>
#include <algorithm>
#include <iterator>

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;
using Sack = set<int>;

#define TOP_DOWN

#ifdef TOP_DOWN
int go(VVI& T, VI& W, VI& V, int i, int j) {
    if (T[i][j] > -1)
        return T[i][j];
    if (i == 0)
        return T[i][j] = 0;
    T[i][j] = go(T, W, V, i - 1, j); // without i-th item
    if (j - W[i - 1] >= 0)
        T[i][j] = max(T[i][j], V[i - 1] + go(T, W, V, i - 1, j - W[i - 1])); // max of with/without i-th item
    return T[i][j];
}
#endif
int main() {
    int N, CAP; cin >> N >> CAP;
    VI W(N), V(N);
    for (auto i{ 0 }; i < N; ++i)
        cin >> W[i] >> V[i];
    VVI T(N + 1, VI(CAP + 1));
#ifdef TOP_DOWN // 👇
    for (auto& row: T)
        fill(row.begin(), row.end(), -1);
    go(T, W, V, N, CAP);
#else // BOTTOM_UP 👆
    for (auto i{ 1 }; i <= N; ++i) {
        for (auto j{ 1 }; j <= CAP; ++j) {
            T[i][j] = T[i - 1][j]; // without i-th item
            if (j - W[i - 1] >= 0)
                T[i][j] = max(T[i][j], T[i - 1][j - W[i - 1]] + V[i - 1]); // max of with/without i-th item
        }
    }
#endif
    Sack best;
    for (auto i{ N }, j{ CAP }; i > 0; --i)
        if (T[i][j] != T[i - 1][j])
            best.insert(i),
            j -= W[i - 1];
    cout << best.size() << endl;
    copy(best.begin(), best.end(), ostream_iterator<int>(cout, " ")), cout << endl;
    return 0;
}
