#include "input.h"

double mouse_input::mouseX;
double mouse_input::mouseY;

std::function<void(double, double)> mouse_input::left_click_callback;
std::function<void(double, double)> mouse_input::right_click_callback;

void mouse_input::mouse_button_callback(GLFWwindow *window, int button, int action, int mods) {
    if (button == GLFW_MOUSE_BUTTON_LEFT && action == GLFW_PRESS) {
        left_click_callback(mouseX, mouseY);
    }
    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
        right_click_callback(mouseX, mouseY);
    }
}

void mouse_input::cursor_position_callback(GLFWwindow *window, double xpos, double ypos) {
    mouseX = xpos;
    mouseY = ypos;
}

mouse_input::mouse_input(GLFWwindow *window, const callback &left_callback, const callback &right_callback) {
    mouse_input::left_click_callback = left_callback;
    mouse_input::right_click_callback = right_callback;

    glfwSetMouseButtonCallback(window, mouse_button_callback);
    glfwSetCursorPosCallback(window, cursor_position_callback);
}

double mouse_input::mouse_x() const { return mouseX; }

double mouse_input::mouse_y() const { return mouseY; }