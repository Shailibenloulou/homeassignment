#include <iostream>
#include <stdexcept>

class CVectorInt {
private:
    int* Vec;
    int vecCapacity;
    int vecSize;

public:
    CVectorInt(int cap = 0) {
        vecCapacity = cap;
        vecSize = 0;
        Vec = new int[vecCapacity];
    }

    ~CVectorInt() {
        delete[] Vec;
    }

    int getCapacity() const { 
        return vecCapacity;
    }

    int size() const { 
        return vecSize;
    }

    bool isEmpty() const { 
        return (vecSize == 0);
    }

    void clear() {
        for (int i = 0; i < vecSize; i++)
            Vec[i] = 0;
        vecSize = 0;
        vecCapacity = 0;
    }

    void remove(int index) {
        if (index < vecSize) {
            for (int i = index; i < vecSize - 1; i++) {
                Vec[i] = Vec[i + 1];
            }
            vecSize--;
            if (vecSize <= vecCapacity / 2) {
                vecCapacity = vecCapacity / 2;
                resize(vecCapacity);
            }
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    void push_back(int val) {
        if (vecSize == vecCapacity) {
            vecCapacity = vecCapacity == 0 ? 1 : vecCapacity * 2;
            resize(vecCapacity);
        }
        Vec[vecSize] = val;
        vecSize++;
    }

    int pop_back() {
        if (vecSize > 0) {
            int temp = Vec[vecSize - 1];
            vecSize--;
            if (vecSize <= vecCapacity / 2) {
                vecCapacity = vecCapacity / 2;
                resize(vecCapacity);
            }
            return temp;
        }
        else {
            throw std::out_of_range("Vector is empty");
        }
    }

    int& operator[](int index) {
        if (index >= 0 && index < vecSize) {
            return Vec[index];
        }
        else {
            throw std::out_of_range("Index out of range");
        }
    }

    void reserve(int cap) {
        if (cap > vecCapacity) {
            vecCapacity = cap;
            resize(vecCapacity);
        }
    }

private:
    void resize(int newCapacity) {
        int* newVec = new int[newCapacity];
        for (int i = 0; i < vecSize; i++) {
            newVec[i] = Vec[i];
        }
        delete[] Vec;
        Vec = newVec;
    }
};

int main(int argc, char* argv[]) {
    try {
        CVectorInt v(5);

        for (int i = 0; i < 5; i++) {
            v.push_back(i);
        }
        std::cout << "the size is: " << v.size() << std::endl;
        std::cout << "the capacity is: " << v.getCapacity() << std::endl;
        v.push_back(1);
        std::cout << "the size is: " << v.size() << std::endl;
        std::cout << "the capacity is: " << v.getCapacity() << std::endl;
        while (!v.isEmpty()) {
            v.pop_back();
        }
        std::cout << "the size is: " << v.size() << std::endl;
        std::cout << "the capacity is: " << v.getCapacity() << std::endl;
        v.reserve(15);
        std::cout << "the size is: " << v.size() << std::endl;
        std::cout << "the capacity is: " << v.getCapacity() << std::endl;
        for (int i = 0; i < 15; i++) {
            v.push_back(i);
        }
        v[5] = 3;
        for (int i = 0; i < v.size(); i++) {
            std::cout << v[i] << " ";
        }
        std::cout << std::endl;
        v.clear();
        std::cout << "the size is: " << v.size() << std::endl;
        std::cout << "the capacity is: " << v.getCapacity() << std::endl;
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
    }

    return 0;
}