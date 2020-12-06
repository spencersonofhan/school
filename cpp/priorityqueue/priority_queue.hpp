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
    class priority_queue
    {
      public:
        using value_type = T;
        using priority_type = R;
        using size_type = unsigned int;
        using TPriori = std::pair<T, R>;

        class node
        {
          public:
            value_type value;
            priority_type priority;

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

            priority_type getPriority() const { return priority; }
            value_type getValue() const { return value; }
            void setPriority(priority_type newPriority) { priority = newPriority; }
            void setValue(value_type newValue) { value = newValue; }
        };

        class iterator : public std::iterator<std::forward_iterator_tag, priority_queue*>
        {
          public:
            typedef std::random_access_iterator_tag iterator_category;
            typedef T value_type;
            typedef std::ptrdiff_t difference_type;
            typedef T& reference;
            typedef T* pointer;

            // friend bool operator==(const iterator&, const iterator&);
            // friend bool operator!=(const iterator&, const iterator&);
            // friend bool operator<(const iterator&, const iterator&);
            // friend bool operator>(const iterator&, const iterator&);
            // friend bool operator<=(const iterator&, const iterator&);
            // friend bool operator>=(const iterator&, const iterator&);

            // Default constructor
            iterator() :
                iterator(nullptr)
            {
            }
            // Overloaded constructor
            iterator(std::shared_ptr<std::vector<node>> dataPointer, std::shared_ptr<size_type> numOfElements, size_type pos = 0)
            // index(pos),
            // Que(dataPointer),
            // num(numOfElements)
            {
                index = pos;
                Que = dataPointer;
                num = numOfElements;
            }
            // Destructor
            ~iterator()
            {
                Que.reset();
                num.reset();
            }
            // Copy constructor
            iterator(const iterator& copy)
            // index(copy.index),
            // Que(copy.Que),
            // num(copy.num)
            {
                index = copy.index;
                Que = copy.Que;
                num = copy.num;
            }
            // Move constructor
            iterator(iterator&& move) noexcept
            // index(move.index),
            // Que(move.Que),
            // num(move.num)
            {
                index = move.index;
                Que = move.Que;
                num = move.num;
            }
            // Copy assignmnet operator overload
            iterator& operator=(const iterator& copy)
            {
                if (this != &copy)
                {
                    index = copy.index;
                    Que = copy.Que;
                    num = copy.num;
                }

                return *this;
            }
            // Move assignment operator overload
            iterator& operator=(iterator&& move)
            {
                if (this != &move)
                {
                    index = move.index;
                    Que.swap(move.Que);
                    num.swap(move.num);
                }

                return *this;
            }

            iterator operator+(int sum)
            {
                index += sum;
                if (!withinBounds())
                {
                    this->setIndex(*(this->num) - 1);
                }

                return *this;
            }

            iterator operator+=(int sum)
            {
                index += sum;
                if (!withinBounds())
                {
                    this->setIndex(*(this->num) - 1);
                }

                return *this;
            }

            // Pre-increment
            iterator operator++()
            {
                index++;

                return *this;
            }

            // Post-increment
            iterator operator++(int)
            {
                iterator iter = *this;
                index++;

                return iter;
            }

            node& operator*()
            {
                return (*Que)[index];
            }

            std::shared_ptr<node> operator->()
            {
                std::shared_ptr<node> currNode = std::make_shared<node>((*Que)[index]);
                return currNode;
            }

            const node operator[](size_type index) const
            {
                if (index >= *num)
                {
                    throw std::exception();
                }
                return (*Que)[index];
            }

            bool operator!=(iterator copy)
            {
                return index != copy.index;
            }

            bool operator==(iterator copy)
            {
                return index == copy.index;
            }

            bool withinBounds()
            {
                if (index >= *num)
                {
                    return false;
                }
                else if (index < 0)
                {
                    throw std::exception();
                }

                return true;
            }

            std::vector<node> getQue() { return *Que; }
            size_type getIndex() const { return index; }
            void setIndex(unsigned int newIndex) { index = newIndex; }

          private:
            size_type index;
            std::shared_ptr<size_type> num;
            std::shared_ptr<std::vector<node>> Que;
        };

        // Default constructor
        priority_queue()
        {
            // size_type NE = new size_type(0);
            // size_type LI = new size_type(0);
            // std::vector<node> QU = new std::vector<node>();
            numElements = std::make_shared<size_type>(*(new size_type(0)));
            lastIndex = std::make_shared<size_type>(*(new size_type(0)));
            Q = std::make_shared<std::vector<node>>(*(new std::vector<node>()));
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
            // Checks if size of Q is adequate
            beginCheck();

            // Max heap operations
            node newNode(value, priority);
            maxHeapAdd(newNode);
        }

        auto dequeue()
        {
            if (empty())
            {
                throw std::exception();
            }

            // Extract first element
            node maxNode = (*Q)[0];

            // Swap with last element than delete
            std::iter_swap(begin(), begin() + *lastIndex);

            (*Q).erase((*Q).begin() + *lastIndex);

            (*numElements)--;
            *lastIndex = *numElements - 1;

            // Trickle down the first element
            iterator i = begin();

            // Check children for bigger priorities
            // Check for child swap
            if (child(i.getIndex()) > 0)
            {
                maxHeapDelete(i);
            }

            return maxNode;
        }

        iterator find(T value)
        {
            for (auto i = begin(); i != end(); ++i)
            {
                if (i->getValue() == value)
                {
                    return i;
                }
            }
            return end();
        }

        void update(iterator i, priority_type priority)
        {
            i->setPriority(priority);
            int currNode = i.getIndex();

            // Check for parent swap
            if (i->compareTo((*Q)[parent(currNode)]) > 0)
            {
                while (i->compareTo((*Q)[parent(currNode)]) > 0)
                {
                    std::iter_swap(begin() + currNode, begin() + parent(currNode));
                    currNode = parent(currNode);
                }
            }
            // Check for child swap
            else if (child(currNode) > 0)
            {
                maxHeapDelete(i);
            }
        }

        iterator begin()
        {
            if (empty())
            {
                return end();
            }

            iterator first(Q, numElements);
            return first;
        }

        iterator end()
        {
            iterator end(Q, numElements, size());

            return end;
        }

        // void resize(unsigned int reduced);
        void beginCheck()
        {
            // This is only for the priority queue at the beginning
            if (*numElements >= capacity())
            {
                while (*numElements >= capacity())
                {
                    resize();
                }
                return;
            }

            /*
            while loop beats std::vector to the punch with resizing first since
            std::vectors size doubles automagically if elements equals half capacity
            */
            if (*numElements > (capacity() / 2) - 1)
            {
                while (*numElements > (capacity() / 2) - 1)
                {
                    resize();
                }
            }
        }

        void maxHeapAdd(node& newNode)
        {
            (*numElements)++;
            *lastIndex = *numElements - 1;
            int currNode = static_cast<int>(*lastIndex);

            (*Q)[currNode] = newNode;

            // Check parent for smaller values
            while ((*Q)[currNode].compareTo((*Q)[parent(currNode)]) > 0)
            {
                std::iter_swap(begin() + currNode, begin() + parent(currNode));
                currNode = parent(currNode);
            }
        }

        void maxHeapDelete(iterator i)
        {
            int kid1 = 0;
            int kid2 = 0;
            int currNode = i.getIndex();

            while (child(currNode) > 0)
            {
                kid1 = child(currNode, 1);
                kid2 = child(currNode, 2);

                // Check for two children
                if (child(currNode) > 1)
                {
                    if (min((*Q)[kid1].getPriority(), (*Q)[kid2].getPriority()) == 1)
                    {
                        std::iter_swap(begin() + currNode, begin() + kid1);
                        currNode = kid1;
                    }
                    else
                    {
                        std::iter_swap(begin() + currNode, begin() + kid2);
                        currNode = kid2;
                    }
                }
                // One child, can only be left child
                else if (i->compareTo((*Q)[child(currNode, 1)]) < 0)
                {
                    std::iter_swap(begin() + currNode, begin() + kid1);
                    currNode = kid1;
                }
            }
        }

        int parent(int node)
        {
            if (node == 0)
            {
                return 0;
            }
            return (node - 1) / 2;
        }

        int child(int node)
        {
            if (node < 0)
            {
                throw std::exception();
            }

            int amount = 0;

            try
            {
                if (child(node, 1) >= 0)
                {
                    amount++;
                }
                if (child(node, 2) >= 0)
                {
                    amount++;
                }
            }
            catch (...)
            {
            }

            return amount;
        }

        int child(size_type node, size_type whichKid)
        {
            if (node < 0)
            {
                throw std::exception();
            }
            else if (node >= *numElements)
            {
                return -1;
            }

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

        int min(priority_type first, priority_type second)
        {
            return first >= second ? 1 : 2;
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
            Q->resize(newSize);
        }
        // Simple function that returns the max size of Q
        size_type capacity() { return Q->capacity(); }
        // Returns the index of that last element in the array that matters
        size_type getLastIndex() const { return *lastIndex; }
        // Returns total amount of elements in Q
        size_type size() const { return *numElements; }
        // Returns 'Q'
        std::vector<node> getQ() const { return *Q; }

      private:
        std::shared_ptr<size_type> numElements;
        std::shared_ptr<size_type> lastIndex;
        std::shared_ptr<std::vector<node>> Q;
    };
} // namespace usu
