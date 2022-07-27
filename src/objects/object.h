#ifndef OBJECT_H
#define OBJECT_H

#define MAX_SIZE_TOKEN_IDENTIFIER 25
#define EMPTY_TOKEN_IDENTIFIER "EMPTY_TOKEN"

extern int OBJECT_ID;

typedef union object { 
    int _objectType; 
    int objectId;
} Object;

#endif