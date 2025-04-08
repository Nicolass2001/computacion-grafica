#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <GL/glut.h>
#include "constants.h"

using namespace std;

void initSDL()
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        exit(1);
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        cerr << "No se pudo iniciar SDL_image: " << IMG_GetError() << endl;
        SDL_Quit();
        exit(1);
    }
}

void initOpenGL(SDL_Window *&window, SDL_GLContext &glContext)
{
    window = SDL_CreateWindow("ICG-UdelaR",
                              SDL_WINDOWPOS_CENTERED,
                              SDL_WINDOWPOS_CENTERED,
                              WIDTH, HEIGHT,
                              SDL_WINDOW_OPENGL);
    if (!window)
    {
        cerr << "Could not create window: " << SDL_GetError() << endl;
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        cerr << "Failed to create OpenGL context: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        IMG_Quit();
        SDL_Quit();
        exit(1);
    }
}

void setupMatrixPerspectiveAndBackgroundColor()
{
    glMatrixMode(GL_PROJECTION);
    float color = 0.3f;
    glClearColor(color, color, color, 1.0f);
    gluPerspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

void ResetOpenGL(int width, int height)
{
    glViewport(0, 0, width, height);
    setupMatrixPerspectiveAndBackgroundColor();
}

void changeFullscreen(SDL_Window *window, SDL_GLContext &glContext, bool &fullscreen, bool &fin)
{
    SDL_GL_DeleteContext(glContext);
    SDL_SetWindowFullscreen(window, fullscreen ? SDL_WINDOW_FULLSCREEN : 0);

    if (!fullscreen)
    {
        SDL_SetWindowSize(window, WIDTH, HEIGHT);
        SDL_SetWindowPosition(window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
    }

    glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        cerr << "Error al recrear OpenGL context: " << SDL_GetError() << endl;
        fin = true;
        return;
    }

    int w, h;
    SDL_GetWindowSize(window, &w, &h);
    ResetOpenGL(w, h);
}