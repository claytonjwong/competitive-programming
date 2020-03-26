#include <iostream>
#include <cmath>

using namespace std;

int main() {
    int x, y; cin >> x >> y;
    auto roundUp = [](double x, double y) { return static_cast<int>(ceil(x / y)); };
    cout << roundUp(x, y) << endl;
    return 0;
}
