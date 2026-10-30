#include "rasterizer.h"
#include <direct.h>

bool Rasterizer::draw_line(Point& a, Point& b) {
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
    const int dy = std::abs(y1 - y0);
    const int dx = x1 - x0;
    const int yStep = (y0 < y1) ? 1 : -1;
    int error = 0.5 * dx;

    for (int x = x0; x <= x1; x++) {
        // x(t) = (1 - t)x0 + tx1
        // x = x0 - tx0 + tx1
        // t = x - x0 / x1 - x0
        // std::cout << "x: " << x << " y: " << y << " t: " << t << std::endl;
        if (steep){
            frameBuffer.set(y, x, color);
        } else {
            frameBuffer.set(x, y, color);
        }
        error -= dy;
        y += (yStep * (error < 0));
        error += dx * (error < 0);
    }

    return true;
}

double get_signed_area_triangle(const int& ax, const int& ay, const int& bx, const int& by, const int& cx, const int& cy) {
  return 0.5*((by - ay)*(bx + ax) + (cy - by)*(cx + bx) + (ay - cy)*(ax + cx));
}

bool Rasterizer::draw_triangle(Point& a, Point& b, Point& c) {  

    const int ax = a.x;
    const int ay = a.y;
    const int bx = b.x;
    const int by = b.y;
    const int cx = c.x;
    const int cy = c.y;

    const int maxX = std::max(ax, bx, cx);
    const int maxY = std::max(ay, by, cy);
    const int minX = std::min(ax, bx, cx);
    const int minY = std::min(ay, by, cy);

    const double totalArea = get_signed_area_triangle(ax, ay, bx, by, cx, cy);

    #pragma omp parallel for
    for (int x = minX; x <= maxX; x++) {
      for (int y = minY; y <= maxY; y++) {
        double first = get_signed_area_triangle(x, y, bx, by, cx, cy);
        double second = get_signed_area_triangle(ax, ay, x, y, cx, cy);
        double third = get_signed_area_triangle(ax, ay, bx, by, x, y);
      }
    }
      
    return true;
}
int orth_view(float val) {
  float s = std::min(HEIGHT, WIDTH) - 1;
  s = s / 2;
  
  return (val * s) + s; 
}
bool Rasterizer::draw_face(std::array<int, 3> face) {
  float s = std::min(HEIGHT, WIDTH) - 1;
  s = s / 2;
  Point v1 = {
    orth_view(currModel->vector(face[0])[0]),
    orth_view(currModel->vector(face[0])[1])
  }; 
  Point v2 = {
    orth_view(currModel->vector(face[1])[0]),
    orth_view(currModel->vector(face[1])[1])
  }; 
  Point v3 = {
    orth_view(currModel->vector(face[2])[0]),
    orth_view(currModel->vector(face[2])[1])
  };

  draw_triangle(v1, v2, v3);
  draw_line(v1, v2);
  draw_line(v2, v3);
  draw_line(v3, v1);
  
  return true;
}

void Rasterizer::draw_obj(Model* model, const TGAColor& color) {
  currModel = model;
  this->color = color;
  int num_faces = model->nfaces();

  for (int i = 0; i < num_faces; i++) {
    draw_face(model->face(i));
  }

  currModel = nullptr;
  
}