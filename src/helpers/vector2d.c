#include "vector2d.h"

Vector2D multiplyVector2D(Vector2D* u, Vector2D* v) {
    return (Vector2D) {
        .x = u->x * v->x,
        .y = u->y * v->y,
    };
}

Vector2D multiplyVector2DByScalar(Vector2D* u, float s) {
    return (Vector2D) {
        u->x * s,
        u->y * s,
    };
}

Vector2D sumVector2D(Vector2D* u, Vector2D* v) {
    return (Vector2D) {
        u->x + v->x,
        u->y + v->y,
    };
}

Vector2D sumVector2DByScalar(Vector2D* u, float s) {
    return (Vector2D) {
        u->x + s,
        u->y + s,
    }; 
}

Vector2D subVector2D(Vector2D* u, Vector2D* v){
    return (Vector2D) {
        u->x - v->x,
        u->y - v->y,
    };
}

Vector2D bounceVector2D(Vector2D* u, Vector2D* v) {
    // u : Velocity
    // v : normal
    float dot_U_V =  dotProductVector2D(u, v);
    Vector2D reflect = multiplyVector2DByScalar(v, -2 * dot_U_V);
    reflect = sumVector2D(u, &reflect);
    return reflect;
}

float dotProductVector2D(Vector2D* u, Vector2D* v) {
    return (u->x * v->x) + (u->y * v->y);
}

float distanceBetweenPoints(Vector2D* u, Vector2D* v) {
    float uv_x, uv_y;
    uv_x = powf(u->x - v->x, 2);
    uv_y = powf(u->y - v->y, 2);
    return sqrtf(uv_x + uv_y);
}

Vector2D rotateVector2D(Vector2D* u, float angle) {
    return (Vector2D) {
        u->x * cos(angle) - u->y * sin(angle),
        u->x * sin(angle) - u->y * cos(angle),
    };
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

void printVector2D(Vector2D* u) {
    printf("Vector2D(%f, %f)\n", u->x, u->y);
}