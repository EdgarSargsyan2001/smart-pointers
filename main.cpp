#include <iostream>
#include "shared_ptr.hpp"
#include "unique_ptr.hpp"

struct A
{
    int val;
    A(int n) : val(n)
    {
        std::cout << "A ctor\n";
    }
    ~A()
    {
        std::cout << "A dtor\n";
    }
};

int main()
{
    // unique ptr
    unique_ptr<A> p1(new A(4));
    std::cout << p1->val << '\n';

    unique_ptr<A> p2(new A(2));
    p2 = std::move(p1);

    // shared_ptr

    shared_ptr<int> ptr1(new int(10));
    shared_ptr<int> ptr2 = ptr1; // Copy construction

    std::cout << "Count after copy construction: " << ptr1.get_count() << std::endl;

    {
        shared_ptr<int> ptr3(new int(20));
        shared_ptr<int> ptr4;
        ptr4 = ptr3; // Copy assignment

        std::cout << "Count inside inner scope: " << ptr3.get_count() << std::endl;
    }

    std::cout << "Count after inner scope: " << ptr2.get_count() << std::endl;
}