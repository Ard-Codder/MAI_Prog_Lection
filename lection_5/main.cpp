#include <iostream>

struct MyClass {
    int value;

    MyClass(int val) : value(val) {}

    void printValue() {
        std::cout << "Value: " << value << std::endl;
    }
};

int main() {
    SmartPointer<MyClass> smartPtr(new MyClass(42));
    smartPtr->printValue();  // Output: Value: 42

    SmartPointer<MyClass> anotherPtr = smartPtr;  // Copy constructor
    (*anotherPtr).printValue();  // Output: Value: 42

    SmartPointer<MyClass> thirdPtr;
    thirdPtr = anotherPtr;  // Assignment operator
    thirdPtr->printValue();  // Output: Value: 42

    return 0;
}
