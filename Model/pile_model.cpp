#include "pile_model.h"

pile_model::pile_model()
{

}

pile_model::pile_model(string filename)
{
    load(filename);

}

void pile_model::load(string path)
{
    ifstream file (path, std::ifstream::in | std::ifstream::binary);;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );

      images.clear();

      images.load_tiff(path.c_str());

      images.display();

      file.close();


    return;

}

void pile_model::save(string path)
{
    return;
}

