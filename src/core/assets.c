#include "assets.h"

char ASSETS_PATH_SEPARATOR[2];
char ASSETS_PATH[255];
// iniciando a tabela de assets com 200 de tamanho
HashTable* assets = NULL;
HashTable* fonts = NULL;

void setAssetPathSeparator(const char* pathSeparator) {
    strcpy(ASSETS_PATH_SEPARATOR, pathSeparator);
}

void setAssetPath(const char* path) {
    strcpy(ASSETS_PATH, path);
}

void addAsset(const char* key, const char* file, AssetType type, void* attributes) {
    if(ISNULL(assets)) {
        assets = createHashTable(10);
    } 
    if(ISNULL(fonts)) {
        fonts = createHashTable(10);
    } 
    
    char buffer[1024];
    switch (type)
    {   
        // URI EXAMPLE: ASSETS_PATH{SEP}{ASSET_x_PATH}{SEP}{file}
        case ASSET_IMAGE:{
            sprintf(buffer, "%s%s%s%s%s", ASSETS_PATH, ASSETS_PATH_SEPARATOR, ASSET_IMAGE_PATH, ASSETS_PATH_SEPARATOR, file);            
        } break;
        case ASSET_FONT: {
            sprintf(buffer, "%s%s%s%s%s", ASSETS_PATH, ASSETS_PATH_SEPARATOR, ASSET_FONT_PATH, ASSETS_PATH_SEPARATOR,  file);            
            // carregando fonte 
            int* size = (int*)attributes;
            TTF_Font *font = TTF_OpenFont(buffer, *size);    
            if(NOTNULL(font)) {                
                addGenericHashNode(&fonts, key, (void*)font);
            } else {
                LOGERR2("Erro ao carregar fonte: ", buffer);                
            }
        } break;
        case ASSET_SOUND:{
            sprintf(buffer, "%s%s%s%s%s", ASSETS_PATH, ASSETS_PATH_SEPARATOR, ASSET_SOUND_PATH, ASSETS_PATH_SEPARATOR, file);            
        } break;
        default:
            break;
    }
    addHashNode(&assets, key, buffer);
}

char* getAsset(const char* key) {
    HashNode* hashNode = findHashNode(assets, key);    
    if(NOTNULL(hashNode))
        return hashNode->value;
    return NULL;
}

TTF_Font* getFont(const char* key) {
    HashNode* hashNode = findHashNode(fonts, key);    
    if(NOTNULL(hashNode))
        return (TTF_Font*)hashNode->data;
    return NULL;
}