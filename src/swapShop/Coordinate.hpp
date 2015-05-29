
#ifndef COORDINATE_HPP
#define COORDINATE_HPP

#include <cstdlib>

template <typename T>
class Coordinate
{
public:
    Coordinate();
    Coordinate(T x, T y);

    T x;
    T y;

    bool operator <(const Coordinate<T>& other) const;
    bool operator ==(const Coordinate<T>& other) const;

private:

};

namespace std
{
    template<typename T>
    struct hash<Coordinate<T> >
    {
        std::size_t operator()(const Coordinate<T>& coordinate) const;
    };
}

#include <swapShop/Coordinate.inl>

#endif

