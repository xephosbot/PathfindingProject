#include <iostream>
#include "drawable.h"

drawable::drawable(float originX, float originY, float sizeX, float sizeY) : origin(originX, originY),
                                                                             size(sizeX, sizeY) {}

void drawable::draw(float originX, float originY, float sizeX, float sizeY, color color) {
    drawQuad(originX, originY, sizeX, sizeY, color, true);
}

quad_drawable::quad_drawable(float originX, float originY, float sizeX, float sizeY, float border_percent)
        : drawable(originX, originY, sizeX, sizeY), border_percent(border_percent) {}

bool quad_drawable::in_bounds(const vector2<float> &mouse) const {
    vector2<float> raw_origin = {
            remap(origin.x, -1.0f, 1.0f, 0.0f, (float) SCREEN_WIDTH),
            remap(origin.y, -1.0f, 1.0f, 0.0f, (float) SCREEN_HEIGHT)};
    vector2<float> raw_size = {
            remap(size.x, 0.0f, MAX_RENDER_RANGE, 0.0f, (float) SCREEN_WIDTH),
            remap(size.y, 0.0f, MAX_RENDER_RANGE, 0.0f, (float) SCREEN_HEIGHT)};

    vector2<float> lower = {raw_origin.x - raw_size.x / 2, raw_origin.y - raw_size.y / 2};
    vector2<float> upper = {raw_origin.x + raw_size.x / 2, raw_origin.y + raw_size.y / 2};

    return lower.x < mouse.x && lower.y < mouse.y && upper.x > mouse.x && upper.y > mouse.y;
}

color quad_drawable::get_color(int type) {
    color result{};
    switch (type) {
        case cell_type::empty:
            result = BEIGE;
            break;
        case cell_type::wall:
            result = GRAY;
            break;
        case cell_type::target:
            result = PURPLE;
            break;
        default:
            result = BEIGE;
            break;
    }
    return result;
}

void quad_drawable::draw(float mouseX, float mouseY, const int &type, const vector2<int> &id) {
    bool is_hovered = in_bounds({mouseX, SCREEN_HEIGHT - mouseY});
    color render_color = get_color(type)
                         + (is_hovered ? RED.alpha(0.35f) : TRANSPARENT);
    auto render_size = size * (1.0f - border_percent);
    drawable::draw(origin.x, origin.y, render_size.x, render_size.y, render_color);
}

void quad_drawable::click(float mouseX, float mouseY, const std::function<void()> &click_callback) {
    if (!in_bounds({mouseX, SCREEN_HEIGHT - mouseY}))
        return;

    click_callback();
}

path_drawable::path_drawable(float startX, float startY, float endX, float endY, float width)
        : drawable(
        (startX + endX) / 2,
        (startY + endY) / 2,
        std::abs(endX - startX),
        std::abs(endY - startY)), width(width) {}

void path_drawable::draw() {
    auto render_size = size;
    if (render_size.x == 0) render_size.x = width;
    if (render_size.y == 0) render_size.y = width;
    drawable::draw(origin.x, origin.y, render_size.x, render_size.y, WHITE);
}

path_key_points::path_key_points() : container({vector2(-1), vector2(-1)}) {}

bool path_key_points::empty() const {
    return container[0] == invalid_value || container[1] == invalid_value;
}

void path_key_points::set_key_point(const vector2<int> &p) {
    if (container[0] == invalid_value) {
        container[0] = p;
    } else if (container[1] == invalid_value) {
        container[1] = p;
    }
}

void path_key_points::clear() {
    container[0] = invalid_value;
    container[1] = invalid_value;
}

vector2<int> path_key_points::operator[](int idx) const {
    return container[idx];
}

