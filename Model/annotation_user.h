#ifndef ANNOTATION_USER_H
#define ANNOTATION_USER_H

#include <string>
#include "annotation_user_memento.h"


class annotation_user
{
private:
    std::string path;

public:
    annotation_user(std::string _path);


    std::string getPath();

    annotation_user_memento *createMemento();

    void reinstateMemento(annotation_user_memento *mem);

};

#endif // ANNOTATION_USER_H
