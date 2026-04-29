#include <iostream>

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
        return *ptr;
    }

    T* operator->() const {
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

    std::cout << *p1 << std::endl;  

    int* raw_ptr = p1.release();  
    std::cout << *raw_ptr << std::endl;  

    delete raw_ptr;  

    UniquePtr<int> p3(new int(100));
    p3.reset(new int(200));  

    UniquePtr<int> p4;
    if (!p4) {
        std::cout << "p4 пуст" << std::endl;
    }

    return 0;
}  