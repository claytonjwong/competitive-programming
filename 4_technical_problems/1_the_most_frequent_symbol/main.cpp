#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;
using PrefixCount = vector<unordered_map<char, int>>;

int main() {
    string S; cin >> S;
    int N = S.size();
    PrefixCount A(N + 1);
    for (auto i{ 1 }; i <= N; ++i)         // i is offset by 1 for recurrent relation...
        A[i] = A[i - 1], ++A[i][S[i - 1]]; // A[i] = A[i - 1] with count of current char at S[i - 1] incremented by 1
    auto getMaxFreq = [&](auto i, auto j) {
        auto max{ 0 };
        auto ans{ 'a' };
        for (auto& pair: A[j]) {
            auto c = pair.first;
            auto cnt = A[j][c] - A[i - 1][c]; // use prefix count for O(1) lookup per range i..j
            if (max < cnt)
                max = cnt,
                ans = c;
        }
        return ans;
    };
    int K; cin >> K;
    while (K--) {
        int L, R; cin >> L >> R;
        cout << getMaxFreq(L, R) << endl;
    }
    return 0;
}
