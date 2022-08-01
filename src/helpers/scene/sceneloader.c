#include "sceneloader.h"

ObjectSceneLoader* createObjectSceneLoader() {
    ObjectSceneLoader* objectSceneLoader = (ObjectSceneLoader*)malloc(sizeof(ObjectSceneLoader));
    ALLOCATE_MEMORY_ERROR(objectSceneLoader, "ObjectSceneLoader");

    // has attributes
    objectSceneLoader->hasSize = 0;
    objectSceneLoader->hasPosition = 0;
    objectSceneLoader->hasBoxCollider2D = 0;
    objectSceneLoader->hasTokenIdentifier = 0;
    objectSceneLoader->hasVelocity = 0;
    objectSceneLoader->hasDirection = 0;
    objectSceneLoader->hasScale = 0;
    objectSceneLoader->hasAnimationSprite2D = 0;

    objectSceneLoader->collisionTag = COLLISION_TAG_0;
    objectSceneLoader->renderBoxCollider2D = 0; 
    setVector2D(&objectSceneLoader->position, 0, 0);
    setVector2D(&objectSceneLoader->size, 16, 16);
    // inicializando vetor de colisoes
    for (int i = 0; i < N_COLLISION_TAGS; i++)
    {
        objectSceneLoader->collisionTags[i] = COLLISION_DISABLED;
    }   
    return objectSceneLoader;
}

void objectSceneLoaderBindWithObject2D(Display* display, ObjectSceneLoader* objectSceneLoader, Object2D* object2D) {

    // bindando atributos e componentes

    // box collider component
    if(objectSceneLoader->hasBoxCollider2D){
        setBoxCollider2D(object2D);
        if(objectSceneLoader->renderBoxCollider2D){
            object2D->renderCollider = objectSceneLoader->renderBoxCollider2D;
        }

        // tags de colisao
        BoxCollider2D* boxCollider2D = getBoxCollider2DFromObject2D(object2D);
        setBoxCollider2DTag(boxCollider2D, objectSceneLoader->collisionTag);
        for (int i = 0; i < N_COLLISION_TAGS; i++)
        {
            boxCollider2D->collisionTags[i] = objectSceneLoader->collisionTags[i];
        }
    }

    // setando sprite component
    setObject2DSprite(display, object2D, getAsset(objectSceneLoader->spriteName));
   
    Vector2D* size = &objectSceneLoader->size;
    Vector2D* scale = &objectSceneLoader->scale;
    Vector2D* pos = &objectSceneLoader->position;
    Vector2D* velocity = &objectSceneLoader->velocity;
    Vector2D* direction = &objectSceneLoader->direction;

    // definindo tamanho
    if(objectSceneLoader->hasSize){
        setObject2DSize(object2D, size->x, size->y);
    }

    // definindo escala
    if(objectSceneLoader->hasScale){
        setObject2DScale(object2D, scale->x, scale->y);
    }

    // definindo posicao inicial
    if(objectSceneLoader->hasPosition) {
        setObject2DPosition(object2D, size->x * pos->x, size->y * pos->y);
    }

    // definindo velocidade do objeto
    if(objectSceneLoader->hasVelocity) {
        setObject2DVelocity(object2D, velocity->x, velocity->y);
    }

    // definindo direção
    if(objectSceneLoader->hasDirection) {
        setObject2DDirection(object2D, direction->x, direction->y);
    }

    // definindo token de identificação
    if(objectSceneLoader->hasTokenIdentifier) {
        setObject2DTokenIdentifier(object2D, objectSceneLoader->tokenIdentifier);
    }

    // setando animação no sprite2D
    if(objectSceneLoader->hasAnimationSprite2D) {
        setObject2DAnimationSprite2D(
            object2D, 
            objectSceneLoader->AnimationSprite2DHelper.speed,
            objectSceneLoader->AnimationSprite2DHelper.frames
        );
    }

}

void printObjectSceneLoader(ObjectSceneLoader* objectSceneLoader) {
    printf("TOKEN: %s\n", objectSceneLoader->token);
    printf("SPRITE_NAME: %s\n", objectSceneLoader->spriteName);
    printf("COLLISION_TAG: %d\n", objectSceneLoader->collisionTag);    
}

