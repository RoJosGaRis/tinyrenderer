#pragma once
#include "../config.h"

class Rasterizer {
public:
  Rasterizer(TGAImage& frameBuffer) : frameBuffer(frameBuffer) {}
  void draw_obj(Model* model, const TGAColor& color);
  bool draw_triangle(Point& a, Point& b, Point& c);

private:
  
  TGAImage& frameBuffer;
  Model* currModel;
  TGAColor color;
  bool draw_face(std::array<int, 3> face);
  bool draw_line(Point& a, Point& b);

};