#include "command_memento.h"
#include "calque.h"
#include "annotation_user_memento.h"

command_memento::command_memento(calque *_receiver, Action _action):
    receiver(_receiver),
    action(_action){}


void command_memento::execute()
{/*
        mementoList[numCommands] = receiver->createMemento();
        commandList[numCommands] = this;
        if (numCommands > highWater)
          highWater = numCommands;
        numCommands++;
        (receiver->*action)();*/
}

void command_memento::undo()
{/*
    if (numCommands == 0)
    {
        return ;
    }
    commandList[numCommands - 1]->receiver->reinstateMemento
      (mementoList[numCommands - 1]);
    numCommands--;*/
}

void command_memento::redo()
{/*
    if (numCommands > highWater)
    {
        return ;
    }
    (commandList[numCommands]->receiver->*(commandList[numCommands]->action))();
    numCommands++;*/
}
