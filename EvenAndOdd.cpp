#include <iostream>
using namespace std;

int main() {
    long int res1;
    long int res2;
    long int a,b;
    cin >> a >> b;

    for(int i = a; i <= b; i++) {
        if((i % 2) == 0) {
            res1 += i;
        } else {
            res2 += i;
        }
    }
    cout << ((res1 - res2) + 1) << endl;

    cin.ignore(32768,'\n');
    cin.get();

    return 0;
}