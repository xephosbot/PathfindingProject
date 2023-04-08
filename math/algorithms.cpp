#include <iostream>
#include <stack>
#include <cmath>
#include <queue>
#include "algorithms.h"

algorithm::algorithm(grid &g) : grid_ref(g), start(), target() {}

std::vector<vector2<int>> algorithm::reconstruct_path(path_container came_from) {
    std::vector<vector2<int>> path;
    vector2<int> current = target;
    if (came_from.find(target) == came_from.end()) {
        return path; // если в came_from нет конечной точки значит мы не можем проложить путь
    }
    while (current != start) {
        path.push_back(current);
        current = came_from[current];
    }
    path.push_back(start);
    std::reverse(path.begin(), path.end()); // так как мы начали с конца, нам нужно развернуть порядок элементов
    return path;
}

vector2<int> algorithm::get_start() const { return start; }

vector2<int> algorithm::get_target() const { return target; }

breadth_first_search::breadth_first_search(grid &g) : algorithm(g) {}

algorithm::path_container breadth_first_search::find_path(const vector2<int> &start, const vector2<int> &target) {
    this->start = start;
    this->target = target;

    std::queue<vector2<int>> frontier;
    frontier.push(start);

    path_container came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        auto current = frontier.front();
        frontier.pop();

        if (current == target) {
            break;
        }
        for (const auto &next: grid_ref.neighbors(current)) {
            if (!came_from.count(next)) {
                if (grid_ref[next] != cell_type::wall) {
                    frontier.push(next);
                    came_from[next] = current;
                }
            }
        }
    }
    return came_from;
}

depth_first_search::depth_first_search(grid &g) : algorithm(g) {}

algorithm::path_container depth_first_search::find_path(const vector2<int> &start, const vector2<int> &target) {
    this->start = start;
    this->target = target;

    std::stack<vector2<int>> frontier;
    frontier.push(start);

    path_container came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        auto current = frontier.top();
        frontier.pop();

        if (current == target) {
            break;
        }

        auto neighbors = grid_ref.neighbors(current);
        std::reverse(neighbors.begin(), neighbors.end());

        for (const auto &next: neighbors) {
            if (!came_from.count(next)) {
                if (grid_ref[next] != cell_type::wall) {
                    frontier.push(next);
                    came_from[next] = current;
                }
            }
        }
    }
    return came_from;
}


greedy_best_first_search::greedy_best_first_search(grid& g) : algorithm(g) {}

int greedy_best_first_search::heuristic(const vector2<int> &a, const vector2<int> &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

algorithm::path_container greedy_best_first_search::find_path(const vector2<int> &start, const vector2<int> &target) {
    this->start = start;
    this->target = target;

    using element = std::pair<int, vector2<int>>;
    std::priority_queue<element, std::vector<element>, std::greater<>> frontier;
    frontier.emplace(0, start);

    path_container came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        auto current = frontier.top().second;
        frontier.pop();

        if (current == target) {
            break;
        }
        for (const auto &next: grid_ref.neighbors(current)) {
            if (!came_from.count(next)) {
                if (grid_ref[next] != cell_type::wall) {
                    int priority = heuristic(target, next);
                    frontier.emplace(priority, next);
                    came_from[next] = current;
                }
            }
        }
    }
    return came_from;
}

wave_search::wave_search(grid &g) : algorithm(g) {}

algorithm::path_container wave_search::find_path(const vector2<int> &start, const vector2<int> &target) {
    this->start = start;
    this->target = target;

    std::queue<vector2<int>> frontier;
    frontier.push(start);

    path_container came_from;
    came_from[start] = start;

    while (!frontier.empty()) {
        auto current = frontier.front();
        frontier.pop();

        if (current == target) {
            break;
        }

        for (const auto &next: grid_ref.neighbors(current)) {
            if (!came_from.count(next)) {
                if (grid_ref[next] != cell_type::wall) {
                    frontier.push(next);
                    came_from[next] = current;
                }
            }
        }
    }
    return came_from;
}

a_star_search::a_star_search(grid &g) : algorithm(g) {}

int a_star_search::heuristic(const vector2<int> &a, const vector2<int> &b) {
    return std::abs(a.x - b.x) + std::abs(a.y - b.y);
}

algorithm::path_container a_star_search::find_path(const vector2<int> &start, const vector2<int> &target) {
    this->start = start;
    this->target = target;

    using element = std::pair<int, vector2<int>>;
    std::priority_queue<element, std::vector<element>, std::greater<>> frontier;
    frontier.emplace(0, start);

    path_container came_from;
    came_from[start] = start;

    std::unordered_map<vector2<int>, int> cost_so_far;
    cost_so_far[start] = 0;

    while (!frontier.empty()) {
        auto current = frontier.top();
        frontier.pop();

        if (current.second == target) {
            break;
        }

        for (auto& next : grid_ref.neighbors(current.second)) {
            int new_cost = cost_so_far[current.second] + (grid_ref[next] == cell_type::weighted ? 5 : 1);
            if (!cost_so_far.count(next) || new_cost < cost_so_far[next]) {
                if (grid_ref[next] != cell_type::wall) {
                    cost_so_far[next] = new_cost;
                    int priority = new_cost + heuristic(next, target);
                    frontier.emplace(priority, next);
                    came_from[next] = current.second;
                }
            }
        }
    }
    return came_from;
}


