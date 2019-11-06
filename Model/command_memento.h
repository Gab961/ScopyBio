#pragma once

#include "CImg.h"

#define NbMaxUndo 20
#define NbMaxCommande 20
class calque;
class annotation_user_memento;

using numImg = int;


class command_memento
{
public:
    typedef void(calque:: *Action)();
    command_memento(calque *_receiver, Action _action);

    virtual void execute();
    void undo();
    void redo();

protected:
      calque *receiver;
      Action action;
      command_memento *commandList[NbMaxCommande];
      annotation_user_memento *mementoList[NbMaxUndo];
      int numCommands = 0;
      int highWater = 0;
};
