#ifndef ANNOTATION_USER_MEMENTO_H
#define ANNOTATION_USER_MEMENTO_H

#include "annotation_user.h"

class annotation_user_memento
{

private:
  friend class annotation_user;
  std::string path;

public:

    annotation_user_memento(std::string _path)
    {
        _path = path;
    }


};

#endif // ANNOTATION_USER_MEMENTO_H

