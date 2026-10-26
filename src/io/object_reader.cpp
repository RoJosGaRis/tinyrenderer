#include "object_reader.h"

Model* ObjectReader::read_obj(const std::string& filepath) {
  std::ifstream file;
  std::string line;

  size_t vector_count = 0;
  size_t face_count = 0;      
  
  file.open(filepath);
  if (!file.is_open()) {
    std::cout << "Couldn't open file" << std::endl;
    return nullptr;
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

  Model* newModel = new Model(vectors, faces);
  
  file.close();
  vectors.clear();
  faces.clear();

  return newModel;
}

bool ObjectReader::read_vector(const std::vector<std::string>& words) {
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

bool ObjectReader::read_face(const std::vector<std::string>& words) {
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