grid_drawable::grid_drawable(grid &g, algorithm &a) : grid_ref(g), algorithm_ref(a), key_points(), render_range() {
    auto count = grid_ref.get_size();

    this->quad_size = MAX_RENDER_RANGE / (float) std::max(count.x, count.y);
    this->render_range = vector2(
            (quad_size * (float) count.x) / 2,
            (quad_size * (float) count.y) / 2);

    for (int y = 0; y < count.y; ++y) {
        for (int x = 0; x < count.x; ++x) {
            float offsetX = remap((float) x, 0, (float) count.x, -render_range.x, render_range.x);
            float offsetY = remap((float) y, 0, (float) count.y, -render_range.y, render_range.y);

            children.emplace_back(
                    offsetX + quad_size / 2, offsetY + quad_size / 2,
                    quad_size, quad_size,
                    0.05f);
        }
    }
}

void grid_drawable::draw(float mouseX, float mouseY) {
    auto count = grid_ref.get_size();

    for (int i = 0; i < children.size(); ++i) {
        auto &child = children[i];
        auto id = vector2(i % count.x, i / count.y);

        child.draw(mouseX, mouseY, grid_ref[id], id);
    }

    if (!path.empty()) {
        for (auto &p: path) p.draw();
    }
}

void grid_drawable::click(float mouseX, float mouseY, int button) {
    auto count = grid_ref.get_size();

    for (int i = 0; i < children.size(); ++i) {
        auto &child = children[i];
        auto id = vector2(i % count.x, i / count.y);

        if (button == GLFW_MOUSE_BUTTON_LEFT) {
            child.click(mouseX, mouseY, [this, &id]() {
                grid_ref[id] = (grid_ref[id] == cell_type::empty) ? cell_type::wall : cell_type::empty;

                if (!key_points.empty()) {
                    auto p = algorithm_ref.reconstruct_path(algorithm_ref.find_path(key_points[0], key_points[1]));
                    set_path(p);
                }
            });
        } else if (button == GLFW_MOUSE_BUTTON_RIGHT) {
            child.click(mouseX, mouseY, [this, &id]() {
                if (key_points.empty()) {
                    if (grid_ref[id] == cell_type::empty) {
                        grid_ref[id] = cell_type::target;
                        key_points.set_key_point(id);
                    } else {
                        grid_ref[id] = cell_type::empty;
                    }

                    if (!key_points.empty()) {
                        auto p = algorithm_ref.reconstruct_path(algorithm_ref.find_path(key_points[0], key_points[1]));
                        set_path(p);
                    }
                } else {
                    grid_ref[key_points[0]] = cell_type::empty;
                    grid_ref[key_points[1]] = cell_type::empty;

                    key_points.clear();
                    path.clear();
                }
            });
        }
    }
}

void grid_drawable::set_path(const std::vector<vector2<int>> &reconstructed_path) {
    path.clear();

    if (reconstructed_path.empty()) return;

    auto count = grid_ref.get_size();

    for (int i = 0; i < reconstructed_path.size() - 1; ++i) {
        auto start = reconstructed_path[i];
        auto end = reconstructed_path[i + 1];

        float startX = remap((float) start.x, 0, (float) count.x, -render_range.x, render_range.x);
        float startY = remap((float) start.y, 0, (float) count.y, -render_range.y, render_range.y);

        float endX = remap((float) end.x, 0, (float) count.x, -render_range.x, render_range.x);
        float endY = remap((float) end.y, 0, (float) count.y, -render_range.y, render_range.y);

        path.emplace_back(
                startX + quad_size / 2, startY + quad_size / 2,
                endX + quad_size / 2, endY + quad_size / 2,
                quad_size * 0.25f);

        //для того чтобы углы были не рваными
        if (i == 0) continue;

        auto prev = reconstructed_path[i - 1];
        if ((prev.x == start.x != end.x) || (prev.y == start.y != end.y)) {
            path.emplace_back(
                    startX + quad_size / 2, startY + quad_size / 2,
                    startX + quad_size / 2, startY + quad_size / 2,
                    quad_size * 0.25f);
        }
    }
}