#include "log.h"

void logMessage(const char* head, const char* message) {
    printf("%s: %s\n", head, message);
}

void logError(const char* message) {
    logMessage("ERROR", message);
}

void logInfo(const char* message) {
    logMessage("INFO", message);
}