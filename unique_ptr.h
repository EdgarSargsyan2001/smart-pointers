#ifndef UNIQUE_PTR_H
#define UNIQUE_PTR_H

template <typename T>
class unique_ptr
{
public:
    // ctor , dtor
    constexpr unique_ptr(T *p) noexcept;
    constexpr unique_ptr(T p) noexcept;
    ~unique_ptr();

    // copy operation is implicitly declared as deleted because 'unique_ptr<A>'
    // declares a move constructor or move assignment operator

    // move asignment operator
    unique_ptr<T> &operator=(unique_ptr<T> &&rhs) noexcept;

    // methods
    void swap(unique_ptr<T> &rhs) noexcept;

    // operators
    T &operator*();
    T *operator->();
    T &operator[](int i);

private:
    T *_ptr;
};

template <typename T>
constexpr unique_ptr<T>::unique_ptr(T *p) noexcept
    : _ptr(p)
{
}
template <typename T>
constexpr unique_ptr<T>::unique_ptr(T p) noexcept
    : _ptr(new T(p))
{
}
template <typename T>
unique_ptr<T>::~unique_ptr()
{
    delete _ptr;
}

template <typename T>
unique_ptr<T> &unique_ptr<T>::operator=(unique_ptr<T> &&rhs) noexcept
{
    if (this != &rhs)
    {
        delete _ptr;
        _ptr = rhs._ptr;
        rhs._ptr = nullptr;
    }
    return *this;
}
template <typename T>
void unique_ptr<T>::swap(unique_ptr<T> &rhs) noexcept
{
    std::swap(_ptr, rhs._ptr);
}

template <typename T>
T &unique_ptr<T>::operator*()
{
    return *_ptr;
}

template <typename T>
T *unique_ptr<T>::operator->()
{
    return _ptr;
}

template <typename T>
T &unique_ptr<T>::operator[](int i)
{
    return _ptr[i];
}

#endif // UNIQUE_PTR_H