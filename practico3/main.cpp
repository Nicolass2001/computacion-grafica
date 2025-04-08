#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <GL/glut.h>
#include "constants.h"
#include "init.h"

using namespace std;

void drawCube(float scale)
{
    glPushMatrix();
    glScalef(scale, scale, scale);

    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0, 1.0, -1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(1.0, -1.0, -1.0);
    glVertex3f(1.0, 1.0, -1.0);
    glVertex3f(1.0, 1.0, 1.0);
    glVertex3f(1.0, -1.0, 1.0);
    glEnd();

    glBegin(GL_QUADS);
    glVertex3f(-1.0, -1.0, -1.0);
    glVertex3f(-1.0, -1.0, 1.0);
    glVertex3f(-1.0, 1.0, 1.0);
    glVertex3f(-1.0, 1.0, -1.0);
    glEnd();

    glPopMatrix();
}

int main()
{

    initSDL();

    SDL_Window *window;
    SDL_GLContext glContext;
    initOpenGL(window, glContext);

    setupMatrixPerspectiveAndBackgroundColor();

    SDL_Event evento;

    bool fin = false;
    bool fullscreen = false;

    Uint32 last = 0;
    Uint32 now = SDL_GetTicks();
    float deltaTime = 0;

    float cameraX = 0;
    float cameraY = 0;
    float cameraZ = 0;
    float cameraAngle = 0;
    float cameraMovementSpeed = 5.0f;
    float cameraAngleSpeed = 140.0f;

    bool turningLeft = false;
    bool turningRight = false;
    bool movingForward = false;
    bool movingBackward = false;

    GLuint displayList = glGenLists(1);

    glNewList(displayList, GL_COMPILE);
    glBegin(GL_TRIANGLES);
    glVertex3f(0., -0.5, 0.5);
    glVertex3f(0., -0.5, -0.5);
    glVertex3f(0., 0.5, 0.);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0., 0.5, 0.5);
    glVertex3f(0., 0.5, -0.5);
    glVertex3f(0., 1.5, 0.);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0., 1.5, 0.5);
    glVertex3f(0., 1.5, -0.5);
    glVertex3f(0., 2.5, 0.);
    glEnd();
    glBegin(GL_TRIANGLES);
    glVertex3f(0., 2.5, 0.5);
    glVertex3f(0., 2.5, -0.5);
    glVertex3f(0., 3.5, 0.);
    glEnd();
    glEndList();

    // Inicializar instancias
    std::vector<Instance> instances;
    for (int i = 0; i < INSTANCE_COUNT; ++i)
    {
        instances.push_back({{(float)rand() / RAND_MAX * 10,
                              (float)rand() / RAND_MAX * 2,
                              (float)rand() / RAND_MAX * 10},
                             (float)rand() / RAND_MAX,
                             (float)rand() / RAND_MAX,
                             (float)rand() / RAND_MAX});
    }

    do
    {
        // SET TIME
        last = now;
        now = SDL_GetTicks();
        deltaTime = (now - last) / 1000.0f; // deltaTime in seconds

        // MANEJO DE EVENTOS
        while (SDL_PollEvent(&evento))
        {
            switch (evento.type)
            {
            case SDL_QUIT:
                fin = true;
                break;
            case SDL_KEYDOWN:
                switch (evento.key.keysym.sym)
                {
                case SDLK_RIGHT:
                    cout << "Right key pressed" << endl;
                    turningRight = true;
                    break;
                case SDLK_LEFT:
                    cout << "Left key pressed" << endl;
                    turningLeft = true;
                    break;
                case SDLK_UP:
                    cout << "Up key pressed" << endl;
                    movingForward = true;
                    break;
                case SDLK_DOWN:
                    cout << "Down key pressed" << endl;
                    movingBackward = true;
                    break;
                }
                break;
            case SDL_KEYUP:
                switch (evento.key.keysym.sym)
                {
                case SDLK_ESCAPE:
                    fin = true;
                    break;
                case SDLK_RIGHT:
                    cout << "Right key released" << endl;
                    turningRight = false;
                    break;
                case SDLK_LEFT:
                    cout << "Left key released" << endl;
                    turningLeft = false;
                    break;
                case SDLK_UP:
                    cout << "Up key released" << endl;
                    movingForward = false;
                    break;
                case SDLK_DOWN:
                    cout << "Down key released" << endl;
                    movingBackward = false;
                    break;
                case SDLK_F10:
                    fullscreen = !fullscreen;
                    changeFullscreen(window, glContext, fullscreen, fin);
                    break;
                }
            }
        }
        // FIN MANEJO DE EVENTOS

        // CLEAR BUFFER RESET MATRIX CHANGE VIEW
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glLoadIdentity();
        gluLookAt(0, 0, 0, -0.1, 0, 0, 0, 1, 0);

        if (turningLeft)
        {
            cameraAngle -= cameraAngleSpeed * deltaTime;
        }
        if (turningRight)
        {
            cameraAngle += cameraAngleSpeed * deltaTime;
        }
        if (movingForward)
        {
            cameraX += cameraMovementSpeed * deltaTime * cos(cameraAngle * M_PI / 180);
            cameraZ += cameraMovementSpeed * deltaTime * sin(cameraAngle * M_PI / 180);
        }
        if (movingBackward)
        {
            cameraX -= cameraMovementSpeed * deltaTime * cos(cameraAngle * M_PI / 180);
            cameraZ -= cameraMovementSpeed * deltaTime * sin(cameraAngle * M_PI / 180);
        }

        // SET CAMERA
        glRotatef(cameraAngle, 0, 1, 0);
        glTranslatef(cameraX, cameraY, cameraZ);
        // FIN SET CAMERA

        // DRAW OBJECTS
        glPushMatrix();
        glTranslatef(-5, 0, -5);
        for (const auto &instance : instances)
        {
            glPushMatrix();
            glTranslatef(instance.position.x, instance.position.y, instance.position.z);
            glColor3f(instance.r, instance.g, instance.b);
            glCallList(displayList);
            glPopMatrix();
        }
        glPopMatrix();

        drawCube(0.125f);

        // FIN DIBUJAR OBJETOS

        SDL_GL_SwapWindow(window);
    } while (!fin);

    glDeleteLists(displayList, 1);
    SDL_GL_DeleteContext(glContext);
    SDL_DestroyWindow(window);
    SDL_Quit();
    IMG_Quit();
    return 0;
}
