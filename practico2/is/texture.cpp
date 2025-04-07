#include "texture.h"
#include <iostream>
#include <SDL2/SDL.h>
#include <SDL2/SDL_opengl.h>
#include <SDL2/SDL_image.h>

using namespace std;

GLuint loadTexture(const char *filename)
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