#ifndef PATHFINDING_DRAWABLE_H
#define PATHFINDING_DRAWABLE_H

#include <vector>
#include <functional>
#include <GLFW/glfw3.h>
#include "drawer.h"
#include "../math/vector.h"
#include "../math/grid.h"
#include "../math/algorithms.h"

class drawable {
protected:
    vector2<float> origin;
    vector2<float> size;

public:
    drawable(float originX, float originY, float sizeX, float sizeY);

    static void draw(float originX, float originY, float sizeX, float sizeY, color color);
};

class quad_drawable : public drawable {
private:
    float border_percent;

    [[nodiscard]] bool in_bounds(const vector2<float> &mouse) const;

    [[nodiscard]] static color get_color(int type);

public:
    quad_drawable(float originX, float originY, float sizeX, float sizeY, float border_percent);

    void draw(float mouseX, float mouseY, const int &type, const vector2<int> &id);

    void click(float mouseX, float mouseY, const std::function<void()> &click_callback);
};

class path_drawable : public drawable {
private:
    float width;

public:
    path_drawable(float startX, float startY, float endX, float endY, float width);

    void draw();
};

struct path_key_points {
private:
    std::array<vector2<int>, 2> container;
    const vector2<int> invalid_value = vector2(-1);

public:
    path_key_points();

    [[nodiscard]] bool empty() const;

    void set_key_point(const vector2<int> &p);

    void clear();

    vector2<int> operator[](int idx) const;
};

class grid_drawable {
private:
    grid &grid_ref;
    algorithm &algorithm_ref;

    std::vector<quad_drawable> children;
    std::vector<path_drawable> path;

    path_key_points key_points;

    vector2<float> render_range;
    float quad_size;

    // устанавливает переданный кратчайший путь в качестве пути для отрисовки в окне
    void set_path(const std::vector<vector2<int>> &reconstructed_path);

public:
    grid_drawable(grid &g, algorithm &a);

    void draw(float mouseX, float mouseY);

    void click(float mouseX, float mouseY, int button);
};

#endif //PATHFINDING_DRAWABLE_H