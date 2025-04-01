#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>
#include <GL/glut.h>

using namespace std;

// Window dimensions
const int WIDTH = 640;
const int HEIGHT = 480;
GLuint texture;

GLuint LoadTexture(const char *filename)
{
    SDL_Surface *image = IMG_Load(filename);
    if (!image)
    {
        cerr << "Error cargando imagen: " << IMG_GetError() << endl;
        return 0;
    }

    GLuint textureID;
    glGenTextures(1, &textureID);
    glBindTexture(GL_TEXTURE_2D, textureID);

    // Configurar formato de la imagen
    GLenum format = (image->format->BytesPerPixel == 4) ? GL_RGBA : GL_RGB;

    glTexImage2D(GL_TEXTURE_2D, 0, format, image->w, image->h, 0, format, GL_UNSIGNED_BYTE, image->pixels);

    // Configurar los parámetros de la textura
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

    SDL_FreeSurface(image); // Liberar memoria
    return textureID;
}

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

int main(int argc, char *argv[])
{
    if (SDL_Init(SDL_INIT_VIDEO) != 0)
    {
        cerr << "No se pudo iniciar SDL: " << SDL_GetError() << endl;
        return 1;
    }

    if (IMG_Init(IMG_INIT_PNG) == 0)
    {
        cerr << "No se pudo iniciar SDL_image: " << IMG_GetError() << endl;
        SDL_Quit();
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

    float color = 0.3f;
    glClearColor(color, color, color, 1.0f);

    gluPerspective(30.0f, (float)WIDTH / (float)HEIGHT, 0.1f, 100.0f);
    glEnable(GL_DEPTH_TEST);
    glMatrixMode(GL_MODELVIEW);

    texture = LoadTexture("opengl.png");

    bool fin = false;
    bool rotate = false;
    bool fullscreen = false;

    SDL_Event evento;

    float x, y, z;

    x = 0.0f;
    y = 0.0f;
    z = 5.0f;

    float degrees = 0.0f;
    float scale = 1.0f;

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
        glColor3f(0.0, 1.0, 0.0);
        glVertex3f(-1.5, 1., -6.);
        glVertex3f(-2.5, -1., -6.);
        glVertex3f(-0.5, -1., -6.);
        glEnd();

        glEnable(GL_TEXTURE_2D);
        glBindTexture(GL_TEXTURE_2D, texture);

        glBegin(GL_QUADS);

        glColor3f(1.0, 1.0, 1.0);
        glTexCoord2f(501. / 512., 263. / 512.);
        glVertex3f(scale * 452 / 512, -scale * 212 / 512, 0.05);
        glTexCoord2f(49. / 512., 263. / 512.);
        glVertex3f(-scale * 452 / 512, -scale * 212 / 512, 0.05);
        glTexCoord2f(49. / 512., 51. / 512.);
        glVertex3f(-scale * 452 / 512, scale * 212 / 512, 0.05);
        glTexCoord2f(501. / 512., 51. / 512.);
        glVertex3f(scale * 452 / 512, scale * 212 / 512, 0.05);

        glEnd();

        glDisable(GL_TEXTURE_2D);

        glBegin(GL_TRIANGLES);
        glColor3f(0.0, 1.0, 0.0);
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
