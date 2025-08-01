#define RGFW_DEBUG
#define RGFW_IMPLEMENTATION
#define RGFW_EGL
#include "RGFW.h"

#include <stdio.h>

void keyfunc(RGFW_window* win, RGFW_key key, u8 keyChar, RGFW_keymod keyMod, RGFW_bool pressed) {
    RGFW_UNUSED(keyMod); RGFW_UNUSED(keyChar); RGFW_UNUSED(win);
    if (key == RGFW_escape && pressed) {
        RGFW_window_setShouldClose(win, 1);
    }
}

int main(void) {
    RGFW_window* win = RGFW_createWindow("a window", RGFW_RECT(0, 0, 800, 600), RGFW_windowUseEGL | RGFW_windowCenter | RGFW_windowNoResize | RGFW_windowTransparent);

    RGFW_setKeyCallback(keyfunc); // you can use callbacks like this if you want

    while (RGFW_window_shouldClose(win) == RGFW_FALSE) {
        RGFW_event event;
        while (RGFW_window_checkEvent(win, &event)) {  // or RGFW_window_checkEvents(); if you only want callbacks
            // you can either check the current event yourself
            if (event.type == RGFW_quit) break;

            if (event.type == RGFW_mouseButtonPressed && event.button == RGFW_mouseLeft) {
                printf("You clicked at x: %d, y: %d\n", event.point.x, event.point.y);
            }

            if (RGFW_isMousePressed(win, RGFW_mouseRight)) {
                printf("The right mouse button was clicked at x: %d, y: %d\n", event.point.x, event.point.y);
            }
        }

        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        glBegin(GL_TRIANGLES);
        glColor3f(1.0f, 0.0f, 0.0f); glVertex2f(-0.6f, -0.75f);
        glColor3f(0.0f, 1.0f, 0.0f); glVertex2f(0.6f, -0.75f);
        glColor3f(0.0f, 0.0f, 1.0f); glVertex2f(0.0f, 0.75f);
        glEnd();

        RGFW_window_swapBuffers_EGL(win);
    }

    RGFW_window_close(win);
    return 0;
}
