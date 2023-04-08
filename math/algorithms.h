#ifndef PATHFINDING_ALGORITHMS_H
#define PATHFINDING_ALGORITHMS_H

#include <unordered_map>
#include "grid.h"

class algorithm {
protected:
    grid &grid_ref;
    vector2<int> start;
    vector2<int> target;

    using path_container = std::unordered_map<vector2<int>, vector2<int>>;
public:
    explicit algorithm(grid &g);

    virtual path_container find_path(const vector2<int> &start, const vector2<int> &target) = 0;

    std::vector<vector2<int>> reconstruct_path(path_container came_from);

    [[nodiscard]] vector2<int> get_start() const;

    [[nodiscard]] vector2<int> get_target() const;
};

class breadth_first_search : public algorithm {
public:
    explicit breadth_first_search(grid &g);

    path_container find_path(const vector2<int> &start, const vector2<int> &target) override;
};

class depth_first_search : public algorithm {
public:
    explicit depth_first_search(grid &g);

    path_container find_path(const vector2<int> &start, const vector2<int> &target) override;
};

class greedy_best_first_search : public algorithm {
private:
    static int heuristic(const vector2<int> &a, const vector2<int> &b);
public:
    explicit greedy_best_first_search(grid &g);

    path_container find_path(const vector2<int> &start, const vector2<int> &target) override;
};

class wave_search : public algorithm {
public:
    explicit wave_search(grid &g);

    path_container find_path(const vector2<int> &start, const vector2<int> &target) override;
};

class a_star_search : public algorithm {
private:
    static int heuristic(const vector2<int> &a, const vector2<int> &b);
public:
    explicit a_star_search(grid &g);

    path_container find_path(const vector2<int> &start, const vector2<int> &target) override;
};

#endif //PATHFINDING_ALGORITHMS_H
