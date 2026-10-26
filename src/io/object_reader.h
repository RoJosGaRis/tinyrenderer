#pragma once
#include "../config.h"

class ObjectReader {
public:
  ObjectReader(){}
  Model* read_obj(const std::string& filepath);

private:
  std::vector<std::array<float, 3>> vectors;
  std::vector<std::array<int, 3>> faces;
  bool read_vector(const std::vector<std::string>& words);
  bool read_face(const std::vector<std::string>& words);

};