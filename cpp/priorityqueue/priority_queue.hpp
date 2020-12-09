#include <algorithm>
#include <cmath>
#include <cstddef>
#include <exception>
#include <initializer_list>
#include <iomanip>
#include <iostream>
#include <iterator>
#include <memory>
#include <utility>
#include <vector>

namespace usu
{
    template <typename T, typename R = unsigned int>
    class node
    {
      public:
        T value;
        R priority;

        node() = default;
        node(T theValue, R thePriority) :
            node()
        {
            value = theValue;
            priority = thePriority;
        }

        bool operator>(const node& rhs) { return priority > rhs.priority; }
        bool operator<(const node& rhs) { return priority < rhs.priority; }
        bool operator==(const node& rhs) { return priority == rhs.priority; }
        bool operator!=(const node& rhs) { return priority != rhs.priority; }
    };

    template <typename T, typename R = unsigned int>
    class priority_queue
    {
      public:
        using value_type = node<T, R>;
        using priority_type = R;
        using pointer = std::shared_ptr<node<T, R>>;
        using difference_type = std::ptrdiff_t;
        using reference = node<T, R>&;
        using size_type = unsigned int;

        class PIterator : public std::iterator<std::forward_iterator_tag, priority_queue*>
        {
          public:
            using iterator_category = std::forward_iterator_tag;

            PIterator();
            // Overloaded constructors
            PIterator(std::vector<node<T, R>> theData, size_type position);
            // Destructor
            ~PIterator();
            // Copy constructor
            PIterator(const PIterator& copy);
            // Move constructor
            PIterator(PIterator&& move) noexcept;

            // Copy assignmnet operator overload
            PIterator& operator=(const PIterator& copy);
            // Move assignment operator overload
            PIterator& operator=(PIterator&& move);
            // Add
            PIterator& operator+(const int& sum);
            // Pre-increment
            PIterator& operator++();
            // Post-increment
            PIterator operator++(int);

            node<T, R>& operator*();
            node<T, R>* operator->();

            bool operator!=(const PIterator& rhs) const { return this->pos != rhs.pos; }
            bool operator==(const PIterator& rhs) const { return this->pos == rhs.pos; }

          private:
            std::vector<node<T, R>> data;
            size_type pos;
        };

        // Default constructor
        priority_queue()
        {
            numElements = 0;
            std::vector<node<T, R>> theQ;
            Q = theQ;
        }

        // Overloaded constructor for initializer_list
        priority_queue(std::initializer_list<std::pair<T, R>> initList) :
            priority_queue()
        {
            for (auto item : initList)
            {
                enqueue(item.first, item.second);
            }
        }

        PIterator begin()
        {
            return PIterator(Q, 0);
        }

        PIterator end()
        {
            return PIterator(Q, numElements);
        }

        void enqueue(T value, R priority)
        {
            // Checks Q size is adequate
            beginCheck();

            // Max heap operations
            node<T, R> newNode(value, priority);
            maxHeapAdd(newNode);
        }

        auto dequeue()
        {
            if (empty())
            {
                throw std::exception();
            }

            // Extract first element copy
            auto maxNode = Q[0];

            // Swap with last element than delete
            Q[0] = Q[numElements - 1];

            Q.erase(Q.begin() + (numElements - 1));
            numElements--;

            // Check children for bigger priorities
            if (children(0) > 0)
            {
                trickleDown(0);
            }

            return maxNode;
        }

        PIterator find(T value)
        {
            for (auto i = begin(); i != end(); ++i)
            {
                if (i->value == value)
                {
                    return i;
                }
            }
            return end();
        }

        void update(PIterator i, priority_type priority)
        {
            int curr = index(i);
            Q[curr].priority = priority;

            // Check parent
            if (Q[curr] > Q[parent(curr)])
            {
                trickleUp(curr);
            }
            // Check children
            else if (children(curr) > 0)
            {
                trickleDown(curr);
            }
        }

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
        }

        void maxHeapAdd(node<T, R>& newNode)
        {
            numElements++;
            Q[numElements - 1] = newNode;

            // Check parent for smaller values
            int curr = numElements - 1;
            trickleUp(curr);
        }

        void trickleUp(int curr)
        {
            while (Q[curr] > Q[parent(curr)])
            {
                int currParent = parent(curr);
                auto temp = Q[currParent];
                Q[currParent] = Q[curr];
                Q[curr] = temp;
                curr = currParent;
            }
        }

