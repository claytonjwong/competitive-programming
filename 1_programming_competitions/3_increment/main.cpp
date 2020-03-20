#include <iostream>
#include <algorithm>

using namespace std;

int main() {
    string S; cin >> S;
    auto N = all_of(S.begin(), S.end(), [](auto c) { return c == '9'; }) ? S.size() + 1 : S.size();
    cout << N << endl;
    return 0;
}
