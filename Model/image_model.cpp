#include "image_model.h"
#include "annotation_user.h"
#include "annotation_user_memento.h"

image_model::image_model(int numImg, annotation_user *_receiver, Action _action):
    numImage(numImg),
    receiver(_receiver),
    action(_action){}


void image_model::execute()
{
        mementoList[numCommands] = receiver->createMemento();
        commandList[numCommands] = this;
        if (numCommands > highWater)
          highWater = numCommands;
        numCommands++;
        (receiver->*action)();
}

void image_model::undo()
{
    if (numCommands == 0)
    {
        return ;
    }
    commandList[numCommands - 1]->receiver->reinstateMemento
      (mementoList[numCommands - 1]);
    numCommands--;
}

void image_model::redo()
{
    if (numCommands > highWater)
    {
        return ;
    }
    (commandList[numCommands]->receiver->*(commandList[numCommands]->action))();
    numCommands++;
}

void image_model::save(std::string pathToSave){
    CImg<float> toSave = mementoList[numCommands]->getCalque();
    std::string pathTmp = pathToSave + "/Calques/calque" + std::to_string(numImage) + ".png";
    char * path = NULL;
    std::strcpy(path, pathTmp.c_str());
    toSave.save_png(path,0);
}