        void trickleDown(int curr)
        {
            size_type lNode = child(curr, 1);
            size_type rNode = child(curr, 2);

            while (children(curr) > 0)
            {
                if (rNode < numElements && children(curr) > 1)
                {
                    if (Q[curr] < Q[lNode] || Q[curr] < Q[rNode])
                    {
                        if (Q[lNode] > Q[rNode])
                        {
                            // Trickle lchild
                            curr = trickle(curr, lNode);
                        }
                        else
                        {
                            // Trickle rchild
                            curr = trickle(curr, rNode);
                        }
                    }
                    else
                    {
                        return;
                    }
                }
                else if ((lNode < numElements) && Q[curr] < Q[lNode])
                {
                    // trickle lchild
                    curr = trickle(curr, lNode);
                }
                else
                {
                    return;
                }

                lNode = child(curr, 1);
                rNode = child(curr, 2);
            }
        }

        size_type trickle(size_type curr, size_type swap)
        {
            auto temp = Q[swap];
            Q[swap] = Q[curr];
            Q[curr] = temp;
            return swap;
        }

        int parent(unsigned int node)
        {
            return node <= 0 ? 0 : (node - 1) / 2;
        }

        int children(unsigned int node)
        {
            int amount = 0;

            if ((2 * node) + 1 < numElements)
            {
                amount++;
            }
            if ((2 * node) + 2 < numElements)
            {
                amount++;
            }

            return amount;
        }

        int child(int node, size_type whichKid)
        {
            switch (whichKid)
            {
                case 1:
                    return (2 * node) + 1;
                case 2:
                    return (2 * node) + 2;
                default:
                    throw std::exception();
            }
        }

        int index(PIterator i)
        {
            int count = 0;
            for (auto j = begin(); j != end(); ++j, count++)
            {
                if (j->value == i->value && j->priority == i->priority)
                {
                    break;
                }
            }

            return count;
        }

        // Returns true if 'Q' is empty
        bool empty()
        {
            return size() == 0;
        }
        // This enlargens size of 'Q' ==>new_size = (current size) * 1.25 + 1
        void resize()
        {
            size_type newSize = capacity() * 1.25 + 1;
            Q.resize(newSize);
        }
        // Simple function that returns the max size of Q
        size_type capacity() { return Q.capacity(); }
        // Returns total amount of elements in Q
        size_type size() const { return numElements; }

      private:
        size_type numElements;
        std::vector<node<T, R>> Q;
    };

    // Overloaded constructor
    template <typename T, typename R = unsigned int>
    priority_queue<T, R>::PIterator::PIterator(std::vector<node<T, R>> theData, size_type position)
    {
        data = theData;
        pos = position;
    }
    // Destructor
    template <typename T, typename R = unsigned int>
    priority_queue<T, R>::PIterator::~PIterator()
    {
    }
    // Copy constructor
    template <typename T, typename R = unsigned int>
    priority_queue<T, R>::PIterator::PIterator(const priority_queue<T, R>::PIterator& copy)
    {
        data = copy.data;
        pos = copy.pos;
    }
    // Move constructor
    template <typename T, typename R = unsigned int>
    priority_queue<T, R>::PIterator::PIterator(priority_queue<T, R>::PIterator&& move) noexcept
    {
        std::swap(data, move.data);
        std::swap(pos, move.pos);
    }
    // Copy assignmnet operator overload
    template <typename T, typename R = unsigned int>
    typename priority_queue<T, R>::PIterator& priority_queue<T, R>::PIterator::operator=(const priority_queue<T, R>::PIterator& copy)
    {
        if (this != &copy)
        {
            data = copy.data;
            pos = copy.pos;
        }

        return *this;
    }
    // Move assignment operator overload
    template <typename T, typename R = unsigned int>
    typename priority_queue<T, R>::PIterator& priority_queue<T, R>::PIterator::operator=(priority_queue<T, R>::PIterator&& move)
    {
        if (this != &move)
        {
            // Swap these
            std::swap(data, move.data);
            std::swap(pos, move.pos);
        }

        return *this;
    }
    // Add operator overload (int)
    template <typename T, typename R = unsigned int>
    typename priority_queue<T, R>::PIterator& priority_queue<T, R>::PIterator::operator+(const int& sum)
    {
        pos += sum;
        return *this;
    }
    // Pre-increment
    template <typename T, typename R = unsigned int>
    typename priority_queue<T, R>::PIterator& priority_queue<T, R>::PIterator::operator++()
    {
        pos++;
        return *this;
    }
    // Post-increment
    template <typename T, typename R = unsigned int>
    typename priority_queue<T, R>::PIterator priority_queue<T, R>::PIterator::operator++(int)
    {
        auto iter = *this;
        pos++;

        return iter;
    }
    // Dereference operator overload
    template <typename T, typename R = unsigned int>
    node<T, R>& priority_queue<T, R>::PIterator::operator*()
    {
        return data[pos];
    }
    // Arrow operator overload
    template <typename T, typename R = unsigned int>
    node<T, R>* priority_queue<T, R>::PIterator::operator->()
    {
        return &(data[pos]);
    }
} // namespace usu
