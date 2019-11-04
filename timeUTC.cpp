#include <iostream>
using namespace std;

int TimeFormat24(int h) {
    if(h > 23) {
        h -= 24;
    } else if(h < 0) {
        h += 24;
    }

    return h;
}
inline int HoursInUTC0(int h, int utc) {
    return h - utc;
}

int main() {
    int h, a, b, utc0, answer;
    h = a = b = utc0 = answer = 0;

    cin >> h >> a >> b;
    
    int TimeInUTC0 = TimeFormat24(HoursInUTC0(h,a));

    cout << TimeFormat24(TimeInUTC0+b) << endl;

    cin.ignore(32768,'\n');
    cin.get();

    return 0;
}