#include <iostream>
#include <stdexcept>  

template <typename T>
class UniquePtr {
private:
    T* ptr;

public:
    explicit UniquePtr(T* p = nullptr) : ptr(p) {}

    UniquePtr(const UniquePtr& other) = delete;
    UniquePtr& operator=(const UniquePtr& other) = delete;

    ~UniquePtr() {
        delete ptr;
    }

    T& operator*() const {
        if (ptr == nullptr) {
            throw std::runtime_error("Ошибка: разыменование пустого UniquePtr");
        }
        return *ptr;
    }

    T* operator->() const {
        if (ptr == nullptr) {
            throw std::runtime_error("Ошибка: обращение через пустой UniquePtr");
        }
        return ptr;
    }

    T* release() {
        T* temp = ptr;
        ptr = nullptr;
        return temp;
    }

    T* get() const {
        return ptr;
    }

    explicit operator bool() const {
        return ptr != nullptr;
    }

    void reset(T* p = nullptr) {
        delete ptr;
        ptr = p;
    }

    void swap(UniquePtr& other) {
        std::swap(ptr, other.ptr);
    }
};

int main() {
    setlocale(LC_ALL, "RUS");

    UniquePtr<int> p1(new int(42));
    std::cout << *p1 << std::endl;  // 42

    UniquePtr<int> p2;

    try {
        std::cout << *p2 << std::endl;  
    }
    catch (const std::runtime_error& e) {
        std::cout << "Ошибка: " << e.what() << std::endl;
    }

    int* raw_ptr = p1.release();
    std::cout << *raw_ptr << std::endl;
    delete raw_ptr;

    UniquePtr<int> p3(new int(100));
    p3.reset(new int(200));

    UniquePtr<int> p4;
    if (!p4) {
        std::cout << "p4 пуст" << std::endl;
    }

    UniquePtr<int> p5(new int(999));
    p5.release();  

    try {
        std::cout << *p5 << std::endl; 
    }
    catch (const std::runtime_error& e) {
        std::cout << "Ещё одна ошибка: " << e.what() << std::endl;
    }

    return 0;
}