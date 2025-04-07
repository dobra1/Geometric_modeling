#define _CRT_SECURE_NO_WARNINGS
#define _CRT_SECURE_NO_DEPRECATE  
#define _CRT_NONSTDC_NO_DEPRECATE
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
    SDL_Window* window = nullptr;
    SDL_GLContext gl_context = nullptr;
    int width = 800;
    int height = 600;

    float ox, oy, R, tx, ty, s;

    printf("Adja meg a forgatás középpontjának x koordinátáját! ");
    scanf_s("%f", &ox);
    printf("Adja meg a forgatás középpontjának y koordinátáját! ");
    scanf_s("%f", &oy);
    printf("Adja meg a forgatás szögét fokokban! ");
    scanf_s("%f", &R);
    printf("Adja meg, hányszorosára nagyítsuk a háromszögeket! ");
    scanf_s("%f", &s);
    printf("Adja meg az eltolás x koordinátáját! ");
    scanf_s("%f", &tx);
    printf("Adja meg az eltolás y koordinátáját! ");
    scanf_s("%f", &ty);

    if (SDL_Init(SDL_INIT_VIDEO) != 0) {
        printf("[ERROR] SDL initialization error: %s\n", SDL_GetError());
        return 1;
    }

    // GL attribútumok beállítása
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION, 1);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);

    SDL_WindowFlags flags = (SDL_WindowFlags)(SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE);
    window = SDL_CreateWindow("Keringes", width, height, flags);
    if (!window) {
        printf("[ERROR] Unable to create the application window: %s\n", SDL_GetError());
        SDL_Quit();
        return 1;
    }

    gl_context = SDL_GL_CreateContext(window);
    if (!gl_context) {
        printf("[ERROR] Unable to create the OpenGL context: %s\n", SDL_GetError());
        SDL_DestroyWindow(window);
        SDL_Quit();
        return 1;
    }

    glewInit();

    glClearColor(0, 0, 0, 1);
    glMatrixMode(GL_PROJECTION);
    glClear(GL_COLOR_BUFFER_BIT);
    glLoadIdentity();
    glOrtho(0, width, height, 0, -200, 200);
    glViewport(0, 0, width, height);

    float A[] = { 390, 300 };
    float B[] = { 450, 300 };
    float C[] = { 420, 320 };

    glPushMatrix();
    glTranslatef(ox, oy, 0);
    glScalef(s, s, 0);
    glTranslatef(-ox, -oy, 0);
    glColor3f(1, 1, 1);
    haromszogRajz(A, B, C);
    glPopMatrix();

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

    printf("Press Enter to exit...\n");
    (void)getchar();



    SDL_GL_DestroyContext(gl_context);
    SDL_DestroyWindow(window);
    SDL_Quit();
    return 0;
}
