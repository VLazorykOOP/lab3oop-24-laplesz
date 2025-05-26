#include <iostream>
#include <new>

using namespace std;

class Vector {
private:
    double* data;
    int size;
    int state;
    static int objectCount;

public:
    Vector() : size(1), state(0) {
        data = new(nothrow) double[1] {0.0};
        if (data) {
            objectCount++;
        }
        else {
            state = -1;
            cerr << "Error: memory lack!" << endl;
        }
    }

    Vector(int n) : size(n), state(0) {
        if (n <= 0) {
            cerr << "Error: wrong vector's size!" << endl;
            data = nullptr;
            size = 0;
            state = -1;
            return;
        }
        data = new(nothrow) double[n] {0.0};
        if (data) {
            objectCount++;
        }
        else {
            state = -1;
            cerr << "Error: memory lack!" << endl;
        }
    }

    Vector(int n, double value) : size(n), state(0) {
        if (n <= 0) {
            cerr << "Error: wrong vector's size!" << endl;
            data = nullptr;
            size = 0;
            state = -1;
            return;
        }
        data = new(nothrow) double[n];
        if (data) {
            for (int i = 0; i < n; i++) data[i] = value;
            objectCount++;
        }
        else {
            state = -1;
            cerr << "Error: memory lack!" << endl;
        }
    }

    Vector(const Vector& other) : size(other.size), state(other.state) {
        data = new(nothrow) double[size];
        if (data) {
            for (int i = 0; i < size; i++) data[i] = other.data[i];
            objectCount++;
        }
        else {
            state = -1;
            cerr << "Error: memory lack!" << endl;
        }
    }

    Vector& operator=(const Vector& other) {
        if (this == &other) return *this;

        delete[] data;

        size = other.size;
        state = other.state;
        data = new(nothrow) double[size];
        if (data) {
            for (int i = 0; i < size; i++) data[i] = other.data[i];
        }
        else {
            state = -1;
            cerr << "Error: memory lack!" << endl;
        }
        return *this;
    }

    ~Vector() {
        delete[] data;
        objectCount--;
    }

    void setElement(int index, double value = 0.0) {
        if (index < 0 || index >= size) {
            cerr << "Error: going beyond the array!" << endl;
            state = -1;
            return;
        }
        data[index] = value;
    }

    double getElement(int index) const {
        if (index < 0 || index >= size) {
            cerr << "Error: going beyond the array!" << endl;
            return 0.0;
        }
        return data[index];
    }

    void print() const {
        cout << "[ ";
        for (int i = 0; i < size; i++) {
            cout << data[i] << " ";
        }
        cout << "]" << endl;
    }

    Vector operator+(const Vector& other) const {
        int minSize = (size < other.size) ? size : other.size;
        Vector result(minSize);
        for (int i = 0; i < minSize; i++) {
            result.data[i] = data[i] + other.data[i];
        }
        return result;
    }

    Vector operator-(const Vector& other) const {
        int minSize = (size < other.size) ? size : other.size;
        Vector result(minSize);
        for (int i = 0; i < minSize; i++) {
            result.data[i] = data[i] - other.data[i];
        }
        return result;
    }

    Vector operator*(double scalar) const {
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] * scalar;
        }
        return result;
    }

    Vector operator/(double scalar) const {
        if (scalar == 0) {
            cerr << "Error: /0!" << endl;
            return Vector(size);
        }
        Vector result(size);
        for (int i = 0; i < size; i++) {
            result.data[i] = data[i] / scalar;
        }
        return result;
    }

    bool operator==(const Vector& other) const {
        if (size != other.size) return false;
        for (int i = 0; i < size; i++) {
            if (data[i] != other.data[i]) return false;
        }
        return true;
    }

    bool operator<(const Vector& other) const {
        return size < other.size;
    }

    bool operator>(const Vector& other) const {
        return size > other.size;
    }

    static int getObjectCount() {
        return objectCount;
    }
};

int Vector::objectCount = 0;

int main() {
    int size;
    cout << "Enter size of vector: ";
    cin >> size;

    if (size <= 0) {
        cerr << "Invalid size!" << endl;
        return 1;
    }

    Vector userVector(size);
    cout << "Enter " << size << " elements for the vector:\n";
    for (int i = 0; i < size; ++i) {
        double value;
        cout << "Element [" << i << "]: ";
        cin >> value;
        userVector.setElement(i, value);
    }

    cout << "Your vector: ";
    userVector.print();

    Vector userVector2(size);
    cout << "\nEnter " << size << " elements for the second vector:\n";
    for (int i = 0; i < size; ++i) {
        double value;
        cout << "Element [" << i << "]: ";
        cin >> value;
        userVector2.setElement(i, value);
    }

    cout << "Second vector: ";
    userVector2.print();

    Vector sum = userVector + userVector2;
    cout << "\nSum: ";
    sum.print();

    Vector diff = userVector - userVector2;
    cout << "Difference: ";
    diff.print();

    double scalar;
    cout << "\nEnter a scalar value to multiply the first vector: ";
    cin >> scalar;

    Vector scaled = userVector * scalar;
    cout << "Scaled vector: ";
    scaled.print();

    cout << "\nAre the vectors equal? " << (userVector == userVector2 ? "Yes" : "No") << endl;

    cout << "Total active Vector objects: " << Vector::getObjectCount() << endl;

    return 0;
}
