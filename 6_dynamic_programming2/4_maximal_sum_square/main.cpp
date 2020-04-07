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
