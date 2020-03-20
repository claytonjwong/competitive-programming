#include <iostream>
#include <vector>
#include <algorithm>
#include <iterator>

using namespace std;

int main() {
    int N{ 0 }, del{ -1 };
    vector<int> A;
    cin >> N, copy_n(istream_iterator<int>(cin), N, back_inserter(A));
    for (auto i{ 0 }, max{ 0 }, cnt{ 0 }; i < N; ++i) {
        if (max < A[i])
            max = A[i], cnt = 0, del = i;
        if (max == A[i] && ++cnt == 3)
            del = i;
    }
    A.erase(A.begin() + del);
    copy(A.begin(), A.end(), ostream_iterator<int>(cout, " ")), cout << endl;
    return 0;
}
