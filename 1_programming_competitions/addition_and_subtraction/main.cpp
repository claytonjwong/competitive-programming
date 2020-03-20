#include <iostream>

using namespace std;

int N = 2 * 1000; // 2 ops (add/sub) result in minimum "helpful" delta of 1 (ie. go 1 step closer to max target 1000)
int main() {
    auto add{ 0 }, sub{ 0 }, target{ 0 }, ans{ -1 };
    cin >> add >> sub >> target;
    for (auto i{ 0 }, x{ 0 }; i <= N; ++i) {
        if (x == target) {
            ans = i;
            break;
        }
        x += i % 2 == 0 ? add : -sub;
    }
    cout << ans << endl;
    return 0;
}