void sceneLoader(ObjectManager* objectManager, Display* display, const char* filePath) {

    FILE* file = fopen(filePath, "r");
    ALLOCATE_MEMORY_ERROR(file, "SceneLoader (file)");
    
    char buffer[1024];
    while (1) {

        int res = fscanf(file, "%s", buffer);
        if (res == EOF)
            break;

        if(strcmp(buffer, "ASSET_PATH") == 0) {
            char path[255];
            fscanf(file, "%s", path);
            setAssetPath(path);
        } else if (strcmp(buffer, "ASSET_IMAGE") == 0) {
            char name[255], path[255];
            fscanf(file, "%s %s", name, path);
            addAsset(name, path, ASSET_IMAGE, NULL);
        } else if (strcmp(buffer, "ASSET_FONT") == 0) {
            int size;
            char name[255], path[255];
            fscanf(file, "%s %s %d", name, path, &size);
            addAsset(name, path, ASSET_FONT, (void*)&size);
        } else if (strcmp(buffer, "ASSET_SOUND") == 0) {
            char name[255], path[255];
            fscanf(file, "%s %s", name, path);
            addAsset(name, path, ASSET_SOUND, NULL);
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
                } else if(strcmp(buffer, "#OBJECT_START") == 0){
                    
                    ObjectSceneLoader* objectSceneLoader = createObjectSceneLoader();
                    
                    // atibutos desse objeto de cena
                    fscanf(file, "%s", objectSceneLoader->token);

                    // lendo os atributos do objeto ate encontrar o fim
                    while(1) {

                        fscanf(file, "%s", buffer);
                        if(strcmp(buffer, "#OBJECT_END") == 0){
                            break;
                        } else if(strcmp(buffer, ">_SIZE") == 0){
                            float x, y;
                            fscanf(file, "%f %f", &x, &y);
                            setVector2D(&objectSceneLoader->size, x, y);
                            objectSceneLoader->hasSize = 1;
                        } else if(strcmp(buffer, ">_SCALE") == 0){
                            float x, y;
                            fscanf(file, "%f %f", &x, &y);
                            setVector2D(&objectSceneLoader->scale, x, y);
                            objectSceneLoader->hasScale = 1;
                        } else if(strcmp(buffer, ">_POSITION") == 0){
                            float x, y;
                            fscanf(file, "%f %f", &x, &y);
                            setVector2D(&objectSceneLoader->position, x, y);
                            objectSceneLoader->hasPosition = 1;
                        } else if(strcmp(buffer, ">_VELOCITY") == 0){
                            float x, y;
                            fscanf(file, "%f %f", &x, &y);
                            setVector2D(&objectSceneLoader->velocity, x, y);
                            objectSceneLoader->hasVelocity = 1;
                        } else if(strcmp(buffer, ">_DIRECTION") == 0){
                            float x, y;
                            fscanf(file, "%f %f", &x, &y);
                            setVector2D(&objectSceneLoader->direction, x, y);
                            objectSceneLoader->hasDirection = 1;
                        } else if(strcmp(buffer, ">_TOKEN_IDENTIFIER") == 0) {
                            fscanf(file, "%s", objectSceneLoader->tokenIdentifier);
                            objectSceneLoader->hasTokenIdentifier = 1;
                        } else if(strcmp(buffer, ">_COLLISION_TAG") == 0){
                            fscanf(file, "%d", &objectSceneLoader->collisionTag);
                        } else if(strcmp(buffer, ">_COLLISION_TAGS") == 0) {
                            for (int i = 0; i < N_COLLISION_TAGS; i++)
                            {
                                fscanf(file, "%d", &objectSceneLoader->collisionTags[i]);                                         
                            }                            
                        } else if(strcmp(buffer, ">_BOX_COLLIDER2D") == 0) {
                            fscanf(file, "%d", &objectSceneLoader->hasBoxCollider2D);
                        } else if(strcmp(buffer, ">_BOX_COLLIDER2D_RENDER") == 0) {
                            if(objectSceneLoader->hasBoxCollider2D){
                                fscanf(file, "%d", &objectSceneLoader->renderBoxCollider2D);
                            }
                        } else if(strcmp(buffer, ">_SPRITE_NAME") == 0) {
                            fscanf(file, "%s", objectSceneLoader->spriteName);                            
                        } else if(strcmp(buffer, ">_ANIMATION_SPRITE") == 0) {
                            struct animation_sprite2d_helper* helper = &objectSceneLoader->AnimationSprite2DHelper;
                            fscanf(file, "%d %f", &helper->frames, &helper->speed);
                            objectSceneLoader->hasAnimationSprite2D = 1;
                        } 

                    }

                    // adicionando object scene loader
                    addGenericHashNode(&objects, objectSceneLoader->token, (void*)objectSceneLoader);
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
                    HashNode* node = findHashNode(objects, c);
                    if(NOTNULL(node)){
                        ObjectSceneLoader* objectSceneLoader = (ObjectSceneLoader*)node->data;
                        Object2D* object2D = createObject2D(display, SIZE * i, SIZE * line, SIZE, SIZE);                    
                        // printObjectSceneLoader(objectSceneLoader);
                        objectSceneLoaderBindWithObject2D(display, objectSceneLoader, object2D);
                        addObjectToManager(objectManager, VOID(object2D));
                    }                     
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