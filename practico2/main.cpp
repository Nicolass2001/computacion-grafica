#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <GL/glut.h>
#include "constants.h"
#include "init.h"
#include "texture.h"
#include "lighting.h"
#include "readFile.h"

using namespace std;

void ResetOpenGL(int width, int height)
{
    glViewport(0, 0, width, height);
    glMatrixMode(GL_PROJECTION);
    float color = 0.3f;
    glClearColor(color, color, color, 1.0f);
    glLoadIdentity();
    gluPerspective(45.0f, (float)width / (float)height, 0.1f, 100.0f);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();
}

int main()
{

    initSDL();

    SDL_Window *window;
    SDL_GLContext glContext;
    initOpenGL(window, glContext);

    setupMatrixPerspectiveAndBackgroundColor();
    setupLighting();

    GLuint texture = loadTexture("opengl.png");

    SDL_Event evento;

    bool fin = false;
    bool fullscreen = false;

    bool rotate = false;

    float degrees = 0.0f;
    float scale = 1.0f;

    Uint32 last = 0;
    Uint32 now = SDL_GetTicks();
    float deltaTime;

    float rotationSpeed = 72.0f; // degrees per second

    std::string fileName = "lightPolygons.txt";
    std::vector<DataPoint> data = readFile(fileName);

    do
    {
        // SET TIME
        last = now;
        now = SDL_GetTicks();
        deltaTime = (now - last) / 1000.0f; // deltaTime in seconds

        // CLEAR BUFFER RESET MATRIX CHANGE VIEW
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(0.0, 2.0, 5.0, 0, -2, -6, 0, 1, 0);

        // ROTATE
        if (rotate)
        {
            degrees = degrees + deltaTime * rotationSpeed;
        }

        // DRAW OBJECTS

        glPushMatrix();
        glTranslatef(0.0, -2.0, -6.0);
        glRotatef(degrees, 0.0, 1.0, 0.0);
        glBegin(GL_QUADS);
        // glBegin(GL_TRIANGLES);
        for (const auto &dp : data)
        {
            if (dp.id == 'C')
                glColor3f(dp.x, dp.y, dp.z);
            else if (dp.id == 'V')
                glVertex3f(dp.x, dp.y, dp.z);
            else if (dp.id == 'N')
                glNormal3f(dp.x, dp.y, dp.z);
            else
                std::cerr << "Unknown data point id: " << dp.id << std::endl;
        }
        glEnd();
        glPopMatrix();

        glPushMatrix();
        glTranslatef(0.0, 0.0, -6.0);
        glRotatef(degrees, 0.0, 1.0, 0.0);

        glPushMatrix();
        glTranslatef(-1.5, 0.0, 0.0);
        glRotatef(degrees, 0.0, 1.0, 0.0);

        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(0, 1., 0.);
        glVertex3f(-1., -1., 0.);
        glVertex3f(1., -1., 0.);
        glEnd();

        glPopMatrix();

        glPushMatrix();
        glTranslatef(1.5, 0.0, 0.0);
        glRotatef(degrees, 0.0, 1.0, 0.0);

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);
        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(501. / 512., 263. / 512.);
        glVertex3f(scale, -scale * 212 / 452, 0.);
        glTexCoord2f(49. / 512., 263. / 512.);
        glVertex3f(-scale, -scale * 212 / 452, 0.);
        glTexCoord2f(49. / 512., 51. / 512.);
        glVertex3f(-scale, scale * 212 / 452, 0.);
        glTexCoord2f(501. / 512., 51. / 512.);
        glVertex3f(scale, scale * 212 / 452, 0.);
        glEnd();

        glDisable(GL_TEXTURE_2D);

        glPopMatrix();
        glPopMatrix();

        // glBegin(GL_TRIANGLES);
        // glColor3f(0.0, 1.0, 0.0);
        // glVertex3f(1., -1., -6.);
        // glColor3f(1.0, 0.0, 0.0);
        // glVertex3f(-1., -1., -6.);
        // glColor3f(0.0, 0.0, 1.0);
        // glVertex3f(0., 1., -6.);
        // glEnd();

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
                case SDLK_SPACE:
                    data = readFile(fileName);
                    break;
                case SDLK_ESCAPE:
                    fin = true;
                    break;
                case SDLK_RIGHT:
                    rotate = !rotate;
                    break;
                case SDLK_UP:
                    scale += 0.1f;
                    break;
                case SDLK_DOWN:
                    scale -= 0.1f;
                    break;
                case SDLK_F10:
                    fullscreen = !fullscreen;

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
                        break;
                    }

                    int w, h;
                    SDL_GetWindowSize(window, &w, &h);
                    ResetOpenGL(w, h);
                    break;
                }
            }
        }
        // FIN MANEJO DE EVENTOS
        SDL_GL_SwapWindow(window);
    } while (!fin);

    glDeleteTextures(1, &texture);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}
