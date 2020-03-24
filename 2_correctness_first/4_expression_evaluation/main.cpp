#include <iostream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;

int main() {
    string s; cin >> s;
    auto getNums = [&](string t = {}, vector<int> nums = {}) {
        transform(s.begin(), s.end(), back_inserter(t), [](auto c) {
            return isdigit(c) ? c : ' ';
        });
        istringstream stream{ t };
        copy(istream_iterator<int>(stream), istream_iterator<int>(), back_inserter(nums));
        return nums;
    };
    auto getOps = [&](string t = {}, vector<char> ops = {}) {
        transform(s.begin(), s.end(), back_inserter(t), [](auto c) {
            return !isdigit(c) ? c : ' ';
        });
        istringstream stream{ t };
        copy(istream_iterator<char>(stream), istream_iterator<char>(), back_inserter(ops));
        return ops;
    };
    auto nums = getNums();
    auto ops = getOps();
    for (auto i{ 1 }; i < nums.size(); ++i)
        if (ops[i - 1] == '-')
            nums[i] = -nums[i];
    cout << accumulate(nums.begin(), nums.end(), 0L) << endl;
    return 0;
}
