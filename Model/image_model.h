#ifndef IMAGE_MODEL_H
#define IMAGE_MODEL_H

#include <string>
#include <cstdlib>

#include "../CImg.h"
#include "annotation_user.h"

class image_model
{
public:
    typedef void(annotation_user:: *Action)();
    image_model(int numImg, annotation_user *_receiver, Action _action);

    void save(std::string pathToSave);
    virtual void execute();
    static void undo();
    void static redo();

protected:
      int numImage;
      annotation_user *receiver;
      Action action;
      static image_model *commandList[20];
      static annotation_user_memento *mementoList[20];
      static int numCommands;
      static int highWater;
};

#endif // IMAGE_MODEL_H
