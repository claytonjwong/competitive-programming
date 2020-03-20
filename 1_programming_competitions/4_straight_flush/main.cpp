#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <deque>
#include <numeric>
#include <unordered_set>

using namespace std;

int main() {
    vector<string> A;
    copy_n(istream_iterator<string>(cin), 5, back_inserter(A));
    vector<int> V; // value
    unordered_set<char> S; // suit
    transform(A.begin(), A.end(), back_inserter(V), [&](auto& card) {
        char val{ card[0] }, suit{ card[1] };
        S.insert(suit);
        if (isalpha(val)) {
            switch (val) {
                case 'A': return 14; // ace high by default
                case 'K': return 13;
                case 'Q': return 12;
                case 'J': return 11;
                case 'T': return 10;
            }
        }
        return val - '0';
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
    string ans = S.size() == 1 && (isStraight() || isStraight(false)) ? "YES" : "NO";
    cout << ans << endl;
    return 0;
}
