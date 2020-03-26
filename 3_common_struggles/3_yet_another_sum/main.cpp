#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>
#include <iterator>
#include <numeric>

using namespace std;
using VD = vector<double>;

int main() {
    int N; cin >> N;
    VD A; copy_n(istream_iterator<double>(cin), N, back_inserter(A));
    auto intSum = [&]() {
        return accumulate(A.begin(), A.end(), 0.0);
    };
    auto divSum = [&](VD div = {}) {
        transform(A.begin(), A.end(), back_inserter(div), [](auto x) { return 1 / x; });
        return accumulate(div.begin(), div.end(), 0.0);
    };
    cout << setprecision(11) << intSum() + divSum() << endl;
    return 0;
}
