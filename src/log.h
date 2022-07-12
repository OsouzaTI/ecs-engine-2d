#ifndef LOG_H
#define LOG_H

#include <stdio.h>

void logMessage(const char* head, const char* message);
void logError(const char* message);
void logInfo(const char* message);

#endif