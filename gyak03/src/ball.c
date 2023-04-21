#include "ball.h"
#include <GL/gl.h>
#include <math.h>

#define PI 3.14159265359

void init_ball(Ball* ball, float x, float y)
{
    ball->x = x;
    ball->y = y;
    ball->radius = 50;
    ball->speed_x = 250;
    ball->speed_y = 250;
    ball->rotation = 0;
}

void update_ball(Ball* ball, double time)
{
    // Update position
    ball->x += ball->speed_x * time;
    ball->y += ball->speed_y * time;

    // Update rotation
    double angular_speed = 1 / ball->radius;
    ball->rotation += ball->speed_x * angular_speed * time;
    if (ball->rotation > 2 * PI) {
        ball->rotation -= 2 * PI;
    } else if (ball->rotation < 0) {
        ball->rotation += 2 * PI;
    }
}

void render_ball(Ball* ball)
{
    double angle;
    double x;
    double y;

    glPushMatrix();
    glTranslatef(ball->x, ball->y, 0.0);
    glRotatef(ball->rotation * 180 / PI, 0, 0, 1);
    glBegin(GL_TRIANGLE_FAN);
    glColor3f(1.0, 0.9, 0.8);
    glVertex2f(0, 0);
    angle = 0;
    while (angle < 2.0 * PI + 1) {
        x = cos(angle) * ball->radius;
        y = sin(angle) * ball->radius;
        glVertex2f(x, y);
        angle += 0.1;
    }
    glEnd();
    glPopMatrix();
}

void handle_collision(Ball* ball, int width, int height)
{
    if (ball->x - ball->radius < 0)
{
ball->x = ball->radius;
ball->speed_x *= -1;
}
if (ball->x + ball->radius > width) {
ball->x = width - ball->radius;
ball->speed_x *= -1;
}
if (ball->y - ball->radius < 0) {
ball->y = ball->radius;
ball->speed_y *= -1;
}
if (ball->y + ball->radius > height) {
ball->y = height - ball->radius;
ball->speed_y *= -1;
}
// update rotation direction based on collision
if (ball->x - ball->radius < 0 || ball->x + ball->radius > width) {
ball->rotation += PI;
}
if (ball->y - ball->radius < 0 || ball->y + ball->radius > height) {
ball->rotation += PI;
}
// normalize rotation angle
if (ball->rotation > 2 * PI) {
ball->rotation -= 2 * PI;
} else if (ball->rotation < 0) {
ball->rotation += 2 * PI;
}
}