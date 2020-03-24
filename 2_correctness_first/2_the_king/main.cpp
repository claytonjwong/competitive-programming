#include <iostream>
#include <vector>
#include <numeric>

using namespace std;
using VI = vector<int>;
using VVI = vector<VI>;

/*

 M = 3, N = 3

   0 1 2 3
 0 k k k
 1 k . k
 2 k k k
 3

 M = 1, N = 10

   0 1 2 3 4 5 6 7 8 9 0
 0 k . k k . k k . k .

 M = 1, N = 9

   0 1 2 3 4 5 6 7 8 9
 0 k . k k . k k . k

 M = 1, N = 8

   0 1 2 3 4 5 6 7 8
 0 k . k k . k k .

 M = 1, N = 7

   0 1 2 3 4 5 6 7
 0 k . k k . k .

 M = 2, N = 7

   0 1 2 3 4 5 6 7
 0 k k k k k k k
 1 k . k k . . k
 2

 from these examples, i believe a greedy algorithm would work...

 question: how to efficiently check if placing a king in a position is OK?  well this may not be efficient,
 but we can just check each of the 8 surround kings u,v to see if there exists more than one empty space, so if all kings
 have more than open empty space, then we can fill in the current space i,j, if the current i,j has > 0 empty adj spaces as well.
 perform this greedy algorithm from top-left to bottom-right.

 */

int main() {
    int M, N; cin >> M >> N;
    VVI A(M, VI(N));
    // clock-wise: up, up-right, right, down-right, down, down-left, left, up-left
    VVI dirs = {{-1, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}};
    auto inBounds = [&](auto i, auto j) {
        return 0 <= i && i < M && 0 <= j && j < N;
    };
    auto adjSpaces = [&](auto i, auto j) {
        auto spaces{ 0 };
        for (auto& dir: dirs) {
            auto u = i + dir[0],
                 v = j + dir[1];
            if (inBounds(u, v) && A[u][v] == 0)
                ++spaces;
        }
        return spaces;
    };
    auto ok = [&](auto i, auto j) {
        if (adjSpaces(i, j) == 0)
            return false; // no empty space for a king at i,j ❌
        for (auto& dir: dirs) {
            auto u = i + dir[0],
                 v = j + dir[1];
            if (inBounds(u, v) && A[u][v] == 1 && adjSpaces(u, v) == 1)
                return false; // adj u,v king's only empty space is i,j so we cannot place a king here ❌
        }
        return true;
    };
    for (auto i{ 0 }; i < M; ++i)
        for (auto j{ 0 }; j < N; ++j)
            if (ok(i, j))
                A[i][j] = 1;
    auto kings{ 0 };
    for (auto& row: A)
        kings += accumulate(row.begin(), row.end(), 0);
    cout << kings << endl;
    return 0;
}
