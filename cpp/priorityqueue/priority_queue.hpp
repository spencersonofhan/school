#include <initializer_list>
#include <vector>
#include <iodint>
#include <iterator>

namespace usu
{
    template <typename T>
    class priority_queue
    {
    public:
        priority_queue(); // DEFAULT
        priority_queue(std::initializer_list);

        void enqueue(T value, priority_type priority);
        auto dequeue();
        iterator find(T value);
        void update(iterator i, priority_type priority);
        bool empty();
        size_type size();
        iterator begin();
        iterator end();

    private:
        unsigned int m_value;
        unsigned int m_priority; // LARGER PRIORITY VALUES REPRESENT HIGHER PRIORTIY
        std::vector Q;


        class iterator
        {
        public:
            using iterator_category = std::forward_iterator_tag;
            iterator() :
                iterator(nullptr)
            {
            }

            iterator(T* pointer) :
                m_data(ptr),
                m_pos(0)
            {
            }

            iterator(unsigned int pos, T* pointer) :
                m_pos(pos),
                m_data(ptr)
            {
            }

            // NEEDS
            // Copy constructor
            // Move constructor
            // Copy assignment op
            // Move assignment op
            // Incrementable
            // Dereferencable


        private:
            unsigned int m_pos;
            // pointer to the data
            T* m_data;
        }
    }

    // using priority_type;
    // using value_type;
    // using size_type;
}
