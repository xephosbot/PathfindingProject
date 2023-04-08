#ifndef PATHFINDING_INPUT_H
#define PATHFINDING_INPUT_H

#include <functional>
#include "GLFW/glfw3.h"
#include "../math/vector.h"

class mouse_input {
private:
    using callback = std::function<void(double, double)>;

    static double mouseX;
    static double mouseY;

    static callback left_click_callback;
    static callback right_click_callback;

    static void mouse_button_callback(GLFWwindow *window, int button, int action, int mods);

    static void cursor_position_callback(GLFWwindow *window, double xpos, double ypos);

public:
    mouse_input(GLFWwindow *window, const callback &left_callback, const callback &right_callback);

    [[nodiscard]] double mouse_x() const;

    [[nodiscard]] double mouse_y() const;
};

#endif //PATHFINDING_INPUT_H
