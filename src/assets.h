#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <string.h>
#include "hashtable.h"

extern const char* ASSETS_PATH;
extern HashTable* assets;

void addAsset(const char* key, const char* file);
char* getAsset(const char* key);
const char* assetPath(const char* fileName);

#endif