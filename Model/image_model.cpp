#include "image_model.h"

image_model::image_model(annotation_user *_receiver, Action _action):
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

