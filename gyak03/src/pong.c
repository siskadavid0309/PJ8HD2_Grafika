#include "pong.h"
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>


void init_pong(Pong* pong, int width, int height)
{
    pong->width = width;
    pong->height = height;
    init_pad(&(pong->left_pad), 0, height, RED_THEME);
    init_pad(&(pong->right_pad), width - 50, height, GREEN_THEME);
    init_ball(&(pong->ball), width / 2, height / 2);
}
/*
void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
    update_ball(&(pong->ball), time);
    int mouse_x, mouse_y;
    Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
    if (buttons & SDL_BUTTON_LEFT) {
        init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
    }
    bounce_ball(pong);
}
*/
void update_pong(Pong* pong, double time)
{
    update_pad(&(pong->left_pad), time);
    update_pad(&(pong->right_pad), time);
	int mouse_x, mouse_y;
    Uint32 buttons = SDL_GetMouseState(&mouse_x, &mouse_y);
    if (buttons & SDL_BUTTON_LEFT) {
        init_ball(&(pong->ball), pong->width / 2, pong->height / 2);
    }

    // check for key presses
    const Uint8* state = SDL_GetKeyboardState(NULL);
    if (state[SDL_SCANCODE_KP_PLUS] || state[SDL_SCANCODE_EQUALS]) {
        // increase ball radius
        if (pong->ball.radius < pong->right_pad.height && pong->ball.radius < pong->width / 2 - 50) {
            pong->ball.radius++;
            if (pong->ball.x - pong->ball.radius < 50) {
                pong->ball.x = 50 + pong->ball.radius;
            } else if (pong->ball.x + pong->ball.radius > pong->width - 50) {
                pong->ball.x = pong->width - 50 - pong->ball.radius;
            }
            if (pong->ball.y - pong->ball.radius < 0) {
                pong->ball.y = pong->ball.radius;
            } else if (pong->ball.y + pong->ball.radius > pong->height) {
                pong->ball.y = pong->height - pong->ball.radius;
            }
        }
    }
    if (state[SDL_SCANCODE_KP_MINUS] || state[SDL_SCANCODE_MINUS]) {
        // decrease ball radius
        if (pong->ball.radius > 10) {
            pong->ball.radius--;
            if (pong->ball.x - pong->ball.radius < 50) {
                pong->ball.x = 50 + pong->ball.radius;
            } else if (pong->ball.x + pong->ball.radius > pong->width - 50) {
                pong->ball.x = pong->width - 50 - pong->ball.radius;
            }
            if (pong->ball.y - pong->ball.radius < 0) {
                pong->ball.y = pong->ball.radius;
            } else if (pong->ball.y + pong->ball.radius > pong->height) {
                pong->ball.y = pong->height - pong->ball.radius;
            }
        }
    }

    update_ball(&(pong->ball), time);
    bounce_ball(pong);
}




void render_pong(Pong* pong)
{
    render_pad(&(pong->left_pad));
    render_pad(&(pong->right_pad));
    render_ball(&(pong->ball));
}

void set_left_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->left_pad), position);
}

void set_left_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->left_pad), speed);
}

void set_right_pad_position(Pong* pong, float position)
{
    set_pad_position(&(pong->right_pad), position);
}

void set_right_pad_speed(Pong* pong, float speed)
{
    set_pad_speed(&(pong->right_pad), speed);
}

void bounce_ball(Pong* pong)
{
    if (pong->ball.x - pong->ball.radius < 50) {
        if (pong->ball.y > pong->left_pad.y && pong->ball.y < pong->left_pad.y + pong->left_pad.height) {
            pong->ball.x = pong->ball.radius + 50;
            pong->ball.speed_x *= -1;
        }
    }
    if (pong->ball.x + pong->ball.radius > pong->width - 50) {
        if (pong->ball.y > pong->right_pad.y && pong->ball.y < pong->right_pad.y + pong->right_pad.height) {
            pong->ball.x = pong->width - pong->ball.radius - 50;
            pong->ball.speed_x *= -1;
        }
    }
    if (pong->ball.y - pong->ball.radius < 0) {
        pong->ball.y = pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
    if (pong->ball.y + pong->ball.radius > pong->height) {
        pong->ball.y = pong->height - pong->ball.radius;
        pong->ball.speed_y *= -1;
    }
}
