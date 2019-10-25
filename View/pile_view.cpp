#include "pile_view.h"

#include <iostream>


Pile_View::Pile_View()
{

}

void Pile_View::openFile(std::string path)
{
    std::cout << "C'est arrivé ici : " << path << std::endl;
    m_imgList.load_tiff(path.c_str());
       std::cout << m_imgList.size() << std::endl;
//        CImgDisplay main_disp(imgListTest[0],"Image");
}
