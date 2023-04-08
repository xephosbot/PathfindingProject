#ifndef PATHFINDING_VECTOR_H
#define PATHFINDING_VECTOR_H

#include <compare>
#include <ostream>

template<typename T>
struct vector2 {
    T x, y;

    vector2() = default;

    explicit vector2(T _v);

    vector2(T _x, T _y);

    vector2<T> operator+(const vector2<T> &v) const;

    vector2<T> operator-(const vector2<T> &v) const;

    vector2<T> operator*(const T &f) const;

    auto operator<=>(const vector2<T> &v) const = default;
};

template<typename T>
std::ostream &operator<<(std::ostream &os, const vector2<T> &v) {
    return os << "(" << v.x << ", " << v.y << ")";
}

namespace std {
// implement hash function, so we can put vector2<T> into an unordered_map
    template<typename T>
    struct hash<vector2<T>> {
        std::size_t operator()(const vector2<T> &id) const noexcept {
            return std::hash<int>()(id.x ^ (id.y << 16));
        }
    };
}

#endif //PATHFINDING_VECTOR_H