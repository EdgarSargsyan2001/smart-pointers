#include <iostream>
#include "shared_ptr.h"
#include "unique_ptr.h"

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

    int arr[] = {1, 2, 3, 4};
    unique_ptr<int> arrPtr(arr);
    std::cout << arrPtr[2] << '\n';

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