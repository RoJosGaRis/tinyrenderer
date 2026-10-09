#include "config.h"
#include "draw_component.h"

int main(int argc, char** argv) {
    TGAImage framebuffer(WIDTH, HEIGHT, TGAImage::RGB);

    DrawComponent drawComponet(framebuffer);
    drawComponet.draw_obj("../obj/diablo3_pose/diablo3_pose.obj", red);    
    
    framebuffer.write_tga_file("framebuffer.tga");

    return 0;
}

