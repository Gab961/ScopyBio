#include <cstdio>
#include <iostream>
/*#include <Model/pile_model.h>*/

// commande pour build
// conan install .. --build protobuf --build openexr --build opencv

#ifndef cimg_debug
#define cimg_debug 1
#endif
#undef min
#undef max

#define cimg_use_tiff

#define cimg_display 0
#define cimg_use_tiff
#define cimg_use_png
#include "CImg.h"

#include <cstdlib>

using namespace cimg_library;

int main()
{
    std:: cout << "gab il a une maitr yi op" << std::endl;

    CImgList<float> images;
    images.load_tiff("../../Data/pileTest.tiff",0,25,1);
    std::cout<< images.size() << std::endl;

    images.data(1)->display("test");
    images.data(24)->display("24");
    images[24].display("24bis");
    return 0;


//    CImg<unsigned char> image("milla.bmp"), visu(500,400,1,3,0);
//    const unsigned char red[] = { 255,0,0 }, green[] = { 0,255,0 }, blue[] = { 0,0,255 };
//    image.blur(2.5);
//    CImgDisplay main_disp(image,"Click a point"), draw_disp(visu,"Intensity profile");
//    while (!main_disp.is_closed() && !draw_disp.is_closed()) {
//      main_disp.wait();
//      if (main_disp.button() && main_disp.mouse_y()>=0) {
//        const int y = main_disp.mouse_y();
//        visu.fill(0).draw_graph(image.get_crop(0,y,0,0,image.width()-1,y,0,0),red,1,1,0,255,0);
//        visu.draw_graph(image.get_crop(0,y,0,1,image.width()-1,y,0,1),green,1,1,0,255,0);
//        visu.draw_graph(image.get_crop(0,y,0,2,image.width()-1,y,0,2),blue,1,1,0,255,0).display(draw_disp);
//        }
//      }
//    return 0;
}
