#ifndef LOG_H
#define LOG_H

#include <string.h>

#define ENGINE_DEBUG 1

#define __FILENAME__ (strrchr(__FILE__, '/') ? strrchr(__FILE__, '/') + 1 : __FILE__)

#define DEBUG_ENABLED \
    if (ENGINE_DEBUG)

#define LOGERR(x) \
    DEBUG_ENABLED printf("[LOGERR][%s][%d] %s\n", __FILENAME__, __LINE__, x)
    
#define LOGERR2(x, y) \
    DEBUG_ENABLED printf("[LOGERR][%s][%d] %s %s\n", __FILENAME__, __LINE__, x, y)

#define LOGINF(x) \
    DEBUG_ENABLED printf("[LOGINF][%s][%d] %s\n", __FILENAME__, __LINE__, x)

#define LOGINF2(x, y) \
    DEBUG_ENABLED printf("[LOGINF][%s][%d] %s %s\n", __FILENAME__, __LINE__, x, y)

#define LOGINF3(x, y, z) \
    DEBUG_ENABLED printf("[LOGINF][%s][%d] %s %s %s\n", __FILENAME__, __LINE__, x, y, z)

#define LOGWARN(x) \
    DEBUG_ENABLED printf("[LOGWARN][%s][%d] %s\n", __FILENAME__, __LINE__, x)

#define ALLOCATE_MEMORY_ERROR(x, y) \
    if (ISNULL(x)) \
        printf("[%s][%d] Nao foi possivel alocar memoria para: %s\n", __FILENAME__, __LINE__, y)

#endif