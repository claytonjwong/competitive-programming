# Week 6: Dynamic Programming 2
## Key Concepts
* Practice implementing dynamic programming solutions
* Design dynamic programming solutions

## Resources
* [Dynamic Programming 2](docs/dynprog2.pdf)

## Assignments
1. [Knapsack](#knapsack)
2. [Chain Matrix Multiplication](#chain-matrix-multiplication)
3. [Longest Common Subsequence](#longest-common-subsequence)
4. [Maximal Sum Square](#maximal-sum-square)

---

## Knapsack

![](1_knapsack/1_knapsack.png)

```cpp
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
```

---

## Chain Matrix Multiplication

![](2_chain_matrix_multiplication/2_chain_matrix_multiplication.png)

```cpp
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
```

---

## Longest Common Subsequence

![](3_longest_common_subsequence/3_longest_common_subsequence.png)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

int main() {
    int N; cin >> N;
    VI A; copy_n(istream_iterator<int>(cin), N, back_inserter(A));
    VI B; copy_n(istream_iterator<int>(cin), N, back_inserter(B));
    VVI T(N + 1, VI(N + 1));
    for (auto i{ 1 }; i <= N; ++i)
        for (auto j{1}; j <= N; ++j)
            if (A[i - 1] == B[j - 1])
                T[i][j] = 1 + T[i - 1][j - 1]; // 1 + max of previous sequence (ie. without i and j == 👆 above and 👈 left)
            else
                T[i][j] = max(T[i - 1][j], T[i][j - 1]); // max of previous sequence (without i xor j == 👆 above xor 👈 left)
    auto len = T[N][N];
    VI seqA(len), seqB(len); // backtrack through the table to find the sequences
    for (auto i{ N }, j{ N }, k{ len - 1 }; i > 0 && j > 0;)
        if (A[i - 1] == B[j - 1]) // target 🎯
            seqA[k] = i - 1,
            seqB[k] = j - 1,
            --i, --j, --k;
        else if (T[i][j] == T[i - 1][j]) --i; // 👆 above
        else if (T[i][j] == T[i][j - 1]) --j; // 👈 left
    cout << T[N][N] << endl;
    copy(seqA.begin(), seqA.end(), ostream_iterator<int>(cout, " ")), cout << endl;
    copy(seqB.begin(), seqB.end(), ostream_iterator<int>(cout, " ")), cout << endl;
    return 0;
}
```

---

## Maximal Sum Square

![](4_maximal_sum_square/4_maximal_sum_square.png)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

int main() {
    int N, K; cin >> N >> K;
    VVI A(N);
    for (auto i{ 0 }; i < N; ++i)
        copy_n(istream_iterator<int>(cin), N, back_inserter(A[i]));
    VVI T(N + 1, VI(N + 1));
    for (auto i{ 1 }; i <= N; ++i)
        for (auto j{ 1 }; j <= N; ++j)
            T[i][j] = A[i - 1][j - 1] // corresponding A[i][j] offset by 1
                    + T[i - 1][j] // top
                    + T[i][j - 1] // left
                    - T[i - 1][j - 1]; // subtract top-left once because it was added twice (once in top and once in left)
    --K; // let K be inclusive for ranges from i..K and j..K to find the max sum (this avoids having to subtract by 1 below)
    auto max{ 0 }, sum{ 0 };
    for (auto i{ 1 }; i + K <= N; ++i)
        for (auto j{ 1 }; j + K <= N; ++j)
            sum = T[i + K][j + K] // bottom-right contains absolute sum from [0, 0] to [i + K, j + K]
                - T[i - 1][j + K] // top  contains absolute sum from [0, 0] to [i - 1, j + K]
                - T[i + K][j - 1] // left contains absolute sum from [0, 0] to [i + K, j - 1]
                + T[i - 1][j - 1], // add top-left once because it was subtracted twice (once in top and once in left)
            max = std::max(max, sum); // max sum 🎯
    cout << max << endl;
    return 0;
}
```