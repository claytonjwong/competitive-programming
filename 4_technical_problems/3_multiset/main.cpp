#include <iostream>
#include <sstream>
#include <vector>
#include <limits>
#include <algorithm>

using namespace std;
using VI = vector<int>;

int main() {
    auto min = numeric_limits<int>::max(),
         max = numeric_limits<int>::min();
    int N = 100 * 1000;
    VI A(N + 1);
    int K; cin >> K;
    for (int i, j; K-- && cin >> i >> j;)
        min = std::min(min, i), ++A[i],
        max = std::max(max, j), --A[j + 1]; // j + 1 because we want i..j inclusive to be counted, then "post-decrement" at j + 1
    for (auto i{ 1 }; i <= N; A[i] += A[i - 1], ++i); // add relative count offsets (ie. overlaps in the sequences)
    stringstream ss;
    for (auto i{ min }; i <= max; ++i)
        if (A[i]) ss << i << ' ' << A[i] << endl;
    cout << ss.str() << endl;
    return 0;
}
