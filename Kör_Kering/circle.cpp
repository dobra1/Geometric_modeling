#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#define _USE_MATH_DEFINES
#include <cmath>



void init_opengl(int width, int height)
{
    glClearColor(0.1, 0.1, 0.1, 1.0);

    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -200, 200);
    glViewport(0, 0, width, height);
}


int main(int argc, char* argv[])
{

    SDL_Window* window;
    SDL_GLContext gl_context;
    int width = 800;
    int height = 600;
    double x = 400;
    double y = 150;
    double radius = 50;
    int error_code;

    double centerx = 400;
    double centery = 300;
    double circ_radius = 150;
    double circ_angle = M_PI / 2;
    double circ_speed = 2 * M_PI / 5;

    double current_time;
    double elapsed_time;
    double last_time = 0;

    error_code = SDL_Init(SDL_INIT_VIDEO);
    if (error_code != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
    }

    window = SDL_CreateWindow("Kering:", width, height, SDL_WINDOW_OPENGL);

    if (window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
    }

    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
    }

    init_opengl(width, height);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    while (1) {

        current_time = (double)SDL_GetTicks() / 1000;
        elapsed_time = current_time - last_time;
        last_time = current_time;

        x = centerx + cos(circ_angle) * circ_radius;
        y = centery + sin(circ_angle) * circ_radius;
        circ_angle += elapsed_time * circ_speed;


        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glPushMatrix();
        glTranslatef(x, y, 0.0);
        glBegin(GL_TRIANGLE_FAN);
        glColor3f(0.0, 1.0, 0.0);
        glVertex2f(0, 0);
        double angle = 0;
        while (angle < 2.0 * M_PI + 1) {
            x = cos(angle) * radius;
            y = sin(angle) * radius;
            glVertex2f(x, y);
            angle += (2 * M_PI) / 36;
        }
        glEnd();
        glPopMatrix();
        SDL_GL_SwapWindow(window);
    }


    printf("Press Enter to exit...\n");
    (void)getchar();


    if (gl_context != NULL) {
        SDL_GL_DestroyContext(gl_context);
    }

    if (window != NULL) {
        SDL_DestroyWindow(window);
    }

    SDL_Quit();
    return 0;
}

