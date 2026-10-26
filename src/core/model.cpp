#include "model.h"

int Model::nvectors() const {
  return vectors.size();
}
int Model::nfaces() const {
  return faces.size();
}
std::array<float,3> Model::vector(int i) const {
  return vectors[i];
}
std::array<int, 3> Model::face(int i) const {
  return faces[i];
};
