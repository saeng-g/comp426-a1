#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

float FRICTION_CONSTANT_X = 0; //default friction
float GRAVITY_CONSTANT_Y = 1; //default gravity

typedef struct {
    float r, b, g;
} color;

typedef struct {
    float x, y;
} point;

typedef struct {
    float vx, vy;
} velocity;

typedef struct {
    point p;
    color c;
    velocity v;
    float w; //weight
} ball;

void set_friction(float);
void set_gravity(float);

void move(ball*);
void change_velocity(ball*);
void change_direction(ball*);
int touch(ball*, ball*);
int touch_wall(ball*, float, float, float, float);

point get_new_point();
color get_new_color();
velocity get_new_velocity();
float get_new_weight();
ball get_new_ball();