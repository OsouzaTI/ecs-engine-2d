#include "object_manager.h"

ObjectManager* createObjectManager() {
    ObjectManager* objectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
    objectManager->objects = createLinkedList();
    return objectManager;
}

void addObjectToManager(ObjectManager* objectManager, void* object) {
    Node* objectNode = createNode(object);
    pushLinkedList(objectManager->objects, objectNode);
}

void addObject2DToManager(ObjectManager* objectManager, Object2D* object2D) {
    addObjectToManager(objectManager, (void*)object2D);
}

void renderAllObjectsInManager(Display* display, ObjectManager* objectManager){
    forEach(object, objectManager->objects){
        Object* _obj = (Object*)object->data;
        switch (_obj->_objectType)
        {
            case OBJECT2D:
                renderObject2D(display, (Object2D*)object->data);
                break;            
            default:
                break;
        }
    }
}

void updateAllObjectsInManager(ObjectManager* objectManager) {
    forEach(object, objectManager->objects){
        Object* _obj = (Object*)object->data;
        switch (_obj->_objectType)
        {
            case OBJECT2D:{
                Object2D* object2D = (Object2D*)object->data;                 
                if(NOTNULL(object2D->Events.update))
                    (object2D->Events.update)(object2D);
            } break;            
            default:
                break;
        }
    }
}

void destroyObjectManager(ObjectManager** objectManager) {
    LinkedList* objects = (*objectManager)->objects;
    destroyLinkedList(&objects);
    free(objectManager);
}