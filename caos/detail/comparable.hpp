#ifndef CAOS_COMPARABLE_HPP
#define CAOS_COMPARABLE_HPP

namespace caos {
namespace detail {

template <class Subclass, class T = Subclass>
class comparable
{
    friend bool operator == (const Subclass& lhs, const T& rhs) noexcept
    {
        return lhs.compare(rhs) == 0;
    }

    friend bool operator == (const T& lhs, const Subclass& rhs) noexcept
    {
        return rhs.compare(lhs) == 0;
    }

    friend bool operator != (const Subclass& lhs, const T& rhs) noexcept
    {
        return lhs.compare(rhs) != 0;
    }

    friend bool operator != (const T& lhs, const Subclass& rhs) noexcept
    {
        return rhs.compare(lhs) != 0;
    }

    friend bool operator < (const Subclass& lhs, const T& rhs) noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    friend bool operator > (const Subclass& lhs, const T& rhs) noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    friend bool operator < (const T& lhs, const Subclass& rhs) noexcept
    {
        return rhs > lhs;
    }

    friend bool operator > (const T& lhs, const Subclass& rhs) noexcept
    {
        return rhs < lhs;
    }

    friend bool operator <= (const Subclass& lhs, const T& rhs) noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    friend bool operator >= (const Subclass& lhs, const T& rhs) noexcept
    {
        return lhs.compare(rhs) >= 0;
    }

    friend bool operator <= (const T& lhs, const Subclass& rhs) noexcept
    {
        return rhs >= lhs;
    }

    friend bool operator >= (const T& lhs, const Subclass& rhs) noexcept
    {
        return rhs <= lhs;
    }
};

template <class Subclass>
class comparable<Subclass, Subclass> {
    friend bool operator == (const Subclass& lhs, const Subclass& rhs) noexcept
    {
        return lhs.compare(rhs) == 0;
    }

    friend bool operator != (const Subclass& lhs, const Subclass& rhs) noexcept
    {
        return lhs.compare(rhs) != 0;
    }

    friend bool operator < (const Subclass& lhs, const Subclass& rhs) noexcept
    {
        return lhs.compare(rhs) < 0;
    }

    friend bool operator <= (const Subclass& lhs, const Subclass& rhs) noexcept
    {
        return lhs.compare(rhs) <= 0;
    }

    friend bool operator > (const Subclass& lhs, const Subclass& rhs) noexcept
    {
        return lhs.compare(rhs) > 0;
    }

    friend bool operator >= (const Subclass& lhs, const Subclass& rhs) noexcept
    {
        return lhs.compare(rhs) >= 0;
    }
};


}
}

#endif // CAOS_COMPARABLE_HPP
