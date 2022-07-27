#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <stdlib.h>
#include <string.h>
#include <helpers/linkedlist.h>
#include <objects/object2d.h>
#include <core/display.h>
#include <core/collision_event.h>

typedef struct object_manager
{
    Display* display;
    LinkedList* objects;
} ObjectManager;

ObjectManager* createObjectManager(Display* display);

void addObjectToManager(ObjectManager* objectManager, void* object);
void addObject2DToManager(ObjectManager* objectManager, Object2D* object2D);
void renderAllObjectsInManager(ObjectManager* objectManager);
void updateAllObjectsInManager(ObjectManager* objectManager);
Object2D* getObject2DByTokenIdentifier(ObjectManager* objectManager, char* tokenIdentifier);
CollisionEvent _firstBoxCollider2DTriggered(ObjectManager* objectManager, Object2D* object2D); 
void destroyObjectManager(ObjectManager** objectManager);

#endif