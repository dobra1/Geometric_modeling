#define _CRT_SECURE_NO_WARNINGS
#include <GL/glew.h>
#include <SDL3/SDL.h>
#include <stdio.h>
#include <cmath>

void haromszogRajz(float A[2], float B[2], float C[2]) {
    glBegin(GL_LINE_LOOP);
    glVertex2f(A[0], A[1]);
    glVertex2f(B[0], B[1]);
    glVertex2f(C[0], C[1]);
    glEnd();
}


int main(int argc, char* argv[])
{

    SDL_Window* window;
    SDL_GLContext gl_context;
    int error_code;
    int width = 800;
    int height = 600;

    /*ox, oy: a forgatás középpontja*/
    float ox = 420;
    float oy = 310;
    // R: forgatás szöge
    float R = -90;
    // tx, ty: eltolás mértéke
    float tx = 0;
    float ty = 0;
    // s: növelés szorzója
    float s = 1;

    printf("Adja meg a forgatás középpontjának x koordinátáját! ");
    scanf("%f", &ox);
    printf("Adja meg a forgatás középpontjának y koordinátáját! ");
    scanf("%f", &oy);
    printf("Adja meg a forgatás szögét fokokban! ");
    scanf("%f", &R);
    printf("Adja meg, hányszorosára nagyítsuk a háromszögeket! ");
    scanf("%f", &s);
    printf("Adja meg az eltolás x koordinátáját! ");
    scanf("%f", &tx);
    printf("Adja meg az eltolás y koordinátáját! ");
    scanf("%f", &ty);

    SDL_WindowFlags flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;
    window = SDL_CreateWindow("An SDL3 window", 640,480,SDL_WINDOW_OPENGL
    );

    SDL_Window* SDL_CreateWindow(const char* title, int w, int h, Uint32 flags);

    if (window == NULL) {
        printf("[ERROR] Unable to create the application window!\n");
    }

    gl_context = SDL_GL_CreateContext(window);
    if (gl_context == NULL) {
        printf("[ERROR] Unable to create the OpenGL context!\n");
    }

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -200, 200);
    glViewport(0, 0, width, height);

    float A[] = { 390, 300 };
    float B[] = { 450, 300 };
    float C[] = { 420, 320 };

    /* Az első háromszög kirajzolása:
     * Eltoljuk a megadott pontba, megnöveljük
     * x és y mentén kétszeresre, visszahúzzuk
     * az eredeti helyére.
    */
    glPushMatrix();
    glTranslatef(ox, oy, 0);
    glScalef(s, s, 0);
    glTranslatef(-ox, -oy, 0);
    haromszogRajz(A, B, C);
    glPopMatrix();

    /*
     * Második háromszög kirajzolása.
     * Eltoljuk a megadott pontba, annak
     * a középpontja szerint elforgatjuk
     * a megadott R szöggel a z tengely körül
     * ezután megnöveljük kétszeresére, majd
     * a koordinátarendszert visszahúzzuk
     * az eredeti helyre, majd úgy egyben
     * eltoljuk a 100;100 pontba.
    */
    glPushMatrix();
    glTranslatef(ox, oy, 0);
    glRotatef(R, 0, 0, 1);
    glScalef(s, s, 0);
    glTranslatef(-ox, -oy, 0);
    glTranslatef(tx, ty, 0);

    glColor3f(1, 0, 1);
    haromszogRajz(A, B, C);
    glPopMatrix();

    glFlush();
    SDL_GL_SwapWindow(window);

    system("PAUSE");
    // Takarítás
    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
