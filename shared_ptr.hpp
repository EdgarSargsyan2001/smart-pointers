#ifndef SHARED_PTR_H
#define SHARED_PTR_H

template <typename T>
class shared_ptr
{
public:
    // ctor , dtor
    shared_ptr() noexcept;
    constexpr shared_ptr(T *) noexcept;
    ~shared_ptr() noexcept;

    // copy operation
    shared_ptr(const shared_ptr<T> &rhs);
    shared_ptr<T> &operator=(const shared_ptr<T> &rhs);

    //  move operation
    shared_ptr(shared_ptr<T> &&rhs) noexcept;
    shared_ptr<T> &operator=(shared_ptr<T> &&rhs) noexcept;

    // methods
    void swap(shared_ptr<T> &rhs);
    int get_count() const;

    // operators
    T &operator*();
    T *operator->();
    T &operator[](int i);

private:
    void release();

private:
    T *_ptr;
    int *_count;
};

template <typename T>
shared_ptr<T>::shared_ptr() noexcept
    : _ptr(nullptr), _count(new int(0))
{
}

template <typename T>
constexpr shared_ptr<T>::shared_ptr(T *p) noexcept
    : _ptr(p), _count(new int(1))
{
}

template <typename T>
shared_ptr<T>::~shared_ptr() noexcept
{
    release();
}

// copy operation
template <typename T>
shared_ptr<T>::shared_ptr(const shared_ptr<T> &rhs)
{
    _ptr = rhs._ptr;
    _count = rhs._count;
    ++(*_count);
}

template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(const shared_ptr<T> &rhs)
{
    if (this != &rhs)
    {
        _ptr = rhs._ptr;
        _count = rhs._count;
        ++(*_count);
    }
    return *this;
}

//  move operation
template <typename T>
shared_ptr<T>::shared_ptr(shared_ptr<T> &&rhs) noexcept
{
    _ptr = rhs._ptr;
    _count = rhs._count;
    rhs._ptr = nullptr;
    rhs._count = nullptr;
}
template <typename T>
shared_ptr<T> &shared_ptr<T>::operator=(shared_ptr<T> &&rhs) noexcept
{
    if (this != &rhs)
    {
        release();
        _ptr = rhs._ptr;
        _count = rhs._count;
        rhs._ptr = nullptr;
        rhs._count = nullptr;
    }
    return *this;
}

// methods
template <typename T>
void shared_ptr<T>::swap(shared_ptr<T> &rhs)
{
    std::swap(_ptr, rhs._ptr);
    std::swap(_count, rhs._count);
}

template <typename T>
int shared_ptr<T>::get_count() const
{
    return *_count;
}

template <typename T>
void shared_ptr<T>::release()
{
    if (_ptr)
    {
        if (--(*_count) == 0)
        {
            delete _ptr;
            delete _count;

            _ptr = nullptr;
            _count = nullptr;
        }
    }
}

// operators
template <typename T>
T &shared_ptr<T>::operator*()
{
    return *_ptr;
}

template <typename T>
T *shared_ptr<T>::operator->()
{
    return _ptr;
}

template <typename T>
T &shared_ptr<T>::operator[](int i)
{
    return _ptr[i];
}
#endif // SHARED_PTR_H