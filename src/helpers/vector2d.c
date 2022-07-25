#include "vector2d.h"

Vector2D* multiplyVector2D(Vector2D* u, Vector2D* v) {
    u->x = u->x * v->x;
    u->y = u->y * v->y;
    return u;
}

Vector2D* multiplyVector2DByScalar(Vector2D* u, float s) {
    u->x = u->x * s;
    u->y = u->y * s;
    return u;
}

Vector2D* sumVector2D(Vector2D* u, Vector2D* v) {
    u->x = u->x + v->x;
    u->y = u->y + v->y;
    return u;
}

float dotProductVector2D(Vector2D* u, Vector2D* v) {
    return (u->x * v->x) + (u->y * v->y);
}

Vector2D* rotateVector2D(Vector2D* u, float angle) {
    u->x = u->x * cos(angle) - u->y * sin(angle);
    u->y = u->x * sin(angle) - u->y * cos(angle);
    return u;
}

// helpers
void setVector2D(Vector2D* u, float x, float y) {
    u->x = x;
    u->y = y;
}

Vector2D cloneVector2D(Vector2D* u) {
    return (Vector2D) {
        .x = u->x,
        .y = u->y
    };
}