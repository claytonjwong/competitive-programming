#include <iostream>

using namespace std;

int main() {
    struct MinMax {
        int INF = 1e9 + 7,
            min{  INF },
            max{ -INF };
    } value, index;
    int N; cin >> N;
    for (auto i{ 1 }; i <= N; ++i) {
        int x; cin >> x;
        if (value.min > x) value.min = x, index.min = i;
        if (value.max < x) value.max = x, index.max = i;
        cout << min(index.min, index.max)
             << " "
             << max(index.min, index.max)
             << endl;
    }
    return 0;
}
