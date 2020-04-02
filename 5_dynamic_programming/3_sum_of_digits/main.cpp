#include <iostream>
#include <sstream>
#include <unordered_map>
#include <vector>

using namespace std;
using LL = long long;
using Memo = unordered_map<string, LL>;
using VLL = vector<LL>;
using VVLL = vector<VLL>;

//#define TOP_DOWN

#ifdef TOP_DOWN
/*
// TLE without memo
LL go(int sum, int len) {
    if (len == 0)
        return int(sum == 0); // base case: if the sum is reduced to 0, then there is exactly 1 solution 🎯
    auto cnt{ 0LL };
    for (auto x{ 0 }; x <= 9; ++x)
        if (sum - x >= 0)
            cnt += go(sum - x, len - 1);
    return cnt;
}
*/
LL go(int sum, int len, Memo&& T = {}) {
    stringstream key; key << sum << "," << len;
    if (T.find(key.str()) != T.end())
        return T[key.str()];
    if (len == 0)
        return sum == 0; // base case: if the sum is reduced to 0, then there is exactly 1 solution 🎯
    auto cnt{ 0LL };
    for (auto x{ 0 }; x <= 9; ++x)
        if (sum - x >= 0)
            cnt += go(sum - x, len - 1, move(T));
    return T[key.str()] = cnt;
}
#endif
int main() {
    int sum, len; cin >> sum >> len;
#ifdef TOP_DOWN // 👇
    auto cnt{ 0LL };
    for (auto x = int(len > 1); x <= 9; ++x) // first digit cannot start with 0 unless it is a single digit of length 1
        if (sum - x >= 0)
            cnt += go(sum - x, len - 1);
    cout << cnt << endl;
#else // BOTTOM_UP 👆
    if (sum == 0) {
        cout << int(len == 1) << endl; // special case if sum == 0, then there is only 1 solution (ie. the single digit 0 with length 1)
    } else {
        VVLL T(len + 1, VLL(sum + 1)); // first row and first column are not used
        for (auto i{ 1 }; i <= len; ++i) T[i][0] = 1; // base case: if the sum is reduced to 0, then there is exactly 1 solution 🎯
        for (auto j{ 1 }; j <= min(9, sum); ++j) T[1][j] = 1; // single digits j = 1..9 have exactly 1 solution of length 1 (ie. j itself)
        for (auto i{ 2 }; i <= len; ++i)
            for (auto j{ 1 }; j <= sum; ++j)
                for (auto x = int(i == len); x <= 9; ++x) // limit final digit to 1..9 as if it where the first digit (ie. cannot be 0)
                    if (j - x >= 0)
                        T[i][j] += T[i - 1][j - x];
        cout << T[len][sum] << endl;
    }
#endif
    return 0;
}
