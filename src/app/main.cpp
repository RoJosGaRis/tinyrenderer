#include "../config.h"
#include "../io/object_reader.h"
#include "../render/rasterizer.h"

int main(int argc, char** argv) {
    TGAImage framebuffer(WIDTH, HEIGHT, TGAImage::RGB);

    // ObjectReader* reader = new ObjectReader();
    // Model* pose = reader->read_obj("../obj/diablo3_pose/diablo3_pose.obj");   
    Rasterizer* rasterizer = new Rasterizer(framebuffer);
    // rasterizer->draw_obj(pose, red);
    Point a {100,100};
    Point b {200,100};
    Point c {150,300};
    rasterizer->draw_triangle(c, b, a);
    
    framebuffer.write_tga_file("framebuffer.tga");

    return 0;
}

