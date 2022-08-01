#ifndef CORE_ASSETS_H
#define CORE_ASSETS_H

#include <stdio.h>
#include <string.h>
#include <helpers/hashtable.h>
#include <SDL2/SDL_ttf.h>

extern char ASSETS_PATH_SEPARATOR[2];
extern char ASSETS_PATH[255];
extern HashTable* assets;
extern HashTable* fonts;

#define ASSET_IMAGE_PATH  "images"
#define ASSET_FONT_PATH   "fonts"
#define ASSET_SOUND_PATH  "sounds"

typedef enum {
    ASSET_IMAGE = 0,
    ASSET_FONT,
    ASSET_SOUND    
} AssetType;

void setAssetPathSeparator(const char* pathSeparator);
void setAssetPath(const char* path);
void addAsset(const char* key, const char* file, AssetType type, void* attributes);
char* getAsset(const char* key);
TTF_Font* getFont(const char* key);
const char* assetPath(const char* fileName);

#endif