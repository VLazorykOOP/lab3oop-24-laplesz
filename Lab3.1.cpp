#include <iostream>

using namespace std;

class Rectangle {
    double height, width;
    unsigned int color;

public:
    Rectangle() : height(1.0), width(1.0), color(0) {}
    Rectangle(double h, double w, int c = 0) {
        setHeight(h);
        setWidth(w);
        setColor(c);
    }

    double getHeight() const { return height; }
    double getWidth() const { return width; }
    int getColor() const { return color; }

    void setHeight(double h) {
        if (h > 0 && h < 1.e+100)
            height = h;
        else
            cout << "Wrong heigh!\n";
    }

    void setWidth(double w) {
        if (w > 0 && w < 1.e+100)
            width = w;
        else
            cout << "Wrong width!\n";
    }

    void setColor(int c) {
        if (c >= 0 && c <= 10000)
            color = c;
        else
            cout << "Wrong colour!\n";
    }

    double area() const { return height * width; }
    double perimeter() const { return 2 * (height + width); }

    void printInfo() const {
        cout << "Heigh = " << height
            << ", Width = " << width
            << ", Colour = " << color
            << "\nArea = " << area()
            << ", Perimeter = " << perimeter() << "\n";
    }
};

int main() {
    Rectangle rect1;
    rect1.printInfo();

    double h, w;
    int c;
    cout << "Input heigh, width and colour: ";
    cin >> h >> w >> c;

    Rectangle rect2(h, w, c);
    rect2.printInfo();

    rect2.setHeight(-5);
    rect2.setWidth(2.e100);
    rect2.setColor(10001);
    rect2.printInfo();

    rect2.setHeight(5);
    rect2.setWidth(10);
    rect2.setColor(500);
    rect2.printInfo();

    return 0;
}