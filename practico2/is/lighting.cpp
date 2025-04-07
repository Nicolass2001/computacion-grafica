#include "lighting.h"
#include <SDL2/SDL_opengl.h>

void setupLighting()
{
    glEnable(GL_LIGHTING); // Enable lighting in general
    glEnable(GL_LIGHT0);   // Enable light #0

    // Define light position and color
    GLfloat light_pos[] = {1.0f, 1.0f, 2.0f, 1.0f};   // Positional light
    GLfloat light_color[] = {1.0f, 1.0f, 1.0f, 1.0f}; // White light

    glLightfv(GL_LIGHT0, GL_POSITION, light_pos);
    glLightfv(GL_LIGHT0, GL_DIFFUSE, light_color);
    glLightfv(GL_LIGHT0, GL_SPECULAR, light_color);

    // Optional: Define material properties
    GLfloat mat_specular[] = {1.0, 1.0, 1.0, 1.0};
    GLfloat mat_shininess[] = {50.0};

    glMaterialfv(GL_FRONT, GL_SPECULAR, mat_specular);
    glMaterialfv(GL_FRONT, GL_SHININESS, mat_shininess);

    // Enable color material to use the current color for ambient and diffuse
    glEnable(GL_COLOR_MATERIAL);
    glColorMaterial(GL_FRONT, GL_AMBIENT_AND_DIFFUSE);
}