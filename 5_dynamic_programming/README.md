# Week 5: Dynamic Programming
## Key Concepts
* Subproblems (and recurrence relation on them) are the most important ingredient of a dynamic programming algorithm
* Two common ways of arriving at the right subproblem:
	1. Analyze the structure of an optimal solution
	2. Implement a brute-force solution and optimize it

## Resources
1. [Dynamic Programming](docs/dynprog.pdf)

## Assignments
1. [Longest Increasing Subsequence](#longest-increasing-subsequence)
2. [Edit Distance](#edit-distance)

---

## Longest Increasing Subsequence

![](1_longest_increasing_subsequence/1_longest_increasing_subsequence.png)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_map>

#define TOP_DOWN

using namespace std;
using VI = vector<int>;
using Memo = unordered_map<int, int>; // { end index, max inc seq len }

#ifdef TOP_DOWN
int go(VI& A, Memo& T, int j) {
    if (T.find(j) != T.end())
        return T[j];
    T[j] = 1; // each index j represents a subsequence of length 1
    for (auto i{ 0 }; i < j; ++i)
        if (A[i] < A[j])
            T[j] = max(T[j], 1 + go(A, T, i));
    return T[j];
}
#endif
int main() {
    int N; cin >> N;
    VI A; copy_n(istream_iterator<int>(cin), N, back_inserter(A));
#ifdef TOP_DOWN // 👇
    auto max{ 0 };
    Memo T;
    for (auto j{ 0 }; j < N; ++j) // for each ending position j inclusive
        max = std::max(max, go(A, T, j)); // best T[j] via each LIS ending at each position i < j where A[i] < A[j]
    cout << max << endl;
#else // BOTTOM_UP 👆
    VI T(N, 1);
    for (auto j{ 0 }; j < N; ++j) // for each ending position j inclusive
        for (auto i{ 0 }; i < j; ++i)
            if (A[i] < A[j])
                T[j] = std::max(T[j], 1 + T[i]); // best T[j] via each LIS ending at each position i < j where A[i] < A[j]
    cout << *max_element(T.begin(), T.end()) << endl;
#endif
    return 0;
}
```

---

## Edit Distance

![](2_edit_distance/2_edit_distance.png)

```cpp
#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

//#define TOP_DOWN

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;
using Memo = unordered_map<string, int>;

int ins, del, sub; // cost of insertions, deletions, and substitutions

#ifdef TOP_DOWN
/*
// TLE without memo
int go(string& A, string& B, int i, int j) {
    if (i == 0) return j * ins;
    if (j == 0) return i * del;
    return min({
        go(A, B, i - 1, j - 1) + (A[i - 1] == B[j - 1] ? 0 : sub),
        go(A, B, i, j - 1) + ins,
        go(A, B, i - 1, j) + del
    });
}
*/
// TLE with memo
int go(string& A, string& B, int i, int j, Memo&& T = {}) {
    stringstream key; key << i << "," << j;
    if (T.find(key.str()) != T.end())
        return T[key.str()];
    if (i == 0) return T[key.str()] = j * ins;
    if (j == 0) return T[key.str()] = i * del;
    return T[key.str()] = min({
        go(A, B, i - 1, j - 1, move(T)) + (A[i - 1] == B[j - 1] ? 0 : sub),
        go(A, B, i, j - 1, move(T)) + ins,
        go(A, B, i - 1, j, move(T)) + del
    });
}
#endif
int main() {
    string _, A, B;
    cin >> _ >> _ >> A >> B;
    cin >> ins >> del >> sub;
#ifdef TOP_DOWN // 👇
    cout << go(A, B, A.size(), B.size()) << endl;
#else // BOTTOM_UP 👆
    int M = A.size(),
        N = B.size();
    VVI T(M + 1, VI(N + 1));
    for (auto i{ 1 }; i <= M; ++i) T[i][0] = i * del;
    for (auto j{ 1 }; j <= N; ++j) T[0][j] = j * ins;
    for (auto i{ 1 }; i <= M; ++i)
        for (auto j{ 1 }; j <= N; ++j)
            T[i][j] = min({
                T[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? 0 : sub),
                T[i][j - 1] + ins,
                T[i - 1][j] + del
            });
    cout << T[M][N] << endl;
#endif
    return 0;
}
```