template <typename T>
class SmartPointer {
private:
    T* pointer;

public:
    explicit SmartPointer(T* ptr = nullptr) : pointer(ptr) {}

    ~SmartPointer() {
        delete pointer;
    }

    SmartPointer(const SmartPointer& other) {
        pointer = new T(*other.pointer);
    }

    SmartPointer& operator=(const SmartPointer& other) {
        if (this == &other) {
            return *this;
        }

        delete pointer;
        pointer = new T(*other);

        return *this;
    }

    T* operator->() const {
        return pointer;
    }

    T& operator*() const {
        return *pointer;
    }
};
