#include "annotation_user.h"
#include "annotation_user_memento.h"

CImg<float> annotation_user::getCalque() const
{
    return calque;
}

annotation_user::annotation_user(CImg<float> _calque):
    calque(_calque)
{

}



annotation_user_memento *annotation_user::createMemento(){
    return new annotation_user_memento(calque);
}

void annotation_user::reinstateMemento(annotation_user_memento *mem){
    calque = mem->calque;
}
