#include "config.h"

std::vector<std::string> split(std::string line, std::string delimiter) {
    std::vector<std::string> lineSplit;

    size_t pos = 0;

    std::string token;

    while (pos = line.find(delimiter) != line.npos) {
        token = line.substr(0, pos);
        lineSplit.push_back(token);
        line.erase(0, pos + delimiter.size());
    }
    lineSplit.push_back(line);
    
    return lineSplit;
}