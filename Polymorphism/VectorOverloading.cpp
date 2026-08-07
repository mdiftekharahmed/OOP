#include <iostream>
#include <cmath>
using namespace std;

class Vector2D {
private:
    double x, y;

public:
    Vector2D(double x = 0, double y = 0) : x(x), y(y) {}

    // ── Arithmetic ────────────────────────────────────────────────
    Vector2D operator+(const Vector2D& v) const { return {x+v.x, y+v.y}; }
    Vector2D operator-(const Vector2D& v) const { return {x-v.x, y-v.y}; }

    // Scalar multiplication: v * 3.0
    Vector2D operator*(double scalar)     const { return {x*scalar, y*scalar}; }

    // Dot product: v1 * v2
    double   operator*(const Vector2D& v) const { return x*v.x + y*v.y; }

    // ── Compound assignment ───────────────────────────────────────
    Vector2D& operator+=(const Vector2D& v) { x+=v.x; y+=v.y; return *this; }
    Vector2D& operator-=(const Vector2D& v) { x-=v.x; y-=v.y; return *this; }

    // ── Unary operators ───────────────────────────────────────────
    Vector2D operator-() const { return {-x, -y}; }  // negate

    // ── Comparison ────────────────────────────────────────────────
    bool operator==(const Vector2D& v) const { return x==v.x && y==v.y; }
    bool operator!=(const Vector2D& v) const { return !(*this==v); }

    // Compare by magnitude
    bool operator< (const Vector2D& v) const { return magnitude() < v.magnitude(); }
    bool operator> (const Vector2D& v) const { return v < *this; }

    // ── Subscript operator: v[0] = x, v[1] = y ───────────────────
    double operator[](int index) const {
        if (index == 0) return x;
        if (index == 1) return y;
        throw out_of_range("Index must be 0 or 1.");
    }

    // ── Utility ───────────────────────────────────────────────────
    double magnitude() const { return sqrt(x*x + y*y); }

    // ── Stream operator ───────────────────────────────────────────
    friend ostream& operator<<(ostream& out, const Vector2D& v) {
        out << "(" << v.x << ", " << v.y << ")";
        return out;
    }
};

int main() {
    Vector2D v1(3.0, 4.0);
    Vector2D v2(1.0, 2.0);

    cout << "v1          = " << v1          << "\n";  // (3, 4)
    cout << "v2          = " << v2          << "\n";  // (1, 2)
    cout << "v1 + v2     = " << (v1 + v2)   << "\n";  // (4, 6)
    cout << "v1 - v2     = " << (v1 - v2)   << "\n";  // (2, 2)
    cout << "v1 * 2.0    = " << (v1 * 2.0)  << "\n";  // (6, 8)
    cout << "v1 dot v2   = " << (v1 * v2)   << "\n";  // 11
    cout << "|v1|        = " << v1.magnitude() << "\n"; // 5
    cout << "v1[0]       = " << v1[0]        << "\n";  // 3
    cout << "v1[1]       = " << v1[1]        << "\n";  // 4
    cout << "v1 > v2     : " << (v1 > v2 ? "true":"false") << "\n"; // true

    v1 += v2;
    cout << "v1 after += : " << v1 << "\n";           // (4, 6)
}
