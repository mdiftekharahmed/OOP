#include <iostream>
using namespace std;

class Point {
public:
    int x, y;

    Point(int a, int b) : x(a), y(b) {}

    Point operator-(const Point& other) {
        return Point(x - other.x,
                     y - other.y);
    }
};

int main() {
    Point p1(8,7);
    Point p2(2,3);

    Point p3 = p1 - p2;

    cout << p3.x << " " << p3.y << endl;
}