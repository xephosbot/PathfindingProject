#include "color.h"

color::color(unsigned int rgba)
        : r((float) ((rgba >> 24) & 0xff) / 255.0f), g((float) ((rgba >> 16) & 0xff) / 255.0f),
          b((float) ((rgba >> 8) & 0xff) / 255.0f), a((float) (rgba & 0xff) / 255.0f) {}

color::color(float r, float g, float b, float a)
        : r(r), g(g), b(b), a(a) {}

color color::alpha(float alpha) const {
    return {r, g, b, alpha};
}

color color::operator+(const color &c) const {
    auto result = color();
    result.a = 1.0f - (1.0f - c.a) * (1.0f - a);
    if (result.a < 1.0e-6) {
        return result;
    }

    result.r = c.r * c.a / result.a + r * a * (1.0f - c.a) / result.a;
    result.g = c.g * c.a / result.a + g * a * (1.0f - c.a) / result.a;
    result.b = c.b * c.a / result.a + b * a * (1.0f - c.a) / result.a;
    return result;
}
