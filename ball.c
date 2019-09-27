#include "ball.h"

// set friction and gravity to user defined values
void set_friction(float f) {
    FRICTION_CONSTANT_X = f;
}
void set_gravity(float g) {
    GRAVITY_CONSTANT_Y = g;
}

// moves ball's position based on its velocity
void move(ball* b) {
    b->p.x = b->p.x + b->v.vx;
    b->p.y = b->p.y + b->v.vy;
}

// change velocity by the gravitational constant
void change_velocity(ball* b) {
    //change vx
    if (fabs(b->v.vx) < FRICTION_CONSTANT_X) {
        b->v.vx = 0;
    }
    else if (b->v.vx > FRICTION_CONSTANT_X) {
        b->v.vx = b->v.vx - FRICTION_CONSTANT_X;
    }
    else if (b->v.vx < 0 - FRICTION_CONSTANT_X) {
        b->v.vx = b->v.vx + FRICTION_CONSTANT_X;
    }
    //change vy
    b->v.vy = b->v.vy == 0 ? 0 : b->v.vy + GRAVITY_CONSTANT_Y;
}

void change_direction(ball* b) {
    b->v.vx = 0 - b->v.vx;
    b->v.vy = 0 - b->v.vy;
}

// returns 1 if balls are touching else 0
int touch(ball* b1, ball* b2) {
    double x_diff = pow((double) b1->p.x, 2);
    double y_diff = pow((double) b1->p.y, 2);
    double dist = sqrt(x_diff + y_diff);
    return ((int)dist <= (b1->w + b2->w));
}

// returns 1 if ball touches wall else 0
int touch_wall(ball* b1, float minx, float maxx, float miny, float maxy) {
    int cond_x = (b1->p.x - b1->w <= minx) && (b1->p.x + b1->w >= maxx);
    int cond_y = (b1->p.y - b1->w <= miny) && (b1->p.y + b1->w >= maxy);
    return cond_x && cond_y;
}

point get_new_point() {
    point p = {(float)(rand()%500+1), (float)(rand()%500+1)};
    return p;
}

color get_new_color() {
    int i = rand()%3 + 1;
    if (i == 1) {
        color c = {0.0f, 0.0f, 255.0f};
        return c;
    }
    else if (i == 2) {
        color c = {0.0f, 255.0f, 0.0f};
        return c;
    }
    else {
        color c = {2.55f, 0.0f, 0.0f};
        return c;
    }
}

velocity get_new_velocity() {
    velocity v = {(float)(rand()%10+1), (float)(rand()%10+1)};
    return v;
}

float get_new_weight() {
    int i = rand()%3 + 1;
    return (float)i*50.0f;
}

ball get_new_ball() {
    ball b = {get_new_point(), get_new_color(), get_new_velocity(), get_new_weight()};
    return b;
}

int main() {
    time_t t;
    srand((unsigned) time(&t));

    int nb_balls = rand()%7 + 3;
    printf("nb of balls generated: %d\n", nb_balls);
    ball* balls = (ball*) malloc(nb_balls * sizeof(ball));
    for (int i=0; i<nb_balls; i++) {
        *(balls + i) = get_new_ball();
    }

    for (int i =0; i<nb_balls; i++) {
        printf("ball%d : p.x=%f, p.y=%f\n", i, (balls + i)->p.x, (balls + i)->p.y);
    }
    return 0;
}