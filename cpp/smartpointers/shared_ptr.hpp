#include <cstdint>
#include <iomanip>
#include <stdexcept>

namespace usu
{
    // shared_ptr class
    template <typename T>
    class shared_ptr
    {
      public:
        shared_ptr();
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

    // Default constructor
    template <typename T>
    shared_ptr<T>::shared_ptr()
    {
        refCount = new std::uint32_t(1);
    }

    // Overloaded constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(T* point) :
        shared_ptr()
    {
        pointer = point;
    }

    // Destructor
    template <typename T>
    shared_ptr<T>::~shared_ptr()
    {
        (*refCount)--;
        if (*refCount == 0)
        {
            delete[] refCount;
            pointer = NULL;
            refCount = NULL;
        }
    }

    // Copy constructor
    template <typename T>
    shared_ptr<T>::shared_ptr(shared_ptr<T>& copy)
    {
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
        (*refCount)++;

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
    uint32_t shared_ptr<T>::use_count() { return *refCount; }

    template <typename T>
    uint32_t* shared_ptr<T>::getRefCount() { return refCount; }

    // shared_ptr class to raw array
    template <typename T>
    class shared_ptr<T[]>
    {
      public:
        // Default constructor
        shared_ptr()
        {
            refCount = new std::uint32_t(1);
        }

        // Overloaded constructor
        shared_ptr(T* array, unsigned int elements) :
            shared_ptr()
        {
            arrayPoint = array;
            elementsNum = elements;
        }

        // Destructor
        ~shared_ptr()
        {
            (*refCount)--;
            if (*refCount == 0)
            {
                delete[] arrayPoint;
                delete[] refCount;
            }
        }

        // Copy constructor
        shared_ptr(shared_ptr<T[]>& copy)
        {
            arrayPoint = copy.arrayPoint;
            refCount = copy.refCount;
            elementsNum = copy.elementsNum;
            (*refCount)++;
        }

        // Move constructor
        shared_ptr(shared_ptr<T[]>&& move)
        {
            arrayPoint = move.pointer;
            refCount = move.refCount;
            elementsNum = move.elementsNum;
        }

        // Assignment operator overload
        shared_ptr<T>& operator=(shared_ptr<T[]>& rhs)
        {
            (*refCount)--;
            arrayPoint = rhs.arrayPointpointer;
            refCount = rhs.refCount;
            elementsNum = rhs.elementsNum;
            (*refCount)++;
            return *this;
        }

        // Move assignment operator overload
        shared_ptr<T>& operator=(shared_ptr<T>&& rhs)
        {
            arrayPoint = rhs.arrayPointpointer;
            refCount = rhs.refCount;
            elementsNum = rhs.elementsNum;
            return *this;
        }

        // Index access operator overload (read only)
        T operator[](unsigned int index) const
        {
            if (index > elementsNum)
            {
                throw std::out_of_range("Index exceeds total number of elements");
            }
            return arrayPoint[index];
        }

        // Index access operator overload (write only)
        T& operator[](unsigned int index)
        {
            if (index > elementsNum)
            {
                throw std::out_of_range("Index exceeds total number of elements");
            }
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
} // namespace usu
