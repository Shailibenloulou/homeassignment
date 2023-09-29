//	1. Implement this addition in the MyBool class (implemented)
//  2. Did it compile successfully? yes it did
//	3. Did it run successfully? yes it did
//	4. Explain the result, explain what happened and why
// the code checks that the pointer is not null and also that the value it contains is greater than zero
// if so, it increments the integer value pointed to and prints the result.

#include <iostream>

class MyBool
{
private:
    bool m_val;

public:
    MyBool(bool b) : m_val(b) {}

    MyBool operator&&(const MyBool& other) const {
        return MyBool(m_val && other.m_val);
    }

    explicit operator bool() const {
        return m_val;
    }

};

MyBool notNull(int* intPtr) {
    return (intPtr != nullptr);
}

MyBool greaterThanZero(int* intPtr) {
    return *intPtr > 0;
}

int main(int argc, char* argv[]) {
    int* a = nullptr;
    int val = 5;
    int* b = &val;

    if (notNull(b) && greaterThanZero(b)) {
        ++* b;
        std::cout << "*b is " << *b << std::endl;
    }

    if (notNull(a) && greaterThanZero(a)) {
        ++* a;
        std::cout << "*a is " << *a << std::endl;
    }

    return 0;
}