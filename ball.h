#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// OpenGL related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>

float FRICTION_CONSTANT_X = 0.0f; //default friction
float GRAVITY_CONSTANT_Y = 0.001f; //default gravity

class ball {
public:
    float r, g, b, x, y, vx, vy, w;
    ball* prev_contact;
    ball();
};

void set_friction(float);
void set_gravity(float);

void move_ball(ball*);
void change_velocity(ball*);
void change_direction(ball*, char);
char touch(ball*, ball*);
char touch_wall(ball*, float, float, float, float);

float get_new_weight(void);
ball get_new_ball(void);
