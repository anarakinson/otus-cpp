#include <iostream>
#include <utility>


template <typename T>
class SmartPtr {
public:
    SmartPtr() noexcept = default;
    SmartPtr(T *ptr) noexcept: m_ptr{ptr} {}

    ~SmartPtr() { reset(); }

    // Not copyable
    SmartPtr(const SmartPtr<T> &other) = delete;
    SmartPtr &operator = (const SmartPtr<T> &other) = delete;

    // Movable
    SmartPtr(SmartPtr<T> &&other) noexcept { 
        std::swap(m_ptr, other.m_ptr); 
    }
    SmartPtr &operator = (SmartPtr<T> &&other) noexcept {
        if (this == other) { return this; }

        reset();
        std::swap(m_ptr, other.m_ptr);
        return *this;
    }

    void reset(T *ptr = nullptr) {
        delete m_ptr;
        m_ptr = ptr;
    }

    [[nodiscard]] bool empty() const noexcept { return m_ptr == nullptr; }
    operator bool() const noexcept { return empty(); }

    [[nodiscard]] T *get() noexcept { return m_ptr; }
    [[nodiscard]] const T *get() const noexcept { return m_ptr; }
    
    // * operator to support code like
    // SmartPtr<T> p{new T};
    // *p = T;
    T &operator * () noexcept { return *get(); }
    const T &operator * () const noexcept { return *get(); }
    
    // -> operator to support code like
    // SmartPtr<T> p{new T};
    // p->some_method();
    T *operator -> () noexcept { return get(); }
    const T *operator -> () const noexcept { return get(); }


private:
    T *m_ptr = nullptr;

    template <typename Tt>
    friend std::ostream &operator << (std::ostream &os, const SmartPtr<Tt> &ptr);

};


class SomeClass {
public:
    explicit SomeClass(int a): m_a{a} {}

    int get() { return m_a; }

private:
    int m_a = 0;
};


template <typename T>
std::ostream &operator << (std::ostream &os, const SmartPtr<T> &ptr) {
    os << *ptr.m_ptr << " ";
    return os; 
}


int main() {

    auto x = SmartPtr<int>{new int{12}};

    std::cout << x << std::endl;

    *x = 13;

    std::cout << *x << std::endl;
    std::cout << x.empty() << std::endl;
    
    /*----------------------------------------------------*/

    std::cout << std::endl;

    auto y = SmartPtr<SomeClass>{new SomeClass{12}};

    std::cout << y->get() << std::endl;    

}
