#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int N; cin >> N;
    vector<int> A; copy_n(istream_iterator<int>(cin), N, back_inserter(A));
    auto sum{ 0L };
    for (auto i{ 0 }; i < N; ++i)
        for (auto j{ i + 1 }; j <= N; ++j)
            sum += *min_element(A.begin() + i, A.begin() + j); // min[i..j)
    cout << sum << endl;
    return 0;
}
