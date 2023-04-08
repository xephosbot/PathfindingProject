#include "vector.h"

template<typename T>
vector2<T>::vector2(T _v)
        : x(_v), y(_v) {}

template<typename T>
vector2<T>::vector2(T _x, T _y)
        : x(_x), y(_y) {}

template<typename T>
vector2<T> vector2<T>::operator+(const vector2<T> &v) const {
    return vector2<T>(x + v.x, y + v.y);
}

template<typename T>
vector2<T> vector2<T>::operator-(const vector2<T> &v) const {
    return vector2<T>(x - v.x, y - v.y);
}

template<typename T>
vector2<T> vector2<T>::operator*(const T &f) const {
    return vector2<T>(x * f, y * f);
}

template struct vector2<int>;
template struct vector2<char>;
template struct vector2<float>;
template struct vector2<double>;