#ifndef PATHFINDING_COLOR_H
#define PATHFINDING_COLOR_H

struct color {
    float r, g, b, a;

    color() = default;

    explicit color(unsigned int rgba);

    color(float r, float g, float b, float a);

    [[nodiscard]] color alpha(float alpha) const;

    color operator+(const color &c) const;
};

#endif //PATHFINDING_COLOR_H
