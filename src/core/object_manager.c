#include "object_manager.h"

ObjectManager* createObjectManager(Display* display) {
    ObjectManager* objectManager = (ObjectManager*)malloc(sizeof(ObjectManager));
    ALLOCATE_MEMORY_ERROR(objectManager, "ObjectManager");

    objectManager->display = display;
    objectManager->objects = createLinkedList();
    return objectManager;
}

void addObjectToManager(ObjectManager* objectManager, void* object) {
    Node* objectNode = createNode(object);
    pushLinkedList(objectManager->objects, objectNode);
}

void renderAllObjectsInManager(ObjectManager* objectManager){
    forEach(object, objectManager->objects){        
        Object* _obj = (Object*)object->data;
        switch (_obj->_objectType)
        {
            case OBJECT2D:
                renderObject2D(objectManager->display, (Object2D*)object->data);
                break;  
            case TEXT2D:
                renderText2D(objectManager->display, (Text2D*)object->data);
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

                // EVENTOS DOS COMPONENTES

                if(NOTNULL(object2D->Components.transform)) {
                    updateTransform(objectManager->display, getTransformFromObject2D(object2D));
                }

                if(NOTNULL(object2D->Components.boxcollider2D)) {
                    updateBoxCollider2D(getBoxCollider2DFromObject2D(object2D));
                }

                if(NOTNULL(object2D->Components.sprite2D)) {
                    updateSprite2D(objectManager->display, getSprite2DFromObject2D(object2D));
                }

                // EVENTOS DO OBJETO

                if(NOTNULL(object2D->Events.update)) {
                    (object2D->Events.update)(object2D, objectManager->display);
                }

                if(NOTNULL(object2D->Events.boxCollision2DEvent)) {
                    CollisionEvent collision = _firstBoxCollider2DTriggered(objectManager, object2D);
                    if(collision.hasCollision){
                        (object2D->Events.boxCollision2DEvent)(object2D, &collision);
                    }                    
                }
            } break;
            case TEXT2D: {
                Text2D* text2D = (Text2D*)object->data;  
                if(NOTNULL(text2D->Events.update)) {
                    (text2D->Events.update)(text2D, objectManager->display);
                }
            } break;    
            default:
                break;
        }
    }
}

Object2D* getObject2DByTokenIdentifier(ObjectManager* objectManager, char* tokenIdentifier) {
    forEach(object, objectManager->objects) {
        Object2D* objectTest = (Object2D*)object->data;
        if(strcmp(objectTest->tokenIdentifier, tokenIdentifier) == 0){
            return objectTest;
        }
    }
    return NULL;
}

CollisionEvent _firstBoxCollider2DTriggered(ObjectManager* objectManager, Object2D* object2D) {
    CollisionEvent collision;
    forEach(object, objectManager->objects) {

        Object* _object = (Object*)object->data;
        if(!isObject2D(_object))
            continue;
        Object2D* objectTest = (Object2D*)object->data;
        if(object2D == objectTest)
            continue;

        BoxCollider2D* boxA = object2D->Components.boxcollider2D;
        BoxCollider2D* boxB = objectTest->Components.boxcollider2D;  
        collision = boxCollision2D(boxA, boxB); 
        if(collision.hasCollision){            
            collision.object = objectTest;
            return collision;
        }
    }
    return collision;
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

int objectManagerMemoryAllocated(ObjectManager* objectManager) {
    if(ISNULL(objectManager)) {
        return 0;
    }
    
    int bytes = 0;
    forEach(object, objectManager->objects){
        Object* _obj = (Object*)object->data;
        switch (_obj->_objectType)
        {
            case OBJECT2D: bytes += object2DMemoryAllocated((Object2D*)object->data);break;
            case TEXT2D: bytes += text2dMemoryAllocated((Text2D*)object->data);break;
            default: break;
        }
    }
    
    return sizeof(ObjectManager) + bytes + linkedListMemoryAllocated(objectManager->objects);
}