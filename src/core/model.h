#pragma once
#include "../config.h"

class Model {  
public:
  Model(std::vector<std::array<float, 3>> vectors, std::vector<std::array<int, 3>> faces) : vectors(std::move(vectors)), faces(std::move(faces)) {}
  Model() : vectors({}), faces({}) {}
  int nvectors()  const;
  int nfaces()    const;
  std::array<float,3> vector(int i) const;
  std::array<int, 3> face(int i) const;

private:
  std::vector<std::array<float, 3>> vectors;
  std::vector<std::array<int, 3>> faces;
};