#include "ball.h"

// set friction and gravity to user defined values
void set_friction(float f) {
    FRICTION_CONSTANT_X = f;
}
void set_gravity(float g) {
    GRAVITY_CONSTANT_Y = g;
}

// moves ball's position based on its velocity
void move_ball(ball* b) {
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
    b->v.vy = (b->v.vy <= 0.001f) && (b->p.y - b->w <= -0.999f) ? 0 : b->v.vy - GRAVITY_CONSTANT_Y;
}

void change_direction(ball* b) {
    b->v.vx = 0 - b->v.vx;
    b->v.vy = 0 - b->v.vy;
}

// returns 1 if balls are touching else 0
int touch(ball* b1, ball* b2) {
    double x_diff = pow((double) b1->p.x - (double) b2->p.x, 2);
    double y_diff = pow((double) b1->p.y - (double) b2->p.y, 2);
    double dist = sqrt(x_diff + y_diff);
    return ((int)dist <= (b1->w + b2->w));
}

// returns 1 if ball touches wall else 0
char touch_wall(ball* b1, float minx, float maxx, float miny, float maxy) {
    if (b1->p.x - b1->w <= minx) { return 'l'; } //left wall
    else if (b1->p.x + b1->w >= maxx) { return 'r'; } //right wall
    else if (b1->p.y - b1->w <= miny) { return 'b'; } //bottom wall
    else if (b1->p.y + b1->w >= maxy) { return 't'; } //top wall
    else { return '0'; } //not touching any walls
}

// ball generation
point get_new_point() {
    point p = {(float)(rand()%1000+1-500)/1000.0f, (float)(rand()%1000+1-500)/1000.0f};
    return p;
}
color get_new_color() {
    int i = rand()%3 + 1;
    if (i == 1) {
        color c = {0.0f, 0.0f, 1.0f};
        return c;
    }
    else if (i == 2) {
        color c = {0.0f, 1.0f, 0.0f};
        return c;
    }
    else {
        color c = {1.0f, 0.0f, 0.0f};
        return c;
    }
}
velocity get_new_velocity() {
    velocity v = {(float)(rand()%40+1-20)/1000.0f, (float)(rand()%40+1-20)/1000.0f};
    return v;
}
float get_new_weight() {
    int i = rand()%3 + 1;
    return (float)i*50.0f/1000.0f;
}
ball get_new_ball() {
    ball b = {get_new_point(), get_new_color(), get_new_velocity(), get_new_weight()};
    return b;
}

int nb_balls = 5; //rand()%7 + 3;
ball* balls = (ball*) malloc(nb_balls * sizeof(ball));

void draw_ball(ball* b) {
    float x = b->p.x;
    float y = b->p.y;
    float r = b->w;
    glColor4f(b->c.r, b->c.g, b->c.b, 0.7f);
    glBegin(GL_TRIANGLES);
    printf("%f,%f,%f\n", x, y, r);
    int nb_vertices = 32;
    for (int i=0; i<nb_vertices; i++) {
        float theta = 2.0f*3.14159 / (float)nb_vertices;
        glVertex2f(x, y);
        glVertex2f(x+(r*sinf(theta*i)), y+(r*cosf(theta*i)));
        glVertex2f(x+(r*sinf(theta*(i+1))), y+(r*cosf(theta*(i+1))));
    }
    glEnd();
}

void timer(int value) {
    glutPostRedisplay();
    glutTimerFunc(30, timer, 0);
}

void display()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glClearColor(1, 1, 1, 1);
    glEnable(GL_BLEND);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    printf("hi");
    for (int i=0; i<nb_balls; i++) {
        printf("%f,%f,%f\n", (balls+i)->p.x, (balls+i)->p.y, (balls+i)->w);
        draw_ball(balls+i);
    }
    for (int i=0; i<nb_balls; i++) {
        move_ball(balls+i);
        printf("ball moved%d\n", i);
    }
    for (int i=0; i<nb_balls; i++) {
        char a = touch_wall(balls+i, -1.0f, 1.0f, -1.0f, 1.0f);
        for (int j=i; j<nb_balls; j++) {
            if (i!=j) {
                int b = touch(balls+i, balls+j);
                printf("b is %d\n", b);
                if (b) {
                    printf("changedir");
                    change_direction(balls+i);
                }
            }
        }
        if (a!='0') {
            change_direction(balls+i);
        }
        change_velocity(balls+i);
    }
    glutSwapBuffers();
}
int main(int argc, char **argv)
{
    for (int i=0; i<nb_balls; i++) {
        *(balls + i) = get_new_ball();
        printf("ball%d completed\n", i);
    }
    srand((unsigned) time(NULL));
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_RGBA | GLUT_DOUBLE | GLUT_DEPTH);
    glutInitWindowSize(1000, 1000);
    glutCreateWindow("comp426_a1: watch me bounce my balls");
    glutDisplayFunc(display);
    glutTimerFunc(0, timer, 0);
    glutMainLoop();
    return 0;
}
