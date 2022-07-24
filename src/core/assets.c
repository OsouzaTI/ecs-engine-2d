#include "assets.h"

const char* ASSETS_PATH = "C:\\Users\\osouza\\OneDrive\\Documentos\\UFRR\\6 semestre\\analise_algoritmos\\trabalho_final\\assets";
// iniciando a tabela de assets com 200 de tamanho
HashTable* assets = NULL;

void addAsset(const char* key, const char* file) {
    if(assets == NULL) assets = createHashTable(10);
    char buffer[255];
    sprintf(buffer, "%s\\%s", ASSETS_PATH, file);
    addHashNode(&assets, key, buffer);
}

char* getAsset(const char* key) {
    HashNode* hashNode = findHashNode(assets, key);    
    if(NOTNULL(hashNode))
        return hashNode->value;
    return NULL;
}