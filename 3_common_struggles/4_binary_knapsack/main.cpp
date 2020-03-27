//#include <iostream>
//#include <vector>
//
//using namespace std;
//using LL = long long;
//using VL = vector<LL>;
//using VVL = vector<VL>;

//// Failed case #11/43: time limit exceeded (Time used: 3.99/2.00, memory used: 9420800/536870912.)
//void go(LL& max, VI& W, VI& V, int cap, LL val = 0, int i = 0) {
//    int N = W.size();
//    if (i == N) {
//        max = std::max(max, val);
//        return;
//    }
//    for (auto j{ 0 }; j < N; ++j) {
//        if (cap >= W[i])
//            go(max, W, V, cap - W[i], val + V[i], i + 1); // with ✅
//        go(max, W, V, cap, val, i + 1);                   // without ❌
//    }
//}
//
//int main() {
//    LL N, cap; cin >> N >> cap;
//    VI W(N), V(N); for (auto i{ 0 }; i < N; cin >> W[i] >> V[i], ++i); // (W)eight, (V)alue
//    auto max{ 0LL };
//    go(max, W, V, cap);
//    cout << max << endl;
//    return 0;
//}


/*

 question: what makes this problem special?  the weight of each item is a power of 2.  ok, but how is
 that meaningful here?  can it help me to more efficiently create a bottom-up solution using DP?

 maybe?... what does the DP matrix and recurrence relation look like then?

        weight
  -------------------
 |
 |
 i
 t
 e      values
 m
 |
 |                  X <-- answer @ bottom-right


 or

     item
  -------------
 |
 |
 w
 e
 i     values
 g
 h
 t
 |
 |            X <-- answer @ bottom-right

let's go with the first representation since that seems more natural to list items top-down, and weight left-right

 */

//// Failed case #21/43: time limit exceeded (Time used: 3.74/2.00, memory used: 2136571904/536870912.)
//int main() {
//    LL N, cap; cin >> N >> cap;
//    VL W(N), V(N); for (auto i{ 0 }; i < N; cin >> W[i] >> V[i], ++i); // (W)eight, (V)alue
//    VVL dp(N + 1, VL(cap + 1));
//    for (auto i{ 1 }; i <= N; ++i) {
//        for (auto j{ 1 }; j <= cap; ++j) {
//            if (W[i - 1] > j)
//                dp[i][j] = dp[i - 1][j];
//            else
//                dp[i][j] = max(dp[i - 1][j], j - W[i - 1] >= 0 ? V[i - 1] + dp[i - 1][j - W[i - 1]] : 0);
//        }
//    }
//    cout << dp[N][cap] << endl;
//    return 0;
//}

/*

 this solution definitely uses too much memory, since the amount of rows (ie. cap) can be about 2 billion!
 let's try to come up with a better solution.  Maybe a greedy algorithm for each power of 2?

 */

/*
5 10
1 4
2 5
1 2
4 6
8 12

   0  1  2  3  4  5  6  7  8  9  0  1
0  0  0  0  0  0  0  0  0  0  0  0
1  0  0  4  4  4  4  4  4  4  4  4
2  0  0  5  5  9  9  9  9  9  9  9
3  0  0  5  5  9 11 11 11 11 11 11
4  0  0  5  5  9 11 11 11 15 17 17
5  0  0  5  5  9 11 11 11 15 17 17
6

*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct item {
    int weight, value;
    bool operator < (const item& other) const {
        return weight < other.weight;
    }
};

int main() {
    cin.sync_with_stdio(false);
    cin.tie(0);

    int n, totalWeight;
    cin >> n >> totalWeight;

    vector<item> items;
    for (int i = 0; i < n; ++i) {
        int weight, value;
        cin >> weight >> value;
        items.push_back({weight, value});
    }

    sort(items.begin(), items.end());
    reverse(items.begin(), items.end());

    int totalValue = 0;
    vector<int> candidates;

    for (int power = 0; power <= 30; ++power) {
        int weight = 1 << power;
        while (items.size() > 0 && items.back().weight == weight) {
            candidates.push_back(items.back().value);
            items.pop_back();
        }

        sort(candidates.begin(), candidates.end());

        if (totalWeight & weight) {
            if (candidates.size() > 0) {
                totalValue += candidates.back();
                candidates.pop_back();
            }
        }

        vector<int> newCandidates;
        while (candidates.size() >= 2) {
            int combinedValue = candidates.back();
            candidates.pop_back();
            combinedValue += candidates.back();
            candidates.pop_back();
            newCandidates.push_back(combinedValue);
        }

        if (candidates.size() >= 1) {
            newCandidates.push_back(candidates.back());
            candidates.pop_back();
        }

        candidates = newCandidates;
    }

    cout << totalValue << '\n';

    return 0;
}
