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
