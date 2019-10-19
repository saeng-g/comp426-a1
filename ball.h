#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// OpenGL related libraries
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <OpenGL/OpenGL.h>
#include <GL/freeglut.h>

// TBB related libraries
#include "tbb/parallel_for.h"
#include "tbb/blocked_range.h"
#include "tbb/task_scheduler_init.h"

float const FRICTION_CONSTANT_X = 0.0f; //default friction
float const GRAVITY_CONSTANT_Y = 0.001f; //default gravity

class ball {
public:
    float r, g, b, x, y, vx, vy, w;
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


//TBB task class
class for_loop_move {
    ball* balls;
public:
    // constructor copies the arguments into local storage
    for_loop_move(ball*);
    // overload () so it does a vector multiply
    void operator() (const blocked_range<size_t> &r) const {
        for (size_t i = r.begin(); i != r.end(); i++)
        {
            ball* a[
        }
    }
}
