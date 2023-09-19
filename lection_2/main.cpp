#include <iostream>
#include <cstring>

class FooString {
private:
    char* buf;

public:
    FooString(char* tbuf) {
        int length = std::strlen(tbuf);
        buf = new char[length + 1];
        std::strcpy(buf, tbuf);
    }

    ~FooString() {
        delete[] buf;
    }

    void show() {
        std::cout << buf << std::endl;
    }

    bool compare(FooString str) {
        return std::strcmp(buf, str.buf) == 0;
    }
};

void runTests() {

    // Тесты для метода compare(FooString str)
    {
        FooString str1("Hello");
        FooString str2("Hello");
        bool result = str1.compare(str2);
        bool expected = true;
        std::cout << "compare(FooString) Test 1: " << (result == expected ? "Passed" : "Failed") << std::endl;

        FooString str3("World");
        result = str1.compare(str3);
        expected = false;
        std::cout << "compare(FooString) Test 2: " << (result == expected ? "Passed" : "Failed") << std::endl;
    }
}

int main() {
    runTests();

    return 0;
}
