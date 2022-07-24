#ifndef OBJECT_MANAGER_H
#define OBJECT_MANAGER_H

#include <stdlib.h>
#include <helpers/linkedlist.h>
#include <objects/object2d.h>
#include <core/display.h>

typedef struct object_manager
{
    LinkedList* objects;
} ObjectManager;

ObjectManager* createObjectManager();

void addObjectToManager(ObjectManager* objectManager, void* object);
void addObject2DToManager(ObjectManager* objectManager, Object2D* object2D);
void renderAllObjectsInManager(Display* display, ObjectManager* objectManager);
void updateAllObjectsInManager(Display* display, ObjectManager* objectManager);
Object2D* _firstBoxCollider2DTriggered(ObjectManager* objectManager, Object2D* object2D); 
void destroyObjectManager(ObjectManager** objectManager);

#endif