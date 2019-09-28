#include "ball.h"

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
