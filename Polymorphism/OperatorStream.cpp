#include <iostream>
using namespace std;

class Point {

public:
    int x, y;

    Point(int a, int b) : x(a), y(b) {}

    friend ostream& operator<<(ostream& out, const Point& p)
    {
        out << "(" << p.x << ", " << p.y << ")";
        return out;
    }
};

int main() {

    Point p(5,7);

    cout << p<<endl;
}