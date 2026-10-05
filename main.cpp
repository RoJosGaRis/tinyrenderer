#include "config.h"

int main(int argc, char** argv) {
    constexpr int width  = 640;
    constexpr int height = 640;
    TGAImage framebuffer(width, height, TGAImage::RGB);

    
    
    framebuffer.write_tga_file("framebuffer.tga");

    return 0;
}

