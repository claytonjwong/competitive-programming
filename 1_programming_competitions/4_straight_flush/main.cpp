#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <unordered_set>
#include <cassert>

using namespace std;

int main() {
    int N{ 5 };
    vector<string> A; copy_n(istream_iterator<string>(cin), N, back_inserter(A));
    auto isSameSuit = [&](unordered_set<char> S = {}) {
        transform(A.begin(), A.end(), inserter(S, S.end()), [](auto& card) { return card[1]; });
        return S.size() == 1;
    };
    auto getValues = [&](bool aceHigh, vector<int> V = {}) {
        transform(A.begin(), A.end(), back_inserter(V), [=](auto& card) {
           auto val = card[0];
            if (isalpha(val)) {
                switch (val) {
                    case 'A': return aceHigh ? 14 : 1;
                    case 'K': return 13;
                    case 'Q': return 12;
                    case 'J': return 11;
                    case 'T': return 10;
                }
            }
            return val - '0';
        });
        return V;
    };
    auto isStraight = [=](auto& values) {
        assert(N == values.size());
        return N == 1 + *max_element(values.begin(), values.end()) // +1 for [i..j] inclusive
                      - *min_element(values.begin(), values.end());
    };
    auto hi = getValues(true),  // ace high
         lo = getValues(false); // ace low
    cout << (isSameSuit() && (isStraight(hi) || isStraight(lo)) ? "YES" : "NO") << endl;
    return 0;
}
