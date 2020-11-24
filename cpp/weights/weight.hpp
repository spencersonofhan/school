#include <iomanip>
#include <cstdint>
#include <ratio>

namespace usu
{
    template <typename T, typename R = uint64_t>
    class weight
    {
    public:
        const static std::uint64_t num = T::num;
        const static std::uint64_t den = T::den;
        R m_storage;

        weight()
        {
            m_storage = 0;
        }

        weight(R weightVariable) :
            weight()
        {
            m_storage = weightVariable;
        }

        weight<T, R> operator+(const weight<T, R> rhs);
        weight<T, R> operator-(const weight<T, R> rhs);

        R count() { return m_storage; }
    };

    template <typename T, typename U>
    T weight_cast(U castFrom)
    {
        auto currStorage = castFrom.m_storage;
        std::uint64_t currNum = castFrom.num;
        std::uint64_t currDen = castFrom.den;

        double grams = (currStorage * currDen) / currNum;
        auto newStorage = (grams * T::num) / T::den;


        T newWeight(newStorage);

        return newWeight;
    }

    // + operator overload
    template <typename T, typename R>
    weight<T, R> weight<T, R>::operator+(const weight<T, R> rhs)
    {
        weight<T, R> newStorage(this->m_storage + rhs.m_storage);
        return newStorage;
    }

    // - operator overload
    template <typename T, typename R>
    weight<T, R> weight<T, R>::operator-(const weight<T, R> rhs)
    {
        weight<T, R> newStorage(this->m_storage - rhs.m_storage);
        return newStorage;
    }


    // * operator overload (both positions)
    template <typename T, typename R, typename D>
    weight<T, R> operator*(D scalar, const weight<T, R>& rhs)
    {
        weight<T, R> newStorage(rhs.m_storage * scalar);
        return newStorage;
    }

    template <typename T, typename R, typename D>
    weight<T, R> operator*(const weight<T, R>& lhs, D scalar)
    {
        weight<T, R> newStorage(lhs.m_storage * scalar);
        return newStorage;
    }

    using microgram = weight<std::ratio<1000000, 1>>;
    using gram = weight<std::ratio<1, 1>>;
    using kilogram = weight<std::ratio<1000, 1>>;
    using ounce = weight<std::ratio<1000000000, 28349523125>, double>;
    using pound = weight<std::ratio<100000, 45359237>, double>;
    using ton = weight<std::ratio<100, 90718474>, double>;
}
