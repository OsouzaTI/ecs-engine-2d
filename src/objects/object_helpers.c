#include "object_helpers.h"

Vector2D getObjectPosition(void* object) {
    Vector2D _default = {.x = -1 , .y = -1};
    
    if(ISNULL(object)) return _default;

    Object* _obj = (Object*)object;
    switch (_obj->_objectType)
    {
        case OBJECT2D: return cloneVector2D(TFGPOS(OBJ2DGTF((Object2D*)object)));
        case TEXT2D: return ((Text2D*)object)->position;
        default: return _default;
    }
}