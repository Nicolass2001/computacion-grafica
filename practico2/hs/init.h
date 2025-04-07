#ifndef INIT_H
#define INIT_H

#include <SDL2/SDL.h>

void initSDL();
void initOpenGL(SDL_Window *&window, SDL_GLContext &glContext);
void setupMatrixPerspectiveAndBackgroundColor();

#endif // INIT_H