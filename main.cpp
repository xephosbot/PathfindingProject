#include <GLFW/glfw3.h>
#include "render/drawer.h"
#include "render/drawable.h"
#include "render/input.h"
#include "math/algorithms.h"
#include "math/grid.h"

int main() {
    GLFWwindow *window;

    if (!glfwInit())
        return -1;

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "Pathfinding Project", nullptr, nullptr);
    if (!window) {
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);

    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glClearColor(WHITE.r, WHITE.g, WHITE.b, WHITE.a);

    auto mainGrid = grid(15, 15);
    auto searcher = a_star_search(mainGrid);
    auto gridDraw = grid_drawable(mainGrid, searcher);

    auto input = mouse_input(window, [&gridDraw](double mouseX, double mouseY) {
            gridDraw.click((float) mouseX, (float) mouseY, GLFW_MOUSE_BUTTON_LEFT);
        },
        [&gridDraw](double mouseX, double mouseY) {
            gridDraw.click((float) mouseX, (float) mouseY, GLFW_MOUSE_BUTTON_RIGHT);
        }
    );

    while (!glfwWindowShouldClose(window)) {
        glClear(GL_COLOR_BUFFER_BIT);

        gridDraw.draw((float) input.mouse_x(), (float) input.mouse_y());

        glfwSwapBuffers(window);
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}