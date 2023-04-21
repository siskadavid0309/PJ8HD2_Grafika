#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_teglalap 1000 // Maximális számú teglalap

int main(int argc, char* argv[]) {
    // Inicializáljuk az SDL-t
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return 1;
    }
    
    // Ablak létrehozása
    SDL_Window* ablak = SDL_CreateWindow("OpenGL teglalaprajzoló",
                                         SDL_WINDOWPOS_UNDEFINED,
                                         SDL_WINDOWPOS_UNDEFINED,
                                         640, 480,
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
    glOrtho(0, 640, 480, 0, -1, 1);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
    
    // teglalapok tárolása
    int teglalapok[MAX_teglalap][4]; // [bal_felső_x, bal_felső_y, jobb_alsó_x, jobb_alsó_y]
    int teglalap_db = 0; // Aktuális teglalapok száma
    GLfloat teglalap_szin[] = { 1.0, 1.0, 1.0 }; // Alapértelmezett teglalapszín
    
    // teglalap rajzolása
    SDL_GL_SwapWindow(ablak);
    bool fut = true;
    bool teglalap_kijelolve = false;
    int teglalap_kezdo_pont[2], teglalap_veg_pont[2];
    while (fut) {
        SDL_Event esemeny;
        while (SDL_PollEvent(&esemeny)) {
            switch (esemeny.type) {
                case SDL_QUIT:
                    fut = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (esemeny.button.button == SDL_BUTTON_LEFT && !teglalap_kijelolve) {
                        teglalap_kezdo_pont[0] = esemeny.button.x;
                        teglalap_kezdo_pont[1] = esemeny.button.y;
                        teglalap_kijelolve = true;
                    } else if (esemeny.button.button == SDL_BUTTON_RIGHT) {
                        // Jobb egérgombbal a teglalapszín beállítása
                    teglalap_szin[0] = (GLfloat)rand() / RAND_MAX;
                    teglalap_szin[1] = (GLfloat)rand() / RAND_MAX;
                    teglalap_szin[2] = (GLfloat)rand() / RAND_MAX;
                }
                break;
            case SDL_MOUSEBUTTONUP:
                if (esemeny.button.button == SDL_BUTTON_LEFT && teglalap_kijelolve) {
                    teglalap_veg_pont[0] = esemeny.button.x;
                    teglalap_veg_pont[1] = esemeny.button.y;
                    teglalapok[teglalap_db][0] = teglalap_kezdo_pont[0];
                    teglalapok[teglalap_db][1] = teglalap_kezdo_pont[1];
                    teglalapok[teglalap_db][2] = teglalap_veg_pont[0];
                    teglalapok[teglalap_db][3] = teglalap_veg_pont[1];
                    teglalap_db++;
                    teglalap_kijelolve = false;
                }
                break;
            case SDL_MOUSEMOTION:
                if (teglalap_kijelolve) {
                    teglalap_veg_pont[0] = esemeny.motion.x;
                    teglalap_veg_pont[1] = esemeny.motion.y;
                }
                break;
            case SDL_KEYDOWN:
                if (esemeny.key.keysym.sym == SDLK_ESCAPE) {
                    fut = false;
                }
                break;
            default:
                break;
        }
    }
    
    // teglalapok kirajzolása
    glClear(GL_COLOR_BUFFER_BIT);
    for (int i = 0; i < teglalap_db; i++) {
        glColor3f(teglalap_szin[0], teglalap_szin[1], teglalap_szin[2]);
        glBegin(GL_QUADS);
        glVertex2i(teglalapok[i][0], teglalapok[i][1]);
        glVertex2i(teglalapok[i][2], teglalapok[i][1]);
        glVertex2i(teglalapok[i][2], teglalapok[i][3]);
        glVertex2i(teglalapok[i][0], teglalapok[i][3]);
        glEnd();
    }
    SDL_GL_SwapWindow(ablak);
}

// Program vége
SDL_GL_DeleteContext(gl_kontextus);
SDL_DestroyWindow(ablak);
SDL_Quit();
return 0;
}