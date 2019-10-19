#include "ball.h"
#import <vector>
#import <thread>

using std::thread;

/*
 DECLARE GLOBAL VARS
 */
int nb_balls = 5; //rand()%7 + 3;
ball* balls[5];
int quadrant_x[] = {-3, -2, -1, 0, 1, 2, 3};
int quadrant_y[] = {-3, -2, -1, 0, 1, 2, 3};

// ball obj constructor;
ball::ball() {
    // select quadrant to prevent starting overlap as much as possible
    int qx = 8;
    int qy = 8;
    while (qx == 8) {
        int k = rand()%6;
        qx = quadrant_x[k];
        quadrant_x[k] = 8;
    }
    while (qy == 8) {
        int k = rand()%6;
        qy = quadrant_y[k];
        quadrant_y[k] = 8;
    }
    // select x,y
    x = ((float)(200.0f)*(float)qx)/1000.0f;
    y = (float)(rand()%1400+1-700)/1000.0f;
    // select colour
    int i = rand()%3 + 1;
    if (i == 1) {
        r = 0.0f;
        g = 0.0f;
        b = 1.0f;
    }
    else if (i == 2) {
        r = 0.0f;
        g = 1.0f;
        b = 0.0f;
    }
    else {
        r = 1.0f;
        g = 0.0f;
        b = 0.0f;
    }
    
    vx = (float)(rand()%20+1-10)/5000.0f;
    vy = (float)(rand()%20+1-10)/5000.0f;
    
    w = (float)(rand()%3 + 1)*50.0f/1000.0f;
};

// moves ball's position based on its velocity
void move_ball(ball* b) {
    b->x = b->x + b->vx;
    b->y = b->y + b->vy;
}

// change velocity by the gravitational constant
void change_velocity(ball* b) {
    //change vx
    if (fabs(b->vx) < FRICTION_CONSTANT_X) {
        b->vx = 0;
    }
    else if (b->vx > FRICTION_CONSTANT_X) {
        b->vx = b->vx - FRICTION_CONSTANT_X;
    }
    else if (b->vx < 0 - FRICTION_CONSTANT_X) {
        b->vx = b->vx + FRICTION_CONSTANT_X;
    }
    //change vy
    b->vy = (b->vy <= 0.001f) && (b->y - b->w <= -0.999f) ? 0 : b->vy - GRAVITY_CONSTANT_Y;
}

// change direction
void change_direction(ball* b, char direction) {
    if (direction == 'l' || direction == 'r') {
        b->vx = 0 - b->vx;
    }
    else if (direction == 't' || direction == 'b') {
        b->vy = 0 - b->vy;
    }
    else {
        b->vx = 0 - b->vx;
        b->vy = 0 - b->vy;
    }
}

// returns 1 if balls are touching else 0
char touch(ball* b1, ball* b2) {
    char result;
    double x_diff = pow((double) b1->x - (double) b2->x, 2);
    double y_diff = pow((double) b1->y - (double) b2->y, 2);
    double dist = sqrt(x_diff + y_diff);
    result = (dist - (b1->w + b2->w)) < -0.0006f ? 'y' : 'n';
    return result;
}

// returns 1 if ball touches wall else 0
char touch_wall(ball* b1, float minx, float maxx, float miny, float maxy) { 
    if (b1->x - b1->w <= minx) { return 'l'; } //left wall
    else if (b1->x + b1->w >= maxx) { return 'r'; } //right wall
    else if (b1->y - b1->w <= miny) { return 'b'; } //bottom wall
    else if (b1->y + b1->w >= maxy) { return 't'; } //top wall
    else { return '0'; } //not touching any walls
}

//
void draw_ball(ball* b) {
    float x = b->x;
    float y = b->y;
    float r = b->w;
    glColor4f(b->r, b->g, b->b, 0.7f);
    glBegin(GL_TRIANGLES);
    int nb_vertices = 32;
    for (int i=0; i<nb_vertices; i++) {
        float theta = 2.0f*3.14159 / (float)nb_vertices;
        glVertex2f(x, y);
        glVertex2f(x+(r*sinf(theta*i)), y+(r*cosf(theta*i)));
        glVertex2f(x+(r*sinf(theta*(i+1))), y+(r*cosf(theta*(i+1))));
    }
    glEnd();
}

// define time between each refresh
void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(33, timer, 0);
}

void change_step(ball* b) {
    char a = touch_wall(b, -1.0f, 1.0f, -1.0f, 1.0f);
    for (int j=0; j<nb_balls; j++) {
        if (b!=balls[j]) {
            char touched = touch(b, balls[j]);
            if (touched == 'n') {
                change_direction(b, touched);
            }
        }
    }
    if (a!='0') {
        change_direction(b, a);
    }
    change_velocity(b);
}

void display()
{
    thread thread_ids[nb_balls];
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    for (int i=0; i<nb_balls; i++) {
        thread_ids[i] = thread(change_step, balls[i]);
    }
    for (int i=0; i<nb_balls; i++) {
        draw_ball(balls[i]);
    }
    for (int i=0; i<nb_balls; i++) {
        thread_ids[i].join();
        thread_ids[i] = thread(move_ball, balls[i]);
    }
    for (int i=0; i<nb_balls; i++) {
        thread_ids[i].join();
    }
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    srand((unsigned) time(NULL));
    for (int i=0; i<nb_balls; i++) {
        balls[i] = new ball();
        printf("ball%d completed\n", i);
    }
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("comp426_a1: watch me bounce my balls");
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
