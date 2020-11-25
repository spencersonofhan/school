#include <iomanip>
#include <cstdint>
#include <iostream>
#include <array>
#include <stdexcept>



namespace usu
{
    template <typename T>
    class shared_ptr
    {
    public:
        shared_ptr(T* point);
        ~shared_ptr();
        shared_ptr(shared_ptr<T>& copy);
        shared_ptr(shared_ptr<T>&& move);
        shared_ptr<T>& operator=(shared_ptr<T>& rhs);
        shared_ptr<T>& operator=(shared_ptr<T>&& rhs);
        T* operator->();
        T operator*();
        T* get();
        std::uint32_t use_count();
        std::uint32_t* getRefCount();


    private:
        T* pointer;
        std::uint32_t* refCount;
    };


    // Overloaded constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(T* point)
    {
        pointer = point;
        refCount = new std::uint32_t(1);
    }

    // Destructor
    template <typename T>
    shared_ptr<T>::~shared_ptr()
    {
        (*refCount)--;
        if(*refCount == 0)
        {
            // delete[] *pointer;
            delete[] refCount;
            pointer = NULL;
            refCount = NULL;
        }
    }

    // Copy constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>& copy)
    {
        std::cout << "COPYCOP IN EFFECT" << std::endl;

        pointer = copy.pointer;
        refCount = copy.refCount;
        (*refCount)++;
    }

    // Move constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr&& move)
    {
        pointer = move.pointer;
        refCount = move.refCount;
    }

    // Assignment operator overload
    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>& rhs)
    {
        (*refCount)--;
        pointer = rhs.pointer;
        refCount = rhs.refCount;
        (*refCount)++;
        return *this;
    }

    // Move assignment operator overload
    template <typename T>
    shared_ptr<T>& shared_ptr<T>::operator=(shared_ptr<T>&& rhs)
    {
        pointer = rhs.pointer;
        refCount = rhs.refCount;
        return *this;
    }

    // -> operator overload
    template <typename T>
    T* shared_ptr<T>::operator->()
    {
        return pointer;
    }

    // * (dereference) operator overload
    template <typename T>
    T shared_ptr<T>::operator*()
    {
        return *pointer;
    }

    // Returns a pointer to the managed raw pointer
    template <typename T>
    T* shared_ptr<T>::get()
    {
        return pointer;
    }

    // Getters/Setters
    template <typename T>
    uint32_t shared_ptr<T>::use_count(){return *refCount;}

    template <typename T>
    uint32_t* shared_ptr<T>::getRefCount(){return refCount;}



    template<typename T>
    class shared_ptr<T[]>
    {
    public:
        shared_ptr(T* array, unsigned int elements)
        {
            arrayPoint = array;
            refCount = new std::uint32_t(1);
            elementsNum = elements;
        }

        ~shared_ptr()
        {
            (*refCount)--;
            if(*refCount == 0)
            {
                delete[] arrayPoint;
                delete[] refCount;
            }
        }

        T operator[](unsigned int index)
        {
            if(index > elementsNum)
            {
                throw std::out_of_range("Index exceeds total number of elements");
            }
            // T temp =
            return arrayPoint[index];
        }

        unsigned int size()
        {
            return elementsNum;
        }

    private:
        T* arrayPoint;
        std::uint32_t* refCount;
        unsigned int elementsNum;
    };

    // Creating a shared pointer
    template <typename T, typename... Args>
    shared_ptr<T> make_shared(Args&&... args)
    {
        return shared_ptr<T>(new T(std::forward<Args>(args)...));
    }

    // Creating a shared array pointer
    template <typename T, unsigned int N>
    shared_ptr<T[]> make_shared_array()
    {
        return shared_ptr<T[]>(new T[N], N);
    }
}
