#include <cmath>
#include <iostream>

#include "tgaimage.h"

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};

struct Point {
    int x;
    int y;
};

void line(Point& a, Point& b, TGAImage& framebuffer, TGAColor color) {
    int x0 = a.x;
    int x1 = b.x;
    int y0 = a.y;
    int y1 = b.y;
    float t = 0.0f;
    int y = 0;

    for (int x = x0; x <= x1; x++) {
        // x(t) = (1 - t)x0 + tx1
        // x = x0 - tx0 + tx1
        // t = x - x0 / x1 - x0
        t = (float)(x - x0) / (float)(x1 - x0);
        y = (1 - t) * y0 + t * y1;
        std::cout << "x: " << x << " y: " << y << " t: " << t << std::endl;
        framebuffer.set(x, y, color);
    }
}

int main(int argc, char** argv) {
    constexpr int width  = 64;
    constexpr int height = 64;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    Point pointA {10,10};
    Point pointB = {20,15};

    // line(pointA, pointB, framebuffer, white);
    line(pointB, pointA, framebuffer, white);

    framebuffer.write_tga_file("framebuffer.tga");
    return 0;
}

