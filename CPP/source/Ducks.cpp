#include <iostream>
using namespace std;

int main()
{
    int a, b, c = 1;
    a = b = 0;
    cin >> a >> b;

    while (!(((c - 1) % a == 0) && ((c + 1) % b == 0)))
        c += 1;

    cout << c << endl;

    cin.ignore(32768,'\n');
    cin.get();

    return 0;
}
