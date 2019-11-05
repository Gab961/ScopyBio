#pragma once

#include <string>
#include <cstdlib>

#include "CImg.h"
class annotation_user;
class annotation_user_memento;

class image_model
{
public:
    typedef void(annotation_user:: *Action)();
    image_model(int numImg, annotation_user *_receiver, Action _action);

    void save(std::string pathToSave);
    virtual void execute();
    void undo();
    void redo();

protected:
      int numImage;
      annotation_user *receiver;
      Action action;
      image_model *commandList[20];
      annotation_user_memento *mementoList[20];
      int numCommands = 0;
      int highWater = 0;
};
