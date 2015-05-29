
template <typename T>
Coordinate<T>::Coordinate() :
x(),
y()
{}

template <typename T>
Coordinate<T>::Coordinate(T x, T y) :
x(x),
y(y)
{}

template <typename T>
bool Coordinate<T>::operator <(const Coordinate<T>& other) const
{
    return std::hash<Coordinate>()(*this) < std::hash<Coordinate>()(other);
}

template <typename T>
bool Coordinate<T>::operator ==(const Coordinate<T>& other) const
{
    return x == other.x && y == other.y;
}

template <typename T>
std::size_t std::hash<Coordinate<T> >::operator ()(const Coordinate<T>& coordinate) const
{
    return coordinate.x + 1000 * coordinate.y;
}

