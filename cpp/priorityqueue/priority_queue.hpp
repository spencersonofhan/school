#include <exception>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <utility>
#include <vector>

namespace usu
{
    template <typename T>
    using TPriori = std::pair<T, unsigned int>;

    template <typename T, typename R = unsigned int>
    class priority_queue
    {
      public:
        using value_type = T;
        using priority_type = R;
        using size_type = unsigned int;
        using TPriori = std::pair<T, R>;

        class node
        {
          private:
            value_type value;
            priority_type priority;

          public:
            node() = default;
            node(value_type theValue, priority_type thePriority) :
                node()
            {
                value = theValue;
                priority = thePriority;
            }

            int compareTo(const node& comperator)
            {
                if (priority < comperator.getPriority())
                {
                    return -1;
                }
                else if (priority > comperator.getPriority())
                {
                    return 1;
                }
                else
                {
                    return 0;
                }
            }
            value_type getValue() { return value; }
            priority_type getPriority() { return priority; }
        };

        std::vector<node> Q;

        // Default constructor
        priority_queue()
        {
            std::vector<node> theQ;
            numElements = 0;
            lastIndex = 0;

            Q = theQ;
        }

        // Overloaded constructor for initializer_list
        priority_queue(std::initializer_list<TPriori> initList) :
            priority_queue()
        {
            for (auto item : initList)
            {
                enqueue(item.first, item.second);
            }
        }

        void enqueue(value_type value, priority_type priority)
        {
            numElements++;

            // // This is only for the priority queue at the beginning
            // if (numElements >= capacity())
            // {
            beginCheck();
            // }
            //
            // /*
            // while loop beats std::vector to the punch with resizing first since
            // std::vectors size doubles automagically if elements equals half capacity
            // */
            // while (numElements > (capacity() / 2) - 1)
            // {
            //     resize();
            // }

            node newNode(value, priority);
            Q[(numElements)-1] = newNode;
            lastIndex = numElements - 1;
        }
        // auto dequeue();
        // iterator find(value_type value);
        // void update(iterator i, priority_type priority);

        // bool empty();
        // iterator begin();
        // iterator end();

        // void resize(unsigned int reduced);
        void beginCheck()
        {
            // This is only for the priority queue at the beginning
            if (numElements >= capacity())
            {
                while (numElements >= capacity())
                {
                    resize();
                }
                return;
            }
            /*
            while loop beats std::vector to the punch with resizing first since
            std::vectors size doubles automagically if elements equals half capacity
            */
            if (numElements > (capacity() / 2) - 1)
            {
                while (numElements > (capacity() / 2) - 1)
                {
                    resize();
                }
            }

            // while (numElements >= capacity())
            // {
            //     resize();
            // }
        }

        // This enlargens size of 'Q' ==>new_size = (current size) * 1.25 + 1
        void resize()
        {
            unsigned int newSize = capacity() * 1.25 + 1;
            Q.resize(newSize);
            std::cout << "CAPACITY AFTER RESIZE: " << capacity() << std::endl;
        }

        // Simple function that returns the max size of Q
        unsigned int capacity() { return Q.capacity(); }
        // Returns the index of that last element in the array that matters
        unsigned int getLastIndex() { return lastIndex; }
        // Returns total amount of elements in Q
        unsigned int size() { return numElements; }
        // Returns 'Q'
        std::vector<node> getQ() { return Q; }

        // class iterator
        // {
        //   public:
        //     using iterator_category = std::forward_iterator_tag;
        //     iterator() :
        //         iterator(nullptr) {}
        //
        //     iterator(value_type* pointer) :
        //         m_data(ptr), m_pos(0) {}
        //
        //     iterator(unsigned int pos, value_type* pointer) :
        //         m_pos(pos), m_data(ptr) {}
        //
        //     // NEEDS
        //     // Copy constructor
        //     // Move constructor
        //     // Copy assignment op
        //     // Move assignment op
        //     // Incrementable
        //     // Dereferencable
        //
        //   private:
        //     unsigned int m_pos;
        //     // pointer to the data
        //     value_type* m_data;
        // };

      private:
        unsigned int numElements;
        unsigned int lastIndex;
        // std::vector<node> Q;
    };

    // auto dequeue();
    // iterator find(T value);
    // void update(iterator i, priority_type priority);
    // bool empty();

    // iterator begin();
    // iterator end();

    // // This reduces size of 'Q'
    // template <typename T>
    // void priority_queue<T>::resize(unsigned int smallSize)
    // {
    //     unsigned int newSize = capacity() * 1.25 + 1;
    //     Q.resize(newSize);
    //     std::cout << "CAPACITY AFTER RESIZE: " << capacity() << std::endl;
    // }

} // namespace usu
