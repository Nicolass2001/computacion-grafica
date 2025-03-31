#include <iostream>
#include <SDL2/SDL.h>
#include <GL/glut.h>

using namespace std;

// Window dimensions
const int WIDTH = 640;
const int HEIGHT = 480;

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        return 1;
    }

    SDL_Window *window =
        SDL_CreateWindow("ICG-UdelaR",
                         SDL_WINDOWPOS_CENTERED,
                         SDL_WINDOWPOS_CENTERED,
                         WIDTH, HEIGHT,
                         SDL_WINDOW_OPENGL);
    if (!window)
    {
        cerr << "Could not create window: " << SDL_GetError() << endl;
        SDL_Quit();
        return 1;
    }

    SDL_GLContext glContext = SDL_GL_CreateContext(window);
    if (!glContext)
    {
        cerr << "Failed to create OpenGL context: " << SDL_GetError() << endl;
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    glMatrixMode(GL_PROJECTION);

    float color = 0.0f;
    glClearColor(color, color, color, 1.0f);

    gluPerspective(45.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    bool fin = false;
    bool rotate = false;

    SDL_Event evento;

    float x, y, z;

    x = 0.0f;
    y = 0.0f;
    z = 5.0f;

    float degrees = 0.0f;

    do
    {
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(x, y, z, 0, 0, 0, 0, 1, 0);

        if (rotate)
        {
            degrees = degrees + 0.1f;
        }
        glRotatef(degrees, 0.0, 1.0, 0.0);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0, 1.0, 1.0);
        glVertex3f(1., -1., 0.);
        glColor3f(1.0, 0.0, 0.0);
        glVertex3f(-1., -1., 0.);
        glColor3f(0.0, 0.0, 1.0);
        glVertex3f(0., 1., 0.);
        glEnd();
        // FIN DIBUJAR OBJETOS

        // MANEJO DE EVENTOS
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_MOUSEBUTTONDOWN:
                rotate = true;
                cout << "ROT\n";
                break;
            case SDL_MOUSEBUTTONUP:
                rotate = false;
                break;
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYUP:
                switch (evento.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    fin = true;
                    break;
                case SDLK_RIGHT:
                    break;
                }
            }
        }
        // FIN MANEJO DE EVENTOS
        SDL_GL_SwapWindow(window);
    } while (!fin);

    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
