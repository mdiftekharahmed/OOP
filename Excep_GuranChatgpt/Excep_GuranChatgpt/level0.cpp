//Object may become inconsistent and resources may leak
//Allocated memory that was never released because execution jumped immediately to catch.
#include <iostream>
#include <stdexcept>
using namespace std;

class BadBuffer {
private:
    int* data;
    int size;
public:
    BadBuffer(int s) {
        size = s;
        data = new int[size];
    }
    ~BadBuffer() {
        delete[] data;
    }
    void resizeBad(int newSize) {
        // Allocate new memory
        int* newData = new int[newSize];
        // Object state is changed too early
        size = newSize;
        // Simulate failure
        throw runtime_error("Failure during resize");
        // Never executed
        delete[] data;
        data = newData;
    }
    int getSize() const {
        return size;
    }
};

int main() {
    BadBuffer buffer(5);
    cout << "Before resize, size = "
         << buffer.getSize() << endl;
    try {
        buffer.resizeBad(10);
    }
    catch (const exception& e) {
        cout << "Exception: "
             << e.what() << endl;
    }
    cout << "After failure, size = "
         << buffer.getSize() << endl;

    return 0;
}