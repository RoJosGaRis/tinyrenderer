#pragma once
#include "config.h"

class DrawComponent {
public:
  DrawComponent(TGAImage& frameBuffer) : frameBuffer(frameBuffer) {}
  void draw_obj(std::string filepath, const TGAColor& color);

private:
  std::vector<std::array<float, 3>> vectors;
  std::vector<std::array<int, 3>> faces;
  TGAImage& frameBuffer;
  TGAColor color;
  bool read_vector(const std::vector<std::string>& words);
  bool read_face(const std::vector<std::string>& words);
  bool draw_face(std::array<int, 3> face);
  bool draw_line(Point& a, Point& b, TGAImage& framebuffer, TGAColor color);
};