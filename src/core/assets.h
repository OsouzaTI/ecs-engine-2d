#ifndef ASSETS_H
#define ASSETS_H

#include <stdio.h>
#include <string.h>
#include <helpers/hashtable.h>

extern char ASSETS_PATH_SEPARATOR[2];
extern char ASSETS_PATH[255];
extern HashTable* assets;

void setAssetPathSeparator(const char* pathSeparator);
void setAssetPath(const char* path);
void addAsset(const char* key, const char* file);
char* getAsset(const char* key);
const char* assetPath(const char* fileName);

#endif