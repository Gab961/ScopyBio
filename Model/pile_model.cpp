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
    try {

      images.clear();

      images.load_tiff(path.c_str());

      images.display();

      file.close();

    }
    catch (std::ifstream::failure e) {
      std::cerr << "Exception opening/reading/closing file\n";
    }
    return;

}

void pile_model::save(string path)
{
    return;
}

