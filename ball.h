#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// OpenGL related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>

float FRICTION_CONSTANT_X = 0.00001f; //default friction
float GRAVITY_CONSTANT_Y = 0.00001f; //default gravity

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

void move_ball(ball*);
void change_velocity(ball*);
void change_direction(ball*);
int touch(ball*, ball*);
char touch_wall(ball*, float, float, float, float);

point get_new_point(void);
color get_new_color(void);
velocity get_new_velocity(void);
float get_new_weight(void);
ball get_new_ball(void);
