#include "pile_model.h"

pile_model::pile_model()
{

}

void pile_model::load(string path)
{
    ifstream file;
    file.exceptions ( std::ifstream::failbit | std::ifstream::badbit );
    try {
      file.open (path);

      images.clear();

          // Open a Stream and decode a TIFF image
          ifstream imageStreamSource = new ifstream(path, "r");
          TiffBitmapDecoder decoder = new TiffBitmapDecoder(imageStreamSource,     BitmapCreateOptions.PreservePixelFormat, BitmapCacheOption.Default);

          foreach(BitmapSource bmpS in decoder.Frames)
          {
             Image img = new Image();
             img.Source = bmpS;
             img.Stretch = Stretch.None;
             img.Margin = new Thickness(10);

             images.Add(img);
          }

          if(images.Count > 0)
              pictureBox1.Image = images[0];

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

