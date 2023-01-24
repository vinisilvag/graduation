#include <iostream>

using namespace std;

int seq(int n, int start) {
    int surpass = 0;

    for(int i = 1; i < n; i++) {
        if(start == 1) surpass = 1;

        if(start % 2 == 0) start = start / 2;
        else start = (3 * start) + 1;
    }

    if(surpass == 1) return 0;
    else return start;
}

int main() {
    int n = 16;
    int start = 11;

    cout << seq(n, start) << endl;
}
