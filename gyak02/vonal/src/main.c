#include <GL/gl.h>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <stdbool.h>
#include <stdio.h>

#define MAX_VONALAK 1000 // Maximális számú vonal

int main(int argc, char* argv[]) {
    // Inicializáljuk az SDL-t
    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        fprintf(stderr, "SDL hiba: %s\n", SDL_GetError());
        return 1;
    }
    
    // Ablak létrehozása
    SDL_Window* ablak = SDL_CreateWindow("OpenGL vonalrajzoló",
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
    
    // Vonalak tárolása
    int vonalak[MAX_VONALAK][4]; // [kezdo_x, kezdo_y, veg_x, veg_y]
    int vonal_db = 0; // Aktuális vonalak száma
    GLfloat vonal_szin[] = { 1.0, 1.0, 1.0 }; // Alapértelmezett vonalszín
    
    // Vonal rajzolása
    SDL_GL_SwapWindow(ablak);
    bool fut = true;
    bool vonal_kijelolve = false;
    int vonal_kezdo_pont[2], vonal_veg_pont[2];
    while (fut) {
        SDL_Event esemeny;
        while (SDL_PollEvent(&esemeny)) {
            switch (esemeny.type) {
                case SDL_QUIT:
                    fut = false;
                    break;
                case SDL_MOUSEBUTTONDOWN:
                    if (esemeny.button.button == SDL_BUTTON_LEFT && !vonal_kijelolve) {
                        vonal_kezdo_pont[0] = esemeny.button.x;
                        vonal_kezdo_pont[1] = esemeny.button.y;
                        vonal_kijelolve = true;
                    } else if (esemeny.button.button == SDL_BUTTON_RIGHT) {
                        // Jobb egérgombbal a vonalszín beállítása
                        vonal_szin[0] = (GLfloat)rand()/(GLfloat)RAND_MAX;
                        vonal_szin[1] = (GLfloat)rand()/(GLfloat)RAND_MAX;
                        vonal_szin[2] = (GLfloat)rand()/(GLfloat)RAND_MAX;
                    }
                    break;
                case SDL_MOUSEBUTTONUP:
                    if (esemeny.button.button == SDL_BUTTON_LEFT && vonal_kijelolve) {
                        vonal_veg_pont[0] = esemeny.button.x;
                        vonal_veg_pont[1] = esemeny.button.y;
                        vonalak[vonal_db][0] = vonal_kezdo_pont[0];
                        vonalak[vonal_db][1] = vonal_kezdo_pont[1];
                        vonalak[vonal_db][2] = vonal_veg_pont[0];
                        vonalak[vonal_db][3] = vonal_veg_pont[1];
                        vonal_db++;
                        vonal_kijelolve = false;
                    }
                    break;
            }
        }
        
        // OpenGL rajzolás
        glClear(GL_COLOR_BUFFER_BIT);
        
        // Korábbi vonalak kirajzolása
        glColor3f(vonal_szin[0], vonal_szin[1], vonal_szin[2]);
        for (int i = 0; i < vonal_db; i++) {
            glBegin(GL_LINES);
            glVertex2i(vonalak[i][0], vonalak[i][1]);
            glVertex2i(vonalak[i][2], vonalak[i][3]);
            glEnd();
        }
        
        // Aktuális vonal kirajzolása
        if (vonal_kijelolve) {
            glColor3f(1.0, 0.0, 0.0);
            glBegin(GL_LINES);
            glVertex2i(vonal_kezdo_pont[0], vonal_kezdo_pont[1]);
            glVertex2i(vonal_veg_pont[0], vonal_veg_pont[1]);
            glEnd();
        }
        
        SDL_GL_SwapWindow(ablak);
    }
    
    // Kilépés
    SDL_GL_DeleteContext(gl_kontextus);
    SDL_DestroyWindow(ablak);
    SDL_Quit();
    return 0;
}
