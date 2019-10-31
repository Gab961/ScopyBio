#include "annotation_user.h"

annotation_user::annotation_user(std::string _path):
    path(_path)
{

}

std::string annotation_user::getPath(){
    return path;
}

annotation_user_memento *annotation_user::createMemento(){
    return new annotation_user_memento(path);
}

void annotation_user::reinstateMemento(annotation_user_memento *mem){
    path = mem->path;
}
