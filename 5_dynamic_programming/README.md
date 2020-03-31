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

---

## Longest Increasing Subsequence

![](1_longest_increasing_subsequence/1_longest_increasing_subsequence.png)

```cpp
#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;
using VI = vector<int>;

int main() {
    int N; cin >> N;
    VI A; copy_n(istream_iterator<int>(cin), N, back_inserter(A));
    VI dp(N, 1);
    for (auto j{ 0 }; j < N; ++j)
        for (auto i{ 0 }; i < j; ++i)
            if (A[i] < A[j])
                dp[j] = std::max(dp[j], 1 + dp[i]);
    cout << *max_element(dp.begin(), dp.end()) << endl;
    return 0;
}
```