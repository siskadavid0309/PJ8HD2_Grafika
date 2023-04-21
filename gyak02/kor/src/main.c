#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define MAX_CIRCLE_COUNT 1000 // Maximális számú kör
#define CIRCLE_RADIUS 30.0f // Kör sugara
#define MARKER_SIZE 10.0f // Jelölő mérete

// Az RGB színeket leképező struktúra
typedef struct {
    GLfloat r, g, b;
} Color;

// A köröket leíró struktúra
typedef struct {
    GLfloat x, y; // középpont koordinátái
    Color color; // szín
    bool marked; // jelölés
} Circle;

int main(int argc, char* argv[]) {
    // Inicializáljuk az SDL-t
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return 1;
    }
    
    // Ablak létrehozása
    SDL_Window* ablak = SDL_CreateWindow("SDL Körök",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         800, 600,
                                         SDL_WINDOW_OPENGL);
    if (ablak == NULL) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }
    
    // OpenGL kontextus létrehozása
    SDL_GLContext gl_kontextus = SDL_GL_CreateContext(ablak);
    if (gl_kontextus == NULL) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        SDL_DestroyWindow(ablak);
        SDL_Quit();
        return 1;
    }
    
    // OpenGL inicializálása
    glClearColor(0.0, 0.0, 0.0, 0.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, 800, 600, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // Változók inicializálása
    Circle circles[MAX_CIRCLE_COUNT];
    int circleCount = 0;
    bool drawMarker = false;
    int selectedCircleIndices[MAX_CIRCLE_COUNT];
    int selectedCircleCount = 0;
    int moveCircleIndex = -1;
    GLfloat cursorX = 0.0f, cursorY = 0.0f;
    
    // Fő ciklus
    bool running = true;
    while (running) {
        // Események kezelése
        SDL_Event event;
        while (SDL_PollEvent(&event)) {
            switch (event.type) {
                case SDL_QUIT:
                    running = false;
                    break;
                case SDL_KEYDOWN:
                    if (event.key.keysym.sym == SDLK_ESCAPE) {
                        running = false;
                        break;
                    }
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    // Kattintás pozíciója
                    cursorX = event.button.x;
                    cursorY = event.button.y;
                    if (event.button.button == SDL_BUTTON_LEFT) {
                        // Új kör hozzáadása
                        if (circleCount < MAX_CIRCLE_COUNT) {
                            Circle newCircle = {cursorX, cursorY, {1.0f, 0.0f, 0.0f}, false};
circles[circleCount++] = newCircle;
}
} else if (event.button.button == SDL_BUTTON_RIGHT) {
// Kör kijelölése
selectedCircleCount = 0;
for (int i = 0; i < circleCount; i++) {
Circle* circle = &circles[i];
GLfloat dx = circle->x - cursorX;
GLfloat dy = circle->y - cursorY;
GLfloat distance = sqrtf(dx * dx + dy * dy);
if (distance <= CIRCLE_RADIUS) {
selectedCircleIndices[selectedCircleCount++] = i;
circle->marked = true;
}
}
}
break;
case SDL_MOUSEBUTTONUP:
if (event.button.button == SDL_BUTTON_RIGHT) {
// Jelölések eltávolítása
for (int i = 0; i < circleCount; i++) {
circles[i].marked = false;
}
}
break;
case SDL_MOUSEMOTION:
// Kurzor pozíciója
cursorX = event.motion.x;
cursorY = event.motion.y;
// Jelölések mozgatása
for (int i = 0; i < selectedCircleCount; i++) {
Circle* circle = &circles[selectedCircleIndices[i]];
circle->x += event.motion.xrel;
circle->y += event.motion.yrel;
}
break;
}
}
    // Kirajzolás
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < circleCount; i++) {
        Circle* circle = &circles[i];
        glLoadIdentity();
        glTranslatef(circle->x, circle->y, 0.0f);
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(circle->color.r, circle->color.g, circle->color.b);
        glVertex2f(0.0f, 0.0f);
        for (int j = 0; j <= 20; j++) {
            float angle = j * 2.0f * M_PI / 20.0f;
            float x = cosf(angle) * CIRCLE_RADIUS;
            float y = sinf(angle) * CIRCLE_RADIUS;
            glVertex2f(x, y);
        }
        glEnd();
        if (circle->marked) {
            glLoadIdentity();
            glTranslatef(circle->x - MARKER_SIZE / 2, circle->y - MARKER_SIZE / 2, 0.0f);
            glBegin(GL_LINES);
            glColor3f(1.0f, 1.0f, 1.0f);
            glVertex2f(0.0f, 0.0f);
            glVertex2f(MARKER_SIZE, MARKER_SIZE);
            glVertex2f(0.0f, MARKER_SIZE);
            glVertex2f(MARKER_SIZE, 0.0f);
            glEnd();
        }
    }
    SDL_GL_SwapWindow(ablak);
}

// Kilépés
SDL_GL_DeleteContext(gl_kontextus);
SDL_DestroyWindow(ablak);
SDL_Quit();
return 0;
}