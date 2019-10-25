#include "pile_view.h"

#include <iostream>
#include "CImg.h"

#define cimg_use_tiff
using namespace cimg_library;

Pile_View::Pile_View()
{

}

void Pile_View::openFile(std::string path)
{
    std::cout << "C'est arrivé ici : " << path << std::endl;
    CImgList<float> imgListTest;
    imgListTest.load_tiff(path.c_str());
       std::cout << imgListTest.size() << std::endl;
//        CImgDisplay main_disp(imgListTest[0],"Image");
}
