#ifndef SCENELOADER_H
#define SCENELOADER_H

#include <stdio.h>
#include <stdlib.h>
#include <core/assets.h>
#include <core/object_manager.h>
#include <objects/object2d.h>
#include <helpers/hashtable.h>

typedef struct object_scene_loader
{
    char spriteName[255];
    int hasBoxCollider2D;
    int renderBoxCollider2D;
} ObjectSceneLoader;

ObjectSceneLoader* createObjectSceneLoader();
void sceneLoader(ObjectManager* objectManager, Display* display, const char* filePath);

#endif