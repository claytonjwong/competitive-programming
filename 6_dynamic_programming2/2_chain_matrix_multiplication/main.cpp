#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#include <iterator>

using namespace std;
using LL = unsigned long long;
using VLL = vector<LL>;
using VVLL = vector<VLL>;
using Memo = unordered_map<string, LL>;
int INF = 1e9 + 7;

//#define TOP_DOWN

#ifdef TOP_DOWN
string key(int i, int j) {
    stringstream key; key << i << "," << j;
    return key.str();
}
int go(VLL& A, int i, int j, Memo&& T = {}) {
    auto x = key(i, j);
    if (T[x])
        return T[x];
    T[x] = INF;
    if (i + 1 >= j)
        return T[x] = 0;
    for (auto k{ i + 1 }; k < j; ++k)
        T[x] = min(T[x], go(A, i, k, move(T)) + go(A, k, j, move(T)) + A[i] * A[k] * A[j]);
    return T[x];
}
#endif
int main() {
    int N; cin >> N;
    VLL A; copy_n(istream_iterator<LL>(cin), N + 1, back_inserter(A)); // N + 1 because each matrix i has dimensions A[i], A[i + 1]
#ifdef TOP_DOWN // 👇
    cout << go(A, 0, N) << endl; // j == N == A.size() - 1
#else // BOTTOM_UP 👆
    VVLL T(N + 1, VLL(N + 1, INF));
    for (auto i{ 0 }; i < N; ++i)
        T[i][i + 1] = 0;
    for (auto len{ 2 }; len <= N; ++len)
        for (auto i{ 0 }; i + len <= N; ++i)
            for (auto j{ i + len }, k{ i + 1 }; k < j; ++k)
                T[i][j] = min(T[i][j], T[i][k] + T[k][j] + A[i] * A[k] * A[j]);
    cout << T[0][N] << endl;
#endif
    return 0;
}
