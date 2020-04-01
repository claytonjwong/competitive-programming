#include <iostream>
#include <sstream>
#include <vector>
#include <unordered_map>
#include <algorithm>

//#define TOP_DOWN

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;
using Memo = unordered_map<string, int>;

int ins, del, sub; // cost of insertions, deletions, and substitutions

#ifdef TOP_DOWN
/*
// TLE without memo
int go(string& A, string& B, int i, int j) {
    if (i == 0) return j * ins;
    if (j == 0) return i * del;
    return min({
        go(A, B, i - 1, j - 1) + (A[i - 1] == B[j - 1] ? 0 : sub),
        go(A, B, i, j - 1) + ins,
        go(A, B, i - 1, j) + del
    });
}
*/
// TLE with memo
int go(string& A, string& B, int i, int j, Memo&& T = {}) {
    stringstream key; key << i << "," << j;
    if (T.find(key.str()) != T.end())
        return T[key.str()];
    if (i == 0) return T[key.str()] = j * ins;
    if (j == 0) return T[key.str()] = i * del;
    return T[key.str()] = min({
        go(A, B, i - 1, j - 1, move(T)) + (A[i - 1] == B[j - 1] ? 0 : sub),
        go(A, B, i, j - 1, move(T)) + ins,
        go(A, B, i - 1, j, move(T)) + del
    });
}
#endif
int main() {
    string _, A, B;
    cin >> _ >> _ >> A >> B;
    cin >> ins >> del >> sub;
#ifdef TOP_DOWN // 👇
    cout << go(A, B, A.size(), B.size()) << endl;
#else // BOTTOM_UP 👆
    int M = A.size(),
        N = B.size();
    VVI T(M + 1, VI(N + 1));
    for (auto i{ 1 }; i <= M; ++i) T[i][0] = i * del;
    for (auto j{ 1 }; j <= N; ++j) T[0][j] = j * ins;
    for (auto i{ 1 }; i <= M; ++i)
        for (auto j{ 1 }; j <= N; ++j)
            T[i][j] = min({
                T[i - 1][j - 1] + (A[i - 1] == B[j - 1] ? 0 : sub),
                T[i][j - 1] + ins,
                T[i - 1][j] + del
            });
    cout << T[M][N] << endl;
#endif
    return 0;
}
