#include <algorithm>
#include <cmath>
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

            value_type getValue() { return value; }
            priority_type getPriority() const { return priority; }
        };

        class iterator : public std::iterator<std::forward_iterator_tag, priority_queue*>
        {
          public:
            using iterator_category = std::forward_iterator_tag;

            iterator() :
                iterator(nullptr)
            {
            }

            iterator(std::shared_ptr<std::vector<node>> pointer, size_type pos = 0) :
                index(pos)
            // data(pointer), index(pos)
            {
                dataList = pointer;
                data = std::make_shared<node>((*dataList)[index]);
            }

            iterator(const iterator& copy)
            {
                this->index = copy.index;
                this->dataList = copy.dataList;
                this->data = copy.data;
            }

            iterator(iterator&& move) noexcept
            {
                this->index = move.index;
                this->dataList = move.dataList;
                this->data = move.data;

                move.dataList = nullptr;
            }

            iterator& operator=(const iterator& copy)
            {
                this->index = copy.index;
                this->dataList = copy.dataList;
                this->data = copy.data;

                return *this;
            }

            iterator& operator=(iterator&& move)
            {
                if (this != &move)
                {
                    std::swap(this->index, move.index);
                    std::swap(this->dataList, move.dataList);
                    std::swap(this->data, move.data);
                }

                return *this;
            }

            iterator operator+(int sum)
            {

                // if (index + sum > capacity())
                // {
                //
                // }

                index += sum;
                std::shared_ptr newData = std::make_shared<node>((*dataList)[index]);
                std::swap(data, newData);

                return *this;
            }

            iterator operator+=(int sum)
            {
                index += sum;
                data = std::make_shared<node>((*dataList)[index]);

                return *this;
            }

            // Pre-increment
            iterator operator++()
            {
                index++;
                data = std::make_shared<node>((*dataList)[index]);
                return *this;
            }

            // Post-increment
            iterator operator++(int)
            {
                iterator iter = *this;
                index++;
                data = std::make_shared<node>((*dataList)[index]);
                return iter;
            }

            node operator*()
            {
                return *data;
            }

            std::shared_ptr<node> operator->()
            {
                return data;
            }

            bool operator!=(iterator copy)
            {
                return index != copy.index;
            }

            bool operator==(iterator copy)
            {
                return index == copy.index;
            }

            size_type getIndex() { return index; }

          private:
            size_type index;
            std::shared_ptr<std::vector<node>> dataList;
            std::shared_ptr<node> data;
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

            node max = Q[0];
            node temp;

            if (size() == 1)
            {
                Q.erase(0);
                numElements--;

                return max;
            }
            else if (size() == 2)
            {
                temp = Q[1];
                Q.erase(0);
                numElements--;

                return max;
            }

            unsigned int index = 0;
            if (Q[1].compareTo(Q[2]) > 0)
            {
                index = 1;
                temp = Q[1];
            }
            else
            {
                index = 2;
                temp = Q[2];
            }
        }

        // iterator find(value_type value);

        // void update(iterator i, priority_type priority);

        iterator begin()
        {
            if (empty())
            {
                return end();
            }

            std::shared_ptr<std::vector<node>> theFirst = std::make_shared<std::vector<node>>(Q);
            iterator first(theFirst);
            return first;
        }

        iterator end()
        {
            std::shared_ptr<std::vector<node>> theEnd = std::make_shared<std::vector<node>>(Q);
            iterator end(theEnd, size());

            return end;
        }

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
        }

        void maxHeapAdd(node& newNode)
        {
            numElements++;
            lastIndex = numElements - 1;
            int currNode = static_cast<int>(lastIndex);

            Q[currNode] = newNode;

            // Check parent for smaller values
            while (Q[currNode].compareTo(Q[parent(currNode)]) > 0)
            {
                std::iter_swap(Q.begin() + currNode, Q.begin() + parent(currNode));
                currNode = parent(currNode);
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

        std::pair<int, int> childs(int node)
        {
            if (node < 0)
            {
                throw std::exception();
            }
            std::pair<int, int> childs((2 * node) + 1, (2 * node) + 2);

            return childs;
        }

        node getFirst()
        {
            if (!empty())
            {
                return Q[0];
            }
            else
            {
                throw std::exception();
            }
        }

        // Returns true if 'Q' is empty
        bool empty()
        {
            return size() == 0;
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
