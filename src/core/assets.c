#include "assets.h"

char ASSETS_PATH_SEPARATOR[2];
char ASSETS_PATH[255];
// iniciando a tabela de assets com 200 de tamanho
HashTable* assets = NULL;

void setAssetPathSeparator(const char* pathSeparator) {
    strcpy(ASSETS_PATH_SEPARATOR, pathSeparator);
}

void setAssetPath(const char* path) {
    strcpy(ASSETS_PATH, path);
}

void addAsset(const char* key, const char* file) {
    if(assets == NULL) assets = createHashTable(10);
    char buffer[1024];
    sprintf(buffer, "%s%s%s", ASSETS_PATH, ASSETS_PATH_SEPARATOR, file);
    addHashNode(&assets, key, buffer);
}

char* getAsset(const char* key) {
    HashNode* hashNode = findHashNode(assets, key);    
    if(NOTNULL(hashNode))
        return hashNode->value;
    return NULL;
}