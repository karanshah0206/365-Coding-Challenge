#include <iostream>
#include <queue>

using namespace std;

int main() {
    priority_queue<size_t, vector<size_t>, greater<size_t>> l;
    size_t hIndex = 0, n;
    cout << "Enter total count of citations: ";
    cin >> n;
    cout << "Enter " << n << " citations in order: ";
    for (size_t i = 0; i < n; i++) {
        size_t x; cin >> x;
        if (x > hIndex) {
            l.push(x);
            while (1) {
                while (l.size() > 0 && l.top() <= hIndex) l.pop();
                if (l.size() >= hIndex + 1) hIndex++;
                else break;
            }
        }
    }
    cout << endl << "H-Index: " << hIndex << endl;
    return 0;
}
