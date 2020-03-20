#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <numeric>

using namespace std;

int main() {
    vector<string> A;
    copy_n(istream_iterator<string>(cin), 5, back_inserter(A));
    sort(A.begin(), A.end());
    auto suit = A[0][1];
    auto sameSuit = all_of(A.begin(), A.end(), [=](auto& card) { return card[1] == suit; });
    vector<int> V;
    transform(A.begin(), A.end(), back_inserter(V), [](auto& card) {
        char c = card[0];
        if (isalpha(c)) {
            switch (c) {
                case 'A': return 14; // ace high by default
                case 'K': return 13;
                case 'Q': return 12;
                case 'J': return 11;
                case 'T': return 10;
            }
        }
        return c - '0';
    });
    auto isStraight = [&](bool aceHigh = true) { // ace high by default
        if (!aceHigh) {
            auto ace = find(V.begin(), V.end(), 14);
            if (ace != V.end())
                *ace = 1; // ace low by manual override
        }
        sort(V.begin(), V.end());
        deque<int> diff; adjacent_difference(V.begin(), V.end(), back_inserter(diff)), diff.pop_front();
        return all_of(diff.begin(), diff.end(), [](auto delta) { return delta == 1; });
    };
    string ans = sameSuit && (isStraight() || isStraight(false)) ? "YES" : "NO";
    cout << ans << endl;
    return 0;
}
