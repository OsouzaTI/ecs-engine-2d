#include "sceneloader.h"

ObjectSceneLoader* createObjectSceneLoader() {
    ObjectSceneLoader* objectSceneLoader = (ObjectSceneLoader*)malloc(sizeof(ObjectSceneLoader));
    return objectSceneLoader;
}

void sceneLoader(ObjectManager* objectManager, Display* display, const char* filePath) {

    FILE* file = fopen(filePath, "r");
    if(ISNULL(file)){
        printf("erro ao ler mapa\n");
        exit(1);
    }

    while (1) {
    
        char buffer[1024];

        int res = fscanf(file, "%s", buffer);
        if (res == EOF)
            break;

        // adicionando asset ao projeto
        if (strcmp(buffer, "ASSET") == 0) {
            char name[255], path[255];
            fscanf(file, "%s %s", name, path);
            addAsset(name, path);
        } else if(strcmp(buffer, "ASSET_PATH") == 0) {
            char path[255];
            fscanf(file, "%s", path);
            setAssetPath(path);
        } else if(strcmp(buffer, "ASSET_PATH_SEPARATOR") == 0) {
            char separator[2];
            fscanf(file, "%s", separator);
            setAssetPathSeparator(separator);
        } else if(strcmp(buffer, "MAP_START") == 0) {
            
            // helpers
            HashTable* objects = createHashTable(50);

            // Atributos do mapa
            int SIZE;

            while(1) {
                fscanf(file, "%s", buffer);                
                if (strcmp(buffer, "#SIZE") == 0){
                    fscanf(file, "%d", &SIZE);
                } else if(strcmp(buffer, "#OBJECT") == 0){
                    char key[2];
                    ObjectSceneLoader objectSceneLoader;
                    fscanf(file,
                        "%s %d %d %s",
                        key, 
                        &objectSceneLoader.hasBoxCollider2D,
                        &objectSceneLoader.renderBoxCollider2D,
                        objectSceneLoader.spriteName
                    );
                    addGenericHashNode(&objects, key, (void*)&objectSceneLoader);
                } else if(strncmp(buffer, "*", 1) == 0){
                    break;
                }
            }


            // mapa de tamanho: WxW
            int width = -1;
            int line = 0;
            while(1){
                
                if(width == -1) {              
                    width = strlen(buffer);
                }

                // iterando caractere por caractere da linha
                for (int i = 0; i < width; i++)
                {
                    if(buffer[i] == '-')
                        continue;                        
                    char c[2];
                    sprintf(c, "%c", buffer[i]);
                    ObjectSceneLoader* objectSceneLoader = (ObjectSceneLoader*)findHashNode(objects, c)->data;
                    // Criando o object
                    Object2D* object2D = createObject2D(display, SIZE * i, SIZE * line, SIZE, SIZE);
                    if(objectSceneLoader->hasBoxCollider2D){
                        setBoxCollider2D(object2D);
                        if(objectSceneLoader->renderBoxCollider2D){
                            object2D->renderCollider = 1;
                        }
                    }                    
                    setSpriteObject2D(display, object2D, getAsset(objectSceneLoader->spriteName));
                    addObject2DToManager(objectManager, object2D);                  
                }          

                // incrementa o numero de linhas lidas
                line++;

                // lendo o mapa linha a linha
                fscanf(file, "%s", buffer);
                if(strcmp(buffer, "MAP_END") == 0)
                    break;
            }

            freeHashTable(objects);
        }

    }

}