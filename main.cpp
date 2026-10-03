#include "config.h"

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
    bool steep = std::abs(y1 - y0) > std::abs(x1 - x0);
    if (steep) {
        std::swap(x0, y0);
        std::swap(x1, y1);
    }
    if (x0 > x1) {
        std::swap(x0, x1);
        std::swap(y0, y1);
    }

    int y = y0;
    const int dy = y1 - y0;
    const int dx = x1 - x0;
    const int yStep = (y0 < y1) ? 1 : -1;
    int error = 0.5 * dx;

    for (int x = x0; x <= x1; x++) {
        // x(t) = (1 - t)x0 + tx1
        // x = x0 - tx0 + tx1
        // t = x - x0 / x1 - x0
        // std::cout << "x: " << x << " y: " << y << " t: " << t << std::endl;
        if (steep){
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);
        }
        error -= dy;
        y += (yStep * (error < 0));
        error += dx * (error < 0);
    }
}

int main(int argc, char** argv) {
    constexpr int width  = 640;
    constexpr int height = 640;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    std::ifstream file ("obj/diablo3_pose/diable3_pose.obj");
    std::string line;

    if (!file.is_open()) {
        std::cout << "Couldn't open file" << std::endl;
        return 0;
    }

    while(getline(file, line)) {
        std::vector<std::string> words = split(line, " ");
        
        if (words[0] == "v") {
            
        } else if (words[0] == "f") {

        }
    }

    file.close();
    
    framebuffer.write_tga_file("framebuffer.tga");

    return 0;
}

