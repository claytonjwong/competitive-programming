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
