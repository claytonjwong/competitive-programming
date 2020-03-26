#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>
#include <iterator>

using namespace std;
using VI = vector<int>;

int main() {
    int N; cin >> N;
    auto getNums = [=](VI nums = {}) {
        for (auto K{ N }; K--;) {
            string s; cin >> s;
            s.erase(remove(s.begin(), s.end(), '.'), s.end());
            nums.push_back(stoi(s));
        }
        return nums;
    };
    VI A = getNums(),
       B = getNums();
    auto sumA = accumulate(A.begin(), A.end(), 0),
         sumB = accumulate(B.begin(), B.end(), 0);
    cout << "SUM(A)"
         << (sumA < sumB ? "<" : sumA > sumB ? ">" : "=")
         << "SUM(B)"
         << endl;
    return 0;
}
