/*

 perform modified kadane's algorithm

 A =  -1   1  -1
       0   1   2   3
 K =   0   1   0


 A =  2  -3  -3  -3   2
      0   1   2   3   4  5
 K =  2   0   0   0   2

 ok so it's not helpful to reset the values to 0 per the problem statement, instead take max of (prev L/R + itself, itself)
 ie. perform kadane from L -> R and from L <- R, then take max per each index

 A =  -1   1  -1
       0   1   2   3
 L =  -1   1   0
 R =   0   1  -1
 M =   0   1   0

 A =  2  -3  -3  -3   2
      0   1   2   3   4  5
 L =  2  -1  -3  -3   2
 R =  2  -3  -3  -1   2
 M =  2  -1  -3  -1   2

 */

#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <cassert>

using namespace std;
using LL = long long;
using VLL = vector<LL>;

int main() {
    int N; cin >> N;
    VLL A, ans;
    copy_n(istream_iterator<LL>(cin), N, back_inserter(A));
    VLL L(N + 1), R(N + 1);
    auto prefixSums = [&]() {
        for (auto i{ 1 }    ; i <= N; ++i) L[i] = L[i - 1] + A[i - 1];
        for (auto i{ N - 1 }; i >= 0; --i) R[i] = R[i + 1] + A[i];
    };
    auto prefixMins = [&]() {
        for (auto i{ 1 }    ; i <= N; ++i) L[i] = min(L[i], L[i - 1]);
        for (auto i{ N - 1 }; i >= 0; --i) R[i] = min(R[i], R[i + 1]);
    };
    prefixSums();
    assert(L[N] == R[0]); // total sum exists at the end of each prefix sum
    auto sum = L[N] = R[0];
    prefixMins();
    for (auto i{ 0 }; i < N; ++i)
        ans.push_back(sum - L[i] - R[i + 1]);
    copy(ans.begin(), ans.end(), ostream_iterator<LL>(cout, " ")), cout << endl;
    return 0;
}
