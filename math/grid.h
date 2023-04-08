#ifndef PATHFINDING_GRID_H
#define PATHFINDING_GRID_H

#include <vector>
#include <array>
#include <unordered_map>
#include "vector.h"

enum cell_type { // типы клеточек:
    target = -2, // начальная & конечная
    wall = -1, // стена (непроходимая)
    empty = 0, // пустая
    weighted = 1 // имеющая стоимость прохода
};

class grid {
private:
    vector2<int> size;
    std::unordered_map<vector2<int>, int> values;
    const std::array<vector2<int>, 4> DIRS = {
            vector2(1, 0),
            vector2(0, -1),
            vector2(-1, 0),
            vector2(0, 1)
    };

    [[nodiscard]] bool in_bounds(const vector2<int> &pos) const;

public:
    grid(int x, int y);

    [[nodiscard]] vector2<int> get_size() const;

    [[nodiscard]] std::vector<vector2<int>> neighbors(const vector2<int> &pos) const;

    int &operator[](const vector2<int> &idx);
};

#endif //PATHFINDING_GRID_H