#pragma once
#include <cmath>
#include <iostream>
#include <ctime>
#include <chrono>
#include <array>
#include <string>

#include "io/tgaimage.h"
#include "core/model.h"

std::vector<std::string> split(std::string line, std::string delimiter);

constexpr TGAColor white   = {255, 255, 255, 255}; // attention, BGRA order
constexpr TGAColor green   = {  0, 255,   0, 255};
constexpr TGAColor red     = {  0,   0, 255, 255};
constexpr TGAColor blue    = {255, 128,  64, 255};
constexpr TGAColor yellow  = {  0, 200, 255, 255};
constexpr int HEIGHT = 320;
constexpr int WIDTH = 320;

struct Point {
    int x;
    int y;
};