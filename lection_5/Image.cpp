#include <iostream>
#include <stdexcept>

class Image {
    int* img;
    int mx, my;

public:
    Image(int tmx, int tmy) : mx(tmx), my(tmy) {
        img = new int[mx * my]();
    }

    Image(const Image& v) : mx(v.mx), my(v.my) {
        img = new int[mx * my];
        for (int i = 0; i < mx * my; i++) {
            img[i] = v.img[i];
        }
    }

    Image& operator=(const Image& v) {
        if (this == &v) {
            return *this;
        }

        delete[] img;
        mx = v.mx;
        my = v.my;
        img = new int[mx * my];
        for (int i = 0; i < mx * my; i++) {
            img[i] = v.img[i];
        }

        return *this;
    }

    virtual ~Image() {
        delete[] img;
    }

    int get(int x, int y) {
        if (x < 0 || x >= mx || y < 0 || y >= my) {
            throw std::out_of_range("Invalid coordinates");
        }
        return img[y * mx + x];
    }

    void set(int x, int y, int color) {
        if (x < 0 || x >= mx || y < 0 || y >= my) {
            throw std::out_of_range("Invalid coordinates");
        }
        img[y * mx + x] = color;
    }

    friend std::ostream& operator<<(std::ostream& out, const Image& d1) {
        for (int y = 0; y < d1.my; y++) {
            for (int x = 0; x < d1.mx; x++) {
                out << d1.get(x, y) << ' ';
            }
            out << '\n';
        }
        return out;
    }

    friend bool operator==(const Image& arrInt, const Image& arrInt2) {
        if (arrInt.mx != arrInt2.mx || arrInt.my != arrInt2.my) {
            return false;
        }

        for (int i = 0; i < arrInt.mx * arrInt.my; i++) {
            if (arrInt.img[i] != arrInt2.img[i]) {
                return false;
            }
        }

        return true;
    }
};

int main() {
    Image image1(3, 3);
    image1.set(0, 0, 1);
    image1.set(1, 1, 2);
    image1.set(2, 2, 3);

    Image image2 = image1;
    Image image3(3, 3);
    image3.set(0, 0, 1);
    image3.set(1, 1, 2);
    image3.set(2, 2, 3);

    std::cout << "Image 1:\n" << image1;
    std::cout << "Image 2:\n" << image2;
    std::cout << "Image 3:\n" << image3;

    std::cout << "image1 == image2: " << std::boolalpha << (image1 == image2) << '\n';
    std::cout << "image1 == image3: " << std::boolalpha << (image1 == image3) << '\n';

    try {
        std::cout << "Pixel (0, 0) of image1: " << image1.get(0, 0) << '\n';
        std::cout << "Pixel (1, 1) of image1: " << image1.get(1, 1) << '\n';
        std::cout << "Pixel (2, 2) of image1: " << image1.get(2, 2) << '\n';
        std::cout << "Pixel (3, 3) of image1: " << image1.get(3, 3) << '\n';  // Out of range
    } catch (const std::out_of_range& e) {
        std::cout << "Exception: " << e.what() << '\n';
    }

    return 0;
}
