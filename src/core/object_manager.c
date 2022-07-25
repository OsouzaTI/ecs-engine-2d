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

void updateAllObjectsInManager(Display* display, ObjectManager* objectManager) {
    forEach(object, objectManager->objects){
        Object* _obj = (Object*)object->data;
        switch (_obj->_objectType)
        {
            case OBJECT2D:{
                Object2D* object2D = (Object2D*)object->data;   

                if(NOTNULL(object2D->Components.transform)) {
                    updateTransform(display, getTransformFromObject2D(object2D));
                }

                if(NOTNULL(object2D->Components.boxcollider2D)) {
                    updateBoxCollider2D(getBoxCollider2DFromObject2D(object2D));
                }

                if(NOTNULL(object2D->Events.update)) {
                    (object2D->Events.update)(object2D, display);
                }

                if(NOTNULL(object2D->Events.boxCollision2DEvent)) {
                    Object2D* objectTriggeredBoxCollision2D = _firstBoxCollider2DTriggered(objectManager, object2D);
                    if(NOTNULL(objectTriggeredBoxCollision2D)){
                        (object2D->Events.boxCollision2DEvent)(object2D, objectTriggeredBoxCollision2D);
                    }                    
                }
            } break;            
            default:
                break;
        }
    }
}

Object2D* _firstBoxCollider2DTriggered(ObjectManager* objectManager, Object2D* object2D) {
    forEach(object, objectManager->objects) {
        Object2D* objectTest = (Object2D*)object->data;
        BoxCollider2D* boxA = object2D->Components.boxcollider2D;
        BoxCollider2D* boxB = objectTest->Components.boxcollider2D;        
        if((object2D != objectTest) && boxCollision2D(boxA, boxB)){
            return objectTest;
        }
    }
    return NULL;
}

void destroyObjectManager(ObjectManager** objectManager) {
    LinkedList* objects = (*objectManager)->objects;
    forEach(object, objects){
        Object* _obj = (Object*)object->data;
        switch (_obj->_objectType)
        {
            case OBJECT2D:
                destroyObject2D((Object2D*)object->data);
                break;
            default:
                break;
        }
    }

    destroyLinkedList(&objects);
    free(objectManager);
}