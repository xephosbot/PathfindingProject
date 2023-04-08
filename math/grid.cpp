#include "grid.h"

grid::grid(int x, int y) : size(x, y), values() {
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            values[{j, i}] = 0;
        }
    }
}

bool grid::in_bounds(const vector2<int> &pos) const {
    return pos.x >= 0 && pos.x < size.x && pos.y >= 0 && pos.y < size.y;
}

vector2<int> grid::get_size() const { return size; }

std::vector<vector2<int>> grid::neighbors(const vector2<int> &pos) const {
    std::vector<vector2<int>> results;
    for (const auto &dir: DIRS) {
        vector2<int> next(pos.x + dir.x, pos.y + dir.y);
        if (in_bounds(next)) {
            results.emplace_back(next);
        }
    }
    return results;
}

int &grid::operator[](const vector2<int> &idx) {
    if (in_bounds(idx)) {
        return values[idx];
    } else {
        throw std::out_of_range("index out of range");
    }
}
