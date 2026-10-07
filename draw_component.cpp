#include "draw_component.h"
#include <direct.h>

bool DrawComponent::draw_line(Point& a, Point& b, TGAImage& framebuffer, TGAColor color) {
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
            framebuffer.set(y, x, color);
        } else {
            framebuffer.set(x, y, color);
        }
        error -= dy;
        y += (yStep * (error < 0));
        error += dx * (error < 0);
    }

    return true;
}
int orth_view(float val) {
  float s = std::min(HEIGHT, WIDTH) - 1;
  s = s / 2;
  
  return (val * s) + s; 
}
bool DrawComponent::draw_face(std::array<int, 3> face) {
  float s = std::min(HEIGHT, WIDTH) - 1;
  s = s / 2;
  Point v1 = {
    orth_view(vectors[face[0]][0]),
    orth_view(vectors[face[0]][1])
  }; 
  Point v2 = {
    orth_view(vectors[face[1]][0]),
    orth_view(vectors[face[1]][1])
  }; 
  Point v3 = {
    orth_view(vectors[face[2]][0]),
    orth_view(vectors[face[2]][1])
  };

  draw_line(v1, v2, frameBuffer, color);
  draw_line(v2, v3, frameBuffer, color);
  draw_line(v3, v1, frameBuffer, color);
  
  return true;
}

void DrawComponent::draw_obj(std::string filepath, const TGAColor& color) {
  std::ifstream file;
  std::string line;
  this->color = color;
  size_t vector_count = 0;
  size_t face_count = 0;
  // Define a buffer 
  const size_t size = 1024; 
  // Allocate a character array to store the directory path
  char buffer[size];        
  
  // Call _getcwd to get the current working directory and store it in buffer
  if (getcwd(buffer, size) != NULL) {
      // print the current working directory
      std::cout << "Current working directory: " << buffer << std::endl;
  } 
  else {
      // If _getcwd returns NULL, print an error message
      std::cerr << "Error getting current working directory" << std::endl;
  }
  file.open(filepath);
  if (!file.is_open()) {
    std::cout << "Couldn't open file" << std::endl;
      return;
    }
    
    while(getline(file, line)) {
      std::vector<std::string> words = split(line, " ");
      
      if (!words[0].compare("v")) {
        ++vector_count;
      } else if (!words[0].compare("f")) {
        ++face_count;
      }
    }
    file.close();
    
    vectors.reserve(vector_count);
    faces.reserve(face_count);
    
    file.open(filepath);
    while(getline(file, line)) {
    std::vector<std::string> words = split(line, " ");
      
    if (!words[0].compare("v")) {
      if (!read_vector(words)) {
        std::cerr << "Could not read vector: " << line << std::endl;
        break;
      } 
    } else if (!words[0].compare("f")) {
      if (!read_face(words)) {
        std::cerr << "Could not read face: " << line << std::endl;
        break;
      } 
    }
  }
  for (auto face : faces) {
    draw_face(face);
  }
  
  file.close();
  vectors.clear();
  faces.clear();
}

bool DrawComponent::read_vector(const std::vector<std::string>& words) {
  try {
    if (words.size() != 4) {
      return false;
    }
    vectors.push_back(
      std::array<float,3>{
        std::stof(words[1]),
        std::stof(words[2]),
        std::stof(words[3])
      }
    );
  } catch (const std::exception &exc) {
    std::cerr << "Error at DrawComponent::read_vector: " << exc.what() << std::endl;
    return false;
  } catch (...) {
    std::cerr << "Unknow error at DrawComponent::read_vector" << std::endl;
    return false;
  }
  
  return true;
}

bool DrawComponent::read_face(const std::vector<std::string>& words) {
  try {
    if (words.size() != 4) {
      return false;
    }
    std::array<int,3> newFace;
    for (int i = 1; i < 4; i++) {
      int idx = stoi(split(words[i], "/")[0]);
      newFace[i - 1] = idx - 1;
    }
    faces.push_back(
      newFace
    );
  } catch (const std::exception &exc) {
    std::cerr << "Error at DrawComponent::read_face: " << exc.what() << std::endl;
    return false;
  } catch (...) {
    std::cerr << "Unknow error at DrawComponent::read_face" << std::endl;
    return false;
  }
  
  return true;
}